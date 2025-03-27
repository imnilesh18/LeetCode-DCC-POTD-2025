/*
 * 2780. Minimum Index of a Valid Split
 *
 * An element x of an integer array arr of length m is dominant if more than half the elements of arr have a value of x.
 * You are given a 0-indexed integer array nums of length n with one dominant element.
 * You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1], but the split is only valid if:
 * 0 <= i < n - 1
 * nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.
 * Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j, both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.
 * Return the minimum index of a valid split. If no valid split exists, return -1.
 *
 * Example 1:
 * Input: nums = [1,2,2,2]
 * Output: 2
 * Explanation: We can split the array at index 2 to obtain arrays [1,2,2] and [2].
 * In array [1,2,2], element 2 is dominant since it occurs twice in the array and 2 * 2 > 3.
 * In array [2], element 2 is dominant since it occurs once in the array and 1 * 2 > 1.
 * Both [1,2,2] and [2] have the same dominant element as nums, so this is a valid split.
 * It can be shown that index 2 is the minimum index of a valid split.
 *
 * Example 2:
 * Input: nums = [2,1,3,1,1,1,7,1,2,1]
 * Output: 4
 * Explanation: We can split the array at index 4 to obtain arrays [2,1,3,1,1] and [1,7,1,2,1].
 * In array [2,1,3,1,1], element 1 is dominant since it occurs thrice in the array and 3 * 2 > 5.
 * In array [1,7,1,2,1], element 1 is dominant since it occurs thrice in the array and 3 * 2 > 5.
 * Both [2,1,3,1,1] and [1,7,1,2,1] have the same dominant element as nums, so this is a valid split.
 * It can be shown that index 4 is the minimum index of a valid split.
 *
 * Example 3:
 * Input: nums = [3,3,3,3,7,2,2]
 * Output: -1
 * Explanation: It can be shown that there is no valid split.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * nums has exactly one dominant element.
 */

// Approach 1 (Using Hashmaps): Use two hashmaps to count frequencies in the left and right subarrays; iterate through the array to update counts and check if the current number is dominant in both parts.
// Time Complexity: O(n) - We iterate through the array twice (once to fill the right map and once to check each split).
// Space Complexity: O(n) - We use two hashmaps to store frequencies, which in the worst-case can hold up to n elements.
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, int> mp1;     // stores frequency counts of elements in the left subarray
        unordered_map<int, int> mp2;     // stores frequency counts of elements in the right subarray

        // Populate mp2 with the frequency counts for the entire array
        for (int& num : nums) {
            mp2[num]++;
        }

        // Iterate over the array to simulate splitting at each index i
        for (int i = 0; i < n; i++) {
            int num = nums[i];

            mp1[num]++;         // Add current number to the left subarray frequency map
            mp2[num]--;         // Remove current number from the right subarray frequency map

            int n1 = i + 1;     // Length of the left subarray
            int n2 = n - i - 1; // Length of the right subarray

            // Check if 'num' is dominant in both subarrays:
            // Dominant means frequency * 2 > length of the subarray
            if (mp1[num] * 2 > n1 && mp2[num] * 2 > n2) {
                return i;     // Return the first valid index where both subarrays have the same dominant element
            }
        }
        return -1;     // If no valid split exists, return -1
    }
};

/*
 * Dry Run:
 * For nums = [1, 2, 2, 2]:
 * 1. Initial setup:
 * - mp2 after loop: {1: 1, 2: 3}
 * - mp1 is empty.
 *
 * 2. i = 0:
 * - Current num = 1
 * - Update mp1: {1: 1}
 * - Update mp2: {1: 0, 2: 3}
 * - Left subarray length n1 = 1, Right subarray length n2 = 3
 * - Check: For num 1, 1*2 = 2 > 1 (true) but 0*2 = 0 > 3 (false)
 * - Not a valid split.
 *
 * 3. i = 1:
 * - Current num = 2
 * - Update mp1: {1: 1, 2: 1}
 * - Update mp2: {1: 0, 2: 2}
 * - n1 = 2, n2 = 2
 * - Check: For num 2, 1*2 = 2 > 2 (false)
 * - Not a valid split.
 *
 * 4. i = 2:
 * - Current num = 2
 * - Update mp1: {1: 1, 2: 2}
 * - Update mp2: {1: 0, 2: 1}
 * - n1 = 3, n2 = 1
 * - Check: For num 2, 2*2 = 4 > 3 (true) and 1*2 = 2 > 1 (true)
 * - Both conditions satisfied, hence valid split at index 2.
 *
 * Return index 2.
 */

// Approach 2 (Boyer-Moore Voting Algorithm): First, use the Boyer-Moore Voting Algorithm to identify the majority (dominant) element.
// Time Complexity: O(n) - Three passes over the array (one for majority element, one for counting, and one for checking splits).
// Space Complexity: O(1) - Only constant extra space is used.
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int n = nums.size();

        // Find the majority element using Boyer-Moore Voting Algorithm.
        int maj   = -1;
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (count == 0) {
                maj   = nums[i];
                count = 1;
            } else if (nums[i] == maj) {
                count++;
            } else {
                count--;
            }
        }

        // Count the total occurrences of the majority element in the array.
        int majCount = 0;
        for (int& num : nums) {
            if (num == maj) {
                majCount++;
            }
        }

        // Reset count for the left subarray and iterate to find a valid split.
        count = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == maj) {
                count++;
            }

            int remainingCount = majCount - count; // Occurrences of maj in the right subarray.
            int n1             = i + 1;            // Length of the left subarray.
            int n2             = n - i - 1;        // Length of the right subarray.

            // Check if maj is dominant in both subarrays.
            if (count * 2 > n1 && remainingCount * 2 > n2) {
                return i;      // Return the minimum index where a valid split is found.
            }
        }
        return -1;      // If no valid split exists, return -1.
    }
};

/*
 * Dry Run:
 * For nums = [1, 2, 2, 2]:
 * 1. Majority Element Identification:
 * - i = 0: count=0, set maj=1, count becomes 1.
 * - i = 1: nums[1]=2, not equal to maj (1), count decreases to 0.
 * - i = 2: count=0, set maj=2, count becomes 1.
 * - i = 3: nums[3]=2, equal to maj (2), count becomes 2.
 * Result: maj = 2.
 *
 * 2. Count Total Occurrences of maj (2):
 * - majCount = 3.
 *
 * 3. Finding Valid Split:
 * - i = 0:
 *     count = 0 + (nums[0]==maj? 0 : 0) = 0,
 *     n1 = 1, n2 = 3, left count for maj is 0 and remainingCount = 3.
 *     Check: 0*2 > 1 (false), so not valid.
 * - i = 1:
 *     count = 0 + (nums[1]==maj? 1 : 0) = 1,
 *     n1 = 2, n2 = 2, remainingCount = 3 - 1 = 2.
 *     Check: 1*2 > 2 (false), so not valid.
 * - i = 2:
 *     count = 1 + (nums[2]==maj? 1 : 0) = 2,
 *     n1 = 3, n2 = 1, remainingCount = 3 - 2 = 1.
 *     Check: 2*2 > 3 (true) and 1*2 > 1 (true),
 *     Valid split found at index 2.
 *
 * Return index 2.
 */
