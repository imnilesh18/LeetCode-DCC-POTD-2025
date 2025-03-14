/*
 * 2226. Maximum Candies Allocated to K Children
 *
 * You are given a 0-indexed integer array candies. Each element in the array denotes a pile of candies of size candies[i]. You can divide each pile into any number of sub piles, but you cannot merge two piles together.
 * You are also given an integer k. You should allocate piles of candies to k children such that each child gets the same number of candies. Each child can be allocated candies from only one pile of candies and some piles of candies may go unused.
 * Return the maximum number of candies each child can get.
 *
 * Example 1:
 * Input: candies = [5,8,6], k = 3
 * Output: 5
 * Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1. We now have five piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.
 *
 * Example 2:
 * Input: candies = [2,5], k = 11
 * Output: 0
 * Explanation: There are 11 children but only 7 candies in total, so it is impossible to ensure each child receives at least one candy. Thus, each child gets no candy and the answer is 0.
 *
 * Constraints:
 * 1 <= candies.length <= 10^5
 * 1 <= candies[i] <= 10^7
 * 1 <= k <= 10^12
 */

// Approach 1 (Brute Force: Time Limit Exceeded 36 / 100 testcases passed): Iterate from the maximum number of candies in any pile down to 1 and, for each candidate candy count, check if the piles can be split into at least k sub-piles each of that size.
// Time Complexity: O(maxCandies * n) where maxCandies is the maximum candies in a pile and n is the number of piles (brute force approach).
// Space Complexity: O(1) since only a constant amount of extra space is used.
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        int n = candies.size();

        int maxC  = 0;          // To track the maximum number of candies in any pile.
        int total = 0;          // To compute the total number of candies.

        // Calculate maxC and total candies.
        for (int i = 0; i < n; i++) {
            maxC   = max(maxC, candies[i]);
            total += candies[i];
        }

        // If total candies are less than k, it's impossible to give each child even one candy.
        if (total < k) {
            return 0;
        }

        // Try every possible candy count from maxC down to 1.
        for (int c = maxC; c >= 1; c--) {
            long long count = 0;
            // Count how many piles of size 'c' we can get from the given piles.
            for (int i = 0; i < n; i++) {
                count += candies[i] / c;
            }

            // If we can form at least k piles of size 'c', return 'c' as the answer.
            if (count >= k) {
                return c;
            }
        }

        // If no valid distribution is found, return 0.
        return 0;
    }
};

/*
 * Dry Run:
 * ---------
 * Example: candies = [5, 8, 6], k = 3
 *
 * Step 1: Calculate maxC and total.
 *  maxC = max(5, 8, 6) = 8
 *  total = 5 + 8 + 6 = 19
 *
 * Step 2: Check if total < k.
 *  19 >= 3, so proceed.
 *
 * Step 3: Iterate from c = maxC down to 1.
 *  For c = 8:
 *      count = floor(5/8) + floor(8/8) + floor(6/8)
 *            = 0 + 1 + 0 = 1
 *      1 < 3, so continue.
 *
 *  For c = 7:
 *      count = floor(5/7) + floor(8/7) + floor(6/7)
 *            = 0 + 1 + 0 = 1
 *      1 < 3, so continue.
 *
 *  For c = 6:
 *      count = floor(5/6) + floor(8/6) + floor(6/6)
 *            = 0 + 1 + 1 = 2
 *      2 < 3, so continue.
 *
 *  For c = 5:
 *      count = floor(5/5) + floor(8/5) + floor(6/5)
 *            = 1 + 1 + 1 = 3
 *      3 >= 3, so we return 5 as the maximum candies per child.
 */

// Approach 2: Use binary search on the possible answer (number of candies each child can get).
//           The helper function canDistr checks if it's possible to distribute candies so that each child gets at least 'mid' candies.
// Time Complexity: O(n * log(maxCandies)) where n is the number of candy piles; binary search runs in log(maxCandies) iterations and each iteration checks all piles.
// Space Complexity: O(1) since only a few extra variables are used.
class Solution {
public:
    // Helper function to check if it's possible to distribute candies such that each child gets at least 'mid' candies.
    bool canDistr(vector<int>& candies, int mid, long long k) {
        int n = candies.size();

        for (int i = 0; i < n; i++) {
            // Subtract the number of sub-piles of size 'mid' that can be formed from candies[i] from k.
            k -= candies[i] / mid;

            // Early return: if we have allocated enough piles for k children, distribution is possible.
            if (k <= 0) {
                return true;
            }
        }
        return k <= 0;
    }
    
    int maximumCandies(vector<int>& candies, long long k) {
        int n = candies.size();

        int       maxC  = 0;    // Track the maximum number of candies in any pile.
        long long total = 0;    // Calculate the total number of candies.

        for (int i = 0; i < n; i++) {
            maxC   = max(maxC, candies[i]);
            total += candies[i];
        }

        // If total candies are less than k, it's impossible to give each child even one candy.
        if (total < k) {
            return 0;
        }

        int l      = 1;                // Lower bound of binary search (minimum possible candies per child).
        int r      = maxC;             // Upper bound of binary search (maximum candies in a single pile).
        int result = 0;                // Store the maximum number of candies each child can get.
        while (l <= r) {
            int mid = l + (r - l) / 2; // Candidate number of candies per child.

            // If it's possible to distribute at least 'mid' candies to each child,
            // update result and search for a higher possible value.
            if (canDistr(candies, mid, k)) {
                result = mid;
                l      = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return result;
    }
};

/*
 * Dry Run:
 * ---------
 * Example: candies = [5, 8, 6], k = 3
 *
 * Step 1: Compute maxC and total.
 *  maxC = max(5, 8, 6) = 8
 *  total = 5 + 8 + 6 = 19
 *
 * Step 2: Check if total < k.
 *  19 >= 3, so proceed.
 *
 * Step 3: Initialize binary search boundaries.
 *  l = 1, r = 8, result = 0
 *
 * Iteration 1:
 *  mid = 1 + (8 - 1) / 2 = 4
 *  canDistr([5, 8, 6], 4, 3):
 *      For candy=5: 5/4 = 1 => k becomes 3 - 1 = 2
 *      For candy=8: 8/4 = 2 => k becomes 2 - 2 = 0 (early return with true)
 *  Since distribution is possible, update result = 4, l = 5
 *
 * Iteration 2:
 *  Now l = 5, r = 8
 *  mid = 5 + (8 - 5) / 2 = 6
 *  canDistr([5, 8, 6], 6, 3):
 *      For candy=5: 5/6 = 0 => k remains 3
 *      For candy=8: 8/6 = 1 => k becomes 3 - 1 = 2
 *      For candy=6: 6/6 = 1 => k becomes 2 - 1 = 1
 *      k > 0, distribution not possible (returns false)
 *  Update r = mid - 1 = 5
 *
 * Iteration 3:
 *  Now l = 5, r = 5
 *  mid = 5 + (5 - 5) / 2 = 5
 *  canDistr([5, 8, 6], 5, 3):
 *      For candy=5: 5/5 = 1 => k becomes 3 - 1 = 2
 *      For candy=8: 8/5 = 1 => k becomes 2 - 1 = 1
 *      For candy=6: 6/5 = 1 => k becomes 1 - 1 = 0 (early return with true)
 *  Since distribution is possible, update result = 5, l = mid + 1 = 6
 *
 * Binary search ends because l (6) > r (5). Final result = 5.
 */
