#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

const int N = 9;

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            std::cout << std::setw(2) << grid[row][col] << " ";
        std::cout << std::endl;
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    return true;
}

bool solveSudoku(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N)
        return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);
    std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_shuffle(numbers.begin(), numbers.end());
    for (int num : numbers) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0;
    }
    return false;
}

void randomizeGrid(int grid[N][N]) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;
    }
    solveSudoku(grid, 0, 0);
    int k = 12; //difficulty
    for (int i = 0; i < N * N - k; i++) {
        int row = std::rand() % N;
        int col = std::rand() % N;
        if (grid[row][col] != 0)
            grid[row][col] = 0;
        else
            i--;
    }
}

int main() {
    int grid[N][N] = {0};
    randomizeGrid(grid);

    std::cout << "Randomized Sudoku Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        std::cout << "\nSudoku solved successfully!\n";
        printGrid(grid);
    } else {
        std::cout << "No solution exists";
    }

    return 0;
}
