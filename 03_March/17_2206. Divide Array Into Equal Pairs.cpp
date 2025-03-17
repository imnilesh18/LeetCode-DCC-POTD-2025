/*
 * 2206. Divide Array Into Equal Pairs
 *
 * You are given an integer array nums consisting of 2 * n integers.
 * You need to divide nums into n pairs such that:
 * Each element belongs to exactly one pair.
 * The elements present in a pair are equal.
 * Return true if nums can be divided into n pairs, otherwise return false.
 *
 * Example 1:
 * Input: nums = [3,2,3,2,2,2]
 * Output: true
 * Explanation:
 * There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
 * If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.
 *
 * Example 2:
 * Input: nums = [1,2,3,4]
 * Output: false
 * Explanation:
 * There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs satisfy every condition.
 *
 * Constraints:
 * nums.length == 2 * n
 * 1 <= n <= 500
 * 1 <= nums[i] <= 500
 */

// Approach 1: Use an unordered_map to count the frequency of each element and check if each frequency is even.
// Time Complexity: O(n) - We traverse the array once to count frequencies and once more to check them.
// Space Complexity: O(n) - In the worst case, each element is unique, and we store counts for all elements.
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_map<int, int> mp;     // Map to count the frequency of each element

        // Count the frequency of each element in nums
        for (int& x : nums) {
            mp[x]++;
        }

        // Check if the frequency of each element is even
        for (auto& it : mp) {
            if (it.second % 2 != 0) {     // If an element appears an odd number of times, return false
                return false;
            }
        }

        return true;     // All elements appear an even number of times, so we can form pairs
    }
};

/*
 * Dry Run:
 * Input: nums = [3, 2, 3, 2, 2, 2]
 * Step 1: Build frequency map:
 *  mp[3] = 2  (elements: 3, 3)
 *  mp[2] = 4  (elements: 2, 2, 2, 2)
 * Step 2: Check each frequency:
 *  For element 3: 2 % 2 == 0 (OK)
 *  For element 2: 4 % 2 == 0 (OK)
 * Output: true (Since all elements appear an even number of times, the array can be divided into equal pairs)
 */

// Approach 2: Use an unordered_set to keep track of elements that have been seen an odd number of times.
//           When an element is encountered, if it's already in the set, remove it (indicating a pair is formed),
//           otherwise add it to the set. If the set is empty at the end, then every element has been paired.
// Time Complexity: O(n) - We iterate through the array once, and each unordered_set operation is O(1) on average.
// Space Complexity: O(n) - In the worst case, if no element forms a pair, the set will store all elements.

class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_set<int> st;     // Set to store elements that are currently unpaired

        // Iterate through each element in nums
        for (int& x : nums) {
            // If element x is already in the set, it means we've encountered it before and can form a pair.
            if (st.count(x)) {
                st.erase(x);     // Remove x as it now forms a pair with its previous occurrence
            } else {
                st.insert(x);    // Insert x as a potential candidate for pairing
            }
        }

        // If the set is empty, all elements have been paired correctly.
        return st.empty();
    }
};

/*
 * Dry Run:
 * Input: nums = [1, 2, 1, 2]
 * Step 1: Initialize an empty set: st = {}
 * Step 2: Process each element:
 *  - For 1: st is empty, so insert 1. st = {1}
 *  - For 2: st does not contain 2, so insert 2. st = {1, 2}
 *  - For 1: st contains 1, so remove 1. st = {2}
 *  - For 2: st contains 2, so remove 2. st = {}
 * Step 3: st is empty, meaning all elements were paired.
 * Output: true
 */

// Approach 3: Use a boolean vector "paired" of fixed size 501 (since nums[i] ranges from 1 to 500) initialized with true.
//           For each element in nums, toggle its corresponding boolean value. If an element appears an odd number of times,
//           its value will be false. Finally, if all values remain true, then every element is paired.
// Time Complexity: O(n + 501) which simplifies to O(n) - iterating through nums and a fixed loop over 501 elements.
// Space Complexity: O(1) - The space is constant because the boolean vector size is fixed (501).
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        vector<bool> paired(501, true);     // Boolean vector to track pairing status for numbers 1 to 500

        // Toggle the pairing status for each element in nums
        for (int& x : nums) {
            paired[x] = !paired[x];
        }

        // Check if every element's pairing status is true (even occurrences)
        for (int i = 0; i < 501; i++) {
            if (paired[i] == false) {     // Found an element with odd occurrences
                return false;
            }
        }

        return true;     // All elements are paired (even occurrences)
    }
};

/*
 * Dry Run:
 * Input: nums = [2, 3, 2, 3]
 * Step 1: Initialize paired vector with all true values.
 * Step 2: Process each element in nums:
 *  - For 2: paired[2] toggles from true to false.
 *  - For 3: paired[3] toggles from true to false.
 *  - For 2: paired[2] toggles from false back to true.
 *  - For 3: paired[3] toggles from false back to true.
 * Step 3: Check the paired vector:
 *  - paired[2] is true, paired[3] is true, and all other indices remain true.
 * Output: true (All numbers have even occurrences and are successfully paired)
 */

// Approach 4: Sort the array so that identical numbers are adjacent, then iterate through the sorted array in pairs to ensure each adjacent pair is equal.
// Time Complexity: O(n log n) - Sorting the array is the dominant factor.
// Space Complexity: O(1) - The sort is in-place and uses only constant extra space.
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int n = nums.size();          // Get the size of the array

        sort(begin(nums), end(nums)); // Sort the array to group equal numbers together

        // Iterate through the array in steps of 2, checking each pair of elements
        for (int i = 1; i < n; i += 2) {
            if (nums[i] != nums[i - 1]) { // If the current pair is not equal
                return false;             // The array cannot be divided into equal pairs
            }
        }
        return true;      // All pairs are equal, hence return true
    }
};

/*
 * Dry Run:
 * Input: nums = [3, 2, 3, 2]
 * Step 1: Sort the array -> nums becomes [2, 2, 3, 3]
 * Step 2: Check pairs in the sorted array:
 *  - For i = 1: compare nums[0] and nums[1] -> 2 == 2 (OK)
 *  - For i = 3: compare nums[2] and nums[3] -> 3 == 3 (OK)
 * Output: true (All adjacent pairs are equal, so the array can be divided into equal pairs)
 */

// Approach 5: First, sort the array to group identical numbers together. Then, iterate through the sorted array in pairs and use the XOR operator to verify that each adjacent pair consists of equal numbers (since x ^ x = 0).
// Time Complexity: O(n log n) - The sorting step dominates the time complexity.
// Space Complexity: O(1) - The sorting is done in-place, using constant extra space.
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int n = nums.size();

        sort(begin(nums), end(nums));     // Sort the array to ensure equal numbers are adjacent

        // Iterate over the sorted array in pairs
        for (int i = 1; i < n; i += 2) {
            // If the XOR of the pair is not 0, the numbers are not equal, so return false
            if ((nums[i] ^ nums[i - 1]) != 0) {
                return false;
            }
        }
        return true;     // All adjacent pairs are equal, so the array can be divided into pairs
    }
};

/*
 * Dry Run:
 * Input: nums = [4, 1, 4, 1]
 * Step 1: Sort the array -> nums becomes [1, 1, 4, 4]
 * Step 2: Iterate in pairs:
 *  - For i = 1: Compare nums[0] and nums[1] -> 1 and 1, XOR: 1 ^ 1 = 0 (pair is valid)
 *  - For i = 3: Compare nums[2] and nums[3] -> 4 and 4, XOR: 4 ^ 4 = 0 (pair is valid)
 * Output: true (All pairs are valid as each pair's XOR equals 0)
 */
