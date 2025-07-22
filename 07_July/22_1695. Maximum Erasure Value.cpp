/*
 * 1695. Maximum Erasure Value
 *
 * Medium
 *
 *
 * You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
 * Return the maximum score you can get by erasing exactly one subarray.
 * An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
 *
 * Example 1:
 *
 * Input: nums = [4,2,4,5,6]
 * Output: 17
 * Explanation: The optimal subarray here is [2,4,5,6].
 *
 * Example 2:
 * Input: nums = [5,2,1,2,5,2,1,2,5]
 * Output: 8
 * Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 */

// Approach 1: Uses a sliding window [i, j] and an unordered_set to keep track of unique elements in the window. If a duplicate is found, the window shrinks from the left (i++) until it's unique again.
// Time Complexity: O(n), as each element is visited at most twice by the i and j pointers.
// Space Complexity: O(n), in the worst case, the set can store all n elements if they are unique.
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        // Get the size of the input array.
        int n = nums.size();
        // Use a set to store unique elements in the current window.
        unordered_set<int> st;

        // Initialize pointers for the sliding window and variables for sum and result.
        int i      = 0; // Left pointer of the window.
        int j      = 0; // Right pointer of the window.
        int sum    = 0; // Current sum of the unique subarray.
        int result = 0; // Maximum sum found so far.

        // Iterate with the right pointer to expand the window.
        while (j < n) {
            // If the current element is not in the set, it's unique in the current window.
            if (!st.count(nums[j])) {
                // Add the element's value to the current sum.
                sum += nums[j];
                // Update the maximum result seen so far.
                result = max(result, sum);
                // Insert the element into the set.
                st.insert(nums[j]);
                // Move the right pointer to expand the window.
                j++;
            } else {
                // If the element is already in the set, a duplicate is found.
                // We need to shrink the window from the left until the duplicate is removed.
                while (i < n && st.count(nums[j])) {
                    // Subtract the leftmost element's value from the sum.
                    sum -= nums[i];
                    // Remove the leftmost element from the set.
                    st.erase(nums[i]);
                    // Move the left pointer to shrink the window.
                    i++;
                }
            }
        }

        return result;
    }
};

/*
 * Dry Run for nums = [4, 2, 4, 5, 6]
 * -----------------------------------
 * Initial State: i=0, j=0, sum=0, result=0, st={}
 * * 1. j=0, nums[j]=4:
 * - '4' is not in st.
 * - sum = 0 + 4 = 4.
 * - result = max(0, 4) = 4.
 * - st.insert(4) -> st = {4}.
 * - j becomes 1. Window: [4]
 * * 2. j=1, nums[j]=2:
 * - '2' is not in st.
 * - sum = 4 + 2 = 6.
 * - result = max(4, 6) = 6.
 * - st.insert(2) -> st = {4, 2}.
 * - j becomes 2. Window: [4, 2]
 * * 3. j=2, nums[j]=4:
 * - '4' is in st. Duplicate found. Enter the 'else' block.
 * - Inner while loop starts (to remove the old '4').
 * - i=0, nums[i]=4:
 * - sum = 6 - 4 = 2.
 * - st.erase(4) -> st = {2}.
 * - i becomes 1.
 * - Inner loop condition 'st.count(nums[j]=4)' is now false. Exit inner loop.
 * * 4. j=2, nums[j]=4: (Outer loop continues from the same j)
 * - '4' is not in st.
 * - sum = 2 + 4 = 6.
 * - result = max(6, 6) = 6.
 * - st.insert(4) -> st = {2, 4}.
 * - j becomes 3. Window: [2, 4]
 * * 5. j=3, nums[j]=5:
 * - '5' is not in st.
 * - sum = 6 + 5 = 11.
 * - result = max(6, 11) = 11.
 * - st.insert(5) -> st = {2, 4, 5}.
 * - j becomes 4. Window: [2, 4, 5]
 * * 6. j=4, nums[j]=6:
 * - '6' is not in st.
 * - sum = 11 + 6 = 17.
 * - result = max(11, 17) = 17.
 * - st.insert(6) -> st = {2, 4, 5, 6}.
 * - j becomes 5. Window: [2, 4, 5, 6]
 * * 7. j=5:
 * - Loop condition 'j < n' (5 < 5) is false. Loop terminates.
 * * Final Result: 17
 */

// Approach 2: An optimized sliding window that uses a prefix sum array for O(1) subarray sum calculation and a map (or array) to store the last seen index of each number, which allows jumping the left pointer directly past a duplicate.
// Time Complexity: O(n), as we iterate through the array once to build the prefix sum and once for the sliding window logic.
// Space Complexity: O(n), due to the cumulative sum array `cus`. The map `mp` has a fixed size based on constraints, so `cus` dominates.
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Create a cumulative sum (prefix sum) array.
        vector<int> cus(n, 0);

        cus[0] = nums[0];
        // Calculate prefix sums. cus[i] = sum of nums[0]...nums[i].
        for (int k = 1; k < n; k++) {
            cus[k] = cus[k - 1] + nums[k];
        }

        // Use a vector as a map to store the last seen index of each number.
        // Constraints: 1 <= nums[i] <= 10^4, so an array of size 10001 is sufficient.
        vector<int> mp(10001, -1);
        int         maxS = 0; // Stores the maximum score (sum).
        int         i    = 0; // The effective start of the current unique subarray.
        int         j    = 0; // The end of the current unique subarray (iterator).

        // Iterate through the array with the right pointer 'j'.
        while (j < n) {
            // If we have seen nums[j] before at index mp[nums[j]],
            // the new unique subarray must start after that index.
            // So, update i to max(current_i, last_seen_index + 1).
            i = max(i, mp[nums[j]] + 1);

            // Calculate the sum of the subarray from i to j using the prefix sum array.
            // Sum(i, j) = cus[j] - cus[i-1].
            int jthSum = cus[j];
            // If i is 0, the sum up to i-1 is 0.
            int ithSum = i - 1 < 0 ? 0 : cus[i - 1];

            // Update the maximum score found so far.
            maxS = max(maxS, jthSum - ithSum);

            // Update the map with the current index of nums[j].
            mp[nums[j]] = j;

            // Move to the next element.
            j++;
        }

        return maxS;
    }
};

/*
 * Dry Run for nums = [4, 2, 4, 5, 6]
 * -----------------------------------
 * Initial State: cus=[4, 6, 10, 15, 21], mp=[-1, -1, ...], maxS=0, i=0, j=0
 * * 1. j=0, nums[j]=4:
 * - mp[4] is -1. i = max(0, -1 + 1) = 0.
 * - currentSum = cus[0] - 0 = 4.
 * - maxS = max(0, 4) = 4.
 * - mp[4] = 0.
 * - j becomes 1. Current valid window starts at i=0.
 * * 2. j=1, nums[j]=2:
 * - mp[2] is -1. i = max(0, -1 + 1) = 0. (i remains 0)
 * - currentSum = cus[1] - 0 = 6. (Sum of [4, 2])
 * - maxS = max(4, 6) = 6.
 * - mp[2] = 1.
 * - j becomes 2. Current valid window starts at i=0.
 * * 3. j=2, nums[j]=4:
 * - mp[4] is 0. i = max(0, 0 + 1) = 1. (Left pointer 'i' jumps to 1 to exclude the previous '4')
 * - currentSum = cus[2] - cus[i-1] = cus[2] - cus[0] = 10 - 4 = 6. (Sum of [2, 4])
 * - maxS = max(6, 6) = 6.
 * - mp[4] = 2. (Update last seen index for '4')
 * - j becomes 3. Current valid window starts at i=1.
 * * 4. j=3, nums[j]=5:
 * - mp[5] is -1. i = max(1, -1 + 1) = 1. (i remains 1)
 * - currentSum = cus[3] - cus[i-1] = cus[3] - cus[0] = 15 - 4 = 11. (Sum of [2, 4, 5])
 * - maxS = max(6, 11) = 11.
 * - mp[5] = 3.
 * - j becomes 4. Current valid window starts at i=1.
 * * 5. j=4, nums[j]=6:
 * - mp[6] is -1. i = max(1, -1 + 1) = 1. (i remains 1)
 * - currentSum = cus[4] - cus[i-1] = cus[4] - cus[0] = 21 - 4 = 17. (Sum of [2, 4, 5, 6])
 * - maxS = max(11, 17) = 17.
 * - mp[6] = 4.
 * - j becomes 5. Current valid window starts at i=1.
 * * 6. j=5:
 * - Loop condition 'j < n' (5 < 5) is false. Loop terminates.
 * * Final Result: 17
 */
