#include <Eigen/Dense>
#include <Eigen/SVD>
#include <iostream>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/*
• Using the SVD module of the Eigen library, perform a singular value decomposition of the
matrix corresponding to the noisy image. Report the two largest computed singular values.
*/

int main (int argc, char* argv[]) {
    int height = 20;
    int width = 20;
    
    // to substitute with the proper matrix
    MatrixXd noisy_matrix = MatrixXd::Random (height, width);

    // Compute SVD
    Eigen::BDCSVD<Eigen::MatrixXd> svd (noisy_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    VectorXd W = svd.singularValues();
    
    // print required singular values
    cout << "Largest singular value: " << sqrt(W[0]) << endl;
    cout << "Second largest singular value: " << sqrt(W[1]) << endl;
    return 0;
}