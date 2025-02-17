#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>

static const int SIZE = 20000;
static int matrix[SIZE][SIZE];

class MatrixOperations {
public:
    static void fillMatrix(int* matrix, int size) {
        std::mt19937 rng(111);
        std::uniform_int_distribution<int> dist(1, 10000);

        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                matrix[row * size + col] = dist(rng);
            }
        }
    }
};

int main() {
    int size;
    std::cout << "Enter size of matrix: ";
    std::cin >> size;

    return 0;
}
