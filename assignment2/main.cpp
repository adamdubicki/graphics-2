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
Bat b2;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float time_s = glfwGetTime();
    b1.draw(time_s);
    b2.draw(time_s);
}


void init(){
      ///- Bat 1 config
      struct bezier_line b1_path[1];
      b1_path[0] = {
              vec3(+1.0f,   -1.0f, +0.0f),
              vec3(+0.0f,   +1.0f, +0.0f),
              vec3(+0.0,    +1.0f, +0.0f),
              vec3(-1.0f,   -1.0f, +0.0f)
      };
      b1.init(0.85f, b1_path);

      ///- Bat 2 config
      struct bezier_line b2_path[1];
      b2_path[0] = {
              vec3(+1.0f,   +1.0f, +0.0f),
              vec3(+0.0f,   +0.0f, +0.0f),
              vec3(+0.0,    +0.0f, +0.0f),
              vec3(-1.0f,   +1.0f, +0.0f)
      };
      b2.init(0.5f, b2_path);
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
