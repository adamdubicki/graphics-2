#include "icg_common.h"
#include "imshow.h"
#include <Eigen/Geometry>


Colour red() { return Colour(255, 0, 0); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }

int main(int, char**){

    /// Rays and vectors represented with Eigen

    typedef Eigen::Vector3f vec3;
    typedef Eigen::ParametrizedLine<float, 3> ray3;

    int wResolution = 640;
    int hResolution = 480;
    
    Image image(wResolution, hResolution);
    
    /// TODO: define camera position and sphere position here

    // example: vec3 spherePos = vec3(0, 5, 0);

    for (int row = 0; row < image.rows; ++row) {
        for (int col = 0; col < image.cols; ++col) {

            /// TODO: build primary rays

            // example: vec3 o = vec3(0,0,0);
            
            /// EXAMPLE: using "image.set(row, col, colour)" to set pixel values
            if (row > 0 && row < 200 && col > 0 && col < 200)  {
                image.set(row, col, red());
            } else {
                image.set(row, col, black());
            }
       }
    }

    image.save("../../out.bmp");
    image.show();

    return EXIT_SUCCESS;
}
