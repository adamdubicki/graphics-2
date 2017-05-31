#include "icg_common.h"
#include "imshow.h"

#include <math.h>
#include <OpenGP/GL/Eigen.h>

#include "Triangle/Triangle.h"
#include "Quad/Quad.h"
#include "Bezier/Bezier.h"


using namespace OpenGP;

Triangle triangle;
Quad quad;
Bezier bezier;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();
    //triangle.draw(time_s);
    bezier.draw(time_s);
}

///
/// You can use this sub-project as a  starting point for your second
/// assignemnt. See the files triangle.h and quad.h for examples of
/// basic OpenGL code.
///

int main(int, char**) {

    OpenGP::glfwInitWindowSize(640, 480);
    OpenGP::glfwMakeWindow("Assignment 2");

    //glClearColor(1.0, 0.4, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    vec3 v1 = vec3(-2.0f, -1.0f, 0.0f);
    vec3 v2 = vec3(1.0f, -1.0f, 0.0f);
    vec3 v3 = vec3(0.0f, 1.0f, 0.0f);
    //triangle.init(v1,v2,v3);
    bezier.init(v1,v2,v3);

    OpenGP::glfwDisplayFunc(&display);

    OpenGP::glfwMainLoop();

    return EXIT_SUCCESS;

}
