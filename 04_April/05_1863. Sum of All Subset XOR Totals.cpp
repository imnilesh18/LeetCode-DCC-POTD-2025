/*
 * 1863. Sum of All Subset XOR Totals
 *
 * Easy
 *
 * The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.
 * For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
 * Given an array nums, return the sum of all XOR totals for every subset of nums.
 * Note: Subsets with the same elements should be counted multiple times.
 * An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.
 *
 * Example 1:
 * Input: nums = [1,3]
 * Output: 6
 * Explanation: The 4 subsets of [1,3] are:
 * - The empty subset has an XOR total of 0.
 * - [1] has an XOR total of 1.
 * - [3] has an XOR total of 3.
 * - [1,3] has an XOR total of 1 XOR 3 = 2.
 * 0 + 1 + 3 + 2 = 6
 *
 * Example 2:
 * Input: nums = [5,1,6]
 * Output: 28
 * Explanation: The 8 subsets of [5,1,6] are:
 * - The empty subset has an XOR total of 0.
 * - [5] has an XOR total of 5.
 * - [1] has an XOR total of 1.
 * - [6] has an XOR total of 6.
 * - [5,1] has an XOR total of 5 XOR 1 = 4.
 * - [5,6] has an XOR total of 5 XOR 6 = 3.
 * - [1,6] has an XOR total of 1 XOR 6 = 7.
 * - [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
 * 0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28
 *
 * Example 3:
 * Input: nums = [3,4,5,6,7,8]
 * Output: 480
 * Explanation: The sum of all XOR totals for every subset is 480.
 *
 * Constraints:
 * 1 <= nums.length <= 12
 * 1 <= nums[i] <= 20
 */

// Approach 1: Recursively generate all subsets of nums, then for each subset compute its XOR total and sum these totals.
// Time Complexity: O(2^n * n) - Generating 2^n subsets and processing each element of every subset.
// Space Complexity: O(2^n * n) - In the worst case, all subsets are stored, each of length up to n.
class Solution {
public:
    // Recursive function to generate all subsets.
    void solve(vector<int>& nums, int i, vector<int>& currSubset, vector<vector<int> >& subsets) {
        // Base case: if we've processed all elements, add the current subset to the list.
        if (i == nums.size()) {
            subsets.push_back(currSubset);
            return;
        }

        // Include nums[i] in the current subset.
        currSubset.push_back(nums[i]);
        // Recurse with the next element included.
        solve(nums, i + 1, currSubset, subsets);

        // Backtrack: remove the last element to try the branch where nums[i] is not included.
        currSubset.pop_back();
        // Recurse with the next element excluded.
        solve(nums, i + 1, currSubset, subsets);
    }
    
    int subsetXORSum(vector<int>& nums) {
        vector<vector<int> > subsets;     // Stores all generated subsets.
        vector<int>          currSubset;  // Holds the current subset being built.

        // Generate all subsets.
        solve(nums, 0, currSubset, subsets);

        int result = 0;
        // For each subset, calculate the XOR total and add it to the result.
        for (vector<int>& subset : subsets) {
            int Xor = 0;      // Initialize XOR for the current subset to 0.
            // Process each element in the subset.
            for (int& num : subset) {
                // Update:
                //   Before processing 'num', Xor holds the current XOR value.
                //   After processing 'num', Xor becomes (Xor XOR num).
                Xor ^= num;
            }
            // Add the computed XOR total of the subset to the overall result.
            result += Xor;
        }
        return result;
    }
};

/*
 *
 * Dry Run for Subset Generation (solve function):
 * Consider nums = [1, 3]
 *
 * Initial Call:
 *   nums: [1, 3]
 *   i: 0
 *   currSubset: []
 *   subsets: []
 *
 * Step 1: At i = 0, include nums[0] (1)
 *   currSubset becomes: [1]
 *   Call: solve(nums, 1, [1], subsets)
 *
 *   At i = 1, include nums[1] (3)
 *       currSubset becomes: [1, 3]
 *       Call: solve(nums, 2, [1, 3], subsets)
 *       Base case reached: i == nums.size()
 *       Add [1, 3] to subsets
 *       subsets becomes: [[1, 3]]
 *
 *   Backtrack: remove last element (3)
 *       currSubset reverts to: [1]
 *   At i = 1, exclude nums[1] (3)
 *       Call: solve(nums, 2, [1], subsets)
 *       Base case reached: i == nums.size()
 *       Add [1] to subsets
 *       subsets becomes: [[1, 3], [1]]
 *
 * Backtrack from first call: remove last element (1)
 *       currSubset reverts to: []
 * Step 2: At i = 0, exclude nums[0] (1)
 *   currSubset remains: []
 *   Call: solve(nums, 1, [], subsets)
 *
 *   At i = 1, include nums[1] (3)
 *       currSubset becomes: [3]
 *       Call: solve(nums, 2, [3], subsets)
 *       Base case reached: i == nums.size()
 *       Add [3] to subsets
 *       subsets becomes: [[1, 3], [1], [3]]
 *
 *   Backtrack: remove last element (3)
 *       currSubset reverts to: []
 *   At i = 1, exclude nums[1] (3)
 *       Call: solve(nums, 2, [], subsets)
 *       Base case reached: i == nums.size()
 *       Add [] to subsets
 *       subsets becomes: [[1, 3], [1], [3], []]
 *
 * Final subsets list:
 *   [1, 3]
 *   [1]
 *   [3]
 *   []
 *
 * Visual Diagram of Subset Generation:
 *
 *  [1, 3] Array (Indices):
 *  +-----+-----+
 *  |  1  |  3  |
 *  +-----+-----+
 *
 *  Recursion Tree:
 *
 *                 solve(0, [])
 *                   /       \
 *        include 1/         \ exclude 1
 *                 /           \
 *         solve(1, [1])      solve(1, [])
 *            /      \             /      \
 *  include 3/        \exclude 3/        \ include/exclude
 *          /          \         /           \
 * solve(2, [1,3])  solve(2, [1])  solve(2, [3])  solve(2, [])
 *
 *  Subsets Formed:
 *    [1, 3], [1], [3], []
 */

/*
 *
 * Dry Run for the XOR Calculation Loop (in subsetXORSum function):
 * Consider the subsets generated from nums = [1, 3]:
 *   Subset 1: [1, 3]
 *   Subset 2: [1]
 *   Subset 3: [3]
 *   Subset 4: []  (empty subset)
 *
 * Initial overall result = 0
 *
 * Iteration 1: Processing Subset: [1, 3]
 * --------------------------------------------------
 * Step 1: Initialize Xor = 0
 *   Visual:
 *      +------------------+
 *      | Initial Xor: 0   |
 *      +------------------+
 *
 * Step 2: Process first element (1)
 *   Before: Xor = 0, Current num = 1
 *   Operation: Xor ^= 1  -> 0 XOR 1 = 1
 *   After:  Xor becomes 1
 *   Visual:
 *         +----------------------------+
 *         | Before: Xor = 0, num = 1   |
 *         | After:  Xor = 1            |
 *         +----------------------------+
 *
 * Step 3: Process second element (3)
 *   Before: Xor = 1, Current num = 3
 *   Operation: Xor ^= 3  -> 1 XOR 3 = 2
 *   After:  Xor becomes 2
 *   Visual:
 *         +----------------------------+
 *         | Before: Xor = 1, num = 3   |
 *         | After:  Xor = 2            |
 *         +----------------------------+
 *
 * Step 4: Update overall result
 *   Before: result = 0, Current subset Xor = 2
 *   Operation: result += 2  -> 0 + 2 = 2
 *   After: result becomes 2
 *   Visual:
 *         +-------------------------------------+
 *         | Before: result = 0, subset Xor = 2  |
 *         | After:  result = 2                  |
 *         +-------------------------------------+
 *
 * Iteration 2: Processing Subset: [1]
 * --------------------------------------------------
 * Step 1: Initialize Xor = 0
 *   Visual:
 *         +------------------+
 *         | Initial Xor: 0   |
 *         +------------------+
 *
 * Step 2: Process the only element (1)
 *   Before: Xor = 0, Current num = 1
 *   Operation: Xor ^= 1  -> 0 XOR 1 = 1
 *   After:  Xor becomes 1
 *   Visual:
 *         +----------------------------+
 *         | Before: Xor = 0, num = 1   |
 *         | After:  Xor = 1            |
 *         +----------------------------+
 *
 * Step 3: Update overall result
 *   Before: result = 2, Current subset Xor = 1
 *   Operation: result += 1  -> 2 + 1 = 3
 *   After: result becomes 3
 *   Visual:
 *         +-------------------------------------+
 *         | Before: result = 2, subset Xor = 1  |
 *         | After:  result = 3                  |
 *         +-------------------------------------+
 *
 * Iteration 3: Processing Subset: [3]
 * --------------------------------------------------
 * Step 1: Initialize Xor = 0
 *   Visual:
 *         +------------------+
 *         | Initial Xor: 0   |
 *         +------------------+
 *
 * Step 2: Process the only element (3)
 *   Before: Xor = 0, Current num = 3
 *   Operation: Xor ^= 3  -> 0 XOR 3 = 3
 *   After:  Xor becomes 3
 *   Visual:
 *         +----------------------------+
 *         | Before: Xor = 0, num = 3   |
 *         | After:  Xor = 3            |
 *         +----------------------------+
 *
 * Step 3: Update overall result
 *   Before: result = 3, Current subset Xor = 3
 *   Operation: result += 3  -> 3 + 3 = 6
 *   After: result becomes 6
 *   Visual:
 *         +-------------------------------------+
 *         | Before: result = 3, subset Xor = 3  |
 *         | After:  result = 6                  |
 *         +-------------------------------------+
 *
 * Iteration 4: Processing Subset: [] (empty subset)
 * --------------------------------------------------
 * Step 1: Initialize Xor = 0
 *   Visual:
 *         +------------------+
 *         | Initial Xor: 0   |
 *         +------------------+
 *
 * Step 2: (No elements to process, so Xor remains 0)
 *
 * Step 3: Update overall result
 *   Before: result = 6, Current subset Xor = 0
 *   Operation: result += 0  -> 6 + 0 = 6
 *   After: result remains 6
 *   Visual:
 *         +-------------------------------------+
 *         | Before: result = 6, subset Xor = 0  |
 *         | After:  result = 6                  |
 *         +-------------------------------------+
 *
 * Final overall result = 6
 *
 * Complete Flow for XOR Calculation:
 *    - Subset [1, 3]: Xor = (0 XOR 1) XOR 3 = 2  -> result becomes 2
 *    - Subset [1]:    Xor = 0 XOR 1 = 1           -> result becomes 3 (2 + 1)
 *    - Subset [3]:    Xor = 0 XOR 3 = 3           -> result becomes 6 (3 + 3)
 *    - Subset []:     Xor = 0                   -> result remains 6
 */
