#include "icg_common.h"
#include "imshow.h"

#include <math.h>
#include <OpenGP/GL/Eigen.h>

#include "Triangle/Triangle.h"
#include "Quad/Quad.h"
#include "Bezier/Bezier.h"


using namespace OpenGP;

Triangle triangle1;
Triangle triangle2;
Quad quad;
Bat b1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();
    b1.draw(time_s);
}

///
/// You can use this sub-project as a  starting point for your second
/// assignemnt. See the files triangle.h and quad.h for examples of
/// basic OpenGL code.
///
///

void init(){
      b1.init(1.5f);
      cout << "b1 was initialized" << endl;
//    struct bezier_line wing[5];
//    wing[0] = {
//            vec3(+0.0f,   +0.0f, +0.0f),
//            vec3(+0.125f, +0.0f, +0.0f),
//            vec3(+0.25,   +0.0f, +0.0f),
//            vec3(+0.5f,   +1.0f, +0.0f)
//      };
//     wing[1] = {
//             vec3(+0.5f,  +1.0f, +0.0f),
//             vec3(+0.75f, +1.0f, 0.0f),
//             vec3(+1.0,   +1.0f, 0.0f),
//             vec3(+2.0f,   0.5f, 0.0f)
//      };
//     wing[2] = {
//             vec3(+2.0f,  +0.5f, +0.0f),
//             vec3(+1.85f, +0.50f, 0.0f),
//             vec3(+1.75,  +0.60f, 0.0f),
//             vec3(+1.5f,  +0.0f, 0.0f)
//     };
//     wing[3] = {
//             vec3(1.5f,  +0.0f, +0.0f),
//             vec3(1.25f, +0.25f, 0.0f),
//             vec3(0.85,  +0.30f, 0.0f),
//             vec3(0.75f, -0.5f, 0.0f)
//     };
//     wing[4] = {
//             vec3(0.75f, -0.5f, 0.0f),
//             vec3(0.50f, +0.00f, 0.0f),
//             vec3(0.25,  +0.05f, 0.0f),
//             vec3(0.20f, -0.5f, 0.0f)
//     };

//    struct bezier_line wing2[5];
//    wing2[0] = {
//            vec3(+0.0f,   +0.0f, +0.0f),
//            vec3(-0.125f, +0.0f, +0.0f),
//            vec3(-0.25,   +0.0f, +0.0f),
//            vec3(-0.5f,   +1.0f, +0.0f)
//      };
//     wing2[1] = {
//             vec3(-0.5f,  +1.0f, +0.0f),
//             vec3(-0.75f, +1.0f, 0.0f),
//             vec3(-1.0,   +1.0f, 0.0f),
//             vec3(-2.0f,   0.5f, 0.0f)
//      };
//     wing2[2] = {
//             vec3(-2.0f,  +0.5f, +0.0f),
//             vec3(-1.85f, +0.50f, 0.0f),
//             vec3(-1.75,  +0.60f, 0.0f),
//             vec3(-1.5f,  +0.0f, 0.0f)
//     };
//     wing2[3] = {
//             vec3(-1.5f,  +0.0f, +0.0f),
//             vec3(-1.25f, +0.25f, 0.0f),
//             vec3(-0.85,  +0.30f, 0.0f),
//             vec3(-0.75f, -0.5f, 0.0f)
//     };
//     wing2[4] = {
//             vec3(-0.75f, -0.5f, 0.0f),
//             vec3(-0.50f, +0.00f, 0.0f),
//             vec3(-0.25,  +0.05f, 0.0f),
//             vec3(-0.20f, -0.5f, 0.0f)
//     };

//     struct bezier_line body_s[8];
//     body_s[0] = {
//         vec3(+0.0f,   -2.5f, +0.0f),
//         vec3(-0.125f, -2.5f, +0.0f),
//         vec3(-0.25,   -2.5f, +0.0f),
//         vec3(-0.5f,   -2.0f, +0.0f)
//     };
//     body_s[1] = {
//         vec3(-0.5f,   -2.0f, +0.0f),
//         vec3(-0.25f, -1.5f, +0.0f),
//         vec3(-1.0f,  -1.5f, +0.0f),
//         vec3(-0.5f,  +0.0f, +0.0f)
//     };
//     body_s[2] = {
//         vec3(-0.5f,  +0.0f, +0.0f),
//         vec3(-1.0f, +1.0f, +0.0f),
//         vec3(-1.0,   +1.0f, +0.0f),
//         vec3(-0.5f,   +2.0f, +0.0f)
//     };
//     body_s[3] = {
//         vec3(-0.5f,  +2.0f, +0.0f),
//         vec3(-0.5f,  +1.0f, +0.0f),
//         vec3(-0.25,  +2.0f, +0.0f),
//         vec3(+0.0f,  +1.5f, +0.0f)
//     };

//     body_s[4] = {
//         vec3(+0.0f,  +1.5f, +0.0f),
//         vec3(+0.25,  +2.0f, +0.0f),
//         vec3(+0.5f,  +1.0f, +0.0f),
//         vec3(+0.5f,  +2.0f, +0.0f)
//     };
//     body_s[5] = {
//        vec3(+0.5f,   +2.0f, +0.0f),
//        vec3(+1.0,   +1.0f, +0.0f),
//        vec3(+1.0f, +1.0f, +0.0f),
//        vec3(+0.5f,  +0.0f, +0.0f)
//     };
//     body_s[6] = {
//         vec3(+0.5f,  +0.0f, +0.0f),
//         vec3(+1.0f,  -1.5f, +0.0f),
//         vec3(+0.25f, -1.5f, +0.0f),
//         vec3(+0.5f,   -2.0f, +0.0f)
//     };
//     body_s[7] = {
//         vec3(+0.5f,   -2.0f, +0.0f),
//         vec3(+0.25,   -2.5f, +0.0f),
//         vec3(+0.125f, -2.5f, +0.0f),
//         vec3(+0.0f,   -2.5f, +0.0f)
//     };


//    bw1.init(wing , 5);
//    bw2.init(wing2 ,5);
//    body.init(body_s, 8);

}

int main(int, char**) {

    OpenGP::glfwInitWindowSize(640, 480);
    OpenGP::glfwMakeWindow("Assignment 2");

    //glClearColor(1.0, 0.4, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    OpenGP::glfwDisplayFunc(&display);
    init();

    OpenGP::glfwMainLoop();

    return EXIT_SUCCESS;

}
