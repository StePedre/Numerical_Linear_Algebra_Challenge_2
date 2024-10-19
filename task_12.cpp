#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>
#include <cstdlib> // For std::srand and std::rand
#include <ctime>   // For std::time
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/*
TASK 9
Introduce a noise into the checkerboard image by adding random fluctuations of color
ranging between [−50, 50] to each pixel. Export the resulting image in .png and upload it.
*/

int main(int argc, char *argv[]){
    int height = 3;
    int width = 3;
    MatrixXd C = MatrixXd::Random(3, 3);
    MatrixXd D = MatrixXd::Random(3, 3);

    MatrixXd CDT = C * D.transpose();

    Matrix<unsigned char, Dynamic, Dynamic, RowMajor> CDT_image_char(height, width);
    CDT_image_char = CDT.unaryExpr([](double val) -> unsigned char
                               { return static_cast<unsigned char>(max(0.0, min(val, 255.0))); });

    const string output_CDT_path = "output/CDT_image.png";
    if (stbi_write_png(output_CDT_path.c_str(), width, height, 1, CDT_image_char.data(), width) == 0)
    {
        cerr << "Error: Could not save noisy image" << endl;
        return 1;
    }

    cout << "CDT image saved to " << output_CDT_path << endl;

}