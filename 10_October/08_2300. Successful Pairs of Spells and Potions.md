# ✨ 2300. Successful Pairs of Spells and Potions

<p align="center">
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Topics-Array-blue" alt="Topics: Array">
  <img src="https://img.shields.io/badge/Topics-Binary_Search-green" alt="Topics: Binary Search">
  <img src="https://img.shields.io/badge/Topics-Two_Pointers-orange" alt="Topics: Two Pointers">
  <img src="https://img.shields.io/badge/Topics-Sorting-purple" alt="Topics: Sorting">
</p>

> **Problem Link:** [https://leetcode.com/problems/successful-pairs-of-spells-and-potions/](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)

---

## 📝 Problem Statement

You are given two positive integer arrays `spells` and `potions`, of length `n` and `m` respectively, where `spells[i]` represents the strength of the `i`-th spell and `potions[j]` represents the strength of the `j`-th potion.

You are also given an integer `success`. A spell and potion pair is considered **successful** if the product of their strengths is **at least** `success`.

Return an integer array `pairs` of length `n` where `pairs[i]` is the number of potions that will form a successful pair with the `i`-th spell.

---

## Constraints

- `n == spells.length`
- `m == potions.length`
- `1 <= n, m <= 10^5`
- `1 <= spells[i], potions[i] <= 10^5`
- `1 <= success <= 10^10`

---

## 🧪 Examples

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `spells = [5,1,3]`, `potions = [1,2,3,4,5]`, `success = 7` | `[4,0,3]` | **0th spell (5):** `5 * [1,2,3,4,5] = [5,10,15,20,25]`. 4 pairs are >= 7. <br/> **1st spell (1):** `1 * [1,2,3,4,5] = [1,2,3,4,5]`. 0 pairs are >= 7. <br/> **2nd spell (3):** `3 * [1,2,3,4,5] = [3,6,9,12,15]`. 3 pairs are >= 7. |
| `spells = [3,1,2]`, `potions = [8,5,8]`, `success = 16` | `[2,0,2]` | **0th spell (3):** `3 * [8,5,8] = [24,15,24]`. 2 pairs are >= 16. <br/> **1st spell (1):** `1 * [8,5,8] = [8,5,8]`. 0 pairs are >= 16. <br/> **2nd spell (2):** `2 * [8,5,8] = [16,10,16]`. 2 pairs are >= 16. |

---

## 💡 Approach

### Brute-Force Intuition

The most straightforward way to solve this is to simulate the process directly. For each spell, we can iterate through every potion, calculate their product, and check if it meets the `success` threshold. We maintain a counter for each spell and increment it for every successful pair.

This approach is simple to understand but inefficient. With up to 10<sup>5</sup> spells and 10<sup>5</sup> potions, the total number of multiplications would be 10<sup>10</sup>, which is too slow and will result in a "Time Limit Exceeded" (TLE) error.

### Optimized Approach: Sorting and Binary Search

We can significantly optimize the process by sorting the `potions` array.

<details>
<summary>Click for a step-by-step walkthrough</summary>

1.  **Sort the `potions` array:** First, sort the `potions` array in non-decreasing order. This is the crucial step that enables a more efficient search.

2.  **Iterate through Spells:** For each `spell` in the `spells` array, we need to find how many potions can form a successful pair with it.

3.  **Calculate Minimum Potion Strength:** Instead of checking every potion, we can calculate the *minimum potion strength* required to achieve `success`. This can be found with the formula:
    `min_potion_strength = ceil(success / current_spell)`

    For example, if `success` is 16 and the current `spell` is 3, we need a potion with strength at least `ceil(16 / 3) = ceil(5.33) = 6`. Any potion with strength 6 or greater will form a successful pair.

    > **Note on Division:** To avoid integer division issues, we can convert the `success` value to a floating-point number before dividing (e.g., `(1.0 * success) / spell`).

4.  **Binary Search for the Minimum Potion:** Now that we have the `min_potion_strength`, we can use binary search on the sorted `potions` array to find the first element that is greater than or equal to this minimum required strength. This is equivalent to finding the **lower bound** of `min_potion_strength`.

5.  **Count Successful Pairs:** If the binary search finds such a potion at index `i`, then all potions from index `i` to the end of the array will also form successful pairs (because the array is sorted). The total count of successful potions is therefore `m - i`, where `m` is the total number of potions. If no such potion is found, the count is 0.

6.  **Store the Result:** Store this count for the current spell and repeat the process for all other spells.

This approach reduces the time complexity from O(n * m) to O(n * log(m) + m * log(m)) due to the initial sort and the subsequent binary searches, which is efficient enough to pass the given constraints.
</details>

---

## 💻 Solution Code

### Brute-Force Approach

```cpp
// Intuition:
// For each spell, iterate through all potions to check if their product is at least 'success'.
// This is a direct simulation of the problem statement.
//
// Approach:
// 1. Initialize an answer vector of the same size as 'spells'.
// 2. Loop through each spell `s` in the `spells` array.
// 3. Inside this loop, initialize a counter for the current spell to zero.
// 4. Loop through each potion `p` in the `potions` array.
// 5. Calculate the product `s * p`.
// 6. If the product is greater than or equal to `success`, increment the counter.
// 7. After iterating through all potions, store the counter value in the answer vector for the current spell.
// 8. Return the answer vector.
//
// Time Complexity: O(n * m), where n is the number of spells and m is the number of potions. This is too slow for the given constraints.
// Space Complexity: O(n) for the answer vector.

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        vector<int> pairs(n, 0); // Stores the result for each spell

        // Iterate through each spell
        for (int i = 0; i < n; ++i) {
            int current_spell = spells[i];
            int count = 0; // Counter for successful pairs for the current spell

            // Iterate through each potion
            for (int j = 0; j < m; ++j) {
                long long product = (long long)current_spell * potions[j];
                // Check if the product meets the success threshold
                if (product >= success) {
                    count++;
                }
            }
            pairs[i] = count; // Store the final count
        }

        return pairs;
    }
};

/*
*
* Dry Run
*
* spells = [5, 1, 3], potions = [1, 2, 3, 4, 5], success = 7
*
* i = 0 (spell = 5):
* 5*1=5 < 7
* 5*2=10 >= 7 (count=1)
* 5*3=15 >= 7 (count=2)
* 5*4=20 >= 7 (count=3)
* 5*5=25 >= 7 (count=4)
* pairs[0] = 4
*
* i = 1 (spell = 1):
* 1*1=1 < 7
* 1*2=2 < 7
* 1*3=3 < 7
* 1*4=4 < 7
* 1*5=5 < 7
* pairs[1] = 0
*
* i = 2 (spell = 3):
* 3*1=3 < 7
* 3*2=6 < 7
* 3*3=9 >= 7 (count=1)
* 3*4=12 >= 7 (count=2)
* 3*5=15 >= 7 (count=3)
* pairs[2] = 3
*
* Final Answer: [4, 0, 3]
*
*/
```

### Optimized Approach (Using `lower_bound` STL)

```cpp
// Intuition:
// Instead of checking every potion for each spell, we can sort the potions array and use binary search.
// For a given spell, we calculate the minimum potion strength needed to meet the `success` value.
// Then, we find the first potion in the sorted array that meets this requirement. All subsequent potions will also be valid.
//
// Approach:
// 1. Get the sizes of spells (m) and potions (n).
// 2. Sort the `potions` array in ascending order. This allows us to use binary search.
// 3. Find the maximum potion value for an early exit optimization.
// 4. Iterate through each spell from i = 0 to m-1.
// 5. For each spell, calculate the minimum potion strength required: `minPotion = ceil((1.0 * success) / spell)`.
//    - Using `1.0` ensures floating-point division to handle non-integer results correctly.
// 6. If `minPotion` is greater than `maxPotion`, no potion can be successful, so add 0 to the answer and continue.
// 7. Use `std::lower_bound` to find the first element in `potions` that is not less than `minPotion`.
//    - The difference between the returned iterator and `potions.begin()` gives the index of this element.
// 8. The number of successful pairs is `n - index`. Add this count to the answer vector.
// 9. Return the answer vector.
//
// Time Complexity: O(m*log(m) + n*log(m)), where m is spells.size() and n is potions.size(). Sorting takes O(m*log(m)), and the loop with binary search takes O(n*log(m)).
// Space Complexity: O(1) if we don't count the answer vector, otherwise O(n).

//Approach-1 : Using lower_bound STL
//T.C : O(nlogn)
//S.C : O(1)
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int m = spells.size(); // Number of spells
        
        int n = potions.size(); // Number of potions
        
        // Sort the potions array to enable binary search
        sort(begin(potions), end(potions));
        
        // Get the maximum potion value for an optimization check
        int maxPotion = potions[n-1];
        
        vector<int> answer; // Vector to store the results
        
        
        // Iterate through each spell
        for(int i = 0; i<m; i++) {
            
            int spell = spells[i]; // Current spell strength
            
            // Calculate the minimum potion strength required
            long long minPotion = ceil((1.0*success)/spell);
            
            // If the minimum required potion is greater than the max available, no pairs are possible
            if(minPotion > maxPotion) {
                answer.push_back(0);
                continue;
            }
            
            // Use lower_bound to find the first potion >= minPotion
            // The result is an iterator, subtract begin() to get the index
            int index = lower_bound(begin(potions), end(potions), minPotion) - begin(potions);
            
            // The count of successful pairs is the total number of potions minus the found index
            answer.push_back(n-index);
            
        }
        
        return answer;
    }
};
/*
*
* Dry Run
*
* spells = [3,1,2], potions = [8,5,8], success = 16
*
* 1. Sort potions: [5, 8, 8]. n = 3. maxPotion = 8.
*
* i = 0 (spell = 3):
* minPotion = ceil((1.0 * 16) / 3) = ceil(5.33) = 6.
* minPotion (6) <= maxPotion (8).
* lower_bound in [5, 8, 8] for 6 finds 8 at index 1.
* count = n - index = 3 - 1 = 2.
* answer.push_back(2).
*
* i = 1 (spell = 1):
* minPotion = ceil((1.0 * 16) / 1) = 16.
* minPotion (16) > maxPotion (8).
* answer.push_back(0).
*
* i = 2 (spell = 2):
* minPotion = ceil((1.0 * 16) / 2) = 8.
* minPotion (8) <= maxPotion (8).
* lower_bound in [5, 8, 8] for 8 finds 8 at index 1.
* count = n - index = 3 - 1 = 2.
* answer.push_back(2).
*
* Final Answer: [2, 0, 2]
*
*/
```

### Optimized Approach (Using Self-Written Binary Search)

```cpp
// Intuition:
// This approach is identical to the one using STL's lower_bound, but we implement the binary search logic ourselves.
// This is often required in interviews to demonstrate a deeper understanding of the algorithm.
// The goal of our binary search is to find the "lower bound" - the index of the first element >= target.
//
// Approach:
// 1. The main `successfulPairs` function remains largely the same: sort potions, iterate through spells, calculate `minPotion`.
// 2. Instead of calling `std::lower_bound`, we call our custom `BinarySearch` function.
// 3. `BinarySearch(l, r, potions, target)`:
//    - Initialize a potential `index` to a value indicating 'not found' (like -1 or n).
//    - While `l <= r`:
//      - Calculate `mid`.
//      - If `potions[mid] >= target`: This is a potential answer. Store `mid` as the current best index and search for a better (smaller) index in the left half by setting `r = mid - 1`.
//      - If `potions[mid] < target`: The potion at `mid` is too small. We must search in the right half by setting `l = mid + 1`.
//    - Return the final `index` found.
// 4. The main function then calculates `n - index` to get the count of successful pairs.
//
// Time Complexity: O(m*log(m) + n*log(m)), identical to the STL version.
// Space Complexity: O(1) if we don't count the answer vector, otherwise O(n).

//Approach-2 : Using self written Binary Search for lower bound
//T.C : O(nlogn)
//S.C : O(1)
class Solution {
public:
    
    // Custom binary search to find the lower bound of the target
    int BinarySearch(int l, int r, vector<int>& potions, int target) {
        
        // We have to find the index of the first element greater than or equal to target (minPotion)
        
        int index = r + 1; // Default to an out-of-bounds index if no element is found
        int mid = 0;
        
        while(l <= r) {
            
            mid = l + (r-l)/2; // Avoid potential integer overflow
            
            if(potions[mid] >= target) {
                index = mid; // Found a potential answer, try to find a smaller index to the left
                r = mid-1;
            } else {
                l = mid+1; // Current element is too small, search to the right
            }
            
        }
        
        return index;
    }
    
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int m = spells.size();
        
        int n = potions.size();
        
        // Sort the potions to allow binary search
        sort(begin(potions), end(potions));
        
        int maxPotion = potions[n-1];
        
        vector<int> answer;
        
        
        for(int i = 0; i<m; i++) {
            
            int spell = spells[i];
            
            // Calculate minimum potion strength needed
            long long minPotion = ceil((1.0*success)/spell);
            
            // Optimization: if required potion is stronger than the max available one
            if(minPotion > maxPotion) {
                answer.push_back(0);
                continue;
            }
            
            // Call our custom binary search to find the lower bound index
            int index = BinarySearch(0, n-1, potions, minPotion);
            
            // Count of successful pairs is total potions minus the found index
            answer.push_back(n-index);
            
        }
        
        return answer;
    }
};

/*
*
* Dry Run (BinarySearch function)
*
* potions = [5, 8, 8], target = 6
*
* 1. l=0, r=2, index=3
* mid = 0 + (2-0)/2 = 1. potions[1] = 8.
* 8 >= 6. It's a possible answer.
* index = 1, r = mid - 1 = 0.
*
* 2. l=0, r=0, index=1
* mid = 0 + (0-0)/2 = 0. potions[0] = 5.
* 5 < 6. Too small.
* l = mid + 1 = 1.
*
* 3. l=1, r=0. Loop terminates.
*
* Return index = 1. This is correct, as the first element >= 6 is at index 1.
*
*/
```

---

## 🔑 Key Insights

-   **Sorting is Key:** The problem becomes much simpler if we sort the `potions` array. Whenever you see a condition like "find the number of elements that satisfy X," and you can do it with a brute-force search, consider if sorting the data could enable a faster search method like binary search or a two-pointer approach.
-   **Binary Search for Counting:** Binary search isn't just for finding if an element exists. It's a powerful tool for counting elements that meet a certain condition in a sorted array. By finding the "first" or "last" element that satisfies a property (the lower or upper bound), you can deduce the count of all such elements.
-   **Integer vs. Floating-Point Division:** Be mindful of division with integers. The expression `(success + spell - 1) / spell` is a common trick to get the ceiling of `success / spell` using only integer arithmetic. Alternatively, casting to a float/double like `(1.0 * success) / spell` before using `ceil()` also works and is often more readable.

---

## 🚀 Further Exploration

-   [LeetCode 1855. Maximum Distance Between a Pair of Values](https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/): Another problem that can be solved efficiently using two pointers or binary search on sorted data.
-   [LeetCode 167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/): A classic problem that showcases the power of the two-pointer technique on a sorted array.
-   **Learn about `lower_bound` and `upper_bound`:** These are powerful STL functions in C++ that are highly optimized for binary search operations. Understanding them can save you time and prevent bugs in competitive programming.

---

## 📚 References

-   [Original LeetCode Problem](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)
-   [Binary Search Algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)

---

## 🏷️ Tags

`Array`, `Binary Search`, `Two Pointers`, `Sorting`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)