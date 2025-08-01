# 🟩 118. Pascal's Triangle

[![LeetCode](https://img.shields.io/badge/LeetCode-118-orange?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/pascals-triangle/description/)
![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![MIT License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

---

> ⚡️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the [LeetCode problem "Pascal's Triangle"](https://leetcode.com/problems/pascals-triangle/description/).

---

<div align="center">

<img src="https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif" width="350" alt="Pascal's triangle gif" />

</div>

---

## 📖 Problem Statement

Given an integer `numRows`, return the first `numRows` of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

```
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

---

## 🧮 Examples

| Input         | Output                                      |
| ------------- | ------------------------------------------- |
| `numRows = 5` | `[[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]` |
| `numRows = 1` | `[[1]]`                                     |

<details>
<summary><b>Example Walkthrough</b></summary>

- For `numRows = 5`, the triangle is:
  ```
  [
      [1],
      [1,1],
      [1,2,1],
      [1,3,3,1],
      [1,4,6,4,1]
  ]
  ```
  </details>

---

## 🚦 Constraints

- `1 <= numRows <= 30`

---

## 🛠️ Approach

### 🚀 Efficient Binomial Coefficient (O(numRows²))

We use the binomial coefficient property to generate each row:

Every element at position `col` in row `row` is:

```
C(row - 1, col) = C(row - 1, col-1) * (row - col) / col
```

This avoids repeated calculations and overflows by using a running product.

---

### 💻 C++ Solution

```cpp
// Intuition: Build Pascal's Triangle row by row using the binomial coefficient formula.
// Approach: For each row, start with 1 and use a running product to generate the next element.
// Time Complexity: O(numRows^2) - Each row has up to numRows elements.
// Space Complexity: O(numRows^2) - For storing the triangle.
class Solution {
public:
    // Generate a single row using binomial property
    vector<int> generateRow(int row) {
        long long ans = 1;
        vector<int> ansRow;
        ansRow.push_back(1); // First value is always 1
        for (int col = 1; col < row; col++) {
            ans = ans * (row - col); // Multiply by decreasing numerator
            ans = ans / col;         // Divide by increasing denominator
            ansRow.push_back((int)ans);
        }
        return ansRow;
    }

    // Generate all rows up to numRows
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        for (int row = 1; row <= numRows; row++) {
            triangle.push_back(generateRow(row));
        }
        return triangle;
    }
};

/*
*
* Dry Run
*
* numRows = 5
* Row 1: [1]
* Row 2: [1, 1]
* Row 3: [1, 2, 1]
* Row 4: [1, 3, 3, 1]
* Row 5: [1, 4, 6, 4, 1]
* Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
*/
```

---

### 💻 Java Solution

```java
// Intuition: Build Pascal's Triangle using the binomial coefficient for each element.
// Approach: For each row, start with 1 and use the running product formula to generate each value efficiently.
// Time Complexity: O(numRows^2) - The triangle has numRows rows and up to numRows elements per row.
// Space Complexity: O(numRows^2) - To store the entire triangle result.
class Solution {
    // Generate a single row using binomial property
    public List<Integer> generateRow(int row){
        long ans = 1;
        List<Integer> ansRow = new ArrayList<>();
        ansRow.add(1); // First element is always 1
        for(int col = 1; col < row; col++){
            ans = ans * (row - col); // Multiply by decreasing numerator
            ans = ans / col;         // Divide by increasing denominator
            ansRow.add((int)ans);
        }
        return ansRow;
    }

    // Generate all rows up to numRows
    public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> triangle = new ArrayList<>();
        for(int row = 1; row <= numRows; row++){
            triangle.add(generateRow(row));
        }
        return triangle;
    }
}

/*
*
* Dry Run
*
* numRows = 5
* Row 1: [1]
* Row 2: [1, 1]
* Row 3: [1, 2, 1]
* Row 4: [1, 3, 3, 1]
* Row 5: [1, 4, 6, 4, 1]
* Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
*/
```

---

## 💡 Key Insights

- Each element of Pascal's Triangle can be computed directly using binomial coefficients.
- Using a running product avoids overflow and extra computation.
- This approach is both efficient and numerically stable for the problem's constraints.

---

## 🔗 Further Exploration

- [119. Pascal's Triangle II](https://leetcode.com/problems/pascals-triangle-ii/) — Generate only the k-th row in O(k) space.
- [Sum of elements in the nth row](https://math.stackexchange.com/questions/67054/sum-of-coefficients-in-pascals-triangle) — It's always 2ⁿ.
- Applications in combinatorics, probability, and algebra (e.g., binomial expansion).

---

## 📚 References

- [LeetCode Problem Page](https://leetcode.com/problems/pascals-triangle/description/)
- [Wikipedia: Pascal's Triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle)

---

## 🙋‍♂️ Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Tag](https://img.shields.io/badge/tag-pascal's%20triangle-blue.svg?style=flat-square)
![Tag](https://img.shields.io/badge/tag-math-grey.svg?style=flat-square)
![Tag](https://img.shields.io/badge/tag-combinatorics-orange.svg?style=flat-square)
![Tag](https://img.shields.io/badge/tag-leetcode-lightgrey.svg?style=flat-square)

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/pascals-triangle/description/) for original content and copyright.**
