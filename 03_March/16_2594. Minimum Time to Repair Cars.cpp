/*
 * 2594. Minimum Time to Repair Cars
 *
 * You are given an integer array ranks representing the ranks of some mechanics. ranksi is the rank of the ith mechanic. A mechanic with a rank r can repair n cars in r * n2 minutes.
 * You are also given an integer cars representing the total number of cars waiting in the garage to be repaired.
 * Return the minimum time taken to repair all the cars.
 * Note: All the mechanics can repair the cars simultaneously.
 *
 * Example 1:
 * Input: ranks = [4,2,3,1], cars = 10
 * Output: 16
 * Explanation:
 * - The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
 * - The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
 * - The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
 * - The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
 * It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​
 *
 * Example 2:
 * Input: ranks = [5,1,8], cars = 6
 * Output: 16
 * Explanation:
 * - The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
 * - The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
 * - The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
 * It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​
 *
 * Constraints:
 * 1 <= ranks.length <= 10^5
 * 1 <= ranks[i] <= 100
 * 1 <= cars <= 10^6
 */

// Approach: Use binary search on the time variable to find the minimum time required.
// For a given time 'T', calculate how many cars each mechanic can repair using the formula:
//      n = floor(sqrt(T / rank))
// Sum these values for all mechanics and check if the sum is at least 'cars'.
// If yes, 'T' minutes is sufficient; otherwise, it's not.
// Time Complexity: O(n * log(maxR * cars^2)) where n is the number of mechanics.
// Space Complexity: O(1) as only a constant amount of extra space is used.
class Solution {
public:
    typedef long long ll;

    // Checks if it is possible to repair at least 'cars' in 'mid' minutes.
    bool isPossible(vector<int>& ranks, ll mid, int cars) {
        ll carsFixed = 0;

        // Iterate over each mechanic and calculate the number of cars they can repair in 'mid' minutes.
        for (int i = 0; i < ranks.size(); i++) {
            // Each mechanic with rank 'r' can repair floor(sqrt(mid / r)) cars.
            carsFixed += sqrt(mid / ranks[i]);
        }
        // Return true if the total number of cars repaired is at least 'cars'.
        return carsFixed >= cars;
    }
    // Returns the minimum time required to repair 'cars' cars.
    long long repairCars(vector<int>& ranks, int cars) {
        int n = ranks.size();
        ll  l = 1;
        // Determine the maximum possible time using the slowest mechanic.
        int maxR = *max_element(begin(ranks), end(ranks));
        ll  r    = 1LL * maxR * cars * cars;

        ll result = -1;

        // Binary search on the time interval [l, r].
        while (l <= r) {
            ll mid = l + (r - l) / 2;
            // If it's possible to repair at least 'cars' in 'mid' minutes,
            // try to find a smaller time.
            if (isPossible(ranks, mid, cars)) {
                result = mid;
                r      = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return result;
    }
};

/*
 * Dry Run:
 * Input: ranks = [4, 2, 3, 1], cars = 10
 *
 * 1. Initialization:
 * - maxR = 4, l = 1, r = 4 * 10 * 10 = 400.
 *
 * 2. First Binary Search Iteration:
 * - mid = (1 + 400) / 2 = 200.
 * - For each mechanic:
 * Mechanic with rank 4: cars repaired = floor(sqrt(200 / 4)) = floor(sqrt(50)) = 7.
 * Mechanic with rank 2: cars repaired = floor(sqrt(200 / 2)) = floor(sqrt(100)) = 10.
 * Mechanic with rank 3: cars repaired = floor(sqrt(200 / 3)) = floor(sqrt(66.67)) = 8.
 * Mechanic with rank 1: cars repaired = floor(sqrt(200 / 1)) = floor(sqrt(200)) = 14.
 * - Total cars repaired = 7 + 10 + 8 + 14 = 39 (which is >= 10).
 * - Since 200 minutes is sufficient, update result = 200 and set r = 199.
 *
 * 3. Subsequent Iterations:
 * - The binary search continues narrowing down the time interval.
 * - Eventually, it finds the smallest 'mid' for which isPossible returns true.
 * - Final result becomes 16 minutes, as no time less than 16 minutes can repair all 10 cars.
 */
