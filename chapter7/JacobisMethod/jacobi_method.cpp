#include <iostream>
#include "/Users/gilbertodemelojr/Documents/programming/cplusplus/NumericalAnalysis/MatrixGenerator/MatrixGenerator.cpp"



int main(int argc, char *argv[]) {

    int m = 5;
    int n = 5;

    double **mtx = generateMatrix<double>(m, n);


    printMatrix(mtx, m, n);



    // Cleanup
    for (int i = 0; i < m; i++) {
        delete[] mtx[i];
    }
    delete[] mtx;


    return 0;
}