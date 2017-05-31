#pragma once
#include "icg_common.h"
#include "math.h"

class Bezier{
private:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID
    GLuint _vbo; ///< memory buffer
public:
    void bezierCoeffeicients(int len, int *coefficients){
        int k, i;
        for(k = 0; k<=len; k++){
            coefficients[k] = 1;
            for(i = len; i >= k+1; i--){
                coefficients[k] *= i;
            }
            for(i = len-k; i >= 2; i--){
                coefficients[k] /= i;
            }
        }
    }

    void init(vec3 v1, vec3 v2, vec3 v3){
        ///--- Compile the shaders
        _pid = OpenGP::load_shaders("Triangle/vshader.glsl", "Triangle/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);
        glUseProgram(_pid);

        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        ///--- Vertex Buffer
        GLfloat vpoint[300];
        //vec3 v1 = vec3(-2.0f, -1.0f, 0.0f);
        //vec3 v2 = vec3(1.0f, -1.0f, 0.0f);
        //vec3 v3 = vec3(0.0f, 1.0f, 0.0f);
        int cp[4][2] = { {-2,-1}, {1, -1}, {0,1}, {0,3} };
        int c[4], k, n =3;
        bezierCoeffeicients(n,c);
        float x, y, blend;
        float u;
        int count = 0;
        for(u = 0; u < 100; u += 1){
            x = 0;
            y = 0;
            for(k = 0; k < 4; k++){
                blend = c[k] * pow(u/100,k) * pow(1-u/100, n-k);
                x += cp[k][0] * blend;
                y += cp[k][1] * blend;
            }
            vpoint[count] = x;
            vpoint[count+1] = y;
            vpoint[count+2] = 0;
            cout << vpoint[count] << " " << vpoint[count+1] << " " << vpoint[count+2] << endl;
            count += 3;
        }

        int i;
        //for(i = 0; i < 300; i+=3) cout << vpoint[i] << endl;

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vpoint), vpoint, GL_STATIC_DRAW);

        ///--- vpoint shader attribute
        GLuint position = glGetAttribLocation(_pid, "vpoint"); ///< Fetch Attribute ID for Vertex Positions
        glEnableVertexAttribArray(position); /// Enable it
        glVertexAttribPointer(position, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void cleanup(){
        glBindVertexArray(0);
        glUseProgram(0);
        glDeleteBuffers(1, &_vbo);
        glDeleteProgram(_pid);
        glDeleteVertexArrays(1, &_vao);
    }

    void draw(float time_s){
        glUseProgram(_pid);
        glBindVertexArray(_vao);
            ///--- Set transformation uniform
            /// @see http://eigen.tuxfamily.org/dox/classEigen_1_1AngleAxis.html#details

            mat4 T = Eigen::Affine3f(Eigen::Translation3f(.5,.5,0)).matrix();
            mat4 R = Eigen::Affine3f(Eigen::AngleAxisf(M_PI/6.0 * time_s, vec3::UnitZ())).matrix();
            mat4 S = mat4::Identity();
            S(0,0) = .25;
            S(1,1) = .25;
            mat4 M = T*S*R;
            GLuint M_id = glGetUniformLocation(_pid, "M");
            glUniformMatrix4fv(M_id, 1, GL_FALSE, M.data());
            ///--- Draw
            glDrawArrays(GL_LINE_LOOP, 0, 100);
        glBindVertexArray(0);
        glUseProgram(0);
    }


};
