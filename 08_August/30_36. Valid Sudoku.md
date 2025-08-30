<div align="center">

# ✨ 36. Valid Sudoku ✨

[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)](https://leetcode.com/problems/valid-sudoku/description/)

</div>

<div align="center">

![Tag](https://img.shields.io/badge/Array-blue)
![Tag](https://img.shields.io/badge/Hash%20Table-blueviolet)
![Tag](https://img.shields.io/badge/Matrix-orange)

</div>

---

## 📝 Problem Statement

Determine if a `9 x 9` Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1.  Each row must contain the digits `1-9` without repetition.
2.  Each column must contain the digits `1-9` without repetition.
3.  Each of the nine `3 x 3` sub-boxes of the grid must contain the digits `1-9` without repetition.

> **Note:**
> * A Sudoku board (partially filled) could be valid but is not necessarily solvable.
> * Only the filled cells need to be validated according to the mentioned rules.

---

## 🖼️ Examples

<details>
<summary><strong>Example 1 (Click to Expand)</strong></summary>

| Input | Output |
| :--- | :--- |
| `board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]` | `true` |

<div align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png" alt="Valid Sudoku Board" width="250"/>
</div>

</details>

<details>
<summary><strong>Example 2 (Click to Expand)</strong></summary>

| Input | Output |
| :--- | :--- |
| `board = [["8","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".",3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]` | `false` |

**Explanation:** Same as Example 1, except with the `5` in the top left corner being modified to `8`. Since there are two `8`'s in the top left 3x3 sub-box, it is invalid.

</details>

---

## 📊 Constraints

-   `board.length == 9`
-   `board[i].length == 9`
-   `board[i][j]` is a digit `1-9` or `'.'`.

---

## 🧠 Approach

The core of this problem is efficiently checking for duplicates across three different dimensions: rows, columns, and 3x3 sub-boxes. A **hash set** is the perfect data structure for this task due to its $O(1)$ average time complexity for insertions and lookups.

<details>
<summary><strong>Approach 1: Brute-Force (3 Passes)</strong></summary>

This is the most direct and intuitive method, perfectly mirroring the problem's rules. We perform three separate sweeps over the board.

1.  **Validate Rows:** We iterate through each of the 9 rows. For each row, we use a *new hash set*. As we traverse the cells in that row, we check if the current number is already in our set.
    * If it is, we've found a duplicate, and the board is **invalid**. We can immediately return `false`.
    * Otherwise, we add the number to the set and continue.

2.  **Validate Columns:** Next, we do the same for columns. We iterate through each of the 9 columns, using a fresh hash set for each one to check for duplicates.

3.  **Validate 3x3 Sub-boxes:** Finally, we check the 9 sub-boxes. This can be done with nested loops that advance by 3 (e.g., `sr` from 0 to 8, `sc` from 0 to 8, with `sr+=3`, `sc+=3`). For each sub-box, we again use a hash set to find duplicates.

If the function completes all three sweeps without finding any duplicates, the board is **valid**, and we return `true`.
</details>

<details>
<summary><strong>Approach 2: Optimized (Single Pass)</strong></summary>

A smarter way is to combine all three checks into a single pass over the board. This avoids repetitive code and can be more efficient.

The key idea is to store a **unique representation** for each number's placement. We can use strings for this.

1.  **Single Iteration & Hash Set:** We'll use a single hash set that stores strings. We traverse the 9x9 board cell by cell.

2.  **Unique String Identifiers:** For each non-empty cell `(i, j)` with value `c`, we generate three unique strings:
    * A string for the row: `string row_key = to_string(c) + " found in row " + to_string(i);`
    * A string for the column: `string col_key = to_string(c) + " found in col " + to_string(j);`
    * A string for the 3x3 box: `string box_key = to_string(c) + " found in box " + to_string(i/3) + "-" + to_string(j/3);`

3.  **Validation Check:** Before inserting these three strings into our set, we check if any of them already exist.
    * If `st.count(row_key)` is true, it means we've seen this number in this row before. The board is **invalid**.
    * The same logic applies to the `col_key` and `box_key`.
    * If none of the keys exist, we add all three to the set and move to the next cell.

If we successfully iterate through the entire board, it means no duplicates were found, and the board is **valid**.
</details>

---

## 💻 Solution Code

### Approach 1: Brute-Force (3 Passes)

```cpp
// Intuition: The problem requires checking three conditions: no duplicates in any row, column, or 3x3 sub-box. The most straightforward way is to check each condition separately across the entire board.
// Approach:
// 1. Iterate through each row and use a hash set to check for duplicates. If a duplicate is found, return false.
// 2. Iterate through each column and use a hash set to check for duplicates. If a duplicate is found, return false.
// 3. Iterate through each of the nine 3x3 sub-boxes. A helper function is used for this. For each sub-box, use a hash set to detect duplicates. If found, return false.
// 4. If all checks pass, the Sudoku board is valid, so return true.
// Time Complexity: O(N^2), where N=9. We traverse the 9x9 board three times. Since N is fixed at 9, the complexity is constant, O(81 * 3) -> O(1).
// Space Complexity: O(N), for the hash set used to store up to 9 unique numbers for each row, column, or box check. This is also O(1) as N is fixed.
class Solution {
public:
    // Helper function to validate a single 3x3 sub-box
    bool validSub(vector<vector<char>>& board, int sr, int er, int sc, int ec) {
        unordered_set<char> st; // Use a hash set to track numbers in the current sub-box
        for(int row = sr; row <= er; row++) {
            for(int col = sc; col <= ec; col++) {
                char ch = board[row][col];
                if(ch == '.') continue; // Ignore empty cells
                if(st.count(ch)) return false; // If number is already in the set, it's a duplicate
                st.insert(ch); // Add the new number to the set
            }
        }
        return true; // The sub-box is valid
    }
    
    bool isValidSudoku(vector<vector<char>>& board) {
        // 1. Validate all rows
        for(int row = 0; row < 9; row++) {
            unordered_set<char> st;
            for(int col = 0; col < 9; col++) {
                char ch = board[row][col];
                if(ch == '.') continue;
                if(st.count(ch)) return false;
                st.insert(ch);
            }
        }
        
        // 2. Validate all columns
        for(int col = 0; col < 9; col++) {
            unordered_set<char> st;
            for(int row = 0; row < 9; row++) {
                char ch = board[row][col];
                if(ch == '.') continue;
                if(st.count(ch)) return false;
                st.insert(ch);
            }
        }
        
		// 3. Validate each 3x3 sub-box
        for(int sr = 0; sr < 9; sr += 3) {
            int er = sr + 2; // Calculate ending row
            for(int sc = 0; sc < 9; sc += 3) {
                int ec = sc + 2; // Calculate ending column
                if(!validSub(board, sr, er, sc, ec)) // Check the sub-box
                    return false;
            }
        }
        
        return true; // If all checks pass, the board is valid
    }
};

/*
*
* Dry Run
* Consider the cell board[0][0] = '5'.
* Row Check: `st` for row 0 will contain {'5'}.
* Column Check: `st` for col 0 will contain {'5'}.
* Box Check: `st` for box (0,0) will contain {'5'}.
* Now consider board[0][1] = '3'.
* Row Check: `st` for row 0 becomes {'5', '3'}.
* If later in row 0, another '5' appears (e.g., board[0][8] = '5'), `st.count('5')` would be true, and we would return false.
*
*/
```

### Approach 2: Optimized (Single Pass)

```cpp
// Intuition: Instead of three separate passes, we can verify all conditions simultaneously in a single pass. The key is to create a unique identifier for each number's position within its row, column, and 3x3 box.
// Approach:
// 1. Iterate through the 9x9 board with a single nested loop (i from 0 to 8, j from 0 to 8).
// 2. For each cell (i, j) containing a number, create three distinct strings:
//    - Row identifier: e.g., "5_row_0" for number '5' in row 0.
//    - Column identifier: e.g., "5_col_3" for number '5' in column 3.
//    - Box identifier: e.g., "5_box_0_1" for number '5' in the box at (0/3, 3/3) -> (0,1).
// 3. Use a single hash set to store all these string identifiers.
// 4. Before inserting, check if any of the three strings for the current number already exist in the set.
//    - If yes, a duplicate is found, and the board is invalid. Return false.
//    - If no, insert all three strings into the set and proceed.
// 5. If the entire board is traversed without conflicts, return true.
// Time Complexity: O(N^2), where N=9. We traverse the board only once. Since N is fixed, this is O(1).
// Space Complexity: O(N^2). In the worst-case (a full board), the set will store 3 * 81 strings. This is also O(1) as N is fixed.
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> st; // A single set to store all unique identifiers
        
        // Iterate through the entire board once
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(board[i][j] == '.') continue; // Skip empty cells
                
                // Create unique string identifiers for the number in its row, column, and box
                string row = string(1, board[i][j]) + "_row_" + to_string(i);
                string col = string(1, board[i][j]) + "_col_" + to_string(j);
                string box = string(1, board[i][j]) + "_box_" + to_string(i/3) + "_" + to_string(j/3);
                
                // Check if any of these identifiers already exist in the set
                if(st.count(row) || st.count(col) || st.count(box)) {
                    return false; // Duplicate found
                }
                
                // Insert the new identifiers into the set
                st.insert(row);
                st.insert(col);
                st.insert(box);
            }
        }
        
        return true; // Board is valid
    }
};

/*
*
* Dry Run
* Let's say board[1][3] = '1'.
* i=1, j=3. The number is '1'.
* 1. Create row string: "1_row_1"
* 2. Create col string: "1_col_3"
* 3. Create box string: "1_box_0_1" (since i/3=0, j/3=1)
* Check if any of these are in the set `st`. Assume they are not.
* Insert all three strings into `st`.
*
* Now, let's say board[1][8] = '1'.
* i=1, j=8. The number is '1'.
* 1. Create row string: "1_row_1"
* 2. Create col string: "1_col_8"
* 3. Create box string: "1_box_0_2"
* When we check `st.count("1_row_1")`, it will return true because we inserted it for board[1][3].
* The condition `st.count(row)` becomes true, and the function immediately returns false.
*
*/
```

---

## 🔑 Key Insights

* **Hash Set Efficiency:** Both solutions leverage the $O(1)$ average time complexity of hash set operations, which is ideal for checking for duplicates efficiently.
* **Single-Pass Elegance:** The second approach is a great example of how creative data representation (using unique strings) can simplify code structure, reducing three loops to one.
* **Box Indexing Trick:** The formula `(row/3, col/3)` is a classic, clean way to map any cell coordinate to its corresponding 3x3 sub-box, a useful pattern in many grid-based problems.

---

## 🚀 Further Exploration

* 🧩 **Sudoku Solver:** Challenge yourself with the next step: [LeetCode 37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/). This requires you to fill the board using algorithms like backtracking.
* 🎭 **Bitmasking:** For a more memory-efficient solution, you can use bitmasks. A 9-bit integer can represent the numbers in a row, column, or box, where the i-th bit indicates the presence of the number `i+1`. This avoids using hash sets and strings.

---

## 🔗 References

* [Wikipedia: Sudoku](https://en.wikipedia.org/wiki/Sudoku)
* [GeeksForGeeks: Valid Sudoku](https://www.geeksforgeeks.org/check-if-given-sudoku-board-configuration-is-valid-or-not/)

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/valid-sudoku/description/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)