#ifndef GENERATE_MATRIX_HPP
#define GENERATE_MATRIX_HPP

#include <iostream>
#include <cstdlib>  // for rand, srand
#include <ctime>    // for time
#include <iomanip>

template <class T>
T **generateMatrix(const int m, const int n) {
    if (m <= 0 || n <= 0) {
        std::cerr << "Matrix (m x n) must be at least (1 x 1)" << std::endl;
        return nullptr;
    }

    T **mtx = new T*[m];
    for (int i = 0; i < m; i++) {
        mtx[i] = new T[n];
    }

     std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (std::is_floating_point<T>::value) {
                // Valor aleatório de ponto flutuante entre 0.0 e 100.0
                mtx[i][j] = static_cast<T>(rand()) / RAND_MAX * 100.0;
            } else {
                // Valor inteiro entre 0 e 99
                mtx[i][j] = rand() % 100;
            }
        }
    }

    return mtx;
}


template <class T>
void printMatrix(T **matrix, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


#endif 
