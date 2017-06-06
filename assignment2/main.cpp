#include "icg_common.h"
#include "imshow.h"

#include <math.h>
#include <OpenGP/GL/Eigen.h>

#include "Triangle/Triangle.h"
#include "Quad/Quad.h"
#include "Bezier/Bezier.h"


using namespace OpenGP;
Mountain mountain;
Bat b1;
Bat b2;
Bezier b;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();
    b.draw(0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
    b1.draw(time_s);
    b2.draw(time_s);
    mountain.draw();
}


void init(){
    // Initialize the bat
    // Speed, path, starting_scale, end_scale, and wing speed

    ///- Bat 1 config
    struct bezier_line b1_path[1];
    b1_path[0] = {
          vec3(+1.0f,   -1.0f, +0.0f),
          vec3(+0.0f,   +1.0f, +0.0f),
          vec3(+0.0f,   +1.0f, +0.0f),
          vec3(-1.0f,   -1.0f, -1.0f)
    };
    b1.init(0.85f, b1_path, 0.1, 0.2, 10);

    ///- Bat 2 config
    struct bezier_line b2_path[1];
    b2_path[0] = {
          vec3(+1.0f,   +1.0f, +0.0f),
          vec3(+0.5f,   +0.0f, +0.0f),
          vec3(-0.5f,   +0.0f, +0.0f),
          vec3(-2.0f,   +1.0f, -1.0f)
    };
    b2.init(0.5f, b2_path, 0.1, 0.2, 2);

    mountain.init();
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
