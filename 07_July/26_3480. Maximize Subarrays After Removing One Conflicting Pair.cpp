/*
 * 3480. Maximize Subarrays After Removing One Conflicting Pair
 *
 * Hard
 *
 * You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
 *
 * Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
 *
 * Return the maximum number of subarrays possible after removing exactly one conflicting pair.
 *
 * Example 1:
 * Input: n = 4, conflictingPairs = [[2,3],[1,4]]
 * Output: 9
 * Explanation:
 * Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
 * There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
 * The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
 *
 * Example 2:
 * Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
 * Output: 12
 * Explanation:
 * Remove [1, 2] from conflictingPairs. Now, conflictingPairs = [[2, 5], [3, 5]].
 * There are 12 subarrays in nums where [2, 5] and [3, 5] do not appear together.
 * The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 12.
 *
 * Constraints:
 * 2 <= n <= 10^5
 * 1 <= conflictingPairs.length <= 2 * n
 * conflictingPairs[i].length == 2
 * 1 <= conflictingPairs[i][j] <= n
 * conflictingPairs[i][0] != conflictingPairs[i][1]
 */

// Approach: The strategy is to first compute the number of valid subarrays with all conflicting pairs present. This is done by iterating from end = 1 to n. For each 'end', we find the largest start index 's' such that the subarray [s, end] is invalid. Any subarray starting after 's' will be valid. We maintain the largest conflicting point seen so far ('maxConflict'). The number of valid subarrays ending at 'end' is then 'end - maxConflict'. Concurrently, we calculate the potential gain from removing one conflict. If we remove the conflict that establishes the current 'maxConflict', the new boundary becomes the 'secondMaxConflict'. The gain for the current 'end' is 'maxConflict - secondMaxConflict'. We accumulate this potential gain for each point 'maxConflict' in an 'extra' array. The final result is the base valid count plus the maximum gain found in the 'extra' array.
// Time Complexity: O(n + p), where 'n' is the number of elements and 'p' is the total number of points in 'conflictingPairs', as we iterate through 'n' elements and process each conflict once.
// Space Complexity: O(n) for storing the conflicting points in an adjacency list and the 'extra' array for gains.
#define ALL(x) begin(x), end(x)
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        // This will store the base number of valid subarrays with all conflicts active.
        long long valid = 0;

        // Create an adjacency list to store conflicts.
        // conflictingPoints[b] will contain a list of all 'a's such that (a, b) is a conflict and a < b.
        vector<vector<int conflictingPoints(n + 1);

        // Populate the adjacency list. We store pairs as (min, max) to simplify processing.
        for (auto& p : conflictingPairs) { // O(number of pairs)
            int a = min(p[0], p[1]);
            int b = max(p[0], p[1]);
            conflictingPoints[b].push_back(a);
        }

        // maxConflict: The largest starting point 's' that makes a subarray invalid.
        int maxConflict = 0;
        // secondMaxConflict: The second largest such point. Needed to calculate gain.
        int secondMaxConflict = 0;

        // extra[i]: Stores the total extra valid subarrays gained if the conflict involving point 'i' is removed.
        vector<long long> extra(n + 1, 0);

        // Iterate through all possible ending points of subarrays.
        // The total time for this loop and the inner loop is O(n + p).
        for (int end = 1; end <= n; end++) {
            // For the current 'end', check all points 'u' that conflict with it.
            // Update maxConflict and secondMaxConflict with these new conflicts.
            for (int& u : conflictingPoints[end]) {
                if (u >= maxConflict) {
                    secondMaxConflict = maxConflict;
                    maxConflict       = u;
                } else if (u > secondMaxConflict) {
                    secondMaxConflict = u;
                }
            }

            // A subarray [start...end] is valid if start > maxConflict.
            // The number of such valid subarrays ending at 'end' is (end - (maxConflict + 1) + 1) = end - maxConflict.
            valid += end - maxConflict;

            // Calculate the potential gain if the conflict that established 'maxConflict' is removed.
            // The new max conflict would become 'secondMaxConflict'.
            // The gain is the difference between the old invalid range and the new one.
            // This gain is added to the tally for the point 'maxConflict'.
            extra[maxConflict] += maxConflict - secondMaxConflict;
        }

        return valid + *max_element(ALL(extra));
    }
};

/*
 *
 * Dry Run for Example 1: n = 4, conflictingPairs = [[2,3],[1,4]]
 *
 * 1. Pre-processing:
 * - conflictingPoints[3] = {2}
 * - conflictingPoints[4] = {1}
 *
 * 2. Initialization:
 * - valid = 0
 * - maxConflict = 0
 * - secondMaxConflict = 0
 * - extra = [0, 0, 0, 0, 0]
 *
 * 3. Loop Iterations:
 * - end = 1:
 * - No conflicts with 1. maxC remains 0, secondMaxC remains 0.
 * - valid += 1 - 0 = 1. (valid = 1)
 * - extra[0] += 0 - 0 = 0.
 *
 * - end = 2:
 * - No conflicts with 2. maxC remains 0, secondMaxC remains 0.
 * - valid += 2 - 0 = 2. (valid = 3)
 * - extra[0] += 0 - 0 = 0.
 *
 * - end = 3:
 * - Conflict with 2. Inner loop: u=2.
 * - u=2 > maxC=0. Update: secondMaxC=0, maxC=2.
 * - valid += 3 - 2 = 1. (valid = 4)
 * - extra[2] += 2 - 0 = 2. (extra = [0,0,2,0,0])
 *
 * - end = 4:
 * - Current state: maxC=2, secondMaxC=0.
 * - Conflict with 1. Inner loop: u=1.
 * - u=1 is not >= maxC=2, but u=1 > secondMaxC=0. Update: secondMaxC=1.
 * - After inner loop: maxC=2, secondMaxC=1.
 * - valid += 4 - 2 = 2. (valid = 6)
 * - extra[2] += 2 - 1 = 1. (extra = [0,0,3,0,0])
 *
 * 4. Final Calculation:
 * - Base valid subarrays = 6.
 * - extra = [0, 0, 3, 0, 0].
 * - max_element in extra is 3.
 * - Return: 6 + 3 = 9.
 *
 * - Let's verify: Removing [2,3] leaves conflict [1,4].
 * - Total subarrays = 4*5/2 = 10.
 * - Invalid subarray containing both 1 and 4 is just [1,2,3,4].
 * - Valid subarrays = 10 - 1 = 9. Correct.
 *
 * - Removing [1,4] leaves conflict [2,3].
 * - Invalid subarrays are [2,3], [1,2,3], [2,3,4], [1,2,3,4]. 4 invalid.
 * - Valid subarrays = 10 - 4 = 6.
 *
 * - Maximum is 9. The code correctly finds this.
 */

// The answer is the base number of valid subarrays plus the maximum possible gain
// from removing exactly one conflicting pair.
