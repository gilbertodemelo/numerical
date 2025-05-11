#include <iostream>
#include <omp.h>
#include <cmath>
#include "/Users/gilbertodemelojr/Documents/programming/cplusplus/NumericalAnalysis/MatrixGenerator/MatrixGenerator.cpp"

/*
The Jaboci Iterative algorithm works
on square matrices only.
 */

// At the top of the file
template <class T>
void jacobi_method_serial(T** mtx, int m, const int n, T* b, T* x, int max_iter = 1000, T tol = 1e-6);

template <class T>
void jacobi_method_omp(T** mtx, int m, const int n, T* b, T* x, int max_iter = 1000, T tol = 1e-3);



int main(int argc, char *argv[]) {


    int n = 50000;
    double **mtx = generateMatrix<double>(n, n);

    for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < n; j++) {
        if (i != j) {
            mtx[i][j] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
            sum += std::abs(mtx[i][j]);
        }
    }
    mtx[i][i] = sum + ((double)rand() / RAND_MAX) * 10.0 + 1.0; // guarantees diagonal dominance
}



    double *b = new double[n];
    double *x = new double[n]{};
    double *x_omp = new double[n]{};

// Inicializa b com valores aleatórios entre -100 e 100, por exemplo:
for (int i = 0; i < n; ++i) {
    b[i] = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
}

    double start, end;

    start = omp_get_wtime();
    jacobi_method_serial(mtx, n, n, b, x, 1000, 1e-6);
    end = omp_get_wtime();

    std::cout << "Serial version took " << (end - start) << " seconds.\n";

    // for (int i = 0; i < n; i++) {
    //     std::cout << x[i] << " ";
    // }
    // std::cout << "\n\n";

    start = omp_get_wtime();
    jacobi_method_omp(mtx, n, n, b, x_omp, 1000, 1e-6);
    end = omp_get_wtime();

    std::cout << "OpenMP version took " << (end - start) << " seconds.\n";

    // for (int i = 0; i < n; i++) {
    //     std::cout << x_omp[i] << " ";
    // }
    // std::cout << "\n\n";


    


    return 0;
}

template <class T>
void jacobi_method_omp(T** mtx, int m, const int n, T* b, T* x, int max_iter, T tol) {
    T * x_new = new T[n];

    for (int k = 0; k < max_iter; k++) {
        int i, j;  // <- declare fora do pragma

        #pragma omp parallel for default(none) shared(mtx, x, b, x_new, n) private(i, j)
        for (i = 0; i < n; i++) {
            T sum = 0;
            for (j = 0; j < n; j++) {
                if (j != i) {
                    sum += mtx[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / mtx[i][i];
        }

        T error = 0.0;

        #pragma omp parallel for default(none) shared(x, x_new, n) reduction(+:error) private(i)
        for (i = 0; i < n; i++) {
            T diff = x_new[i] - x[i];
            error += diff * diff;
            x[i] = x_new[i];
        }

        if (std::sqrt(error) < tol) {
            break;
        }
    }

    delete[] x_new;
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

        if (std::sqrt(error) < tol) {
            break;
        }
    }

    delete[] x_new;

}