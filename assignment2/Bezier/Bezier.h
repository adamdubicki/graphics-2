#ifndef BEZIERH
#define BEZIERH
#include "icg_common.h"
#include "math.h"


class bezier_composite {
    public:
        virtual void init();
        virtual void draw(float time_s);
};

struct bezier_line {
    vec3 c1;
    vec3 c2;
    vec3 c3;
    vec3 c4;
};

class Bezier{
private:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID
    GLuint _vbo; ///< memory buffer
    int num_segments;
public:
    void bezierCoeffeicients(int len, float *coefficients){
        float k, i;
        for(k = 0; k<=len; k++){
            coefficients[int(k)] = 1;
            for(i = len; i >= k+1; i--){
                coefficients[int(k)] *= i;
            }
            for(i = len-k; i >= 2; i--){
                coefficients[int(k)] /= i;
            }
        }
    }

    void init(bezier_line* bp, int size){
        ///--- Compile the shaders
        _pid = OpenGP::load_shaders("Triangle/vshader.glsl", "Triangle/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);
        glUseProgram(_pid);
        num_segments = size;

        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        ///--- Vertex Buffer
        GLfloat vpoint[300*size];

        int i, count;
        float c[4], k, n = 3;
        float x, y, blend;
        float u;
        for(int i = 0; i < size; i++){
            count = i*300;
            float cp[4][2] = {
                {bp[i].c1[0], bp[i].c1[1]},
                {bp[i].c2[0], bp[i].c2[1]},
                {bp[i].c3[0], bp[i].c3[1]},
                {bp[i].c4[0], bp[i].c4[1]}
            };
            bezierCoeffeicients(n,c);
            for(u = 0; u < 100; u += 1){
                x = 0;
                y = 0;
                for(k = 0; k < 4; k++){
                    blend = c[int(k)] * pow(u/100,k) * pow(1-u/100, n-k);
                    x += cp[int(k)][0] * blend;
                    y += cp[int(k)][1] * blend;
                }
                vpoint[count] = x;
                vpoint[count+1] = y;
                vpoint[count+2] = 0;
                count += 3;
            }
        }

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

    void draw(float time_s, float rotation, float tx, float ty){
        glUseProgram(_pid);
        glBindVertexArray(_vao);
        ///--- Set transformation uniform
        /// @see http://eigen.tuxfamily.org/dox/classEigen_1_1AngleAxis.html#details

        mat4 T = Eigen::Affine3f(Eigen::Translation3f(tx,ty,0)).matrix();
        mat4 R = Eigen::Affine3f(Eigen::AngleAxisf(rotation, vec3::UnitZ())).matrix();
        mat4 S = mat4::Identity();
        S(0,0) =  0.25;
        S(1,1) =  0.25;
        mat4 M = T*S*R;
        GLuint M_id = glGetUniformLocation(_pid, "M");
        glUniformMatrix4fv(M_id, 1, GL_FALSE, M.data());
        ///--- Draw
        /// //GL_TRIANGLE_FAN
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments*100);
        glBindVertexArray(0);
        glUseProgram(0);
    }
};

class Bat {
    public:
        Bat(){
        }
        virtual void init(float speed_factor){
            struct bezier_line right_wing[5];
            right_wing[0] = {
                    vec3(+0.0f,   +0.0f, +0.0f),
                    vec3(+0.125f, +0.0f, +0.0f),
                    vec3(+0.25,   +0.0f, +0.0f),
                    vec3(+0.5f,   +1.0f, +0.0f)
              };
             right_wing[1] = {
                     vec3(+0.5f,  +1.0f, +0.0f),
                     vec3(+0.75f, +1.0f, 0.0f),
                     vec3(+1.0,   +1.0f, 0.0f),
                     vec3(+2.0f,   0.5f, 0.0f)
              };
             right_wing[2] = {
                     vec3(+2.0f,  +0.5f, +0.0f),
                     vec3(+1.85f, +0.50f, 0.0f),
                     vec3(+1.75,  +0.60f, 0.0f),
                     vec3(+1.5f,  +0.0f, 0.0f)
             };
             right_wing[3] = {
                     vec3(1.5f,  +0.0f, +0.0f),
                     vec3(1.25f, +0.25f, 0.0f),
                     vec3(0.85,  +0.30f, 0.0f),
                     vec3(0.75f, -0.5f, 0.0f)
             };
             right_wing[4] = {
                     vec3(0.75f, -0.5f, 0.0f),
                     vec3(0.50f, +0.00f, 0.0f),
                     vec3(0.25,  +0.05f, 0.0f),
                     vec3(0.20f, -0.5f, 0.0f)
             };
             struct bezier_line left_wing[5];
             left_wing[0] = {
                     vec3(+0.0f,   +0.0f, +0.0f),
                     vec3(-0.125f, +0.0f, +0.0f),
                     vec3(-0.25,   +0.0f, +0.0f),
                     vec3(-0.5f,   +1.0f, +0.0f)
               };
              left_wing[1] = {
                      vec3(-0.5f,  +1.0f, +0.0f),
                      vec3(-0.75f, +1.0f, 0.0f),
                      vec3(-1.0,   +1.0f, 0.0f),
                      vec3(-2.0f,   0.5f, 0.0f)
               };
              left_wing[2] = {
                      vec3(-2.0f,  +0.5f, +0.0f),
                      vec3(-1.85f, +0.50f, 0.0f),
                      vec3(-1.75,  +0.60f, 0.0f),
                      vec3(-1.5f,  +0.0f, 0.0f)
              };
              left_wing[3] = {
                      vec3(-1.5f,  +0.0f, +0.0f),
                      vec3(-1.25f, +0.25f, 0.0f),
                      vec3(-0.85,  +0.30f, 0.0f),
                      vec3(-0.75f, -0.5f, 0.0f)
              };
              left_wing[4] = {
                      vec3(-0.75f, -0.5f, 0.0f),
                      vec3(-0.50f, +0.00f, 0.0f),
                      vec3(-0.25,  +0.05f, 0.0f),
                      vec3(-0.20f, -0.5f, 0.0f)
              };
              struct bezier_line body[8];
              body[0] = {
                  vec3(+0.0f,   -2.5f, +0.0f),
                  vec3(-0.125f, -2.5f, +0.0f),
                  vec3(-0.25,   -2.5f, +0.0f),
                  vec3(-0.5f,   -2.0f, +0.0f)
              };
              body[1] = {
                  vec3(-0.5f,   -2.0f, +0.0f),
                  vec3(-0.25f, -1.5f, +0.0f),
                  vec3(-1.0f,  -1.5f, +0.0f),
                  vec3(-0.5f,  +0.0f, +0.0f)
              };
              body[2] = {
                  vec3(-0.5f,  +0.0f, +0.0f),
                  vec3(-1.0f, +1.0f, +0.0f),
                  vec3(-1.0,   +1.0f, +0.0f),
                  vec3(-0.5f,   +2.0f, +0.0f)
              };
              body[3] = {
                  vec3(-0.5f,  +2.0f, +0.0f),
                  vec3(-0.5f,  +1.0f, +0.0f),
                  vec3(-0.25,  +2.0f, +0.0f),
                  vec3(+0.0f,  +1.5f, +0.0f)
              };
              body[4] = {
                  vec3(+0.0f,  +1.5f, +0.0f),
                  vec3(+0.25,  +2.0f, +0.0f),
                  vec3(+0.5f,  +1.0f, +0.0f),
                  vec3(+0.5f,  +2.0f, +0.0f)
              };
              body[5] = {
                 vec3(+0.5f,   +2.0f, +0.0f),
                 vec3(+1.0,   +1.0f, +0.0f),
                 vec3(+1.0f, +1.0f, +0.0f),
                 vec3(+0.5f,  +0.0f, +0.0f)
              };
              body[6] = {
                  vec3(+0.5f,  +0.0f, +0.0f),
                  vec3(+1.0f,  -1.5f, +0.0f),
                  vec3(+0.25f, -1.5f, +0.0f),
                  vec3(+0.5f,   -2.0f, +0.0f)
              };
              body[7] = {
                  vec3(+0.5f,   -2.0f, +0.0f),
                  vec3(+0.25,   -2.5f, +0.0f),
                  vec3(+0.125f, -2.5f, +0.0f),
                  vec3(+0.0f,   -2.5f, +0.0f)
              };
            left_wing_bezier.init(left_wing , wing_size);
            right_wing_bezier.init(right_wing ,wing_size);
            body_bezier.init(body, body_size);
            speed = speed_factor;
        }

        virtual void draw(float time_s){
            float wing_rot = M_PI * time_s * speed;
            left_wing_bezier.draw(time_s,   0.6 * std::cos(wing_rot), -0.1, -0.1);
            right_wing_bezier.draw(time_s, -0.6 * std::cos(wing_rot), +0.1, -0.1);
            body_bezier.draw(time_s, 0, 0, 0);
        }

        struct bezier_line* left_wing;
        struct bezier_line* right_wing;
        struct bezier_line* body;
        Bezier right_wing_bezier;
        Bezier left_wing_bezier;
        Bezier body_bezier;
        int wing_size = 5;
        int body_size = 8;
        float speed;
};
#endif
