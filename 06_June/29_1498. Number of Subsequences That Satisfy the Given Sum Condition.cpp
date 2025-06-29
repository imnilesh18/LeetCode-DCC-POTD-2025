/*
 * 1498. Number of Subsequences That Satisfy the Given Sum Condition
 *
 * Medium
 *
 * You are given an array of integers nums and an integer target.
 * Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.
 *
 * Example 1:
 * Input: nums = [3,5,6,7], target = 9
 * Output: 4
 * Explanation: There are 4 subsequences that satisfy the condition.
 * [3] -> Min value + max value <= target (3 + 3 <= 9)
 * [3,5] -> (3 + 5 <= 9)
 * [3,5,6] -> (3 + 6 <= 9)
 * [3,6] -> (3 + 6 <= 9)
 *
 * Example 2:
 * Input: nums = [3,3,6,8], target = 10
 * Output: 6
 * Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
 * [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]
 *
 * Example 3:
 * Input: nums = [2,3,3,4,6,7], target = 12
 * Output: 61
 * Explanation: There are 63 non-empty subsequences, two of them do not satisfy the condition ([6,7], [7]).
 * Number of valid subsequences (63 - 2 = 61).
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^6
 * 1 <= target <= 10^6
 */

// Approach: Sort the array and use two pointers to count valid subsequences by fixing the minimum and finding all combinations of elements between pointers.
// Time Complexity: O(n log n) for sorting + O(n) for two-pointer scan, overall O(n log n).
// Space Complexity: O(n) for the power array storing 2^i mod M.
class Solution {
public:
    const int M = 1e9 + 7;

    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();

        // 1. Sort the input array to enable two-pointer technique
        sort(nums.begin(), nums.end());

        // 2. Precompute powers of 2 modulo M: power[i] = 2^i % M
        vector<int> power(n);
        power[0] = 1;
        for (int i = 1; i < n; i++) {
            power[i] = (power[i - 1] * 2) % M;
        }

        // 3. Initialize two pointers and result accumulator
        int l = 0, r = n - 1;
        int result = 0;

        // 4. Move pointers to count valid subsequences
        while (l <= r) {
            // If the sum of the smallest and largest <= target,
            // all subsequences where nums[l] is min and any subset of nums[l+1..r] are valid
            if (nums[l] + nums[r] <= target) {
                int count = r - l; // number of elements between l and r
                result = (result + power[count]) % M;
                l++;               // move left pointer to consider next minimum
            } else {
                // Sum too large: decrease the maximum candidate
                r--;
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run (Example 1: nums = [3,5,6,7], target = 9)
 *
 * Input sorted: [3,5,6,7]
 * Precomputed power = [1,2,4,8]
 *
 * Iteration 1: l=0, r=3 => nums[l]+nums[r]=3+7=10 >9 => r-->2
 * Iteration 2: l=0, r=2 => nums[l]+nums[r]=3+6=9 <=9 => count=2, add power[2]=4 => result=4, l-->1
 * Iteration 3: l=1, r=2 => nums[l]+nums[r]=5+6=11 >9 => r-->1
 * Iteration 4: l=1, r=1 => nums[l]+nums[r]=5+5=10 >9 => r-->0 (loop ends since l>r)
 *
 * Final result = 4
 */
