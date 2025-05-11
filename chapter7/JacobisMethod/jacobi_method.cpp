#include <iostream>
#include "/Users/gilbertodemelojr/Documents/programming/cplusplus/NumericalAnalysis/MatrixGenerator/MatrixGenerator.cpp"

/*
The Jaboci Iterative algorithm works
on square matrices only.
 */

// At the top of the file
template <class T>
void jacobi_method_serial(T** mtx, int m, const int n, T* b, T* x, int max_iter = 1000, T tol = 1e-6);



int main(int argc, char *argv[]) {



    const int n = 4;
    double** mtx = new double*[n];
    for (int i = 0; i < n; ++i) {
        mtx[i] = new double[n];
    }

    // Initialize matrix manually
    mtx[0][0] = 10;  mtx[0][1] = -2;  mtx[0][2] =  2;  mtx[0][3] =  0;
    mtx[1][0] = -1;  mtx[1][1] = 11;  mtx[1][2] = -1;  mtx[1][3] =  3;
    mtx[2][0] =  2;  mtx[2][1] = -1;  mtx[2][2] = 10;  mtx[2][3] = -1;
    mtx[3][0] =  0;  mtx[3][1] =  3;  mtx[3][2] = -1;  mtx[3][3] =  8;

    double *b = new double[n];
    b[0] = 6; b[1] = 25; b[2] = -11; b[3] = 15;

    double *x = new double[4]{0, 0, 0, 0};

    jacobi_method_serial(mtx, n, n, b, x, 1000, 1e-6);

    for (int i = 0; i < n; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";


    


    return 0;
}


template <class T>
void jacobi_method_serial(T **mtx, int m, const int n, T *b, T *x, int max_iter, T tol) {

    T * x_new = new T[n];
    for (int k = 0; k < max_iter; k++) {
        for (int i = 0; i < n; i++) {
            T sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += mtx[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / mtx[i][i];
        }

        // Check for the convergence
        T error = 0;
        for (int i = 0; i < n; i++) {
            error += (x_new[i] - x[i]) * (x_new[i] - x[i]);
            x[i] = x_new[i];
        }

        if (sqrt(error) < tol) {
            break;
        }
    }

    delete[] x_new;

}