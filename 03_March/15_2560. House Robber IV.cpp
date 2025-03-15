/*
 * 2560. House Robber IV
 *
 * There are several consecutive houses along a street, each of which has some money inside. There is also a robber, who wants to steal money from the homes, but he refuses to steal from adjacent homes.
 *
 * The capability of the robber is the maximum amount of money he steals from one house of all the houses he robbed.
 *
 * You are given an integer array nums representing how much money is stashed in each house. More formally, the ith house from the left has nums[i] dollars.
 *
 * You are also given an integer k, representing the minimum number of houses the robber will steal from. It is always possible to steal at least k houses.
 *
 * Return the minimum capability of the robber out of all the possible ways to steal at least k houses.
 *
 * Example 1:
 * Input: nums = [2,3,5,9], k = 2
 * Output: 5
 * Explanation:
 * There are three ways to rob at least 2 houses:
 * - Rob the houses at indices 0 and 2. Capability is max(nums[0], nums[2]) = 5.
 * - Rob the houses at indices 0 and 3. Capability is max(nums[0], nums[3]) = 9.
 * - Rob the houses at indices 1 and 3. Capability is max(nums[1], nums[3]) = 9.
 * Therefore, we return min(5, 9, 9) = 5.
 *
 * Example 2:
 * Input: nums = [2,7,9,3,1], k = 2
 * Output: 2
 * Explanation: There are 7 ways to rob the houses. The way which leads to minimum capability is to rob the house at index 0 and 4. Return max(nums[0], nums[4]) = 2.
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= (nums.length + 1)/2
 */

// Approach 1 (Brute Force Time Limit Exceeded 52 / 64 testcases passed): Use recursion with memoization (DP) to decide whether to rob the current house (and skip the next one) or skip it, and choose the option that minimizes the maximum money stolen from any single house.
// Time Complexity: O(n * k) where n is the number of houses and k is the number of houses to rob, since each (index, k) state is computed once.
// Space Complexity: O(n * k) due to the memoization table and recursion stack.
class Solution {
public:
    int n;     // Number of houses

    // Recursive function to compute the minimum possible maximum money stolen (capability)
    // starting from index i with k houses remaining to be robbed.
    int solve(vector<int>& nums, int i, int k, vector<vector<int> >& t) {
        // If no more houses need to be robbed, return 0 (base capability)
        if (k == 0) {
            return 0;
        }

        // If index goes out of bounds, return INT_MAX to indicate an invalid (infeasible) path.
        if (i >= n) {
            return INT_MAX;
        }

        // Return memoized result if it exists.
        if (t[i][k] != -1) {
            return t[i][k];
        }

        // Option 1: Rob the current house.
        // Capability becomes the maximum of the current house's money and the best result
        // from robbing the remaining houses (skipping the adjacent house).
        int take = max(nums[i], solve(nums, i + 2, k - 1, t));

        // Option 2: Skip the current house.
        // Continue to check for possibility starting from the next house with the same k.
        int not_take = solve(nums, i + 1, k, t);

        // Memoize and return the minimum capability between taking or not taking the current house.
        return t[i][k] = min(take, not_take);
    }
    int minCapability(vector<int>& nums, int k) {
        n = nums.size();     // Set the total number of houses.
        // Create a memoization table initialized with -1.
        vector<vector<int> > t(n + 1, vector<int>(k + 1, -1));
        // Start recursion from index 0 with k houses to rob.
        return solve(nums, 0, k, t);
    }
};

/*
 * Dry Run:
 * For nums = [2, 3, 5, 9] and k = 2:
 *
 * 1. Call solve(nums, 0, 2, t):
 * - At index 0 with k=2:
 *   Option 1: Take house 0 (money = 2)
 *     -> Call solve(nums, 2, 1, t):
 * At index 2 with k=1:
 *            - Option 1: Take house 2 (money = 5)
 *                 -> Call solve(nums, 4, 0, t) returns 0 (base case)
 *                 -> Capability = max(5, 0) = 5.
 *            - Option 2: Skip house 2
 *                 -> Call solve(nums, 3, 1, t):
 *                      - At index 3 with k=1:
 + Option 1: Take house 3 (money = 9)
 +                                -> Call solve(nums, 5, 0, t) returns 0 (base case)
 +                                -> Capability = max(9, 0) = 9.
 + Option 2: Skip house 3
 +                                -> Call solve(nums, 4, 1, t) returns INT_MAX (invalid path).
 + Minimum = min(9, INT_MAX) = 9.
 +                 -> Capability from skipping house 2 = 9.
 +            - Minimum at index 2 = min(5, 9) = 5.
 +     -> Capability when taking house 0 = max(2, 5) = 5.
 +
 +   Option 2: Skip house 0
 +     -> Call solve(nums, 1, 2, t):
 * At index 1 with k=2:
 *            - Option 1: Take house 1 (money = 3)
 *                 -> Call solve(nums, 3, 1, t) returns 9 (from previous computation).
 *                 -> Capability = max(3, 9) = 9.
 *            - Option 2: Skip house 1
 *                 -> Call solve(nums, 2, 2, t) eventually yields INT_MAX (not enough houses remaining).
 *            - Minimum at index 1 = min(9, INT_MAX) = 9.
 * - Final answer = min(5, 9) = 5.
 */

// Approach 2: Use binary search on the possible range of capabilities (from min to max in nums) and, for each mid value, use a greedy method to check if at least k houses can be robbed without robbing adjacent houses.
// Time Complexity: O(n * log(max(nums))) since each binary search iteration takes O(n) time.
// Space Complexity: O(1) extra space, apart from the input.
class Solution {
public:
    // Checks if it's possible to rob at least k houses such that each robbed house has money <= mid.
    bool isPossible(vector<int>& nums, int mid, int k) {
        int house = 0;     // Count of houses robbed

        // Iterate over the houses
        for (int i = 0; i < nums.size(); i++) {
            // If the current house's money is within the allowed capability (<= mid)
            if (nums[i] <= mid) {
                house++;      // Rob this house
                i++;          // Skip the next house to avoid adjacent robbery
            }
        }
        // Return true if at least k houses have been robbed
        return house >= k;
    }
    // Returns the minimum capability (threshold) required to rob at least k houses.
    int minCapability(vector<int>& nums, int k) {
        int n = nums.size();

        // Set binary search boundaries: lower bound is the smallest value, upper bound is the largest value in nums.
        int l      = *min_element(begin(nums), end(nums));
        int r      = *max_element(begin(nums), end(nums));
        int result = r;

        // Perform binary search on the range [l, r]
        while (l <= r) {
            int mid = l + (r - l) / 2;

            // If it is possible to rob at least k houses with capability mid, try to lower the capability.
            if (isPossible(nums, mid, k) == true) {
                result = mid;       // Update result with the current possible capability
                r      = mid - 1;   // Try to find an even smaller capability
            } else {
                // Otherwise, increase the capability threshold
                l = mid + 1;
            }
        }
        return result;
    }
};

/*
 * Dry Run:
 * Example: nums = [2, 7, 9, 3, 1], k = 2
 *
 * 1. Initialization:
 * - l = min(nums) = 1, r = max(nums) = 9, result = 9
 *
 * 2. First Iteration:
 * - mid = 1 + (9 - 1) / 2 = 5
 * - Call isPossible(nums, 5, 2):
 *     i = 0: nums[0] = 2 <= 5, count becomes 1, skip next index (i becomes 1 + 1 = 2)
 *     i = 2: nums[2] = 9 > 5, count remains 1
 *     i = 3: nums[3] = 3 <= 5, count becomes 2, skip next index (i becomes 3 + 1 = 4)
 *     i = 4: Skipped due to previous skip.
 *     -> Total houses robbed = 2, which is >= k. Returns true.
 * - Since true, update result = 5, r = mid - 1 = 4
 *
 * 3. Second Iteration:
 * - l = 1, r = 4, mid = 1 + (4 - 1) / 2 = 2
 * - Call isPossible(nums, 2, 2):
 *     i = 0: nums[0] = 2 <= 2, count becomes 1, skip next index (i becomes 0 + 1 = 1, then increment to 2)
 *     i = 2: nums[2] = 9 > 2, count remains 1
 *     i = 3: nums[3] = 3 > 2, count remains 1
 *     i = 4: nums[4] = 1 <= 2, count becomes 2, skip next index (i becomes 4 + 1 = 5)
 *     -> Total houses robbed = 2, which is >= k. Returns true.
 * - Since true, update result = 2, r = mid - 1 = 1
 *
 * 4. Third Iteration:
 * - l = 1, r = 1, mid = 1 + (1 - 1) / 2 = 1
 * - Call isPossible(nums, 1, 2):
 *     i = 0: nums[0] = 2 > 1, count remains 0
 *     i = 1: nums[1] = 7 > 1, count remains 0
 *     i = 2: nums[2] = 9 > 1, count remains 0
 *     i = 3: nums[3] = 3 > 1, count remains 0
 *     i = 4: nums[4] = 1 <= 1, count becomes 1, skip next index (i becomes 4 + 1 = 5)
 *     -> Total houses robbed = 1, which is < k. Returns false.
 * - Since false, update l = mid + 1 = 2
 *
 * 5. Termination:
 * - Now l (2) > r (1), so binary search stops.
 * - Final result is 2.
 */
