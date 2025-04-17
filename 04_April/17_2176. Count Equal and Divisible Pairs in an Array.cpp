/*
 * 2176. Count Equal and Divisible Pairs in an Array
 *
 * Easy
 *
 * Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i, j) where 0 <= i < j < n, such that nums[i] == nums[j] and (i * j) is divisible by k.
 *
 * Example 1:
 * Input: nums = [3,1,2,2,2,1,3], k = 2
 * Output: 4
 * Explanation:
 * There are 4 pairs that meet all the requirements:
 * - nums[0] == nums[6], and 0 * 6 == 0, which is divisible by 2.
 * - nums[2] == nums[3], and 2 * 3 == 6, which is divisible by 2.
 * - nums[2] == nums[4], and 2 * 4 == 8, which is divisible by 2.
 * - nums[3] == nums[4], and 3 * 4 == 12, which is divisible by 2.
 *
 * Example 2:
 * Input: nums = [1,2,3,4], k = 1
 * Output: 0
 * Explanation: Since no value in nums is repeated, there are no pairs (i,j) that meet all the requirements.
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 1 <= nums[i], k <= 100
 */

// Approach: Group indices by value, precompute k’s divisors, then for each index use gcd and a divisor-frequency map to count valid pairs.
// Time Complexity: O(n * √k) — grouping is O(n), precomputing divisors is O(√k), and each index checks O(√k) divisors.
// Space Complexity: O(n + d) — storing the index groups and the divisor map, where d is the number of divisors of k.
class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        int n      = nums.size();
        int result = 0;

        // 1) Group indices by their value
        unordered_map<int, vector<int> > indicesMap;

        for (int i = 0; i < n; i++) {
            indicesMap[nums[i]].push_back(i);
        }

        // 2) Precompute all divisors of k
        unordered_set<int> divisors;
        for (int f = 1; f* f <= k; f++) {
            if (k % f == 0) {
                divisors.insert(f);
                divisors.insert(k / f);
            }
        }

        // 3) For each group of equal numbers, count valid pairs
        for (auto& [num, indices] : indicesMap) {
            // Maps divisor -> count of previous indices divisible by that divisor
            unordered_map<int, int> factorMap;

            for (int i : indices) {
                // 3a) Determine which j's would satisfy (i*j)%k == 0
                int g = gcd(i, k);
                int requiredFactor = k / g;

                // 3b) Add all previous j’s that meet the divisibility requirement
                result += factorMap[requiredFactor];

                // 3c) Record this index i as “previous” for future indices
                for (int d : divisors) {
                    if (i % d == 0) {
                        factorMap[d]++;
                    }
                }
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Visual Representation:
 * Indices:   0   1   2   3   4   5   6
 *          +---+---+---+---+---+---+---+
 * Array:   | 3 | 1 | 2 | 2 | 2 | 1 | 3 |  , k = 2
 *          +---+---+---+---+---+---+---+
 *
 * Grouped indices:
 *   3 -> [0,6]
 *   1 -> [1,5]
 *   2 -> [2,3,4]
 * Divisors of k = 2: {1, 2}
 *
 * For num = 3, indices = [0, 6]:
 *   i = 0: gcd(0,2)=2 → req=2/2=1
 *     result += factorMap[1] = 0
 *     update: 0%1==0 → factorMap[1]=1; 0%2==0 → factorMap[2]=1
 *   i = 6: gcd(6,2)=2 → req=1
 *     result += factorMap[1] = 1  (pair: (0,6))
 *     update: 6%1==0 → factorMap[1]=2; 6%2==0 → factorMap[2]=2
 *
 * For num = 1, indices = [1, 5]:
 *   i = 1: gcd(1,2)=1 → req=2
 *     result += factorMap[2] = 0
 *     update: 1%1==0 → factorMap[1]=1
 *   i = 5: gcd(5,2)=1 → req=2
 *     result += factorMap[2] = 0
 *     update: 5%1==0 → factorMap[1]=2
 *
 * For num = 2, indices = [2, 3, 4]:
 *   Reset factorMap
 *   i = 2: gcd(2,2)=2 → req=1
 *     result += 0
 *     update: 2%1==0 → map[1]=1; 2%2==0 → map[2]=1
 *   i = 3: gcd(3,2)=1 → req=2
 *     result += map[2] = 1  (pair: (2,3))
 *     update: 3%1==0 → map[1]=2
 *   i = 4: gcd(4,2)=2 → req=1
 *     result += map[1] = 2  (pairs: (2,4), (3,4))
 *     update: 4%1==0 → map[1]=3; 4%2==0 → map[2]=2
 *
 * Final result = 4
 */
