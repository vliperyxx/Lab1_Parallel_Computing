#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdlib>  
#include <ctime> 


class MatrixOperations {
public:
    static int* allocateMatrix(int size) {
        return new int[size * size];
    }

    static void freeMatrix(int* matrix) {
        delete[] matrix;
    }

    static void fillMatrix(int* matrix, int size) {
        srand(time(nullptr));  

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                matrix[row * size + col] = rand() % 10000 + 1;  
            }
        }
    }

    static void calculateMaxOfColumn(int* matrix, int size, int col) {
        if (col >= size)
            return;

        int maxRow = col;  
        int maxVal = matrix[col * size + col];  

        for (int row = 0; row < size; row++) {
            if (matrix[row * size + col] > maxVal) {
                maxVal = matrix[row * size + col];
                maxRow = row; 
            }
        }

        if (maxRow != col) {
            std::swap(matrix[col * size + col], matrix[maxRow * size + col]);
        }
    }

    static void calculateAllMax(int* matrix, int size) {
        for (int col = 0; col < size; col++) {
            calculateMaxOfColumn(matrix, size, col);
        }
    }

    static void printMatrix(int* matrix, int size) {
        for (int row = 0; row < std::min(size, 10); row++) { 
            for (int col = 0; col < std::min(size, 10); col++) {
                std::cout << std::setw(6) << matrix[row * size + col] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main() {
    int size;
    std::cout << "Enter size of matrix: ";
    std::cin >> size;

    int* matrix = MatrixOperations::allocateMatrix(size);
    MatrixOperations::fillMatrix(matrix, size);

    if (size <= 10) {
        std::cout << "Initial Matrix:\n";
        MatrixOperations::printMatrix(matrix, size);
    }

    auto startSingleThread = std::chrono::high_resolution_clock::now();
    MatrixOperations::calculateAllMax(matrix, size);
    auto endSingleThread = std::chrono::high_resolution_clock::now();

    double durationSingleThread = std::chrono::duration<double, std::milli>(endSingleThread - startSingleThread).count();
    std::cout << "Single-thread execution time: " << durationSingleThread << " ms\n";

    if (size <= 10) {
        std::cout << "\nMatrix after replacing diagonal with max column values:\n";
        MatrixOperations::printMatrix(matrix, size);
    }

    MatrixOperations::freeMatrix(matrix);

    return 0;
}
