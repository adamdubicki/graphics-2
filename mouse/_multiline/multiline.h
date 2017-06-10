#include "icg_common.h"
#include "../assignment2/Bezier/Bezier.h"

const static OpenGP::Scalar H = 1;
const static OpenGP::Scalar R = 1;

class MultiLine{
public:
    class Hull{
    public:
        Hull() {
            _p1 = _p2 = _p3 = _p4 = vec3::Zero();
        }

        vec3& p1(){ return _p1; }
        vec3& p2(){ return _p2; }
        vec3& p3(){ return _p3; }
        vec3& p4(){ return _p4; }

    public:
        vec3 _p1;
        vec3 _p2;
        vec3 _p3;
        vec3 _p4;
    };
    
public:
    Hull _hull;                  ///< control points
    std::vector<vec3> _vertices; ///< multiline points
    GLuint _vao;                 ///< Vertex array objects
    GLuint _pid;          ///< GLSL program ID
    GLuint _vbo;
    Bezier _b;
    
private:

    void multiline(Hull & p)
    {
        _vertices.push_back(p.p1());
        _vertices.push_back(p.p2());
        _vertices.push_back(p.p3());
        _vertices.push_back(p.p4());
    }

public:
    void init(GLuint pid){
        ///--- Set the (compiled) shaders
        _pid = pid;
        
        /// Generate the vertex array
        glGenVertexArrays(ONE, &_vao);
        glBindVertexArray(_vao);
        
        /// Generate one buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(ONE, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        ///--- to avoid the current object being polluted
        glBindVertexArray(0);
        glUseProgram(0);
    }
    void set_points(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4) {
        _vertices.clear();

        ///--- initialize data
        _hull.p1() = p1;
        _hull.p2() = p2;
        _hull.p3() = p3;
        _hull.p4() = p4;

        ///--- create the multiline
        multiline(_hull);
    }  

    void draw(const mat4& model, const mat4& view, const mat4& projection){
        if (_vertices.empty()) return;

        glUseProgram(_pid);
        glBindVertexArray(_vao);


        ///--- Vertex Attribute ID for Vertex Positions
        GLuint position = glGetAttribLocation(_pid, "position");
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);

        ///--- vertices
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*_vertices.size(), &_vertices[0], GL_STATIC_DRAW);

        ///--- setup view matrices        
        GLuint projection_id = glGetUniformLocation(_pid, "projection");
        glUniformMatrix4fv(projection_id, ONE, DONT_TRANSPOSE, projection.data());
        mat4 MV = view;
        GLuint model_view_id = glGetUniformLocation(_pid, "model_view");
        glUniformMatrix4fv(model_view_id, ONE, DONT_TRANSPOSE, MV.data());

        struct bezier_line line_coords[1];
        line_coords[0] = {
            _hull._p1,
            _hull._p2,
            _hull._p3,
            _hull._p4
        };
        const char* vshader = "../assignment2/Bezier/vshader_mountain.glsl";
        const char* fshader = "../assignment2/Bezier/fshader_mountain.glsl";
        _b.init(line_coords, 1, vshader, fshader);
        _b.mode = GL_LINE_STRIP;
        _b.draw(0.01, 0, 0, 0, 1.0, 1.0);

        glDisableVertexAttribArray(position);
        glBindVertexArray(0);
    }
};
