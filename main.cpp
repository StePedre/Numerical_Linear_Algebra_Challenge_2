#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/SparseExtra>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
using namespace Eigen;

MatrixXd generateCMatrix(MatrixXd& U, int k);
MatrixXd generateDMatrix(VectorXd& S, MatrixXd& V, int k);
int saveImage(MatrixXd& matrix, const string path, double maxValue, double multiplier);

int main(int argc, char* argv[]){
    cout<<"*********TASK 1*********"<<endl;
    const char* imagePath = argv[1];
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, 1);
    if (!imageData) {
        cerr << "Error: could not load the image " << imagePath << "." << endl;
        return 1;
    }
    MatrixXd A(height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            A(i, j) = imageData[index] / 255.0;
        }
    }
    stbi_image_free(imageData);
    cout << "Image loaded correctly. The size of the matrix is " << A.rows() << "x" << A.cols() << endl;
    MatrixXd ATA;
    ATA = A.transpose() * A;
    cout << "Euclidean norm of A^T * A is " << ATA.norm() << endl << endl;
    
    cout<<"*********TASK 2*********"<<endl;
    SelfAdjointEigenSolver<MatrixXd> eigensolver(ATA);
    if (eigensolver.info() != Success) {
        cerr << "Eigenvalue computation did not succeed!" << endl;
        return -1;
    }

    VectorXd eigenvalues = eigensolver.eigenvalues();
    int n = eigenvalues.size();
    double largest_singular_value = sqrt(eigenvalues(n-1));  
    double second_largest_singular_value = sqrt(eigenvalues(n-2));

    cout << "Largest singular value: " << largest_singular_value << endl;
    cout << "Second largest singular value: " << second_largest_singular_value << endl << endl;

    cout<<"*********TASK 3*********"<<endl;
    const string output_ata_market_path = "./output/ata.mtx";
    
    saveMarket(ATA, output_ata_market_path);
    cout << "ATA matrix saved to " << output_ata_market_path << endl;

    system("mpicc -DUSE_MPI -I${mkLisInc} -L${mkLisLib} -llis ./resource/lis-2.0.34/test/etest1.c -o ./resource/lis-2.0.34/test/etest1");
    string command = "./resource/lis-2.0.34/test/etest1 " 
        + output_ata_market_path
        + " ./output/eigvec.txt ./output/hist.txt -e pi -etol 1.0e-8";
    system(command.c_str());

    cout<<"*********TASK 4*********"<<endl;
    command = "./resource/lis-2.0.34/test/etest1 " 
        + output_ata_market_path
        + " ./output/eigvec.txt ./output/hist.txt -e pi -etol 1.0e-8 -shift 190";
    system(command.c_str());

    cout<<"*********TASK 5*********"<<endl;
    BDCSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);

    VectorXd sigma = svd.singularValues();
    double sigmaNorm = sigma.norm();

    cout << "Euclidean norm of the singular values (Σ): " << sigmaNorm << endl;
    
    cout<<"*********TASK 6*********"<<endl;
    MatrixXd U = svd.matrixU();
    MatrixXd V = svd.matrixV();
   
    MatrixXd C_40 = generateCMatrix(U, 40);
    MatrixXd D_40 = generateDMatrix(sigma, V, 40);
    cout << "Nonzero entries of C_40: " << C_40.nonZeros() << endl;
    cout << "Nonzero entries of D_40: " << D_40.nonZeros() << endl;
   
    MatrixXd C_80 = generateCMatrix(U, 80);
    MatrixXd D_80 = generateDMatrix(sigma, V, 80);
    cout << "Nonzero entries of C_80: " << C_80.nonZeros() << endl;
    cout << "Nonzero entries of D_80: " << D_80.nonZeros() << endl;

    cout<<"*********TASK 7*********"<<endl;

    MatrixXd CDT_40 = C_40 * D_40.transpose();
    saveImage(CDT_40, "output/CDT_40.png", 1.0, 255.0);
    
    MatrixXd CDT_80 = C_80 * D_80.transpose();
    saveImage(CDT_80, "output/CDT_80.png", 1.0, 255.0);

    cout<<"*********TASK 8*********"<<endl;
    int checkerboard_hight = 200;
    int checkerboard_width = 200;
    int blockSize = checkerboard_hight / 8;

    MatrixXd checkerboard(checkerboard_hight, checkerboard_width);

    for (int i = 0; i < checkerboard_hight; ++i) {
        for (int j = 0; j < checkerboard_width; ++j) {
            if (((i / blockSize) % 2 == 0 && (j / blockSize) % 2 == 0) || 
                ((i / blockSize) % 2 == 1 && (j / blockSize) % 2 == 1)) {
                checkerboard(i, j) = 0.0;
            } else {
                checkerboard(i, j) = 255.0;
            }
       }
    }

    cout << "Norma of checkerboard: " << checkerboard.norm() << endl;
    saveImage(checkerboard, "output/checkerboard.png", 255.0, 1.0);

    cout<<"*********TASK 9*********"<<endl;
    MatrixXd checkerboard_noise = checkerboard + (MatrixXd::Random(checkerboard_hight, checkerboard_width) * 50);
    saveImage(checkerboard_noise, "output/checkerboard_noise.png", 255.0, 1.0);

    cout<<"*********TASK 10*********"<<endl;

    Eigen::BDCSVD<Eigen::MatrixXd> svd_checkerboard (checkerboard_noise, Eigen::ComputeThinU | Eigen::ComputeThinV);
    VectorXd sigma_checkerboard = svd_checkerboard.singularValues();

    cout << "Largest singular value: " << sqrt(sigma_checkerboard[0]) << endl;
    cout << "Second largest singular value: " << sqrt(sigma_checkerboard[1]) << endl;

    cout<<"*********TASK 11*********"<<endl;
    MatrixXd U_checkerboard = svd_checkerboard.matrixU();
    MatrixXd V_checkerboard = svd_checkerboard.matrixV();
    MatrixXd C_5 = generateCMatrix(U_checkerboard, 5);
    MatrixXd D_5 = generateDMatrix(sigma_checkerboard, V_checkerboard, 5);
    cout << "Size of C_5: " << C_5.rows() << "x" << C_5.cols() << endl;
    cout << "Size of D_5: " << D_5.rows() << "x" << D_5.cols() << endl;
    
    MatrixXd C_10 = generateCMatrix(U_checkerboard, 10);
    MatrixXd D_10 = generateDMatrix(sigma_checkerboard, V_checkerboard, 10);
    cout << "Size of C_10: " << C_10.rows() << "x" << C_10.cols() << endl;
    cout << "Size of D_10: " << D_10.rows() << "x" << D_10.cols() << endl;

    cout<<"*********TASK 12*********"<<endl;
    MatrixXd CDT_5 = C_5 * D_5.transpose();
    saveImage(CDT_5, "output/CDT_5.png", 255.0, 1.0);
    
    MatrixXd CDT_10 = C_10 * D_10.transpose();
    saveImage(CDT_10, "output/CDT_10.png", 255.0, 1.0);
    
}

MatrixXd generateCMatrix(MatrixXd& U, int k){
    MatrixXd C(U.rows(), k);
    for(int i=0; i<k; i++)
        C.col(i) = U.col(i);
    return C;
}

MatrixXd generateDMatrix(VectorXd& S, MatrixXd& V, int k){
    MatrixXd D(S.rows(), k);
    for(int i=0; i<k; i++)
        D.col(i) = S(i) * V.col(i);
    return D;
}

int saveImage(MatrixXd& matrix, const string path, double maxValue, double multiplier){
    Matrix<unsigned char, Dynamic, Dynamic, RowMajor> matrix_image(matrix.rows(), matrix.cols());
    matrix_image = matrix.unaryExpr([maxValue, multiplier](double val) -> unsigned char {
        return static_cast<unsigned char>(max(0.0, min(val, maxValue) * multiplier));
    });

    if (stbi_write_png(path.c_str(), matrix.cols(), matrix.rows(), 1, matrix_image.data(), matrix.cols()) == 0) {
        cerr << "Error: Could not save "<< path << " image" << endl;
        return -1;
    }

    cout << "Image saved to " << path << endl;
    return 0;
}