# ✍️ 37. Sudoku Solver

<p align="center">
  <img src="https://img.shields.io/badge/Difficulty-Hard-red" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue" alt="Language" />
  <a href="https://leetcode.com/problems/sudoku-solver/">
    <img src="https://img.shields.io/badge/Problem%20Link-LeetCode-brightgreen" alt="Problem Link" />
  </a>
</p>

---

## 📝 Problem Statement

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of the grid.

The `.` character indicates empty cells. It is **guaranteed** that the input board has only one solution.

---

## 🖼️ Visuals

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png" alt="Sudoku Input" style="margin-right: 20px;"/>
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Sudoku-by-L2G-20050714_solution.svg/250px-Sudoku-by-L2G-20050714_solution.svg.png" alt="Sudoku Solution"/>
</p>

---

## ⚙️ Constraints

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` is a digit or `.`.
- The input board has only one solution.

---

## 🧪 Examples

| Input Board                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       | Output (Solved Board)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `[["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]` | `[["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]` |

---

## 🧠 Approach

The problem asks us to fill a 9x9 Sudoku grid. Since there's no direct formula, we have to try placing numbers in empty cells and see if they lead to a valid solution. This trial-and-error process is a perfect fit for **backtracking**.

The core idea is to simulate how a human would solve the puzzle:
1.  **Scan the Grid**: Traverse the grid from top-left (`[0][0]`) to bottom-right (`[8][8]`).
2.  **Find an Empty Cell**: When we find an empty cell (marked with a `.`), we pause and try to fill it.
3.  **Try Numbers (1-9)**: For the empty cell, we try placing each digit from '1' to '9'.
4.  **Check Validity**: Before placing a digit, we must check if it's a valid move. A move is valid if the digit doesn't already exist in the current:
    -   Row
    -   Column
    -   3x3 sub-grid
5.  **Recurse & Explore**: If the digit is valid, we place it on the board and recursively call our solver function to continue filling the rest of the board.
6.  **Backtrack**:
    -   If the recursive call returns `true`, it means a solution was found down the line, so we also return `true`.
    -   If the recursive call returns `false`, it means our current placement led to a dead end. We must **undo** the move (change the cell back to `.`) and try the next digit.
7.  **No Solution Found**: If we try all digits from '1' to '9' in the current empty cell and none of them lead to a solution, we return `false` to the previous recursive call, signaling that a prior decision was incorrect.
8.  **Base Case**: If we successfully traverse the entire grid without finding any more empty cells, it means the puzzle is solved, and we return `true`.

This "Choose, Explore, Un-choose" pattern is the classic backtracking template.

<details>
<summary><strong>Detailed Walkthrough of `isValid` and Box Calculation</strong></summary>

### The `isValid` Helper
This function is crucial. Given a `board`, a cell `(row, col)`, and a digit `d`, it checks three things:
1.  **Row Check**: Iterate from `i = 0` to `8` and check if `board[row][i] == d`.
2.  **Column Check**: Iterate from `i = 0` to `8` and check if `board[i][col] == d`.
3.  **3x3 Box Check**: This is the trickiest. We first need to find the top-left corner of the 3x3 box that `(row, col)` belongs to. A simple formula for this is:
   -   `start_row = (row / 3) * 3`
   -   `start_col = (col / 3) * 3`

   For example, if we're at cell `(4, 7)`:
   -   `start_row = (4 / 3) * 3 = 1 * 3 = 3`
   -   `start_col = (7 / 3) * 3 = 2 * 3 = 6`
   So, the top-left corner of the box is `(3, 6)`.

   Once we have the corner, we can iterate through the 3x3 box from `start_row` to `start_row + 2` and `start_col` to `start_col + 2` to check for the digit `d`.

If all three checks pass, the function returns `true`; otherwise, `false`.
</details>

---

## 💻 Solution Code

Here is the C++ implementation using the backtracking approach.

```cpp
// Intuition:
// The problem requires filling a Sudoku grid, which involves making choices and potentially reversing them if they lead to an invalid state. This is a classic application of backtracking. We can simulate the process of trying a number in an empty cell, recursively trying to solve the rest of the grid, and backtracking if our initial choice was wrong.

// Approach:
// 1. Create a recursive function `solve(board)`.
// 2. Iterate through each cell of the 9x9 board from top-left to bottom-right.
// 3. If a cell contains a '.', it's an empty cell that needs to be filled.
// 4. For this empty cell, try placing each digit from '1' to '9'.
// 5. For each digit, check its validity using a helper function `isValid()`.
//    - `isValid()` checks if the digit is already present in the current row, column, and the 3x3 sub-grid.
// 6. If the digit is valid:
//    a. Place the digit in the cell (the "do" step).
//    b. Make a recursive call to `solve(board)` to solve the rest of the board.
//    c. If the recursive call returns `true`, it means a solution was found, so we return `true` up the call stack.
//    d. If it returns `false`, our placement was incorrect. We must backtrack by resetting the cell to '.' (the "undo" step) and try the next digit.
// 7. If we try all 9 digits and none lead to a solution, return `false` to indicate failure for this path.
// 8. If the initial nested loops complete without finding any empty cells ('.'), it means the board is already solved, so return `true`.

// Time Complexity:
// O(9^m), where 'm' is the number of empty cells. In the worst-case scenario, for each of the 'm' empty cells, we might have to try up to 9 different digits. Since the board size is fixed (m <= 81), this is technically a very large constant, so it can be considered O(1).

// Space Complexity:
// O(m) or O(81), representing the maximum depth of the recursion stack. For a fixed-size 9x9 board, the recursion depth is at most 81 (the number of cells). Thus, the space complexity is constant, O(1).
class Solution {
public:

    // Checks if placing digit 'd' at board[row][col] is valid
    bool isValid(vector<vector<char>>& board, int row, int col, char d) {
        for(int i = 0; i < 9; i++) {
            // Check the column for the same digit
            if(board[i][col] == d)
                return false;
            
            // Check the row for the same digit
            if(board[row][i] == d) {
                return false;
            }
        }

        // Determine the top-left corner of the 3x3 sub-grid
        int start_i = row/3 * 3;
        int start_j = col/3 * 3;

        // Check the 3x3 sub-grid for the same digit
        for(int k = 0; k < 3; k++) {
            for(int l = 0; l < 3; l++) {
                if(board[start_i+k][start_j+l] == d) {
                    return false;
                }
            }
        }

        // If no conflicts are found, the placement is valid
        return true;
    }

    // Main recursive backtracking function
    bool solve(vector<vector<char>>& board) {
        // Iterate through each cell of the grid
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                // Find an empty cell
                if(board[i][j] == '.') {

                    // Try placing digits '1' through '9'
                    for(char d = '1'; d <= '9'; d++) { 

                        // Check if the current digit is a valid placement
                        if(isValid(board, i, j, d)) {
                            // Place the digit (Do)
                            board[i][j] = d;

                            // Recurse to solve the rest of the board (Explore)
                            if(solve(board) == true) {
                                return true; // Solution found
                            }

                            // If recursion fails, backtrack (Undo)
                            board[i][j] = '.';
                        }

                    }

                    // If no digit works, return false to trigger backtracking in parent calls
                    return false;
                }
            }
        }
        // If all cells are filled (no '.' found), the puzzle is solved
        return true;
    }

    // Wrapper function to initiate the solver
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};

/*
*
* Dry Run
* Let's trace the first empty cell at board[0][2] from the example.
*
* Initial Board (partial view):
* [["5","3",".",...],
* ["6",".",".",...],
* ...]
*
* 1. `solve(board)` is called. The loops run until they find the empty cell at `i=0, j=2`.
* 2. The inner loop `for(char d = '1'; d <= '9'; d++)` starts for this cell.
* 3. **Try d = '1'**:
* - `isValid(board, 0, 2, '1')` is called.
* - Row check: '1' is not in row 0.
* - Column check: '1' is not in column 2.
* - Box check: '1' is not in the top-left 3x3 box.
* - `isValid` returns `true`.
* 4. **Do**: `board[0][2]` is set to '1'.
* 5. **Explore**: `solve(board)` is called recursively with the updated board.
* 6. The new `solve` call will continue from `(0,3)` trying to find the next empty cell and solve from there.
*
* Let's assume this path eventually fails (returns `false`).
*
* 7. The `if(solve(board) == true)` condition is false.
* 8. **Undo**: The code backtracks. `board[0][2]` is reset to '.'.
* 9. The loop continues to the next digit.
* 10. **Try d = '2'**: `isValid` is called. Assume it's valid.
* 11. **Do**: `board[0][2]` is set to '2'.
* 12. **Explore**: `solve(board)` is called again.
*
* This process continues. Eventually, it will try `d = '4'`, which is part of the final solution. The recursive call with `board[0][2] = '4'` will eventually return `true`, causing the entire chain of recursive calls to return `true`, and the solved board is finalized.
*
*/
```

---

## 💡 Key Insights

-   **Backtracking is a natural fit** for problems that involve searching for a solution by exploring all possibilities and pruning invalid paths.
-   The "do, explore, undo" pattern is the fundamental structure of a backtracking algorithm.
-   Breaking down the validation logic (`isValid` function) into smaller, manageable checks (row, column, box) simplifies the code and makes it easier to debug.
-   The formula `(index / 3) * 3` is a clever and efficient way to find the starting coordinate of any 3x3 sub-grid.

---

## 🚀 Further Exploration

-   **Optimization**: Instead of iterating through the whole board every time in the recursive call, you could pass the current `row` and `col` to the next call to start searching from where you left off.
-   **Bitmasking**: For a more optimized `isValid` check, you can use bitmasks to represent the numbers used in each row, column, and box. This can make the validation checks O(1).
-   **Related Problems**:
    -   [Valid Sudoku (LeetCode 36)](https://leetcode.com/problems/valid-sudoku/): The prerequisite for this problem.
    -   [N-Queens (LeetCode 51)](https://leetcode.com/problems/n-queens/): Another classic backtracking problem.

---

## 📚 References

-   [LeetCode Problem Page](https://leetcode.com/problems/sudoku-solver/)
-   [Backtracking Template](https://en.wikipedia.org/wiki/Backtracking)

---

## 🏷️ Tags

`Backtracking` `Array` `Matrix` `Recursion`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/sudoku-solver/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)

---
This video offers a straightforward explanation of the backtracking logic applied to the Sudoku Solver problem.
[Sudoku Solver Explained | Leetcode 37](https://www.youtube.com/watch?v=5g6fheUtjRs)