#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>

using namespace Eigen;
using namespace std;

/*
TASK 6
Compute the matrices C and D described in (1) assuming k = 40 and k = 80. Report the
number of nonzero entries in the matrices C and D.
*/

MatrixXd generateCMatrix(MatrixXd& U, int k);
MatrixXd generateDMatrix(MatrixXd& S, MatrixXd& V, int k);

int main(int argc, char *argv[])
{
    cout << "Matrix U" << endl;
    MatrixXd U = MatrixXd::Random(6, 6);
    cout << U << endl << endl;

    cout << "Matrix S" << endl;
    MatrixXd S = MatrixXd::Random(6, 4);
    cout << S << endl << endl;

    cout << "Matrix V" << endl;
    MatrixXd V = MatrixXd::Random(4, 4);
    cout << V << endl << endl;

    cout << "Matrix C" << endl;
    MatrixXd C = generateCMatrix(U, 2);
    cout << C << endl;
    cout << "Nonzero entries of C: " << C.nonZeros() << endl;

    cout << "Matrix D" << endl;
    MatrixXd D = generateDMatrix(S, V, 2);
    cout << D << endl;
    cout << "Nonzero entries of D: " << D.nonZeros() << endl;

    return 0;
}

MatrixXd generateCMatrix(MatrixXd& U, int k){
    MatrixXd C(U.rows(), k);
    for(int i=0; i<k; i++)
        C.col(i) = U.col(i);
    return C;
}

MatrixXd generateDMatrix(MatrixXd& S, MatrixXd& V, int k){
    MatrixXd D(S.cols(), k);
    for(int i=0; i<k; i++)
        D.col(i) = S(i, i) * V.col(i);
    return D;

}