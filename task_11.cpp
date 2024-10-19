#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>

using namespace Eigen;
using namespace std;

/*
TASK 11
Starting from the previously computed SVD, create the matrices C and D defined in (1)
assuming k = 5 and k = 10. Report the size of the matrices C and D.
*/

// Funzione per generare la matrice C
MatrixXd generateCMatrix(MatrixXd& U, int k);
// Funzione per generare la matrice D
MatrixXd generateDMatrix(MatrixXd& S, MatrixXd& V, int k);

int main(int argc, char *argv[]) {
    // Ora metto dei valori a caso ma in realtà U, S e V arrivano dallo SVD delle task precendenti
    cout << "Matrix U (già calcolata nello SVD)" << endl;
    MatrixXd U = MatrixXd::Random(6, 6); // Placeholder per U
    cout << U << endl << endl;

    cout << "Matrix S (già calcolata nello SVD)" << endl;
    MatrixXd S = MatrixXd::Random(6, 4); // Placeholder per S
    cout << S << endl << endl;

    cout << "Matrix V (già calcolata nello SVD)" << endl;
    MatrixXd V = MatrixXd::Random(4, 4); // Placeholder per V
    cout << V << endl << endl;

    // Primo valore di k = 5
    int k = 5;

    cout << "Matrix C for k = " << k << endl;
    MatrixXd C = generateCMatrix(U, k);
    cout << C << endl;
    cout << "Nonzero entries of C: " << C.nonZeros() << endl;

    cout << "Matrix D for k = " << k << endl;
    MatrixXd D = generateDMatrix(S, V, k);
    cout << D << endl;
    cout << "Nonzero entries of D: " << D.nonZeros() << endl;

    // Secondo valore di k = 10
    k = 10;

    cout << "Matrix C for k = " << k << endl;
    C = generateCMatrix(U, k);
    cout << C << endl;
    cout << "Nonzero entries of C: " << C.nonZeros() << endl;

    cout << "Matrix D for k = " << k << endl;
    D = generateDMatrix(S, V, k);
    cout << D << endl;
    cout << "Nonzero entries of D: " << D.nonZeros() << endl;

    return 0;
}

// Funzione che genera la matrice C, che contiene le prime k colonne di U
MatrixXd generateCMatrix(MatrixXd& U, int k){
    MatrixXd C(U.rows(), k);
    for(int i=0; i<k; i++)
        C.col(i) = U.col(i);
    return C;
}

// Funzione che genera la matrice D, che contiene i primi k vettori singolari
MatrixXd generateDMatrix(MatrixXd& S, MatrixXd& V, int k){
    MatrixXd D(S.cols(), k);
    for(int i=0; i<k; i++)
        D.col(i) = S(i, i) * V.col(i);
    return D;
}
