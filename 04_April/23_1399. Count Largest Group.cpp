/*
 * 1399. Count Largest Group
 *
 * Easy
 *
 * You are given an integer n.
 * Each number from 1 to n is grouped according to the sum of its digits.
 * Return the number of groups that have the largest size.
 *
 * Example 1:
 * Input: n = 13
 * Output: 4
 * Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
 * [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
 * There are 4 groups with largest size.
 *
 * Example 2:
 * Input: n = 2
 * Output: 2
 * Explanation: There are 2 groups [1], [2] of size 1.
 *
 * Constraints:
 * 1 <= n <= 10^4
 */

// Approach: Use a hash map to count how many numbers share the same digit sum, track the maximum group size on the fly, and count how many groups reach that size.
// Time Complexity: O(n * log₁₀ n) because we process n numbers and summing digits of each takes O(log₁₀ n) time.
// Space Complexity: O(n) in the worst case for the hash map storing counts for each possible digit sum.
class Solution {
public:
    // Helper to compute the sum of digits of num
    int findDigitsSum(int num) {
        int sum = 0;

        while (num) {
            sum += num % 10;       // add the last digit
            num /= 10;             // remove the last digit
        }
        return sum;
    }
    int countLargestGroup(int n) {
        unordered_map<int, int> mp;     // maps digit-sum -> group size
        int maxSize = 0;                // current largest group size
        int count   = 0;                // how many groups have size == maxSize

        for (int num = 1; num <= n; num++) {
            int digitSum = findDigitsSum(num);     // compute digit sum
            mp[digitSum]++;                        // increment group count

            if (mp[digitSum] == maxSize) {
                // this group just reached the current max size
                count++;
            } else if (mp[digitSum] > maxSize) {
                // found a new larger group size
                maxSize = mp[digitSum];
                count   = 1;   // reset count to this one group
            }
        }
        return count;     // number of groups with the largest size
    }
};

/*
 *
 * Dry Run
 *
 * Input: n = 13
 *
 * num = 1: sum = 1 → mp[1] = 1 → maxSize = 1, count = 1
 * num = 2: sum = 2 → mp[2] = 1 → mp[2] == maxSize → count = 2
 * num = 3: sum = 3 → mp[3] = 1 → mp[3] == maxSize → count = 3
 * ...
 * num = 9: sum = 9 → mp[9] = 1 → mp[9] == maxSize → count = 9
 * num = 10: sum = 1 → mp[1] = 2 → mp[1] > maxSize → maxSize = 2, count = 1
 * num = 11: sum = 2 → mp[2] = 2 → mp[2] == maxSize → count = 2
 * num = 12: sum = 3 → mp[3] = 2 → mp[3] == maxSize → count = 3
 * num = 13: sum = 4 → mp[4] = 2 → mp[4] == maxSize → count = 4
 *
 * Return 4
 */
