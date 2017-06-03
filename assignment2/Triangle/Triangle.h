#pragma once
#include "icg_common.h"

class Triangle{
private:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID 
    GLuint _vbo; ///< memory buffer
public:
    void init(vec3 v1, vec3 v2, vec3 v3){
        ///--- Compile the shaders
        _pid = OpenGP::load_shaders("Triangle/vshader.glsl", "Triangle/fshader.glsl");
        if(!_pid) exit(EXIT_FAILURE);       
        glUseProgram(_pid);
        
        ///--- Vertex one vertex Array
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
     
        ///--- Vertex Buffer
        GLfloat vpoint[] = { v1[0], v1[1], v1[2],
                             v2[0], v2[1], v2[2],
                             v3[0], v3[1], v3[2]};
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
            
            mat4 T = Eigen::Affine3f(Eigen::Translation3f(0,0,0)).matrix();
            mat4 R = Eigen::Affine3f(Eigen::AngleAxisf(0, vec3::UnitZ())).matrix();
            mat4 S = mat4::Identity();
            S(0,0) = 1;
            S(1,1) = 1;
            mat4 M = T*S*R;            
            GLuint M_id = glGetUniformLocation(_pid, "M");
            glUniformMatrix4fv(M_id, 1, GL_FALSE, M.data());
            ///--- Draw
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
        glBindVertexArray(0);        
        glUseProgram(0);
    }
};
