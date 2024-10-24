#include <Eigen/Dense>
#include <iostream>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/*
• Compute the compressed images as the matrix product CDT (again for k = 40 and k = 80).
Export and upload the resulting images in .png.
*/

int main(int argc, char* argv[]) {
    // da sostituire con le matrici effettive
    int height = 3;
    int width = 3;
    MatrixXd C = MatrixXd::Random (height, width);
    MatrixXd D = MatrixXd::Random (height, width);

    MatrixXd multiplication = C * D.transpose();

    Matrix<unsigned char, Dynamic, Dynamic, RowMajor> multiplication_image(height, width);
    multiplication_image = multiplication.unaryExpr([](double val) -> unsigned char {
        return static_cast<unsigned char>(max(0.0, min(val, 255.0)));
    });

    const string CDt_path = "output/CDt.png";
    if (stbi_write_png(CDt_path.c_str(), width, height, 1, multiplication_image.data(), width) == 0) {
        cerr << "Error: Could not save grayscale image" << endl;
        return 1;
    }

    cout << "CDt image saved to " << CDt_path << endl;

    return 0;
}