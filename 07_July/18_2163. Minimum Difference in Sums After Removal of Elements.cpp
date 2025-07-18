/*
 * 2163. Minimum Difference in Sums After Removal of Elements
 *
 * Hard
 *
 * You are given a 0-indexed integer array nums consisting of 3 * n elements.
 * You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
 * The first n elements belonging to the first part and their sum is sumfirst.
 * The next n elements belonging to the second part and their sum is sumsecond.
 * The difference in sums of the two parts is denoted as sumfirst - sumsecond.
 * For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
 * Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
 * Return the minimum difference possible between the sums of the two parts after the removal of n elements.
 *
 * Example 1:
 * Input: nums = [3,1,2]
 * Output: -1
 * Explanation: Here, nums has 3 elements, so n = 1.
 * Thus we have to remove 1 element from nums and divide the array into two equal parts.
 * - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
 * - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
 * - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
 * The minimum difference between sums of the two parts is min(-1,1,2) = -1.
 *
 * Example 2:
 * Input: nums = [7,9,5,8,1,3]
 * Output: 1
 * Explanation: Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
 * If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3]. The difference in sums will be (7+9) - (1+3) = 12.
 * To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1. The resultant array becomes [7,5,8,3]. The difference in sums of the two parts is (7+5) - (8+3) = 1.
 * It can be shown that it is not possible to obtain a difference smaller than 1.
 *
 * Constraints:
 * nums.length == 3 * n
 * 1 <= n <= 10^5
 * 1 <= nums[i] <= 10^5
 */

// Approach: Use two heaps to efficiently maintain the smallest sums possible for the left segment and the largest for the right segment after removing n elements. For each possible split, we update the minimum possible difference.
// Time Complexity: O(n log n) – since we maintain heaps of size at most n and perform insertion/removal for 2n and n iterations.
// Space Complexity: O(n) – we use two auxiliary arrays and two heaps, all of size up to n.
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int N = nums.size();                 // Size of the array (3*n)
        int n = N / 3;                       // 'n' as per problem definition

        vector<long long> leftMinSum(N, 0);  // leftMinSum[i]: min sum of n elements chosen from 0 to i
        vector<long long> rightMaxSum(N, 0); // rightMaxSum[i]: max sum of n elements chosen from i to N-1

        priority_queue<int> maxHeap;         // Max heap for smallest n elements on left
        long long           leftSum = 0;

        for (int i = 0; i < 2 * n; i++) {     // Traverse first 2n elements
            maxHeap.push(nums[i]);            // Add this element
            leftSum += nums[i];

            if (maxHeap.size() > n) {         // If heap size exceeds n
                leftSum -= maxHeap.top();     // Remove the largest element (no longer part of n-minimum sum)
                maxHeap.pop();
            }

            leftMinSum[i] = leftSum;          // Capture the current sum of the n smallest selected so far
        }

        priority_queue<int, vector<int>, greater<int>> minHeap; // Min heap for largest n elements on right
        long long rightSum = 0;
        for (int i = N - 1; i >= n; i--) {                       // Traverse last 2n elements backwards
            minHeap.push(nums[i]);                               // Add current element
            rightSum += nums[i];

            if (minHeap.size() > n) {                // If heap size exceeds n
                rightSum -= minHeap.top();           // Remove the smallest element (no longer part of n-maximum sum)
                minHeap.pop();
            }

            rightMaxSum[i] = rightSum;               // Capture the current sum of the n largest selected so far
        }

        long long result = LLONG_MAX;                // To store the minimum difference

        for (int i = n - 1; i <= 2 * n - 1; i++) {   // Try all split points
            result = min(result, leftMinSum[i] - rightMaxSum[i + 1]);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [7,9,5,8,1,3]
 *         n = 2, N = 6
 *
 * Step 1: Build leftMinSum with a maxHeap, window: [0...3] (i in 0..3)
 *   - maxHeap: [7]            leftSum: 7         leftMinSum[0] = 7
 *   - maxHeap: [9,7]          leftSum: 16        leftMinSum[1] = 16
 *   - maxHeap: [9,7,5]        leftSum: 21. Exceeds n=2, so remove 9.
 *   - Pop 9: leftSum = 21-9=12     leftMinSum[2] = 12
 *   - maxHeap: [8,7,5]        leftSum: 12+8=20. Remove 8.
 *   - Pop 8: leftSum = 20-8=12     leftMinSum[3] = 12
 *
 * leftMinSum = [7,16,12,12,0,0]
 *
 * Step 2: Build rightMaxSum with minHeap, window: [4...1] (i in 5..1)
 *   - minHeap: [3]
 *   - minHeap: [1,3]
 *   - i=4: rightSum = 1+3=4              rightMaxSum[4]=4
 *   - i=3: rightSum += 8 = 12, minHeap: [1,3,8]. Pop 1->rightSum=11, rightMaxSum[3]=11
 *   - i=2: rightSum += 5 = 16, minHeap: [3,8,5]. Pop 3->rightSum=13, rightMaxSum[2]=13
 *   - i=1: rightSum += 9 = 22, minHeap: [8,5,9]. Pop 5->rightSum=17, rightMaxSum[1]=17
 *
 * rightMaxSum should be: [0,17,13,11,4,0]
 *
 * Step 3: Try possible splits i = n-1 to 2n-1: (i=1,2,3)
 *   i=1: leftMinSum[1]=16, rightMaxSum[2]=13, diff=3
 *   i=2: leftMinSum[2]=12, rightMaxSum[3]=11, diff=1
 *   i=3: leftMinSum[3]=12, rightMaxSum[4]=4, diff=8
 *
 * Minimum difference = 1
 *
 */
