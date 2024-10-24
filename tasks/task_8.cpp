#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace Eigen;
using namespace std;

/*
Using Eigen create a black and white checkerboard image with height and width equal to 200 pixels.
The checkerboard will have 8x8 cells, with the top-left cell being black. 
Report the Euclidean norm of the matrix corresponding to the image.
*/

// Funzione che converte un valore double in unsigned char
unsigned char toUnsignedChar(double val) {
    return static_cast<unsigned char>(val);
}

int main() {
    // Dimensione dell'immagine (200x200 pixel)
    int height = 200, width = 200;

    // Numero di celle per riga e colonna della scacchiera (8x8)
    int cellsPerRow = 8;
    int blockSize = height / cellsPerRow;  // Dimensione di ciascun blocco della scacchiera (25x25 pixel)

    // Creare una matrice 200x200
    MatrixXd checkerboard(height, width);

    // Riempire la matrice con il pattern a scacchiera
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Determinare se il blocco corrente è nero (0) o bianco (255)
            if (((i / blockSize) % 2 == 0 && (j / blockSize) % 2 == 0) || 
                ((i / blockSize) % 2 == 1 && (j / blockSize) % 2 == 1)) {
                checkerboard(i, j) = 0.0;  // Nero
            } else {
                checkerboard(i, j) = 255.0;  // Bianco
            }
        }
    }

    // Calcolare la norma euclidea della matrice
    double norm = checkerboard.norm();
    cout << "Norma Euclidea della scacchiera: " << norm << endl;

    // Convertire la matrice in unsigned char per salvare l'immagine
    Matrix<unsigned char, Dynamic, Dynamic, RowMajor> checkerboard_char(height, width);
    checkerboard_char = checkerboard.unaryExpr(&toUnsignedChar);

    // Salvare l'immagine in formato PNG nel percorso /resource
    const char* output_image_path = "resource/checkerboard.png";
    if (stbi_write_png(output_image_path, width, height, 1, checkerboard_char.data(), width) == 0) {
        cerr << "Errore: Impossibile salvare l'immagine a scacchiera" << endl;
        return 1;
    }

    cout << "Immagine a scacchiera salvata in 'resource/checkerboard.png'" << endl;

    return 0;
}
