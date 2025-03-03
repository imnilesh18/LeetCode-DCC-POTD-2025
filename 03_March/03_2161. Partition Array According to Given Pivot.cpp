/*
 * 2161. Partition Array According to Given Pivot
 *
 * You are given a 0-indexed integer array nums and an integer pivot. Rearrange nums such that the following conditions are satisfied:
 * Every element less than pivot appears before every element greater than pivot.
 * Every element equal to pivot appears in between the elements less than and greater than pivot.
 * The relative order of the elements less than pivot and the elements greater than pivot is maintained.
 * More formally, consider every pi, pj where pi is the new position of the ith element and pj is the new position of the jth element. If i < j and both elements are smaller (or larger) than pivot, then pi < pj.
 * Return nums after the rearrangement.
 *
 * Example 1:
 * Input: nums = [9,12,5,10,14,3,10], pivot = 10
 * Output: [9,5,3,10,10,12,14]
 * Explanation:
 * The elements 9, 5, and 3 are less than the pivot so they are on the left side of the array.
 * The elements 12 and 14 are greater than the pivot so they are on the right side of the array.
 * The relative ordering of the elements less than and greater than pivot is also maintained. [9, 5, 3] and [12, 14] are the respective orderings.
 *
 * Example 2:
 * Input: nums = [-3,4,3,2], pivot = 2
 * Output: [-3,2,4,3]
 * Explanation:
 * The element -3 is less than the pivot so it is on the left side of the array.
 * The elements 4 and 3 are greater than the pivot so they are on the right side of the array.
 * The relative ordering of the elements less than and greater than pivot is also maintained. [-3] and [4, 3] are the respective orderings.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * -10^6 <= nums[i] <= 10^6
 * pivot equals to an element of nums.
 */

// Approach 1 (Using Three Vectors): Use three separate vectors to collect elements less than, equal to, and greater than the pivot,
// then merge them while preserving the relative order of elements.
// Time Complexity: O(n) - We iterate through the array once.
// Space Complexity: O(n) - Extra space is used for three vectors to store partitioned elements.
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();

        // Vectors to store elements less than, equal to, and greater than the pivot.
        vector<int> lessPivot;
        vector<int> equalPivot;
        vector<int> morePivot;

        // Partition the array into three parts based on the pivot.
        for (int i = 0; i < n; i++) {
            if (nums[i] < pivot) {
                lessPivot.push_back(nums[i]);
            } else if (nums[i] == pivot) {
                equalPivot.push_back(nums[i]);
            } else {
                morePivot.push_back(nums[i]);
            }
        }

        // Append the elements equal to the pivot to the end of the lessPivot vector.
        for (int& num : equalPivot) {
            lessPivot.push_back(num);
        }

        // Append the elements greater than the pivot to the end of the vector.
        for (int& num : morePivot) {
            lessPivot.push_back(num);
        }

        return lessPivot;
    }
};

/*
 * Dry Run
 * Input: nums = [9, 12, 5, 10, 14, 3, 10], pivot = 10
 *
 * Iteration over nums:
 * 1. nums[0] = 9   -> 9 < 10, add to lessPivot  => lessPivot = [9]
 * 2. nums[1] = 12  -> 12 > 10, add to morePivot  => morePivot = [12]
 * 3. nums[2] = 5   -> 5 < 10, add to lessPivot   => lessPivot = [9, 5]
 * 4. nums[3] = 10  -> 10 == 10, add to equalPivot  => equalPivot = [10]
 * 5. nums[4] = 14  -> 14 > 10, add to morePivot  => morePivot = [12, 14]
 * 6. nums[5] = 3   -> 3 < 10, add to lessPivot   => lessPivot = [9, 5, 3]
 * 7. nums[6] = 10  -> 10 == 10, add to equalPivot  => equalPivot = [10, 10]
 *
 * Merging steps:
 * - Append equalPivot to lessPivot: [9, 5, 3, 10, 10]
 * - Append morePivot to the merged vector: [9, 5, 3, 10, 10, 12, 14]
 *
 * Output: [9, 5, 3, 10, 10, 12, 14]
 */

// Approach 2 (Using Three Pointers): Count the number of elements less than and equal to the pivot to pre-determine positions in the result array, then place each element accordingly while preserving order.
// Time Complexity: O(n) - Two passes over the array: one for counting and one for placing elements.
// Space Complexity: O(n) - A new result vector of size n is used.
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();

        int countLess  = 0;     // Count of elements less than pivot
        int countEqual = 0;     // Count of elements equal to pivot

        // First pass: Count elements less than and equal to pivot.
        for (int& num : nums) {
            if (num < pivot) {
                countLess++;
            } else if (num == pivot) {
                countEqual++;
            }
        }

        // Set starting indices for each segment in the result array.
        int         i = 0;                      // Index for elements less than pivot.
        int         j = countLess;              // Index for elements equal to pivot.
        int         k = countLess + countEqual; // Index for elements greater than pivot.
        vector<int> result(n);                  // Result vector to store partitioned elements.

        // Second pass: Place each element in its correct segment based on comparison with pivot.
        for (int& num : nums) {
            if (num < pivot) {
                result[i] = num;     // Place element in less-than-pivot segment.
                i++;
            } else if (num == pivot) {
                result[j] = num;     // Place element in equal-to-pivot segment.
                j++;
            } else {
                result[k] = num;     // Place element in greater-than-pivot segment.
                k++;
            }
        }

        return result;
    }
};

/*
 * Dry Run
 * Input: nums = [9, 12, 5, 10, 14, 3, 10], pivot = 10
 *
 * Step 1: Counting
 * - Iterate through nums:
 * 9 < 10 -> countLess becomes 1.
 * 12 > 10 -> no change.
 * 5 < 10 -> countLess becomes 2.
 * 10 == 10 -> countEqual becomes 1.
 * 14 > 10 -> no change.
 * 3 < 10 -> countLess becomes 3.
 * 10 == 10 -> countEqual becomes 2.
 *
 * Step 2: Determine starting indices
 * - i = 0 (for elements < pivot)
 * - j = countLess = 3 (for elements == pivot)
 * - k = countLess + countEqual = 3 + 2 = 5 (for elements > pivot)
 *
 * Step 3: Placing elements
 * - Process 9 (<10): result[0] = 9; i becomes 1.
 * - Process 12 (>10): result[5] = 12; k becomes 6.
 * - Process 5 (<10): result[1] = 5; i becomes 2.
 * - Process 10 (==10): result[3] = 10; j becomes 4.
 * - Process 14 (>10): result[6] = 14; k becomes 7.
 * - Process 3 (<10): result[2] = 3; i becomes 3.
 * - Process 10 (==10): result[4] = 10; j becomes 5.
 *
 * Final Result: [9, 5, 3, 10, 10, 12, 14]
 */

// Approach 3: Traverse the array from both ends simultaneously—one pointer collects elements less than pivot from the front and the other collects elements greater than pivot from the back—then fill the remaining positions with the pivot.
// Time Complexity: O(n) - Each element is processed at most once during the traversal and then filled in the gap.
// Space Complexity: O(n) - An extra vector of size n is used to store the rearranged array.
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();

        vector<int> result(n);

        // original nums pointers: i for forward traversal, j for backward traversal.
        int i = 0;
        int j = n - 1;

        // result array pointers: i_ for placing elements less than pivot, j_ for placing elements greater than pivot.
        int i_ = 0;
        int j_ = n - 1;

        // Process elements from both ends until all positions have been examined.
        while (i < n && j >= 0) {
            if (nums[i] < pivot) {
                result[i_] = nums[i];
                i_++;
            }

            if (nums[j] > pivot) {
                result[j_] = nums[j];
                j_--;
            }

            i++;
            j--;
        }

        // Fill the gap between i_ and j_ with the pivot value.
        while (i_ <= j_) {
            result[i_] = pivot;
            i_++;
        }

        return result;
    }
};

/*
 * Dry Run
 * Input: nums = [9, 12, 5, 10, 14, 3, 10], pivot = 10
 * n = 7, result = [_, _, _, _, _, _, _]
 * Initial pointers: i = 0, j = 6, i_ = 0, j_ = 6
 *
 * Iteration 1:
 * - i = 0: nums[0] = 9 < 10 -> result[0] = 9; i_ becomes 1.
 * - j = 6: nums[6] = 10 is not > 10 -> no change.
 * Update: i becomes 1, j becomes 5.
 *
 * Iteration 2:
 * - i = 1: nums[1] = 12 is not < 10 -> no change.
 * - j = 5: nums[5] = 3 is not > 10 -> no change.
 * Update: i becomes 2, j becomes 4.
 *
 * Iteration 3:
 * - i = 2: nums[2] = 5 < 10 -> result[1] = 5; i_ becomes 2.
 * - j = 4: nums[4] = 14 > 10 -> result[6] = 14; j_ becomes 5.
 * Update: i becomes 3, j becomes 3.
 *
 * Iteration 4:
 * - i = 3: nums[3] = 10 is not < 10 -> no change.
 * - j = 3: nums[3] = 10 is not > 10 -> no change.
 * Update: i becomes 4, j becomes 2.
 *
 * Iteration 5:
 * - i = 4: nums[4] = 14 is not < 10 -> no change.
 * - j = 2: nums[2] = 5 is not > 10 -> no change.
 * Update: i becomes 5, j becomes 1.
 *
 * Iteration 6:
 * - i = 5: nums[5] = 3 < 10 -> result[2] = 3; i_ becomes 3.
 * - j = 1: nums[1] = 12 > 10 -> result[5] = 12; j_ becomes 4.
 * Update: i becomes 6, j becomes 0.
 *
 * Iteration 7:
 * - i = 6: nums[6] = 10 is not < 10 -> no change.
 * - j = 0: nums[0] = 9 is not > 10 -> no change.
 * Update: i becomes 7, j becomes -1.
 * Exit loop.
 *
 * Fill gap:
 * i_ = 3, j_ = 4, so fill indices 3 and 4 with pivot:
 * - result[3] = 10; i_ becomes 4.
 * - result[4] = 10; i_ becomes 5.
 * Final result: [9, 5, 3, 10, 10, 12, 14]
 */
