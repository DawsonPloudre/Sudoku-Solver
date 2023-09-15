#include "Sudoku.h"

#include <string>

using std::endl;

// Static data field
const char Sudoku::BLANK = '.';

// Default constructor
Sudoku::Sudoku() : solved(false) {
    board = new char* [16];
    for (size_t row = 0; row < 16; row++) { board[row] = new char[16]; }
}

// Copy constructor
Sudoku::Sudoku(const Sudoku& other) {
    board = NULL;
    *this = other;
}

// Destructor
Sudoku::~Sudoku() {
    for (size_t row = 0; row < 16; row++) { delete[] board[row]; }
    delete[] board;
}

// Deep-copy assignment operator
const Sudoku& Sudoku::operator = (const Sudoku& rhs) {
    if (this != &rhs) {
        if (board) {
            for (size_t row = 0; row < 16; row++) { delete[] board[row]; }
            delete[] board;
            board = NULL;
        }
        solved = rhs.solved;
        board = new char* [16];
        for (size_t row = 0; row < 16; row++) {
            board[row] = new char[16];
            for (size_t col = 0; col < 16; col++) { board[row][col] = rhs.board[row][col]; }
        }
    }
    return *this;
}

/** Reads the puzzle from an input stream.
    @param in: an input stream to read the puzzle
*/
void Sudoku::load_data(istream& in) {
    char ch;
    for (size_t row = 0; row < 16; row++) {
        for (size_t col = 0; col < 16; col++) {
            in >> ch;
            board[row][col] = ch;
        }
    }
}

bool Sudoku::valid(size_t row, size_t col, char ch) {
    return(!in_same_row(row, ch) && !in_same_col(col, ch) && !in_same_grid(row, col, ch));
}
/** Tests whether a digit already appears in a row.
    @param row: index of the row to search
    @param digit: digit to test
    @return: {true} if the digit is found in the row; {false} otherwise
*/
bool Sudoku::in_same_row(size_t row, char digit) const {
    for (size_t col = 0; col < 16; col++) {
        if (digit == board[row][col]) { return true; }
    }
    return false;
}

/** Tests whether a digit already appears in a column.
    @param col: index of the column to search
    @param digit: digit to test
    @return: {true} if the digit is found in the column; {false} otherwise
*/
bool Sudoku::in_same_col(size_t col, char digit) const {
    for (size_t row = 0; row < 16; row++) {
        if (digit == board[row][col]) { return true; }
    }
    return false;
}

/** Tests whether a digit already appears in the 3-by-3 grid a cell resides in.
    @param row: row index of the cell
    @param col: column index of the cell
    @param digit: digit to test
    @return: {true} if the digit is found in the grid; {false} otherwise
*/
bool Sudoku::in_same_grid(size_t row, size_t col, char digit) const {
    int BoxRow = row - row % 4;
    int BoxCol = col - col % 4;
    for (size_t i = BoxRow; i < BoxRow + 4; i++) {
        for (size_t j = BoxCol; j < BoxCol + 4; j++) {
            if (board[i][j] == digit) { return true; }
        }
    }
    return false;
}

/** Finds the row index of the next cell in row-major order.
    @param row: row index of the current cell
    @param col: column index of the current cell
    @return: row index of the next cell
*/
size_t Sudoku::next_row_index(size_t row, size_t col) const {
    if (col == 15) { return row + 1; }
    else { return row; }
}

/** Finds the column index of the next cell in row-major order.
    @param row: row index of the current cell
    @param col: column index of the current cell
    @return: column index of the next cell
*/
size_t Sudoku::next_col_index(size_t row, size_t col) const {
    if (col == 15) { return 0; }
    else { return col + 1; }
}

/** Solves the puzzle beginning with some cell.
    @param row: row index of the beginning cell
    @param col: column index of the beginning cell
    @param out: output stream to write output
    */
void Sudoku::solve(size_t row, size_t col, ostream& out) {
    char chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    // Base case
    if (row == 16) {
        print_solution(out);
    }
    else {
        // If the current cell is not blank, then go to the next cell.
        if (board[row][col] != BLANK) { solve(next_row_index(row, col), next_col_index(row, col), out); }

        else {  // Current cell is blank.
            for (int digit = 0; digit <= 15; digit++) {
                if (!valid(row, col, chars[digit])) { continue; }

                // Fill the cell with the digit.
                board[row][col] = chars[digit];

                // Go to the next cell and solve the puzzle recursively.
                solve(next_row_index(row, col), next_col_index(row, col), out);

                // If no solution found, change the cell back to blank and try the next digit.
                board[row][col] = BLANK;
            }
        }
    }
}

// Wrapper function
void Sudoku::solve(ostream& out) { solve(0, 0, out); }

/** Writes the solution to an output stream.
    @param out: an output stream to write the solution
*/
void Sudoku::print_solution(ostream& out) {
    // Write the solution number.
    out << "Solution " << ++num_of_solutions << endl << endl;
    //Write the sudoku puzzle
    for (size_t row = 0; row < 16; row++) {
        for (size_t col = 0; col < 16; col++) {
            out << board[row][col];
        }
        out << endl;
    }
    out << endl << endl;
}