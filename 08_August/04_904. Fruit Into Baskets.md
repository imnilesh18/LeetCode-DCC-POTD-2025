# 🍓 904. Fruit Into Baskets

![LeetCode](https://img.shields.io/badge/LeetCode-904-brightgreen?style=for-the-badge&logo=leetcode)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

> ⚡️ **Educational Use Only:** > This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/fruit-into-baskets/).

---

## Problem Statement

You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array `fruits` where `fruits[i]` is the **type** of fruit the `ith` tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

- You only have **two** baskets, and each basket can only hold a **single type** of fruit. There is no limit on the amount of fruit each basket can hold.
- Starting from any tree of your choice, you must pick **exactly one fruit** from **every** tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
- Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array `fruits`, return _the **maximum** number of fruits you can pick_.

---

## Examples

| Input                  | Output | Explanation                                                                                    |
| :--------------------- | :----: | :--------------------------------------------------------------------------------------------- |
| `fruits = [1,2,1]`     |  `3`   | We can pick from all 3 trees.                                                                  |
| `fruits = [0,1,2,2]`   |  `3`   | We can pick from trees `[1,2,2]`. If we start at the first tree, we could only pick `[0,1]`.   |
| `fruits = [1,2,3,2,2]` |  `4`   | We can pick from trees `[2,3,2,2]`. If we start at the first tree, we could only pick `[1,2]`. |

<details>
<summary><strong>Example Walkthrough for `fruits = [1,2,3,2,2]`</strong></summary>

1.  **Start at index 0 (fruit type 1):**

    - Basket 1: `[1]`
    - Move to index 1 (fruit type 2): Baskets `[1], [2]`
    - Move to index 2 (fruit type 3): Cannot pick. We have types 1 and 2 already.
    - **Total collected: 2**

2.  **Start at index 1 (fruit type 2):**
    - Basket 1: `[2]`
    - Move to index 2 (fruit type 3): Baskets `[2], [3]`
    - Move to index 3 (fruit type 2): Baskets `[2,2], [3]`
    - Move to index 4 (fruit type 2): Baskets `[2,2,2], [3]`
    - **Total collected: 4**

The maximum we can collect is 4.

</details>

---

## Constraints

- `1 <= fruits.length <= 10^5`
- `0 <= fruits[i] < fruits.length`

---

## 🛠️ Approach

The problem asks for the longest subarray of `fruits` that contains at most two distinct fruit types. This is a classic **Sliding Window** problem.

We can use two pointers, `i` (start of the window) and `j` (end of the window), to define a "window" of fruits we are currently collecting. A hash map will be used to keep track of the count of each type of fruit within the current window.

The main idea is to expand the window by moving the `j` pointer to the right. As we add a new fruit to our window, we update its count in the hash map. If the number of unique fruit types in our map (i.e., `map.size()`) exceeds 2, it means we have violated the "two baskets" rule. To fix this, we must shrink the window from the left by moving the `i` pointer to the right, until the window is valid again (contains at most 2 distinct fruit types).

At each step, after ensuring the window is valid, we calculate its size (`j - i + 1`) and update our maximum count.

---

### Solution (C++)

```cpp
// Intuition: The problem is asking for the longest subarray with at most 2 distinct elements. This is a classic application of the sliding window technique. We maintain a "window" (a subarray) and expand it to the right. If the window becomes invalid (more than 2 types of fruit), we shrink it from the left until it's valid again.

// Approach:
// 1. Initialize two pointers, `i` (start) and `j` (end), to 0.
// 2. Use an unordered_map `mp` to store the frequency of fruit types in the current window [i, j].
// 3. Iterate `j` from 0 to n-1 to expand the window to the right.
// 4. In each step, add `fruits[j]` to the window and increment its count in the map.
// 5. Check if `mp.size() <= 2`. If so, the window is valid. Calculate its length (j - i + 1) and update the max count.
// 6. If `mp.size() > 2`, the window is invalid. We must shrink it from the left.
// 7. Decrement the count of `fruits[i]` in the map. If its count becomes 0, erase it from the map.
// 8. Increment `i` to shrink the window.
// 9. Repeat until `j` reaches the end of the array. The maximum length found is the answer.

// Time Complexity: O(n), because each element will be visited by the `i` and `j` pointers at most once.
// Space Complexity: O(1) or O(k) where k is the number of basket types. In this case, k=2, so it's constant space as the map will hold at most 3 elements at any time.

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        // Map to store frequency of fruit types
        unordered_map<int, int> mp;

        int i = 0; // Left pointer of the window
        int j = 0; // Right pointer of the window
        int count = 0; // Stores the maximum number of fruits collected

        while(j < n) {
            // Add the current fruit to the map
            mp[fruits[j]]++;

            // If the window has at most 2 types of fruits, it's a valid window
            if(mp.size() <= 2) {
                // Update the maximum count with the current window size
                count = max(count, j - i + 1);
            } else {
                // If the window has more than 2 types, shrink it from the left
                mp[fruits[i]]--; // Decrement the count of the fruit at the left pointer

                // If the count of that fruit becomes 0, remove it from the map
                if(mp[fruits[i]] == 0)
                    mp.erase(fruits[i]);

                i++; // Move the left pointer to the right
            }

            j++; // Always expand the window to the right
        }
        return count;
    }
};

/*
*
* Dry Run
* Example: fruits = [1, 2, 3, 2, 2]
*
* Initial state: i=0, j=0, count=0, mp={}
*
* j=0, fruit=1: mp={1:1}. mp.size=1 <= 2. count=max(0, 0-0+1)=1.
* j=1, fruit=2: mp={1:1, 2:1}. mp.size=2 <= 2. count=max(1, 1-0+1)=2.
* j=2, fruit=3: mp={1:1, 2:1, 3:1}. mp.size=3 > 2.
* -> Shrink window: mp[fruits[i=0]] (which is 1) becomes 0. Erase 1. mp={2:1, 3:1}. i becomes 1.
* -> Window is now [2, 3].
* j=3, fruit=2: mp={2:2, 3:1}. mp.size=2 <= 2. count=max(2, 3-1+1)=3.
* j=4, fruit=2: mp={2:3, 3:1}. mp.size=2 <= 2. count=max(3, 4-1+1)=4.
*
* Loop ends. Final count = 4.
*
*/
```

### Solution (Java)

```java
// Intuition: The problem seeks the longest continuous subarray containing at most two distinct integers. This structure suggests a sliding window approach. We can define a "window" and slide it across the array, expanding and shrinking it to find the longest valid one.

// Approach:
// 1. Use two pointers, `i` (left) and `j` (right), to manage the window, both starting at 0.
// 2. Employ a HashMap to store the frequency of each fruit type within the current window.
// 3. Iterate with the `j` pointer to expand the window, adding `fruits[j]` and updating its count in the map.
// 4. After each expansion, check if the map's size is greater than 2.
// 5. If it is, the window is invalid. We must shrink it from the left by moving `i`.
// 6. To shrink, get the fruit at `fruits[i]`, decrement its count in the map.
// 7. If the fruit's count drops to 0, remove it entirely from the map.
// 8. Increment `i`. Repeat shrinking until the map's size is 2 again.
// 9. In each valid state, calculate the window size (`j - i + 1`) and update the maximum length found so far.

// Time Complexity: O(n), as both `i` and `j` pointers traverse the array at most once.
// Space Complexity: O(1), since the HashMap will store at most 3 distinct fruit types at any given time.

class Solution {
    public int totalFruit(int[] fruits) {
        int n = fruits.length;

        // Map to store the frequency of fruit types
        Map<Integer, Integer> map = new HashMap<>();

        int i = 0; // Left pointer of the window
        int j = 0; // Right pointer of the window
        int maxFruits = 0; // Stores the maximum number of fruits collected

        while (j < n) {
            // Add the current fruit to the map, updating its frequency
            map.put(fruits[j], map.getOrDefault(fruits[j], 0) + 1);

            // While the window is invalid (more than 2 fruit types)
            while (map.size() > 2) {
                // Shrink the window from the left
                int leftFruit = fruits[i];
                map.put(leftFruit, map.get(leftFruit) - 1); // Decrement count

                // If the count becomes 0, remove the fruit type from our "baskets"
                if (map.get(leftFruit) == 0) {
                    map.remove(leftFruit);
                }

                i++; // Move the left pointer to the right
            }

            // At this point, the window [i, j] is valid
            // Update the maximum count with the current window size
            maxFruits = Math.max(maxFruits, j - i + 1);

            j++; // Expand the window to the right
        }

        return maxFruits;
    }
}

/*
*
* Dry Run
* Example: fruits = [0, 1, 2, 2]
*
* Initial state: i=0, j=0, maxFruits=0, map={}
*
* j=0, fruit=0: map={0:1}. map.size=1 <= 2. maxFruits=max(0, 0-0+1)=1.
* j=1, fruit=1: map={0:1, 1:1}. map.size=2 <= 2. maxFruits=max(1, 1-0+1)=2.
* j=2, fruit=2: map={0:1, 1:1, 2:1}. map.size=3 > 2.
* -> Shrink: map[fruits[i=0]] (which is 0) count becomes 0. Remove 0. map={1:1, 2:1}. i becomes 1.
* -> Window is now [1, 2, 2]. Current size is 2-1+1=2. maxFruits is still 2.
* -> maxFruits=max(2, 2-1+1) = 2.
* j=3, fruit=2: map={1:1, 2:2}. map.size=2 <= 2. maxFruits=max(2, 3-1+1)=3.
*
* Loop ends. Final maxFruits = 3.
*
*/
```

---

## Key Insights

The core insight is reframing the problem. "Picking fruits from any starting tree with at most two baskets" is equivalent to finding the **"longest subarray with at most two distinct elements."**

The Sliding Window technique is perfect for this because it avoids re-calculating results for overlapping subarrays. Instead of starting a new count for every possible starting tree (a brute-force O(n^2) approach), the window efficiently slides across the array in a single pass (O(n)), adding elements from the right and removing them from the left as needed.

---

## Further Exploration

- **Follow-up Question:** What if you had `k` baskets instead of 2? The solution can be easily generalized by changing the condition from `map.size() > 2` to `map.size() > k`.

- **Related LeetCode Problems:**
  - [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) (Sliding window with 1 unique character per type)
  - [159. Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/) (The exact same problem, but with characters instead of fruit types)
  - [340. Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/) (The generalized version of this problem)

---

## References

- **Original Problem:** [https://leetcode.com/problems/fruit-into-baskets/](https://leetcode.com/problems/fruit-into-baskets/)
- **Sliding Window Technique:** [GeeksForGeeks Article](https://www.geeksforgeeks.org/dsa/window-sliding-technique/)

---

## Author

- [imnilesh18](https://github.com/imnilesh18)

---

## Tags

![Array](https://img.shields.io/badge/Array-2088FF?style=for-the-badge)
![Hash Table](https://img.shields.io/badge/Hash_Table-45B8D8?style=for-the-badge)
![Sliding Window](https://img.shields.io/badge/Sliding_Window-5A6978?style=for-the-badge)

---

## License

This project is licensed under the MIT License.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

**Disclaimer:** This content is for educational purposes only. All intellectual property rights for the problem statement and test cases belong to LeetCode.
