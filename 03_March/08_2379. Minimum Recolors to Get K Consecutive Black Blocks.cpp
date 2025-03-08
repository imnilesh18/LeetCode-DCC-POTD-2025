/*
 * 2379. Minimum Recolors to Get K Consecutive Black Blocks
 *
 * You are given a 0-indexed string blocks of length n, where blocks[i] is either 'W' or 'B', representing the color of the ith block. The characters 'W' and 'B' denote the colors white and black, respectively.
 * You are also given an integer k, which is the desired number of consecutive black blocks.
 * In one operation, you can recolor a white block such that it becomes a black block.
 * Return the minimum number of operations needed such that there is at least one occurrence of k consecutive black blocks.
 *
 * Example 1:
 * Input: blocks = "WBBWWBBWBW", k = 7
 * Output: 3
 * Explanation:
 * One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
 * so that blocks = "BBBBBBBWBW".
 * It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
 * Therefore, we return 3.
 *
 * Example 2:
 * Input: blocks = "WBWBBBW", k = 2
 * Output: 0
 * Explanation:
 * No changes need to be made, since 2 consecutive black blocks already exist.
 * Therefore, we return 0.
 *
 * Constraints:
 * n == blocks.length
 * 1 <= n <= 100
 * blocks[i] is either 'W' or 'B'.
 * 1 <= k <= n
 */

// Approach: Iterate over every contiguous block of k characters, count the number of white blocks, and return the minimum count found.
// Time Complexity: O(n*k) where n is the length of the string, because for each window of size k we count white blocks.
// Space Complexity: O(1) since only constant extra space is used.
class Solution {
public:

    int minimumRecolors(string blocks, int k) {
        int n = blocks.length();

        int result = INT_MAX;

        for (int i = 0; i <= n - k; i++) {
            int w = 0;
            for (int j = i; j < i + k; j++) {
                if (blocks[j] == 'W') {
                    w++;
                }
            }
            result = min(result, w);
        }
        return result;
    }
};

/*
 * Dry Run:
 * For blocks = "WBBWWBBWBW", k = 7:
 *
 * Iteration 1:
 *  i = 0, window = "WBBWWBB"
 *  - blocks[0] = 'W' → white count = 1
 *  - blocks[1] = 'B' → white count = 1
 *  - blocks[2] = 'B' → white count = 1
 *  - blocks[3] = 'W' → white count = 2
 *  - blocks[4] = 'W' → white count = 3
 *  - blocks[5] = 'B' → white count = 3
 *  - blocks[6] = 'B' → white count = 3
 *  Result = min(INT_MAX, 3) = 3
 *
 * Iteration 2:
 *  i = 1, window = "BBWWBBW"
 *  - blocks[1] = 'B' → white count = 0
 *  - blocks[2] = 'B' → white count = 0
 *  - blocks[3] = 'W' → white count = 1
 *  - blocks[4] = 'W' → white count = 2
 *  - blocks[5] = 'B' → white count = 2
 *  - blocks[6] = 'B' → white count = 2
 *  - blocks[7] = 'W' → white count = 3
 *  Result = min(3, 3) = 3
 *
 * Iteration 3:
 *  i = 2, window = "BWWBBWB"
 *  - blocks[2] = 'B' → white count = 0
 *  - blocks[3] = 'W' → white count = 1
 *  - blocks[4] = 'W' → white count = 2
 *  - blocks[5] = 'B' → white count = 2
 *  - blocks[6] = 'B' → white count = 2
 *  - blocks[7] = 'W' → white count = 3
 *  - blocks[8] = 'B' → white count = 3
 *  Result = min(3, 3) = 3
 *
 * Iteration 4:
 *  i = 3, window = "WWBBWBW"
 *  - blocks[3] = 'W' → white count = 1
 *  - blocks[4] = 'W' → white count = 2
 *  - blocks[5] = 'B' → white count = 2
 *  - blocks[6] = 'B' → white count = 2
 *  - blocks[7] = 'W' → white count = 3
 *  - blocks[8] = 'B' → white count = 3
 *  - blocks[9] = 'W' → white count = 4
 *  Result = min(3, 4) = 3
 *
 * Final Answer: 3
 */

// Approach 2: Use a sliding window of size k to count the white ('W') blocks.
// For each window, update the result with the count of white blocks, then slide the window by removing the effect of the leftmost block.
// Time Complexity: O(n) because each block is visited at most twice (once when entering and once when exiting the window).
// Space Complexity: O(1) since only a constant amount of extra space is used.
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n      = blocks.length();
        int i      = 0;
        int j      = 0;
        int w      = 0; // Count of white blocks in the current window
        int result = INT_MAX;

        while (j < n) {
            if (blocks[j] == 'W') {
                w++;
            }

            // When the current window size equals k, update result and slide the window
            if (j - i + 1 == k) {
                result = min(result, w);
                if (blocks[i] == 'W') {
                    w--;
                }
                i++;
            }
            j++;
        }
        return result;
    }
};

/*
 * Dry Run:
 * For blocks = "WBBWWBBWBW", k = 7:
 *
 * Initial state:
 *  i = 0, j = 0, w = 0, result = INT_MAX
 *
 * Iteration 1: (j = 0)
 *  blocks[0] = 'W' → w = 1
 *  Window size = 1 (not equal to k)
 *
 * Iteration 2: (j = 1)
 *  blocks[1] = 'B' → w remains 1
 *  Window size = 2
 *
 * Iteration 3: (j = 2)
 *  blocks[2] = 'B' → w remains 1
 *  Window size = 3
 *
 * Iteration 4: (j = 3)
 *  blocks[3] = 'W' → w = 2
 *  Window size = 4
 *
 * Iteration 5: (j = 4)
 *  blocks[4] = 'W' → w = 3
 *  Window size = 5
 *
 * Iteration 6: (j = 5)
 *  blocks[5] = 'B' → w remains 3
 *  Window size = 6
 *
 * Iteration 7: (j = 6)
 *  blocks[6] = 'B' → w remains 3
 *  Window size becomes 7 (equals k)
 *  Update result = min(INT_MAX, 3) = 3
 *  Slide window: blocks[i]=blocks[0] = 'W' → decrement w to 2, increment i to 1
 *
 * Iteration 8: (j = 7)
 *  blocks[7] = 'W' → w becomes 3
 *  Window size = 7 (from i=1 to j=7)
 *  Update result = min(3, 3) = 3
 *  Slide window: blocks[i]=blocks[1] = 'B' → w remains 3, increment i to 2
 *
 * Subsequent iterations continue similarly for j = 8 and j = 9.
 * Final result remains 3.
 */
