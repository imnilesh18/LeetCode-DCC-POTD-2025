/*
 * 2929. Distribute Candies Among Children II
 *
 * Medium
 *
 * You are given two positive integers n and limit.
 * Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
 *
 * Example 1:
 * Input: n = 5, limit = 2
 * Output: 3
 * Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
 *
 * Example 2:
 * Input: n = 3, limit = 3
 * Output: 10
 * Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies: (0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).
 *
 * Constraints:
 * 1 <= n <= 10^6
 * 1 <= limit <= 10^6
 */

// Approach: Fix candies for child 1 and compute valid distributions for child 2 and child 3 using limits.
// Time Complexity: O(n), in the worst case we loop from max(0, n-2*limit) to min(n, limit)
// Space Complexity: O(1), no extra space used except a few variables
class Solution {
public:
    long long distributeCandies(int n, int limit) {
        long long ways = 0;

        // Calculate the valid range of candies child1 can receive
        int minCh1 = max(0, n - 2 * limit); // ensure ch2 and ch3 can get at most limit
        int maxCh1 = min(n, limit);         // child1 can't exceed limit

        // Try all valid candy counts for child1
        for (int i = minCh1; i <= maxCh1; i++) { // fixing child1 assignment of candies
            int N = n - i;                       // remaining candies to be distributed to child2 and child3

            // Calculate valid range for child2 so that child3 also doesn't exceed limit
            int minCh2 = max(0, N - limit); // child3 gets at most limit, so ch2 must get at least N-limit
            int maxCh2 = min(N, limit);     // child2 can't get more than limit

            // Count all possible values for child2 within this range
            ways += maxCh2 - minCh2 + 1;
        }

        return ways;
    }
};

/*
 *
 * Dry Run
 * Input: n = 5, limit = 2
 * minCh1 = max(0, 5 - 2*2) = 1
 * maxCh1 = min(5, 2) = 2
 * So child1 can take 1 or 2 candies
 *
 * Iteration 1: i = 1 (child1 takes 1 candy)
 * Remaining = 5 - 1 = 4
 * minCh2 = max(0, 4 - 2) = 2
 * maxCh2 = min(4, 2) = 2
 * Only one option for child2: 2, then child3 = 2
 * ways += 1 → ways = 1
 *
 * Iteration 2: i = 2 (child1 takes 2 candies)
 * Remaining = 5 - 2 = 3
 * minCh2 = max(0, 3 - 2) = 1
 * maxCh2 = min(3, 2) = 2
 * child2 = 1 → child3 = 2
 * child2 = 2 → child3 = 1
 * ways += 2 → ways = 3
 *
 * Final Answer = 3
 *
 */
