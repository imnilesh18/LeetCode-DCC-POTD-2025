/*
 * 2570. Merge Two 2D Arrays by Summing Values
 *
 * You are given two 2D integer arrays nums1 and nums2.
 * nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
 * nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
 * Each array contains unique ids and is sorted in ascending order by id.
 * Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:
 * Only ids that appear in at least one of the two arrays should be included in the resulting array.
 * Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays, then assume its value in that array to be 0.
 * Return the resulting array. The returned array must be sorted in ascending order by id.
 *
 * Example 1:
 * Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
 * Output: [[1,6],[2,3],[3,2],[4,6]]
 * Explanation: The resulting array contains the following:
 * - id = 1, the value of this id is 2 + 4 = 6.
 * - id = 2, the value of this id is 3.
 * - id = 3, the value of this id is 2.
 * - id = 4, the value of this id is 5 + 1 = 6.
 *
 * Example 2:
 * Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
 * Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
 * Explanation: There are no common ids, so we just include each id with its value in the resulting list.
 *
 * Constraints:
 * 1 <= nums1.length, nums2.length <= 200
 * nums1[i].length == nums2[j].length == 2
 * 1 <= idi, vali <= 1000
 * Both arrays contain unique ids.
 * Both arrays are in strictly ascending order by id.
 */

// Approach 1 (Using Unordered Map): Use a hash map to accumulate sums for each id from both arrays, then build and sort the result vector.
// Time Complexity: O(m+n+k log k) where m and n are the lengths of the arrays and k is the number of unique ids.
// Space Complexity: O(k) for the hash map and the result vector.
class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        // Get sizes of nums1 and nums2
        int m = nums1.size();
        int n = nums2.size();

        // Hash map to store the sum of values for each id
        unordered_map<int, int> mp;
        // Vector to store the final merged result
        vector<vector<int>> result;

        // Process nums1: add each id's value to the map
        for (int i = 0; i < m; i++) {
            int id  = nums1[i][0]; // current id from nums1
            int val = nums1[i][1]; // corresponding value from nums1
            mp[id] += val;         // add value to the map for the given id
        }

        // Process nums2: add each id's value to the map
        for (int i = 0; i < n; i++) {
            int id  = nums2[i][0]; // current id from nums2
            int val = nums2[i][1]; // corresponding value from nums2
            mp[id] += val;         // add value to the map for the given id
        }

        // Build the result vector from the map entries
        for (auto& it : mp) {
            int key = it.first;  // id
            int val = it.second; // total summed value for the id
            result.push_back({ key, val });
        }

        // Sort the result vector by id in ascending order
        sort(begin(result), end(result));
        return result; // return the merged and sorted array
    }
};

/*
 * Dry Run
 * Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
 * Step 1: Process nums1:
 *  - For [1,2]: mp becomes {1:2}
 *  - For [2,3]: mp becomes {1:2, 2:3}
 *  - For [4,5]: mp becomes {1:2, 2:3, 4:5}
 * Step 2: Process nums2:
 *  - For [1,4]: mp becomes {1:6, 2:3, 4:5}
 *  - For [3,2]: mp becomes {1:6, 2:3, 3:2, 4:5}
 *  - For [4,1]: mp becomes {1:6, 2:3, 3:2, 4:6}
 * Step 3: Build result vector from mp:
 *  - Unsorted result could be: [[1,6],[2,3],[3,2],[4,6]]
 * Step 4: Sort result vector by id:
 *  - Sorted result: [[1,6],[2,3],[3,2],[4,6]]
 * Output: [[1,6],[2,3],[3,2],[4,6]]
 */

// Approach 2 (Using Ordered Map): Use an ordered map to accumulate sums for each id, which keeps keys sorted automatically, then build the result vector.
// Time Complexity: O((m+n)*log k) where m and n are the lengths of the arrays and k is the number of unique ids (log k due to map insertions).
// Space Complexity: O(k) for storing the unique ids and their summed values in the map.
class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        int m = nums1.size(); // size of nums1
        int n = nums2.size(); // size of nums2

        // Using an ordered map (std::map) to store the sum of values for each id; keys are maintained in sorted order.
        map<int, int>        mp;
        vector<vector<int>> result;

        // Process nums1: add each id's value to the map.
        for (int i = 0; i < m; i++) {
            int id  = nums1[i][0]; // current id from nums1
            int val = nums1[i][1]; // corresponding value from nums1
            mp[id] += val;         // accumulate the value for this id
        }

        // Process nums2: add each id's value to the map.
        for (int i = 0; i < n; i++) {
            int id  = nums2[i][0]; // current id from nums2
            int val = nums2[i][1]; // corresponding value from nums2
            mp[id] += val;         // accumulate the value for this id
        }

        // Build the result vector from the map entries; map keeps keys sorted.
        for (auto& it : mp) {
            int key = it.first;  // id
            int val = it.second; // total summed value for the id
            result.push_back({ key, val });
        }
        return result; // return the merged and sorted array
    }
};

/*
 * Dry Run
 * Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
 * Process nums1:
 * - For [1,2]: mp becomes {1:2}
 * - For [2,3]: mp becomes {1:2, 2:3}
 * - For [4,5]: mp becomes {1:2, 2:3, 4:5}
 * Process nums2:
 * - For [1,4]: mp becomes {1:6, 2:3, 4:5}
 * - For [3,2]: mp becomes {1:6, 2:3, 3:2, 4:5}
 * - For [4,1]: mp becomes {1:6, 2:3, 3:2, 4:6}
 * Build result:
 * - result = [[1,6],[2,3],[3,2],[4,6]]
 * Output: [[1,6],[2,3],[3,2],[4,6]]
 */

// Approach 3 (Using Two Pointers): Use two pointers to merge two sorted arrays by comparing ids; when ids match, sum the values.
// Time Complexity: O(m+n) since each array is traversed once.
// Space Complexity: O(1) for storing the merged result.
class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        int m = nums1.size();        // Number of elements in nums1
        int n = nums2.size();        // Number of elements in nums2

        int i = 0;                   // Pointer for nums1
        int j = 0;                   // Pointer for nums2
        vector<vector<int>> result; // Vector to store the merged arrays

        // Traverse both arrays until one is exhausted
        while (i < m && j < n) {
            if (nums1[i][0] < nums2[j][0]) {
                result.push_back(nums1[i]);      // nums1's id is smaller, add it to result
                i++;
            } else if (nums2[j][0] < nums1[i][0]) {
                result.push_back(nums2[j]);      // nums2's id is smaller, add it to result
                j++;
            } else {
                // ids are equal, sum the values and add the combined element to result
                result.push_back({ nums1[i][0], nums1[i][1] + nums2[j][1] });
                i++;
                j++;
            }
        }

        // Append any remaining elements from nums1
        while (i < m) {
            result.push_back(nums1[i]);
            i++;
        }

        // Append any remaining elements from nums2
        while (j < n) {
            result.push_back(nums2[j]);
            j++;
        }

        return result;      // Return the merged and sorted array
    }
};

/*
 * Dry Run
 * Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
 * Initialization:
 * i = 0, j = 0, result = []
 * Iteration 1:
 * Compare nums1[0][0] = 1 with nums2[0][0] = 1 (equal)
 * Push {1, 2+4} = {1,6} into result; now i = 1, j = 1
 * Iteration 2:
 * Compare nums1[1][0] = 2 with nums2[1][0] = 3 (2 < 3)
 * Push nums1[1] = {2,3} into result; now i = 2
 * Iteration 3:
 * Compare nums1[2][0] = 4 with nums2[1][0] = 3 (3 < 4)
 * Push nums2[1] = {3,2} into result; now j = 2
 * Iteration 4:
 * Compare nums1[2][0] = 4 with nums2[2][0] = 4 (equal)
 * Push {4, 5+1} = {4,6} into result; now i = 3, j = 3
 * No remaining elements; Final result: [[1,6],[2,3],[3,2],[4,6]]
 */
