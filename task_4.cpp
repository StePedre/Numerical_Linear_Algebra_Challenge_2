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
• Find a shift mu yielding an acceleration of the previous eigensolver. Report mu and the
number of iterations required to achieve a tolerance of 1e-8.
*/

int main(int argc, char* argv[]) {
    // In task 3 "-tol 1e-8" is missing (?)
    // with a shift of 500 the eigenvalue computed it's the same as the one in task 3 (1.608332e+04), but the number of iteration is 10 (two less then task 3)
    // 10 iterations are achieved by choosing a shift between 383 and 943.
    system("mpicc -DUSE_MPI -I${mkLisInc} -L${mkLisLib} -llis ./resource/lis-2.0.34/test/etest1.c -o ./resource/lis-2.0.34/test/etest1");
    system("./resource/lis-2.0.34/test/etest1 output/ata.mtx ./output/eigvec.txt ./output/hist.txt -e pi -tol 1e-8 -shift 500");
}