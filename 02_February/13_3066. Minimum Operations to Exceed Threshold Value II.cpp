/*
 * 3066. Minimum Operations to Exceed Threshold Value II
 *
 * You are given a 0-indexed integer array nums, and an integer k.
 * In one operation, you will:
 * Take the two smallest integers x and y in nums.
 * Remove x and y from nums.
 * Add min(x, y) * 2 + max(x, y) anywhere in the array.
 * Note that you can only apply the described operation if nums contains at least two elements.
 * Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.
 *
 * Example 1:
 * Input: nums = [2,11,10,1,3], k = 10
 * Output: 2
 * Explanation: In the first operation, we remove elements 1 and 2, then add 1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3].
 * In the second operation, we remove elements 3 and 4, then add 3 * 2 + 4 to nums. nums becomes equal to [10, 11, 10].
 * At this stage, all the elements of nums are greater than or equal to 10 so we can stop.
 * It can be shown that 2 is the minimum number of operations needed so that all elements of the array are greater than or equal to 10.
 *
 * Example 2:
 * Input: nums = [1,1,2,4,9], k = 20
 * Output: 4
 * Explanation: After one operation, nums becomes equal to [2, 4, 9, 3].
 * After two operations, nums becomes equal to [7, 4, 9].
 * After three operations, nums becomes equal to [15, 9].
 * After four operations, nums becomes equal to [33].
 * At this stage, all the elements of nums are greater than 20 so we can stop.
 * It can be shown that 4 is the minimum number of operations needed so that all elements of the array are greater than or equal to 20.
 *
 * Constraints:
 * 2 <= nums.length <= 2 * 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= 10^9
 * The input is generated such that an answer always exists. That is, there exists some sequence of operations after which all elements of the array are greater than or equal to k.
 */

// Approach: Use a min-heap to repeatedly combine the two smallest elements until all elements are ≥ k.
// Time Complexity: O(n log n) – each operation (pop/pop/push) takes O(log n) and up to O(n) operations may occur.
// Space Complexity: O(n) – extra space is used by the min-heap.
class Solution {
public:
   int minOperations(vector<int>& nums, int k) {
      // Create a min-heap from the input array to efficiently extract the smallest elements.
      priority_queue<long, vector<long>, greater<long> > pq(begin(nums), end(nums));

      int count = 0;       // Counter for the number of operations performed.

      // Continue operations until the smallest element in the heap is at least k.
      while (!pq.empty() && pq.top() < k) {
         long smallest = pq.top();       // Get the smallest element.
         pq.pop();                       // Remove the smallest element.

         long secondSmallest = pq.top(); // Get the second smallest element.
         pq.pop();                       // Remove the second smallest element.

         // Calculate the new element: (smallest * 2 + secondSmallest) and push it back into the heap.
         pq.push(smallest * 2 + secondSmallest);

         count++;        // Increment the operation count.
      }

      return count;       // Return the total number of operations performed.
   }
};

/* DRY RUN:
 * Input: nums = [2, 11, 10, 1, 3], k = 10
 * After heapify, min-heap: [1, 2, 3, 10, 11]
 *
 * Operation 1:
 *   - smallest = 1, secondSmallest = 2
 *   - New element = 1 * 2 + 2 = 4
 *   - Heap now: [3, 4, 10, 11]
 *
 * Operation 2:
 *   - smallest = 3, secondSmallest = 4
 *   - New element = 3 * 2 + 4 = 10
 *   - Heap now: [10, 10, 11]
 *
 * Now, all elements are ≥ k (10), so the process stops.
 * Total operations = 2
 */
