#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/* 
 * Task 2:
 * Solve the eigenvalue problem (A^T A) x = λx using a solver from the Eigen library.
 * Report the two largest singular values calculated from the eigenvalues.
 */

int main(int argc, char* argv[]) {
    // Verificare che l'utente abbia fornito il percorso dell'immagine
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <image_path>" << endl;
        return 1;
    }

    const char* imagePath = argv[1];  // Caricare il percorso dell'immagine dal primo argomento

    // LOAD IMAGE
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, 1);
    if (!imageData) {
        cerr << "Error: could not load the image " << imagePath << "." << endl;
        return 1;
    }

    // Copiare i dati dell'immagine in una matrice Eigen
    MatrixXd imageMatrix(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            imageMatrix(i, j) = imageData[index] / 255.0;
        }
    }
    stbi_image_free(imageData);  //FREE MEMORY

    // Calcolare A^T A
    MatrixXd ATA = imageMatrix.transpose() * imageMatrix;

    // Risolvere il problema agli autovalori utilizzando il solver di Eigen
    SelfAdjointEigenSolver<MatrixXd> eigensolver(ATA);
    if (eigensolver.info() != Success) {
        cerr << "Eigenvalue computation did not succeed!" << endl;
        return -1;
    }

    // Ottenere gli autovalori di A^T A (sono i quadrati dei valori singolari)
    VectorXd eigenvalues = eigensolver.eigenvalues();
    int n = eigenvalues.size();
    double largest_singular_value = sqrt(eigenvalues(n-1));  // Maggiore autovalore
    double second_largest_singular_value = sqrt(eigenvalues(n-2));  // Secondo maggiore autovalore

    // Stampare i due maggiori valori singolari
    cout << "Largest singular value: " << largest_singular_value << endl;
    cout << "Second largest singular value: " << second_largest_singular_value << endl;

    return 0;
}
