<div align="center">
  <h1>1493. Longest Subarray of 1's After Deleting One Element</h1>
  <a href="https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description/">
    <img src="https://img.shields.io/badge/Link-LeetCode-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Link">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
</div>

<br>

## 📝 Problem Statement

Given a binary array `nums`, you should **delete exactly one element** from it.

Return the size of the **longest non-empty subarray** containing only `1`'s in the resulting array. If there is no such subarray, return `0`.

---

## 📌 Constraints

-   `1 <= nums.length <= 10^5`
-   `nums[i]` is either `0` or `1`.

---

## 🧪 Examples

| Input                               | Output | Explanation                                                                                                 |
| ----------------------------------- | :----: | ----------------------------------------------------------------------------------------------------------- |
| `nums = [1,1,0,1]`                  |  `3`   | After deleting the `0` at position 2, the array becomes `[1,1,1]`, which has a length of 3.                 |
| `nums = [0,1,1,1,0,1,1,0,1]`        |  `5`   | After deleting the `0` at position 4, the longest subarray of 1s is `[1,1,1,1,1]`, with a length of 5.       |
| `nums = [1,1,1]`                    |  `2`   | You must delete one element. Deleting any `1` leaves a subarray of 1s with a length of 2.                  |
| `nums = [0,0,0]`                    |  `0`   | After deleting any element, there are no subarrays of 1s.                                                   |

---

## 🤔 Approach

The problem asks for the longest subarray of ones after deleting a single element. This element can be a zero or a one. Our goal is to maximize the length of this subarray. This problem can be solved using several approaches, from a straightforward brute-force method to highly efficient sliding window techniques.

<details>
<summary><strong>1. Brute-Force Approach</strong></summary>

The most intuitive way to solve this is to try deleting every possible element. Since we want to maximize the subarray of ones, it makes the most sense to delete the zeros.

-   **Iterate** through the array. Whenever we encounter a `0`, we conceptually delete it.
-   After deleting the `0` at index `i`, we then **scan the entire modified array** to find the longest continuous subarray of `1`s.
-   We keep track of the **maximum length** found across all deletions.
-   A special **edge case** is when the array contains no zeros. In this case, we must delete one `1`, so the answer will be `n-1`, where `n` is the length of the array.

This approach is simple to understand but inefficient, as it involves nested loops, leading to a time complexity of O(n²).

</details>

<details>
<summary><strong>2. Sliding Window Approach</strong></summary>

A more optimal solution uses the sliding window technique. The core idea is to maintain a "window" (a subarray) that is valid according to the problem's constraints and try to expand it as much as possible.

-   A window is considered **valid** if it contains **at most one zero**.
-   We use two pointers, `i` (start of the window) and `j` (end of the window).
-   We expand the window by incrementing `j`. As we do, we keep a count of zeros within the window `[i, j]`.
-   If the `zeroCount` exceeds `1`, the window becomes invalid. We must then **shrink the window** from the left by incrementing `i` until the `zeroCount` is back to `1` or less.
-   At each step, the length of the valid subarray of ones (after deleting the one zero) is `j - i`. We update our maximum result with this length. The window size is `j - i + 1`, and after deleting one element, the length becomes `(j - i + 1) - 1 = j - i`.

This approach processes each element at most twice (once by `j` and once by `i`), resulting in a linear time complexity of O(n).

</details>

<details>
<summary><strong>3. Optimized Sliding Window Approach</strong></summary>

We can further refine the sliding window approach to make it even cleaner and more efficient by eliminating the inner `while` loop.

-   Instead of counting zeros, we only need to remember the index of the **last zero encountered**.
-   We use two pointers, `i` (start) and `j` (end).
-   We expand the window by moving `j`.
-   When `nums[j]` is a `0`, it means we have found a second zero in our potential subarray. The window `[i, j]` is now invalid because it contains two zeros (the `last_zero` and the current one at `j`).
-   To make the window valid again, we must discard the old zero. We do this by jumping the start pointer `i` to the position right after the `last_zero_idx`.
-   We then update `last_zero_idx` to the current index `j`.
-   The length of the current valid window is always `j - i`, and we continuously update our maximum result.

This approach is highly efficient as it iterates through the array only once, maintaining a constant number of variables. It also has a time complexity of O(n) but is often faster in practice due to better cache performance and no nested loops.

</details>

---

## 💻 Solution Code

### 🚀 Approach 1: Brute Force

```cpp
// Intuition: The brute-force idea is to iterate through the array and for each zero found, we temporarily "delete" it and then calculate the longest consecutive sequence of ones in the rest of the array. We keep track of the maximum length found after trying to delete each zero.

// Approach:
// 1. Handle the edge case where there are no zeros. If so, we must delete a '1', and the result is n-1.
// 2. Count the total number of zeros.
// 3. Iterate through the input array `nums` with an index `i`.
// 4. If `nums[i]` is a zero, call a helper function `findMax` that calculates the longest subarray of ones, assuming the element at `i` is skipped.
// 5. The `findMax` function iterates through the array again, skipping the `skip_idx`, and counts consecutive ones, updating a `maxLength`.
// 6. Update a global `result` with the maximum length found from all calls to `findMax`.
// 7. Return the final `result`.

// Time Complexity: O(n^2), because for each element, we might traverse the entire array again in the `findMax` function.
// Space Complexity: O(1), as we are not using any extra space proportional to the input size.

class Solution {
public:
    int n; // Size of the nums array

    // Helper function to find the max length of consecutive ones, skipping one index
    int findMax(vector<int>& nums, int skip_idx) {
        int currLength = 0; // Length of the current subarray of ones
        int maxLength  = 0; // Maximum length found so far
        
        for(int i = 0; i < n; i++) {
            if(i == skip_idx) // Skip the element that is considered deleted
                continue;
            
            if(nums[i] == 1) {
                currLength++; // Increment current length for consecutive ones
            } else {
                maxLength = max(maxLength, currLength); // A zero breaks the sequence, update max
                currLength = 0; // Reset current length
            }
        }
        maxLength = max(maxLength, currLength); // Final check after the loop
        
        return maxLength;
    }
    
    int longestSubarray(vector<int>& nums) {
        n = nums.size(); // Initialize the size
        int result = 0;
        
        int countZero = 0; // Count of zeros in the array
        for(int x : nums) {
            if (x == 0) {
                countZero++;
            }
        }
        
        if(countZero == 0) // If no zeros, we must delete one '1'
            return n - 1;
        
        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                // If we find a zero, we calculate the max length by skipping it
                result = max(result, findMax(nums, i));
            }
        }
        
        return result;
    }
};

/*
*
* Dry Run
*
* Input: nums = [0,1,1,1,0,1,1,0,1]
* 1. **Initial Call**: `longestSubarray` is called. It finds `countZero = 3`. Since this is not 0, it proceeds to the loop.
*
* 2. **Outer loop (i=0)**: `nums[0]` is 0.
* - Call `findMax(nums, 0)`. This simulates deleting the first zero.
* - **Inside `findMax(skip_idx=0)`**:
* - The loop iterates. When `i=0`, it's skipped.
* - For `i=1,2,3`, `currLength` increments to 3. `maxLength` becomes 3.
* - At `i=4` (`nums[4]==0`), `currLength` resets to 0.
* - For `i=5,6`, `currLength` becomes 2. `maxLength` remains 3.
* - At `i=7` (`nums[7]==0`), `currLength` resets.
* - For `i=8`, `currLength` becomes 1.
* - `findMax` returns `maxLength` = 3.
* - Back in `longestSubarray`, `result` is updated to `max(0, 3) = 3`.
*
* 3. **Outer loop (i=4)**: `nums[4]` is 0.
* - Call `findMax(nums, 4)`. This simulates deleting the middle zero.
* - **Inside `findMax(skip_idx=4)`**:
* - At `i=0`, `currLength` resets.
* - For `i=1,2,3`, `currLength` becomes 3. `maxLength` is 3.
* - At `i=4`, the index is skipped. The `currLength` is NOT reset, it remains 3.
* - For `i=5,6`, `currLength` continues incrementing to 4, then 5. `maxLength` is updated to 5. This correctly "merges" the subarrays `[1,1,1]` and `[1,1]`.
* - At `i=7`, `currLength` resets to 0.
* - At `i=8`, `currLength` becomes 1.
* - `findMax` returns `maxLength` = 5.
* - Back in `longestSubarray`, `result` is updated to `max(3, 5) = 5`.
*
* 4. **Outer loop (i=7)**: `nums[7]` is 0.
* - Call `findMax(nums, 7)`.
* - **Inside `findMax(skip_idx=7)`**:
* - It finds a sequence of three 1s (indices 1-3), then `currLength` resets at `i=4`.
* - Then it finds a sequence of two 1s (indices 5-6).
* - The index `i=7` is skipped.
* - `currLength` increments for `i=8`, making the last sequence `[1,1,1]` of length 3.
* - The max length found in this pass is 3.
* - Back in `longestSubarray`, `result` is updated to `max(5, 3) = 5`.
*
* 5. The loop finishes. The function returns `result`, which is **5**.
*
*/
```

### 🚀 Approach 2: Traditional Sliding Window

```cpp
// Intuition: We can maintain a "window" or a subarray that contains at most one zero. The size of this window minus one (for the deleted zero) is a potential answer. We slide and expand this window through the array to find the maximum possible length.

// Approach:
// 1. Initialize two pointers, `i` (start of window) and `j` (end of window), to 0.
// 2. Initialize `zeroCount` to 0 and `longestWindow` to 0.
// 3. Iterate with the `j` pointer from left to right to expand the window.
// 4. If `nums[j]` is 0, increment `zeroCount`.
// 5. Use a `while` loop to shrink the window from the left (by incrementing `i`) as long as `zeroCount` is greater than 1. If `nums[i]` was a zero, decrement `zeroCount` as it leaves the window.
// 6. After ensuring the window is valid (has at most one zero), calculate the size of the subarray of ones. The current window size is `j - i + 1`. With one deletion, it's `(j - i + 1) - 1 = j - i`.
// 7. Update `longestWindow = max(longestWindow, j - i)`.
// 8. After the loop, `longestWindow` will hold the answer.

// Time Complexity: O(n), as each element is visited at most twice (by pointer `j` and pointer `i`).
// Space Complexity: O(1), as we only use a few variables to store state.

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int zeroCount = 0;       // To count zeros in the current window
        int longestWindow = 0;   // To store the maximum length found
        int i = 0;               // Start of the sliding window

        // Iterate through the array with the end of the window pointer 'j'
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] == 0) {
                zeroCount++;     // Increment zero count if we see a zero
            }

            // Shrink the window from the left if it contains more than one zero
            while (zeroCount > 1) {
                if (nums[i] == 0) {
                    zeroCount--; // Decrement as the zero at 'i' is now outside the window
                }
                i++;             // Move the start of the window to the right
            }
            
            // The current valid subarray of ones has length j - i
            // (Window size is j-i+1, but we delete one element)
            longestWindow = max(longestWindow, j - i);
        }

        return longestWindow;
    }
};

/*
*
* Dry Run
*
* Input: nums = [0,1,1,1,0,1,1,0,1]
* * j=0, nums[0]=0, zeroCount=1. longestWindow=max(0, 0-0)=0
* j=1, nums[1]=1. longestWindow=max(0, 1-0)=1
* j=2, nums[2]=1. longestWindow=max(1, 2-0)=2
* j=3, nums[3]=1. longestWindow=max(2, 3-0)=3
* j=4, nums[4]=0, zeroCount=2. 
* - while(zeroCount > 1): nums[i=0]=0, zeroCount=1. i becomes 1. Window is now [1,1,1,0].
* - longestWindow=max(3, 4-1)=3.
* j=5, nums[5]=1. longestWindow=max(3, 5-1)=4
* j=6, nums[6]=1. longestWindow=max(4, 6-1)=5
* j=7, nums[7]=0, zeroCount=2.
* - while(zeroCount > 1):
* - nums[i=1]=1, i=2
* - nums[i=2]=1, i=3
* - nums[i=3]=1, i=4
* - nums[i=4]=0, zeroCount=1. i becomes 5. Window is now [1,1,0,1].
* - longestWindow=max(5, 7-5)=5
* j=8, nums[8]=1. longestWindow=max(5, 8-5)=5
* * End of loop. Return longestWindow = 5.
*/
```

### 🚀 Approach 3: Better Sliding Window

```cpp
// Intuition: This is a more direct sliding window approach. Instead of counting zeros, we just keep track of the index of the last zero we've seen. When we see a new zero, our window is defined from the position right after the last zero up to the current position.

// Approach:
// 1. Initialize two pointers, `i = 0` (start) and `j = 0` (end).
// 2. Keep a variable `last_zero_idx = -1` to store the index of the most recently encountered zero.
// 3. Iterate with `j` to expand the window.
// 4. If `nums[j]` is a zero:
//    a. The current window has two zeros (the one at `last_zero_idx` and the new one at `j`).
//    b. To make the window valid again, we must discard the old zero. We do this by setting `i` to `last_zero_idx + 1`.
//    c. Update `last_zero_idx` to the current index `j`.
// 5. The length of the valid subarray of ones is `j - i`. Update the result with `max(result, j - i)`.
// 6. Return the final result.

// Time Complexity: O(n), as we iterate through the array only once.
// Space Complexity: O(1), constant extra space is used.

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int i = 0; // Start of the current window of ones (with at most one zero)
        int last_zero_idx = -1; // Index of the last zero encountered
        int result = 0;

        // j is the end of the window
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] == 0) {
                // When we find a zero, the new valid window must start after the PREVIOUS zero.
                i = last_zero_idx + 1;
                // Update the last zero index to the current position.
                last_zero_idx = j;
            }
            
            // The length of the current subarray of ones (after deleting the zero at last_zero_idx) is j - i.
            result = max(result, j - i);
        }
        
        return result;
    }
};

/*
*
* Dry Run
*
* Input: nums = [0,1,1,1,0,1,1,0,1]
* i=0, last_zero_idx=-1, result=0
* * j=0, nums[0]=0. i=last_zero_idx+1=0. last_zero_idx=0. result=max(0, 0-0)=0
* j=1, nums[1]=1. result=max(0, 1-0)=1
* j=2, nums[2]=1. result=max(1, 2-0)=2
* j=3, nums[3]=1. result=max(2, 3-0)=3
* j=4, nums[4]=0. i=last_zero_idx+1=1. last_zero_idx=4. result=max(3, 4-1)=3
* j=5, nums[5]=1. result=max(3, 5-1)=4
* j=6, nums[6]=1. result=max(4, 6-1)=5
* j=7, nums[7]=0. i=last_zero_idx+1=5. last_zero_idx=7. result=max(5, 7-5)=5
* j=8, nums[8]=1. result=max(5, 8-5)=5
*
* End of loop. Return result = 5.
*/
```

---

## ✨ Key Insights

-   The problem can be rephrased as "Find the longest subarray with at most one zero." The final answer is the length of this subarray minus one.
-   Sliding window is a natural fit for problems asking for the longest/shortest subarray that satisfies a certain condition.
-   The constraint of deleting *exactly one* element is important. If the array is all ones, we must delete one, making the answer `n-1`. The sliding window approaches handle this naturally because `longestWindow` would be `n-1` as `j-i` would reach `n-1` but `j-i+1` would be n. When we return `j-i`, it's correct. Wait, the problem is simpler. `j-i` is the length of the window *after* one deletion. If there are no zeros, `i` never moves from 0, `j` goes to `n-1`. `j-i` becomes `n-1`. This is correct.

---

## 🚀 Further Exploration

-   What if you are allowed to delete **k** elements? The standard sliding window approach (`Approach 2`) can be easily adapted by changing the condition `while (zeroCount > 1)` to `while (zeroCount > k)`.
-   Consider a variation where you can replace up to `k` zeros with ones. This is LeetCode problem #1004 "Max Consecutive Ones III", which can be solved with the same sliding window pattern.

---

## 📚 References

-   [Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/)
-   [LeetCode Problem: Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

---

## 🏷️ Tags

<div align="center">
  <a href="https://leetcode.com/tag/array/"><img src="https://img.shields.io/badge/Array-2496ED?style=for-the-badge&logo=dependabot&logoColor=white" alt="Array"></a>
  <a href="https://leetcode.com/tag/sliding-window/"><img src="https://img.shields.io/badge/Sliding%20Window-007ACC?style=for-the-badge&logo=windowsterminal&logoColor=white" alt="Sliding Window"></a>
  <a href="https://leetcode.com/tag/dynamic-programming/"><img src="https://img.shields.io/badge/Dynamic%20Programming-4CAF50?style=for-the-badge&logo=google&logoColor=white" alt="Dynamic Programming"></a>
</div>

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)