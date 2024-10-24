#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <unsupported/Eigen/SparseExtra>

using namespace Eigen;
using namespace std;

/*
TASK 3
Export matrix ATA in the matrix market format and move it to the lis-2.1.6/test
folder. Using the proper iterative solver available in the LIS library compute the largest
eigenvalue of ATA up to a tolerance of 10−8. Report the computed eigenvalue. Is the result
in agreement with the one obtained in the previous point?
*/

int main(int argc, char *argv[])
{
    MatrixXd ata = MatrixXd::Random(3, 3);

    const string output_ata_market_path = "output/ata.mtx";
    remove(output_ata_market_path.c_str());
    FILE *out = fopen(output_ata_market_path.c_str(), "w");
    if (!out)
    {
        std::cerr << "Error opening file: " << output_ata_market_path << std::endl;
        return -1;
    }
    fprintf(out, "%%%%MatrixMarket matrix coordinate real general\n");
    fprintf(out, "%d %d %d\n", ata.rows(), ata.cols(), ata.nonZeros());
    for (int k = 0; k < ata.outerSize(); ++k)
    {
        for (MatrixXd::InnerIterator it(ata, k); it; ++it)
        {
            fprintf(out, "%d %d  %.20e\n", it.row() + 1, it.col() + 1, it.value());
        }
    }
    fclose(out);
    cout << "ATA matrix saved to " << output_ata_market_path << endl;

    system("mpicc -DUSE_MPI -I${mkLisInc} -L${mkLisLib} -llis ./resource/lis-2.0.34/test/etest1.c -o ./resource/lis-2.0.34/test/etest1");
    system("./resource/lis-2.0.34/test/etest1 output/ata.mtx ./output/eigvec.txt ./output/hist.txt -e pi");
}