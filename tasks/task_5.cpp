#include <Eigen/Dense>
#include <Eigen/SVD>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/*
TASK 5
Using the SVD module of the Eigen library, perform a singular value decomposition of the matrix A.
Report the Euclidean norm of the diagonal matrix Σ of the singular values.
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <image_path>" << endl;
        return 1;
    }

    const char* imagePath = argv[1];

    // Carico l'immagine
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, 1);
    if (!imageData) {
        cerr << "Error: could not load the image " << imagePath << "." << endl;
        return 1;
    }

    // Creo la matrice A dall'immagine
    MatrixXd A(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            A(i, j) = static_cast<double>(imageData[index]) / 255.0;
        }
    }
    stbi_image_free(imageData);  // FREE MEMORY

    // Decomposizione SVD
    BDCSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);
    VectorXd singularValues = svd.singularValues();

    // Calcolo la norma euclidea dei singular values
    double sigmaNorm = singularValues.norm();

    cout << "Euclidean norm of the singular values (Σ): " << sigmaNorm << endl;

    return 0;
}
