# 📍 3516. Find Closest Person

<div align="center">
  <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Topic-Math-blue?style=for-the-badge" alt="Topic: Math" />
  <img src="https://img.shields.io/badge/Topic-Simulation-yellow?style=for-the-badge" alt="Topic: Simulation" />
</div>

---

### **[Problem Link](https://leetcode.com/problems/find-closest-person/description/)**

---

## 📝 Problem Statement

You are given three integers `x`, `y`, and `z`, representing the positions of three people on a number line:
- `x` is the position of Person 1.
- `y` is the position of Person 2.
- `z` is the position of Person 3, who does not move.

Both Person 1 and Person 2 move toward Person 3 at the **same** speed.

Determine which person reaches Person 3 **first**:
- Return `1` if Person 1 arrives first.
- Return `2` if Person 2 arrives first.
- Return `0` if both arrive at the **same** time.

Return the result accordingly.

---

## ⛓️ Constraints

- `1 <= x, y, z <= 100`

---

##  Examples

| Input | Output | Explanation |
| :--- | :---: | :--- |
| `x = 2, y = 7, z = 4` | `1` | Person 1 is at pos 2, needs 2 steps. Person 2 is at pos 7, needs 3 steps. Person 1 is first. |
| `x = 2, y = 5, z = 6` | `2` | Person 1 is at pos 2, needs 4 steps. Person 2 is at pos 5, needs 1 step. Person 2 is first. |
| `x = 1, y = 5, z = 3` | `0` | Person 1 is at pos 1, needs 2 steps. Person 2 is at pos 5, needs 2 steps. Both arrive at the same time. |

---

## 🧠 Approach

The core of the problem is to determine which person is closer to Person 3. Since both Person 1 and Person 2 move at the same speed, the one with the shorter distance to Person 3 will arrive first.

Distance is always a non-negative value. The position can be on a number line, so Person 1 or 2 could be on either side of Person 3. To find the distance, we calculate the absolute difference between their positions.

1.  **Calculate Distance 1:** The distance between Person 1 (at `x`) and Person 3 (at `z`) is `abs(x - z)`.
2.  **Calculate Distance 2:** The distance between Person 2 (at `y`) and Person 3 (at `z`) is `abs(y - z)`.
3.  **Compare Distances:**
    - If `abs(x - z) < abs(y - z)`, Person 1 is closer and arrives first. Return `1`.
    - If `abs(x - z) > abs(y - z)`, Person 2 is closer and arrives first. Return `2`.
    - If `abs(x - z) == abs(y - z)`, they are equidistant and arrive at the same time. Return `0`.

This simple comparison of absolute distances directly gives us the solution.

---

## 💻 Solution Code

### Simple Solution (C++)
```cpp
// Intuition: The problem asks to find which of two people reaches a third person first. Since their speeds are identical, the person who is physically closer will arrive first. The distance on a number line is the absolute difference between positions.
// Approach:
// 1. Calculate the distance for Person 1 to Person 3: dist1 = abs(x - z).
// 2. Calculate the distance for Person 2 to Person 3: dist2 = abs(y - z).
// 3. Use an if-else if-else structure to compare the two distances.
// 4. If dist1 is smaller, return 1.
// 5. If dist2 is smaller, return 2.
// 6. If they are equal, return 0.
// Time Complexity: O(1), as it involves a few constant-time arithmetic operations and comparisons.
// Space Complexity: O(1), as no extra space is used that depends on the input size.
class Solution {
public:
    int findClosest(int x, int y, int z) {
        // Calculate distance for Person 1 to Person 3
        int dist1 = abs(x - z);
        // Calculate distance for Person 2 to Person 3
        int dist2 = abs(y - z);

        // Compare the distances
        if (dist1 < dist2) {
            return 1; // Person 1 is closer
        } else if (dist2 < dist1) {
            return 2; // Person 2 is closer
        } else {
            return 0; // Both are at the same distance
        }
    }
};

/*
*
* Dry Run
* Input: x = 2, y = 7, z = 4
*
* dist1 = abs(2 - 4) = abs(-2) = 2
* dist2 = abs(7 - 4) = abs(3) = 3
*
* Check condition: (dist1 < dist2) -> (2 < 3) is true.
* Return 1.
*
*/
```

### Clean Solution (C++)
```cpp
// Intuition: The problem boils down to a direct comparison of distances between two points (Person 1 and Person 2) and a reference point (Person 3) on a number line. The person with the minimum absolute distance reaches first.
// Approach: This can be solved compactly using a series of ternary operators. First, check if the distances are equal. If they are, return 0. Otherwise, check if Person 1's distance is less than Person 2's. If true, return 1, otherwise return 2.
// Time Complexity: O(1), as the solution performs a fixed number of calculations regardless of the input values.
// Space Complexity: O(1), as no auxiliary data structures are used.
class Solution {
public:
    int findClosest(int x, int y, int z) {
        // Use a nested ternary operator for a compact solution
        return abs(x - z) == abs(y - z) ? 0 :   // Check for a tie
               abs(x - z) < abs(y - z) ? 1 :   // Check if Person 1 is closer
               2;                              // Otherwise, Person 2 is closer
    }
};

/*
*
* Dry Run
* Input: x = 1, y = 5, z = 3
*
* abs(x - z) -> abs(1 - 3) -> abs(-2) -> 2
* abs(y - z) -> abs(5 - 3) -> abs(2) -> 2
*
* First ternary condition: (abs(x - z) == abs(y - z)) -> (2 == 2) is true.
* The expression evaluates to the first part of the ternary operator.
* Return 0.
*
*/
```

---

## 💡 Notes

- The use of `abs()` is crucial because distance cannot be negative. For example, the distance between position 7 and 4 is `3`, and the distance between 1 and 4 is also `3`. `abs(7-4)` and `abs(1-4)` both correctly yield `3`.
- The problem states that the speeds are the same, which simplifies the logic to only comparing distances. If speeds were different, we would need to calculate time (`time = distance / speed`) for each person and compare the times.

---

## 🚀 Key Insights

- **Absolute Distance is Key:** The problem is a straightforward application of finding the absolute distance between points on a 1D line.
- **Direct Comparison:** No complex algorithms are needed. A simple comparison of two calculated values determines the outcome. The optimized solution showcases how this comparison can be elegantly written in a single line.

---

## 🗺️ Further Exploration

- **Different Speeds:** How would you modify the solution if Person 1 and Person 2 had different speeds, `speed1` and `speed2`?
- **2D Plane:** What if the people were on a 2D grid at coordinates `(x1, y1)`, `(x2, y2)`, and `(z1, z2)`? You would need to use the Euclidean distance formula: `sqrt((x_a - x_b)^2 + (y_a - y_b)^2)`.
- **Manhattan Distance:** Consider the same 2D grid problem but using Manhattan distance (city block distance): `abs(x_a - x_b) + abs(y_a - y_b)`.

---

## 📚 References

- **[LeetCode Problem: Find Closest Person](https://leetcode.com/problems/find-closest-person/description/)**
- **[Absolute Value](https://en.wikipedia.org/wiki/Absolute_value)**

---

## 🏷️ Tags

`Math`, `Absolute Value`, `Simulation`, `Comparison`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-closest-person/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)