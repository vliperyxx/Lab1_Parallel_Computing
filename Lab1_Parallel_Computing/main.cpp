#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>


class MatrixOperations {
public:
    static int* allocateMatrix(int size) {
        return new int[size * size];
    }

    static void freeMatrix(int* matrix) {
        delete[] matrix;
    }

    static void fillMatrix(int* matrix, int size) {
        std::mt19937 rng(111);
        std::uniform_int_distribution<int> dist(1, 10000);

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                matrix[row * size + col] = dist(rng);
            }
        }
    }

    static void calculateMaxOfColumn(int* matrix, int size, int col) {
        if (col >= size) return;

        int maxVal = matrix[col];
        for (int row = 1; row < size; row++) {
            maxVal = std::max(maxVal, matrix[row * size + col]);
        }
        matrix[col] = maxVal;  
    }

    static void calculateAllMax(int* matrix, int size) {
        for (int col = 0; col < size; col++) {
            calculateMaxOfColumn(matrix, size, col);
        }
    }
};

int main() {
    int size;
    std::cout << "Enter size of matrix: ";
    std::cin >> size;

    int* matrix = MatrixOperations::allocateMatrix(size);
    MatrixOperations::fillMatrix(matrix, size);

    auto startSingleThread = std::chrono::high_resolution_clock::now();
    MatrixOperations::calculateAllMax(matrix, size);
    auto endSingleThread = std::chrono::high_resolution_clock::now();

    double durationSingleThread = std::chrono::duration<double, std::milli>(endSingleThread - startSingleThread).count();
    std::cout << "Single-thread execution time: " << durationSingleThread << " ms\n";

    MatrixOperations::freeMatrix(matrix);

    return 0;
}
