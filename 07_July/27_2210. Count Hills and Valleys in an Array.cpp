/*
 * 2210. Count Hills and Valleys in an Array
 *
 * Easy
 *
 * You are given a 0-indexed integer array nums. An index i is part of a hill in nums if the closest non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is part of a valley in nums if the closest non-equal neighbors of i are larger than nums[i]. Adjacent indices i and j are part of the same hill or valley if nums[i] == nums[j].
 *
 * Note that for an index to be part of a hill or valley, it must have a non-equal neighbor on both the left and right of the index.
 *
 * Return the number of hills and valleys in nums.
 *
 * Example 1:
 * Input: nums = [2,4,1,1,6,5]
 * Output: 3
 * Explanation:
 * At index 0: There is no non-equal neighbor of 2 on the left, so index 0 is neither a hill nor a valley.
 * At index 1: The closest non-equal neighbors of 4 are 2 and 1. Since 4 > 2 and 4 > 1, index 1 is a hill.
 * At index 2: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 2 is a valley.
 * At index 3: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 3 is a valley, but note that it is part of the same valley as index 2.
 * At index 4: The closest non-equal neighbors of 6 are 1 and 5. Since 6 > 1 and 6 > 5, index 4 is a hill.
 * At index 5: There is no non-equal neighbor of 5 on the right, so index 5 is neither a hill nor a valley.
 * There are 3 hills and valleys so we return 3.
 *
 * Example 2:
 * Input: nums = [6,6,5,5,4,1]
 * Output: 0
 * Explanation:
 * At index 0: There is no non-equal neighbor of 6 on the left, so index 0 is neither a hill nor a valley.
 * At index 1: There is no non-equal neighbor of 6 on the left, so index 1 is neither a hill nor a valley.
 * At index 2: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4, index 2 is neither a hill nor a valley.
 * At index 3: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4, index 3 is neither a hill nor a valley.
 * At index 4: The closest non-equal neighbors of 4 are 5 and 1. Since 4 < 5 and 4 > 1, index 4 is neither a hill nor a valley.
 * At index 5: There is no non-equal neighbor of 1 on the right, so index 5 is neither a hill nor a valley.
 * There are 0 hills and valleys so we return 0.
 *
 * Constraints:
 * 3 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 */

// Intuition 1: To determine if a point is a hill or valley, we need its nearest different neighbors. It's efficient to pre-calculate these neighbors for all points in two passes rather than finding them repeatedly.
// Approach 1: First, create a `left` array storing the closest non-equal neighbor to the left for each element. Second, create a `right` array for the right neighbors. Finally, iterate through the array, using the pre-calculated neighbors to check the hill/valley condition, ensuring plateaus are counted only once by checking against the previous element.
// Time Complexity: O(N), as the algorithm involves three separate linear passes through the array.
// Space Complexity: O(N), due to the two auxiliary arrays, `left` and `right`, each of size N.
class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int         n = nums.size(); // Get the total number of elements in the array.
        vector<int> left(n, -1);     // This vector will store the closest non-equal neighbor to the left.

        // First pass: Populate the 'left' neighbor array from left to right.
        for (int i = 1; i < n; i++) {
            // If the previous element is different, it's the neighbor.
            // If they are the same (a plateau), carry over the neighbor from the previous element.
            left[i] = nums[i] != nums[i - 1] ? nums[i - 1] : left[i - 1];
        }

        vector<int> right(n, -1);  // This vector will store the closest non-equal neighbor to the right.
        // Second pass (from end to start): Populate the 'right' neighbor array.
        for (int i = n - 2; i >= 0; i--) {
            // If the next element is different, it's the neighbor.
            // Otherwise, carry over the neighbor from the next element.
            right[i] = nums[i] != nums[i + 1] ? nums[i + 1] : right[i + 1];
        }

        int count = 0; // Initialize the counter for hills and valleys.
        // Third pass: Iterate through the array to count the hills and valleys.
        // We skip the first and last elements as they cannot be hills or valleys.
        for (int i = 1; i < n - 1; i++) {
            // A point must have a valid non-equal neighbor on both sides to be a hill or valley.
            if (left[i] == -1 || right[i] == -1) {
                continue;
            }

            // Check for the hill condition (current > both neighbors) OR
            // the valley condition (current < both neighbors).
            if (nums[i] > left[i] && nums[i] > right[i] ||
                nums[i] < left[i] && nums[i] < right[i]) {
                // This check ensures we only count a plateau once, at its starting point.
                if (nums[i] != nums[i - 1]) {
                    count++;
                }
            }
        }
        return count; // Return the final total count.
    }
};

/*
 *
 * Dry Run for nums = [2, 4, 1, 1, 6, 5]
 *
 * 1. Initial State:
 * - n = 6
 * - left = [-1, -1, -1, -1, -1, -1]
 * - right = [-1, -1, -1, -1, -1, -1]
 * - count = 0
 *
 * 2. Populate `left` array (loop i from 1 to 5):
 * - i = 1: `left[1]` = nums[0] = 2
 * - i = 2: `left[2]` = nums[1] = 4
 * - i = 3: `nums[3]` == `nums[2]`, so `left[3]` = `left[2]` = 4
 * - i = 4: `left[4]` = nums[3] = 1
 * - i = 5: `left[5]` = nums[4] = 6
 * - Final `left` = [-1, 2, 4, 4, 1, 6]
 *
 * 3. Populate `right` array (loop i from 4 to 0):
 * - i = 4: `right[4]` = nums[5] = 5
 * - i = 3: `right[3]` = nums[4] = 6
 * - i = 2: `nums[2]` == `nums[3]`, so `right[2]` = `right[3]` = 6
 * - i = 1: `right[1]` = nums[2] = 1
 * - i = 0: `right[0]` = nums[1] = 4
 * - Final `right` = [4, 1, 6, 6, 5, -1]
 *
 * 4. Count Hills and Valleys (loop i from 1 to 4):
 * - i = 1: `nums[1]`=4, `left[1]`=2, `right[1]`=1. -> Hill. `nums[1]` != `nums[0]`. `count` becomes 1.
 * - i = 2: `nums[2]`=1, `left[2]`=4, `right[2]`=6. -> Valley. `nums[2]` != `nums[1]`. `count` becomes 2.
 * - i = 3: `nums[3]`=1, `left[3]`=4, `right[3]`=6. -> Valley. `nums[3]` == `nums[2]`. `count` remains 2.
 * - i = 4: `nums[4]`=6, `left[4]`=1, `right[4]`=5. -> Hill. `nums[4]` != `nums[3]`. `count` becomes 3.
 *
 * 5. Final Result: return `count`, which is 3.
 *
 */

// Intuition 2: This method uses a simplified two-pointer approach to find "turning points" (hills/valleys). It uses the last found turning point as the left reference, rather than searching for the strictly closest non-equal neighbor, which works for the problem's core logic but differs from a literal interpretation.
// Approach 2: A pointer `i` anchors the last hill/valley. A second pointer `j` scans the array. A hill/valley is counted at index `j` if `nums[j]` is a peak or trough relative to `nums[i]` and `nums[j+1]`. When one is found, `i` is updated to `j` to set a new anchor.
// Time Complexity: O(N), because the scanner pointer `j` traverses the array once.
// Space Complexity: O(1), as it only uses a constant amount of extra space for pointers and a counter.
class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int n = nums.size();
        // `i` acts as the left anchor, pointing to the last identified hill or valley.
        int i = 0;
        // `j` is the main scanner, looking for the next hill or valley.
        int j = 1;

        int count = 0; // Stores the total count of hills and valleys.

        // Loop until the scanner `j` can safely look at its right neighbor `j+1`.
        while (j + 1 < n) {
            // Check for a hill (peak) or a valley (trough) at index `j`.
            if ((nums[i] <nums[j] && nums[j]> nums[j + 1])   // Hill condition
                ||
                (nums[i] > nums[j] && nums[j] < nums[j + 1]) // Valley condition
                ) {
                count++;                                     // Increment count if a hill or valley is found.
                i = j;                                       // Update the left anchor to the current position.
            }
            j++;                                             // Move the scanner to the next element.
        }
        return count;                                        // Return the final count.
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [2, 4, 1, 1, 6, 5]
 *
 * Initial: i = 0, j = 1, count = 0
 *
 * j=1: (nums[0]<nums[1] && nums[1]>nums[2]) -> (2<4 && 4>1) is true. Hill found.
 * count becomes 1. i becomes 1.
 *
 * j=2: No condition met.
 *
 * j=3: (nums[1]>nums[3] && nums[3]<nums[4]) -> (4>1 && 1<6) is true. Valley found.
 * count becomes 2. i becomes 3.
 *
 * j=4: (nums[3]<nums[4] && nums[4]>nums[5]) -> (1<6 && 6>5) is true. Hill found.
 * count becomes 3. i becomes 4.
 *
 * j=5: Loop terminates as j+1 is not less than n.
 *
 * Final Return: 3
 *
 */
