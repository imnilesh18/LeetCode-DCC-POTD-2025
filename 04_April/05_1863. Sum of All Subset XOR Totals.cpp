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
    void solve(vector<int>& nums, int i, vector<int>& currSubset, vector<vector<int>>& subsets) {
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
        vector<vector<int>> subsets;     // Stores all generated subsets.
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

// Approach 2: Use recursion to compute the XOR total for each subset on the fly without storing all subsets.
//           At each index, choose to either include the current element (update XOR) or exclude it (keep XOR unchanged).
//           Sum the XOR totals returned by the recursive calls.
// Time Complexity: O(2^n) - Each element has 2 choices, leading to 2^n recursive calls.
// Space Complexity: O(n) - The recursion stack depth is at most n.
class Solution {
public:
    // Recursive function that returns the sum of XOR totals for all subsets starting at index i,
    // with the current cumulative XOR value 'Xor'.
    int solve(vector<int>& nums, int i, int Xor) {
        // Base case: if we've processed all elements, return the current XOR value.
        if (i == nums.size()) {
            return Xor;
        }

        // Include nums[i]: update the XOR with nums[i] and move to the next element.
        int include = solve(nums, i + 1, nums[i] ^ Xor);

        // Exclude nums[i]: keep the current XOR unchanged and move to the next element.
        int exclude = solve(nums, i + 1, Xor);

        // The total sum is the sum from including and excluding the current element.
        return include + exclude;
    }
    int subsetXORSum(vector<int>& nums) {
        // Start recursion with index 0 and initial XOR value 0.
        return solve(nums, 0, 0);
    }
};

/*
 *
 * Dry Run for solve function:
 * Consider nums = [1, 3]
 *
 * Initial Call:
 *   Call: solve(nums, i=0, Xor=0)
 *   Visual Diagram:
 *               solve(0, 0)
 *                   |
 *          +--------+--------+
 *          |                 |
 *    include branch      exclude branch
 *
 * Step 1: At i = 0, element = 1
 *   - Include:
 *         New Xor = 0 XOR 1 = 1
 *         Call: solve(nums, i=1, Xor=1)
 *         Visual:
 *                   solve(1, 1)
 *                       |
 *              +--------+--------+
 *              |                 |
 *        include branch      exclude branch
 *
 *   - Exclude:
 *         Xor remains 0
 *         Call: solve(nums, i=1, Xor=0)
 *         Visual:
 *                   solve(1, 0)
 *                       |
 *              +--------+--------+
 *              |                 |
 *        include branch      exclude branch
 *
 * Step 2: At i = 1, for the include branch from previous call (solve(1, 1)), element = 3
 *   - Include:
 *         New Xor = 1 XOR 3 = 2
 *         Call: solve(nums, i=2, Xor=2)
 *         Since i == nums.size(), returns 2.
 *         Visual:
 *                solve(2, 2) -> returns 2
 *
 *   - Exclude:
 *         Xor remains 1
 *         Call: solve(nums, i=2, Xor=1)
 *         Since i == nums.size(), returns 1.
 *         Visual:
 *                solve(2, 1) -> returns 1
 *
 *   Result from solve(1, 1): include + exclude = 2 + 1 = 3
 *
 * Step 3: At i = 1, for the exclude branch from the initial call (solve(1, 0)), element = 3
 *   - Include:
 *         New Xor = 0 XOR 3 = 3
 *         Call: solve(nums, i=2, Xor=3)
 *         Since i == nums.size(), returns 3.
 *         Visual:
 *                solve(2, 3) -> returns 3
 *
 *   - Exclude:
 *         Xor remains 0
 *         Call: solve(nums, i=2, Xor=0)
 *         Since i == nums.size(), returns 0.
 *         Visual:
 *                solve(2, 0) -> returns 0
 *
 *   Result from solve(1, 0): include + exclude = 3 + 0 = 3
 *
 * Final Step: Back at the initial call (solve(0, 0)):
 *   - Total Sum = result from including index 0 + result from excluding index 0
 *                = 3 (from solve(1, 1)) + 3 (from solve(1, 0))
 *                = 6
 *
 * Visual Diagram of the Recursion Tree:
 *
 *                    solve(0, 0)
 *                         |
 *          +--------------+---------------+
 *          |                              |
 *   solve(1, 1)                      solve(1, 0)
 *      /       \                        /       \
 * solve(2,2) solve(2,1)          solve(2,3)   solve(2,0)
 *      |         |                  |             |
 *      2         1                  3             0
 *
 * Calculation:
 *    solve(1,1) = 2 + 1 = 3
 *    solve(1,0) = 3 + 0 = 3
 *    Total = 3 + 3 = 6
 *
 * Update Visual (Conceptual Flow):
 *
 *  Initial Call:
 *    Xor = 0, i = 0, Element = 1
 *      Include: Update Xor = 0 XOR 1 = 1  -> Move to i = 1
 *      Exclude: Xor remains 0             -> Move to i = 1
 *
 *  At i = 1 (for branch with Xor = 1):
 *    Xor = 1, Element = 3
 *      Include: Update Xor = 1 XOR 3 = 2  -> i becomes 2, return 2
 *      Exclude: Xor remains 1             -> i becomes 2, return 1
 *
 *  At i = 1 (for branch with Xor = 0):
 *    Xor = 0, Element = 3
 *      Include: Update Xor = 0 XOR 3 = 3  -> i becomes 2, return 3
 *      Exclude: Xor remains 0             -> i becomes 2, return 0
 *
 *  Combining results:
 *    Branch with Xor = 1 returns: 2 + 1 = 3
 *    Branch with Xor = 0 returns: 3 + 0 = 3
 *    Final Result = 3 + 3 = 6
 */

// Approach 3: Use a bitwise trick where the sum of XOR totals for all subsets equals the bitwise OR of all numbers,
//           with (n-1) zeros appended to its binary representation. Appending (n-1) zeros (i.e. left shifting by (n-1))
//           is equivalent to multiplying the OR result by 2^(n-1).
// Time Complexity: O(n) - We iterate once over the array to compute the bitwise OR.
// Space Complexity: O(1) - Only constant extra space is used.

//---------------------------------------------------------------------------------------------------------------------------------------
// Intuition with Examples:
// ---------------------------------------------
// Example 1:
//   nums = [1, 3]
//   n = 2
//   Binary representations:
//      1 -> 01
//      3 -> 11
//   Bitwise OR: 01 | 11 = 11 (binary) = 3 (decimal)
//   Append (n-1) = 1 zero to the right: 11 becomes 110 (binary) = 6 (decimal)
//   Hence, output = 6.
//
// Example 2:
//   nums = [5, 1, 6]
//   n = 3
//   Binary representations:
//      5 -> 101
//      1 -> 001
//      6 -> 110
//   Bitwise OR: 101 | 001 = 101, then 101 | 110 = 111 (binary) = 7 (decimal)
//   Append (n-1) = 2 zeros to the right: 111 becomes 11100 (binary) = 28 (decimal)
//   Hence, output = 28.
//
// Example 3:
//   nums = [5, 20]
//   n = 2
//   Binary representations (using 5 bits for clarity):
//      5  -> 00101
//      20 -> 10100
//   Bitwise OR: 00101 | 10100 = 10101 (binary) = 21 (decimal)
//   Append (n-1) = 1 zero to the right: 10101 becomes 101010 (binary) = 42 (decimal)
//   Hence, output = 42.
//---------------------------------------------------------------------------------------------------------------------------------------
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n      = nums.size();
        int result = 0;

        // Compute the bitwise OR of all elements in the array.
        for (int& num : nums) {
            result |= num;
        }

        // Append (n-1) zeros to the right by left shifting, which is equivalent to multiplying by 2^(n-1).
        return result << (n - 1);
    }
};

/*
 *
 * Dry Run for subsetXORSum Function:
 *
 * Example: nums = [1, 3]
 *
 * Step 1: Initialization
 *   - n = nums.size() = 2
 *   - result = 0
 *
 * Step 2: Compute the bitwise OR of all elements:
 *
 *   Iteration 1:
 *     - Current num = 1 (binary: 01)
 *     - Before: result = 0 (binary: 00)
 *     - Operation: result |= 1  ->  0 | 1 = 1 (binary: 01)
 *     - After: result = 1 (binary: 01)
 *
 *   Iteration 2:
 *     - Current num = 3 (binary: 11)
 *     - Before: result = 1 (binary: 01)
 *     - Operation: result |= 3  ->  1 | 3 = 3 (binary: 11)
 *     - After: result = 3 (binary: 11)
 *
 *   Visual Diagram for Bitwise OR:
 *     +--------------------------------+
 *     |  Initial:   result = 0  (00)   |
 *     |  After 1:  result = 1  (01)    |
 *     |  After 2:  result = 3  (11)    |
 *     +--------------------------------+
 *
 * Step 3: Append (n-1) zeros (Left Shift):
 *   - n - 1 = 2 - 1 = 1, so we append 1 zero to the right.
 *   - Left shift operation: result << 1
 *   - Calculation: 3 (binary: 11) becomes 110 (binary) after shifting left by 1,
 *                  which is 6 in decimal.
 *
 *   Visual Diagram for Final Calculation:
 *     +---------------------------------+
 *     | Before Shift: 3   (binary: 11)  |
 *     | Shift Left by 1:                |
 *     | After Shift: 6   (binary: 110)   |
 *     +---------------------------------+
 *
 * Final Result: 6
 *
 * Summary:
 *   - Bitwise OR of [1, 3] = 3 (binary: 11)
 *   - Append 1 zero (n-1 = 1) gives binary: 110, which equals 6 in decimal.
 *   - Output: 6
 */
