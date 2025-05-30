#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

const int board_size = 8;
int queen_col_in_row[board_size];

bool threat(int r1, int c1, int r2, int c2) {
    return (r1 == r2 || c1 == c2 || abs(r1 - r2) == abs(c1 - c2));
}

bool safe_to_put_at(int row, int col,vector<vector<string>>&blocked_cells) {
    if (blocked_cells[row][col] == "*")
        return false;
    
    for (int prev_row = 0; prev_row < row; prev_row++)
        if (threat(row, col, prev_row, queen_col_in_row[prev_row]))
            return false;

    return true;
}

void solve(int row, int& solutions_count,vector<vector<string>>&blocked_cells) {
    if (row == board_size) {
        solutions_count++;
        return;
    }
        
    for (int col = 0; col < board_size; col++) {
        if (safe_to_put_at(row, col,blocked_cells)) {
            queen_col_in_row[row] = col; 
            solve(row + 1, solutions_count,blocked_cells); 
            queen_col_in_row[row] = -1;
        }
    }
}
vector<vector<string>> handleInput(){
    vector<vector<string>> blocked_cells(board_size, vector<string>(board_size));

    for (int i = 0; i < board_size; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        for (int j = 0; j < board_size; ++j) {
            char ch; 
            iss >> ch;
            blocked_cells[i][j] = string(1, ch); 
        }
    }
    return blocked_cells;
}
int main() {
    
    vector<vector<string>> blocked_cells = handleInput();
    for (int row = 0; row < board_size; row++)
        queen_col_in_row[row] = -1;

    int count = 0;
    solve(0, count,blocked_cells);
    cout <<count << endl;

    return 0;
}