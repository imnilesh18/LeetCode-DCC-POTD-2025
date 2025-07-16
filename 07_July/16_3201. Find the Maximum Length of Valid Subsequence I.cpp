/*
 * 3201. Find the Maximum Length of Valid Subsequence I
 *
 * Medium
 *
 * You are given an integer array nums.
 * A subsequence sub of nums with length x is called valid if it satisfies:
 * (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
 * Return the length of the longest valid subsequence of nums.
 * A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: 4
 * Explanation:
 * The longest valid subsequence is [1, 2, 3, 4].
 *
 * Example 2:
 * Input: nums = [1,2,1,1,2,1,2]
 * Output: 6
 * Explanation:
 * The longest valid subsequence is [1, 2, 1, 2, 1, 2].
 *
 * Example 3:
 * Input: nums = [1,3]
 * Output: 2
 * Explanation:
 * The longest valid subsequence is [1, 3].
 *
 * Constraints:
 * 2 <= nums.length <= 2 * 10^5
 * 1 <= nums[i] <= 10^7
 */

// Approach: Count total evens and odds to handle uniform-parity subsequences, then compute the longest alternating-parity subsequence; the answer is the maximum of these three possibilities.
// Time Complexity: O(n) – one pass to count evens/odds and one pass to build the alternating-parity subsequence.
// Space Complexity: O(1) – uses only a fixed number of integer variables.
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int countEven = 0, countOdd = 0;

        // Count the number of even and odd elements in the array
        for (int num : nums) {
            if (num % 2 == 0) {
                countEven++;
            }else{
                countOdd++;
            }
        }

        // Build the longest subsequence where adjacent elements alternate in parity
        int altLen     = 1;                      // At least one element always forms a valid subsequence
        int prevParity = nums[0] % 2;            // Parity of the first element

        for (int i = 1; i < nums.size(); ++i) {
            int currParity = nums[i] % 2;       // Compute current element's parity
            if (currParity != prevParity) {     // If it alternates with the previous
                altLen++;                       // extend the alternating subsequence
                prevParity = currParity;        // update the reference parity
            }
        }

        // The answer is the max of: all-even subsequence, all-odd subsequence, or the alternating-parity subsequence
        return max({ countEven, countOdd, altLen });
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [1, 2, 1, 1, 2, 1, 2]
 *
 * 1) Counting evens and odds:
 *    countEven = 0, countOdd = 0
 *    - num = 1 -> odd  => countOdd = 1
 *    - num = 2 -> even => countEven = 1
 *    - num = 1 -> odd  => countOdd = 2
 *    - num = 1 -> odd  => countOdd = 3
 *    - num = 2 -> even => countEven = 2
 *    - num = 1 -> odd  => countOdd = 4
 *    - num = 2 -> even => countEven = 3
 *    => countEven = 3, countOdd = 4
 *
 * 2) Building alternating-parity subsequence:
 *    altLen = 1
 *    prevParity = nums[0] % 2 = 1
 *
 *    i = 1: nums[1]=2  currParity=0 != prevParity(1) -> altLen=2, prevParity=0
 *    i = 2: nums[2]=1  currParity=1 != prevParity(0) -> altLen=3, prevParity=1
 *    i = 3: nums[3]=1  currParity=1 == prevParity(1) -> no change
 *    i = 4: nums[4]=2  currParity=0 != prevParity(1) -> altLen=4, prevParity=0
 *    i = 5: nums[5]=1  currParity=1 != prevParity(0) -> altLen=5, prevParity=1
 *    i = 6: nums[6]=2  currParity=0 != prevParity(1) -> altLen=6, prevParity=0
 *    => altLen = 6
 *
 * 3) Final result = max(countEven, countOdd, altLen) = max(3, 4, 6) = 6
 */
