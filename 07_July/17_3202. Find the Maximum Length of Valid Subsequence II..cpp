/*
 * 3202. Find the Maximum Length of Valid Subsequence II
 *
 * Medium
 *
 * You are given an integer array nums and a positive integer k.
 * A subsequence sub of nums with length x is called valid if it satisfies:
 * (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
 * Return the length of the longest valid subsequence of nums.
 *
 * Example 1:
 * Input: nums = [1,2,3,4,5], k = 2
 * Output: 5
 * Explanation:
 * The longest valid subsequence is [1, 2, 3, 4, 5].
 *
 * Example 2:
 * Input: nums = [1,4,2,3,1,4], k = 3
 * Output: 4
 * Explanation:
 * The longest valid subsequence is [1, 4, 1, 4].
 *
 * Constraints:
 * 2 <= nums.length <= 10^3
 * 1 <= nums[i] <= 10^7
 * 1 <= k <= 10^3
 */

// Approach: Bottom-up DP using LIS pattern generalized to k mods—maintain a k×n table dp where dp[r][i] is the longest valid subsequence ending at i with adjacent-sum%k == r, and extend dp[mod][j] to dp[mod][i] for each j<i.
// Time Complexity: O(n²) — two nested loops over n elements, computing mod in O(1).
// Space Complexity: O(n·k) — storing a dp table of size k × n.
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // Using the same LIS bottom-up approach, extended for k possible remainders

        int n = nums.size();

        // Alternative single-row initializations (commented out):
        // vector<int> dp0(n, 1); // for mod=0
        // vector<int> dp1(n, 1); // for mod=1
        // ...
        // vector<int> dpk-1(n, 1); // for mod=k-1

        // Consolidate into a k×n table: row r holds lengths for remainder r
        vector<vector<int>> dp(k, vector<int>(n, 1));
        int maxSub = 1;  // At least one element always forms a valid subsequence

        // Build DP table: for each i from 1 to n-1, try extending every j < i
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int mod = (nums[j] + nums[i]) % k;
                // Extend any subsequence ending at j with same mod into position i
                dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);
                // Update global maximum
                maxSub = max(maxSub, dp[mod][i]);
            }
        }
        return maxSub;
    }
};

/*
 *
 * Dry Run for Input: nums = [1, 4, 2, 3, 1, 4], k = 3
 * Output: 4
 * Explanation: The longest valid subsequence is [1, 4, 1, 4], with (1+4)%3=2, (4+1)%3=2, (1+4)%3=2.
 *
 * n = 6, k = 3
 * Initialize dp rows of length 6 with 1:
 *   dp[0] = [1,1,1,1,1,1]  // sums ≡0 mod 3
 *   dp[1] = [1,1,1,1,1,1]  // sums ≡1 mod 3
 *   dp[2] = [1,1,1,1,1,1]  // sums ≡2 mod 3
 * maxSub = 1
 *
 * i = 1 (nums[1]=4):
 *   j = 0 (nums[0]=1): (1+4)%3=2 → dp[2][1]=max(1,1+dp[2][0])=2 → maxSub=2
 *
 * i = 2 (nums[2]=2):
 *   j=0: (1+2)%3=0 → dp[0][2]=2 → maxSub=2
 *   j=1: (4+2)%3=0 → dp[0][2]=max(2,1+dp[0][1]=2)=2
 *
 * i = 3 (nums[3]=3):
 *   j=0: (1+3)%3=1 → dp[1][3]=2 → maxSub=2
 *   j=1: (4+3)%3=1 → dp[1][3]=max(2,1+dp[1][1]=2)=2
 *   j=2: (2+3)%3=2 → dp[2][3]=max(1,1+dp[2][2]=2)=2
 *
 * i = 4 (nums[4]=1):
 *   j=0: (1+1)%3=2 → dp[2][4]=2
 *   j=1: (4+1)%3=2 → dp[2][4]=max(2,1+dp[2][1]=3)=3 → maxSub=3
 *   j=2: (2+1)%3=0 → dp[0][4]=max(1,1+dp[0][2]=3)=3 → maxSub=3
 *   j=3: (3+1)%3=1 → dp[1][4]=max(1,1+dp[1][3]=3)=3 → maxSub=3
 *
 * i = 5 (nums[5]=4):
 *   j=0: (1+4)%3=2 → dp[2][5]=2
 *   j=1: (4+4)%3=2 → dp[2][5]=max(2,1+dp[2][1]=3)=3
 *   j=2: (2+4)%3=0 → dp[0][5]=max(1,1+dp[0][2]=3)=3
 *   j=3: (3+4)%3=1 → dp[1][5]=max(1,1+dp[1][3]=3)=3
 *   j=4: (1+4)%3=2 → dp[2][5]=max(3,1+dp[2][4]=4)=4 → maxSub=4
 *
 * Final maxSub = 4
 */
