#include "Sudoku.h"

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Open the input file.
    ifstream fin("puzzle_7.txt");

    // Test whether the input file was successfully opened.
    if (!fin) {
        cout << "[Error] Nonexistent input file" << endl;
        system("pause");
        return -1;
    }

    // Open the output file.
    ofstream fout("solution.txt");

    Sudoku puzzle;  // Create a Sudoku puzzle.
    puzzle.load_data(fin);  // Load the puzzle from the input file.
    puzzle.solve(fout);  // Solve the puzzle.

    // Close the input and output file.
    fin.close();
    fout.close();

    return 0;
}