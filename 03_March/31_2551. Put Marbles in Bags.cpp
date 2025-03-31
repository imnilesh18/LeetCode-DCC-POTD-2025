/*
 * 2551. Put Marbles in Bags
 *
 * Hard
 *
 * You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of the ith marble. You are also given the integer k.
 *
 * Divide the marbles into the k bags according to the following rules:
 *
 * No bag is empty.
 * If the ith marble and jth marble are in a bag, then all marbles with an index between the ith and jth indices should also be in that same bag.
 * If a bag consists of all the marbles with an index from i to j inclusively, then the cost of the bag is weights[i] + weights[j].
 * The score after distributing the marbles is the sum of the costs of all the k bags.
 *
 * Return the difference between the maximum and minimum scores among marble distributions.
 *
 * Example 1:
 * Input: weights = [1,3,5,1], k = 2
 * Output: 4
 * Explanation:
 * The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
 * The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
 * Thus, we return their difference 10 - 6 = 4.
 *
 * Example 2:
 * Input: weights = [1, 3], k = 2
 * Output: 0
 * Explanation: The only distribution possible is [1],[3].
 * Since both the maximal and minimal score are the same, we return 0.
 *
 * Constraints:
 * 1 <= k <= weights.length <= 10^5
 * 1 <= weights[i] <= 10^9
 */

// Approach:
// 1. The total cost for any valid partition always includes the weights of the first and last marbles.
// 2. The only flexibility lies in where we make the cuts between adjacent marbles.
// 3. Each cut adds an extra cost equal to the sum of the two marbles it separates (i.e., weights[i] + weights[i+1]).
// 4. We need to select (k-1) cuts; to minimize the extra cost, choose the smallest (k-1) adjacent pair sums, and to maximize it, choose the largest (k-1) sums. The answer is the difference between these two totals.
// Time Complexity: O(n log n) - primarily due to sorting the (n-1) pair sums.
// Space Complexity: O(n) - for storing the pair sums.
class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int         n = weights.size();        // Total number of marbles
        int         m = n - 1;                 // Number of adjacent pairs
        vector<int> pairSum(m, 0);             // Vector to store sums of adjacent pairs

        // Compute the sum for each adjacent pair
        for (int i = 0; i < m; i++) {
            pairSum[i] = weights[i] + weights[i + 1];      // Pair sum at index i
        }

        // Sort the pair sums to easily pick the smallest and largest (k-1) values
        sort(begin(pairSum), end(pairSum));

        long maxSum = 0;
        long minSum = 0;

        // Accumulate (k-1) smallest values for the minimum score
        // and (k-1) largest values for the maximum score
        for (int i = 0; i < k - 1; i++) {
            minSum += pairSum[i];                // Adding the smallest (k-1) pair sums
            maxSum += pairSum[m - 1 - i];        // Adding the largest (k-1) pair sums
        }

        // The answer is the difference between maximum and minimum extra costs
        return maxSum - minSum;
    }
};

/*
 *
 * Dry Run for weights = {3, 2, 1, 4, 5, 2} and k = 3
 *
 * Intuition Recap:
 * - The first and last marbles (3 and 2) are always part of the total cost.
 * - Only the cuts (i.e., between adjacent marbles) affect the extra cost.
 * - Each cut contributes a cost equal to the sum of the two marbles it separates.
 * - We choose 2 cuts (since k-1 = 2) to minimize or maximize the extra cost.
 *
 * Step 1: Initial Setup
 * --------------------------------------------------------
 * | weights array:       [ 3,   2,   1,   4,   5,   2 ]  |
 * | Number of marbles:   6                               |
 * | Number of pairs:     5  (6 - 1)                      |
 * --------------------------------------------------------
 *
 * Step 2: Compute the pairSum array (sums of adjacent pairs)
 *   pairSum[0] = 3 + 2 = 5
 *   pairSum[1] = 2 + 1 = 3
 *   pairSum[2] = 1 + 4 = 5
 *   pairSum[3] = 4 + 5 = 9
 *   pairSum[4] = 5 + 2 = 7
 *
 * Visual Representation:
 * --------------------------------------------------
 * | pairSum array:       [ 5,   3,   5,   9,   7 ] |
 * --------------------------------------------------
 *
 * Step 3: Sort the pairSum array
 *
 * Before Sorting:  [ 5,   3,   5,   9,   7 ]
 * After Sorting:
 * --------------------------------------------------
 * | Sorted pairSum:      [ 3,   5,   5,   7,   9 ] |
 * --------------------------------------------------
 *
 * Step 4: Select (k-1)=2 cuts
 * For Minimum Score (minSum):
 *   - Choose the smallest two sums: 3 and 5
 *   - minSum = 3 + 5 = 8
 *
 * For Maximum Score (maxSum):
 *   - Choose the largest two sums: 9 and 7
 *   - maxSum = 9 + 7 = 16
 *
 * Step 5: Compute the Difference
 *   Difference = maxSum - minSum = 16 - 8 = 8
 *
 * Visual Summary:
 * ---------------------------------------------------------
 * | Initial weights:      [ 3,   2,   1,   4,   5,   2 ]  |
 * | Computed pairSum:     [ 5,   3,   5,   9,   7 ]       |
 * | Sorted pairSum:       [ 3,   5,   5,   7,   9 ]       |
 * | Minimum extra cost:   3 + 5 = 8                       |
 * | Maximum extra cost:   7 + 9 = 16                      |
 * | Final Answer:         16 - 8 = 8                      |
 * ---------------------------------------------------------
 *
 * Thus, the difference between the maximum and minimum scores is 8.
 *
 */
