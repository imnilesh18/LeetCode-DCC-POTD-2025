/*
 * 3191. Minimum Operations to Make Binary Array Elements Equal to One I
 * (First Solve LeetCode: 995. Minimum Number of K Consecutive Bit Flips)
 *
 * You are given a binary array nums.
 * You can do the following operation on the array any number of times (possibly zero):
 * Choose any 3 consecutive elements from the array and flip all of them.
 * Flipping an element means changing its value from 0 to 1, and from 1 to 0.
 * Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
 *
 * Example 1:
 * Input: nums = [0,1,1,1,0,0]
 * Output: 3
 * Explanation:
 * We can do the following operations:
 * Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
 * Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
 * Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
 *
 * Example 2:
 * Input: nums = [0,1,1,1]
 * Output: -1
 * Explanation:
 * It is impossible to make all elements equal to 1.
 *
 * Constraints:
 * 3 <= nums.length <= 10^5
 * 0 <= nums[i] <= 1
 */

// Approach 1: Use a greedy sliding window method to flip 3 consecutive bits when needed; track flip operations with an auxiliary boolean array to know when their effect ends.
// Time Complexity: O(n) - The array is traversed once.
// Space Complexity: O(n) - An extra boolean vector of size n is used to mark the start of each flip.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int          n         = nums.size();     // Total number of elements in nums.
        int          flips     = 0;               // Counts the total number of flip operations performed.
        int          flipCount = 0;               // Tracks the number of active flips affecting the current index.
        int          k         = 3;               // The number of consecutive bits to flip.
        vector<bool> isFlipped(n, false);         // Marks the indices where a flip operation starts.

        for (int i = 0; i < n; i++) {
            // If the current index is beyond the effect window of an earlier flip,
            // remove its effect.
            if (i >= k && isFlipped[i - k]) {
                flipCount--;
            }

            // Check if the current bit (after considering active flips) is 0.
            // If so, we need to flip the next k consecutive bits.
            if (flipCount % 2 == nums[i]) {
                // If there are not enough elements remaining to perform a flip, it's impossible.
                if (i + k > n) {
                    return -1;
                }
                // Start a new flip operation at index i.
                flipCount++;
                flips++;
                isFlipped[i] = true;
            }
        }
        return flips;
    }
};

/*
 * Dry Run
 * Example: nums = [0,1,1,1,0,0], k = 3
 * Initial State: flips = 0, flipCount = 0, isFlipped = [false, false, false, false, false, false]
 *
 * i = 0:
 * - nums[0] = 0, flipCount = 0, condition (0 % 2 == 0) holds → need to flip.
 * - Check: 0 + 3 <= 6 (valid).
 * - Perform flip: flipCount becomes 1, flips becomes 1, mark isFlipped[0] = true.
 *
 * i = 1:
 * - nums[1] = 1, flipCount = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 1 + 3 <= 6 (valid).
 * - Perform flip: flipCount becomes 2, flips becomes 2, mark isFlipped[1] = true.
 *
 * i = 2:
 * - nums[2] = 1, flipCount = 2, condition (2 % 2 == 1) i.e., (0 == 1) fails → no flip.
 * - isFlipped[2] remains false.
 *
 * i = 3:
 * - i >= k, remove effect from isFlipped[0] (true): flipCount becomes 1.
 * - nums[3] = 1, flipCount = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 3 + 3 <= 6 (valid).
 * - Perform flip: flipCount becomes 2, flips becomes 3, mark isFlipped[3] = true.
 *
 * i = 4:
 * - i >= k, remove effect from isFlipped[1] (true): flipCount becomes 1.
 * - nums[4] = 0, flipCount = 1, condition (1 % 2 == 0) fails → no flip.
 * - Mark isFlipped[4] = false.
 *
 * i = 5:
 * - i >= k, remove effect from isFlipped[2] (false): flipCount remains 1.
 * - nums[5] = 0, flipCount = 1, condition (1 % 2 == 0) fails → no flip.
 * - Mark isFlipped[5] = false.
 *
 * Final Result: flips = 3
 */

// Approach 2: Greedy sliding window using the input array for in-place marking of flip operations (using value 5) and maintaining a running counter of active flips.
// Time Complexity: O(n) - Only one pass through the array is needed.
// Space Complexity: O(1) - No extra space is used besides a few variables for counters.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n                 = nums.size();    // Total number of elements in the array.
        int flips             = 0;              // Counter for the total number of flips performed.
        int flipCountFromPast = 0;              // Counter for the number of flips affecting the current index.
        int k                 = 3;              // The fixed size of the subarray to flip.

        for (int i = 0; i < n; i++) {
            // If we've moved past the window of a flip started at index i - k, remove its effect.
            if (i >= k && nums[i - k] == 5) {
                flipCountFromPast--;
            }

            // Determine if the current bit (after accounting for previous flips) is 0.
            // flipCountFromPast % 2 == nums[i] implies that after an even number of flips, nums[i] remains unchanged.
            if (flipCountFromPast % 2 == nums[i]) {
                // If there aren't enough remaining bits to flip, return -1.
                if (i + k > n) {
                    return -1;
                }
                // Start a new flip operation at index i.
                flipCountFromPast++;
                flips++;
                nums[i] = 5;      // Mark the start of a flip by setting the element to 5.
            }
        }
        return flips;
    }
};

/*
 * Dry Run
 * Example: nums = [0,1,1,1,0,0], k = 3
 * Initial State: flips = 0, flipCountFromPast = 0, nums = [0,1,1,1,0,0]
 *
 * i = 0:
 * - nums[0] = 0, flipCountFromPast = 0, condition (0 % 2 == 0) holds → need to flip.
 * - Check: 0 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 1, flips becomes 1, mark nums[0] as 5.
 * - Array becomes: [5,1,1,1,0,0]
 *
 * i = 1:
 * - i < k, so no removal.
 * - nums[1] = 1, flipCountFromPast = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 1 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 2, flips becomes 2, mark nums[1] as 5.
 * - Array becomes: [5,5,1,1,0,0]
 *
 * i = 2:
 * - i < k, so no removal.
 * - nums[2] = 1, flipCountFromPast = 2, condition (2 % 2 == 1) i.e., (0 == 1) false → no flip.
 * - Array remains: [5,5,1,1,0,0]
 *
 * i = 3:
 * - i >= k, remove effect: Check nums[0] (5) → flipCountFromPast becomes 1.
 * - nums[3] = 1, flipCountFromPast = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 3 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 2, flips becomes 3, mark nums[3] as 5.
 * - Array becomes: [5,5,1,5,0,0]
 *
 * i = 4:
 * - i >= k, remove effect: Check nums[1] (5) → flipCountFromPast becomes 1.
 * - nums[4] = 0, flipCountFromPast = 1, condition (1 % 2 == 0) false → no flip.
 * - Array remains: [5,5,1,5,0,0]
 *
 * i = 5:
 * - i >= k, remove effect: Check nums[2] (1, not 5) → flipCountFromPast remains 1.
 * - nums[5] = 0, flipCountFromPast = 1, condition (1 % 2 == 0) false → no flip.
 * - Array remains: [5,5,1,5,0,0]
 *
 * Final Result: flips = 3
 */

// Approach 3: Greedy sliding window method using a deque to track the effect of previous flip operations over a window of size k.
// Time Complexity: O(n) - We traverse the array once and each deque operation is O(1).
// Space Complexity: O(k) - The deque holds at most k elements representing flip operations.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int        n                 = nums.size(); // Number of elements in the input array.
        int        flips             = 0;           // Total count of flips performed.
        int        flipCountFromPast = 0;           // Running count of flips affecting the current index.
        deque<int> flipQue;                         // Queue to keep track of the flip operations in the last k indices.
        int        k = 3;                           // The fixed window size for flip operations.

        for (int i = 0; i < n; i++) {
            // If the current index is beyond the window of the earliest flip in the deque,
            // remove its effect.
            if (i >= k) {
                flipCountFromPast -= flipQue.front();
                flipQue.pop_front();
            }

            // If the current bit (after accounting for previous flips) is 0 (needs to be flipped)
            // then perform a flip operation.
            if (flipCountFromPast % 2 == nums[i]) {
                // Check if there are enough elements left to perform a flip.
                if (i + k > n) {
                    return -1;
                }
                // Perform a new flip starting at index i.
                flipCountFromPast++;
                flips++;
                flipQue.push_back(1);      // Mark that a flip is started at index i.
            } else {
                // No flip is needed at index i; record a 0 in the queue.
                flipQue.push_back(0);
            }
        }
        return flips;
    }
};

/*
 * Dry Run
 * Example: nums = [0,1,1,1,0,0], k = 3
 * Initial State: flips = 0, flipCountFromPast = 0, flipQue = []
 *
 * i = 0:
 * - i < k, so no removal from deque.
 * - nums[0] = 0, flipCountFromPast = 0, condition (0 % 2 == 0) holds → need to flip.
 * - Check: 0 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 1, flips becomes 1, push_back(1) → flipQue = [1].
 *
 * i = 1:
 * - i < k, so no removal.
 * - nums[1] = 1, flipCountFromPast = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 1 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 2, flips becomes 2, push_back(1) → flipQue = [1, 1].
 *
 * i = 2:
 * - i < k, so no removal.
 * - nums[2] = 1, flipCountFromPast = 2, condition (2 % 2 == 1) i.e., (0 == 1) fails → no flip.
 * - push_back(0) → flipQue = [1, 1, 0].
 *
 * i = 3:
 * - i >= k, remove effect: subtract flipQue.front() (1) → flipCountFromPast becomes 1, pop front → flipQue = [1, 0].
 * - nums[3] = 1, flipCountFromPast = 1, condition (1 % 2 == 1) holds → need to flip.
 * - Check: 3 + 3 <= 6 (valid).
 * - Perform flip: flipCountFromPast becomes 2, flips becomes 3, push_back(1) → flipQue = [1, 0, 1].
 *
 * i = 4:
 * - i >= k, remove effect: subtract flipQue.front() (1) → flipCountFromPast becomes 1, pop front → flipQue = [0, 1].
 * - nums[4] = 0, flipCountFromPast = 1, condition (1 % 2 == 0) fails → no flip.
 * - push_back(0) → flipQue = [0, 1, 0].
 *
 * i = 5:
 * - i >= k, remove effect: subtract flipQue.front() (0) → flipCountFromPast remains 1, pop front → flipQue = [1, 0].
 * - nums[5] = 0, flipCountFromPast = 1, condition (1 % 2 == 0) fails → no flip.
 * - push_back(0) → flipQue = [1, 0, 0].
 *
 * Final Result: flips = 3
 */
