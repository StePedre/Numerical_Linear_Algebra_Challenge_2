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

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    int height = 200;
    int width = 200;
    MatrixXd random = MatrixXd::Random(height, width);

    random = random + (MatrixXd::Random(height, width) * 50);


    Matrix<unsigned char, Dynamic, Dynamic, RowMajor> noise_image_char(height, width);
    noise_image_char = random.unaryExpr([](double val) -> unsigned char
                               { return static_cast<unsigned char>(max(0.0, min(val, 255.0))); });

    const string output_noise_path = "output/noise_image.png";
    if (stbi_write_png(output_noise_path.c_str(), width, height, 1, noise_image_char.data(), width) == 0)
    {
        cerr << "Error: Could not save noisy image" << endl;
        return 1;
    }

    cout << "Y image saved to " << output_noise_path << endl;

}