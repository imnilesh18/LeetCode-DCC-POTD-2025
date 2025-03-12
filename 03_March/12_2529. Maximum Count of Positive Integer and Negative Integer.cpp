/*
 * 2529. Maximum Count of Positive Integer and Negative Integer
 *
 * Given an array nums sorted in non-decreasing order, return the maximum between the number of positive integers and the number of negative integers.
 * In other words, if the number of positive integers in nums is pos and the number of negative integers is neg, then return the maximum of pos and neg.
 * Note that 0 is neither positive nor negative.
 *
 * Example 1:
 * Input: nums = [-2,-1,-1,1,2,3]
 * Output: 3
 * Explanation: There are 3 positive integers and 3 negative integers. The maximum count among them is 3.
 *
 * Example 2:
 * Input: nums = [-3,-2,-1,0,0,1,2]
 * Output: 3
 * Explanation: There are 2 positive integers and 3 negative integers. The maximum count among them is 3.
 *
 * Example 3:
 * Input: nums = [5,20,66,1314]
 * Output: 4
 * Explanation: There are 4 positive integers and 0 negative integers. The maximum count among them is 4.
 *
 * Constraints:
 * 1 <= nums.length <= 2000
 * -2000 <= nums[i] <= 2000
 * nums is sorted in a non-decreasing order.
 *
 * Follow up: Can you solve the problem in O(log(n)) time complexity?
 */

/************************************************** C++ **************************************************/

// Approach 1: Use two lambda functions with count_if to count positive and negative numbers separately, then return the maximum of the two counts.
// Time Complexity: O(n) - Each element in the array is checked once.
// Space Complexity: O(1) - Only a constant amount of extra space is used.
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        // Lambda function to check if a number is positive
        auto lambdaP = [](int num) {
                           return num > 0;
                       };

        // Lambda function to check if a number is negative
        auto lambdaN = [](int num) {
                           return num < 0;
                       };

        // Count the positive numbers using lambdaP
        int countPositive = count_if(begin(nums), end(nums), lambdaP);
        // Count the negative numbers using lambdaN
        int countNegative = count_if(begin(nums), end(nums), lambdaN);

        // Return the maximum count between positive and negative numbers
        return max(countPositive, countNegative);
    }
};

/*
 * Dry Run:
 * Input: nums = [-2, -1, -1, 1, 2, 3]
 * Step 1: lambdaP counts positive numbers: [1, 2, 3] => countPositive = 3
 * Step 2: lambdaN counts negative numbers: [-2, -1, -1] => countNegative = 3
 * Step 3: Return max(3, 3) which is 3.
 */

// Approach 2: Use binary search (lower_bound) to find the first positive number and the first non-negative number.
// The count of positives is calculated as the number of elements after the first positive,
// and the count of negatives is given by the index of the first non-negative element.
// Time Complexity: O(log(n)) - Each lower_bound operation performs a binary search.
// Space Complexity: O(1) - Only constant extra space is used.
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int n = nums.size();

        // Find the index of the first positive number using lower_bound for value 1
        int firstP = lower_bound(begin(nums), end(nums), 1) - begin(nums);
        // Find the index of the first non-negative number using lower_bound for value 0
        int firstN = lower_bound(begin(nums), end(nums), 0) - begin(nums);

        // Count positives as n - firstP, and negatives as firstN (since negatives precede the first non-negative)
        return max(n - firstP, firstN);
    }
};

/*
 * Dry Run:
 * Input: nums = [-3, -2, -1, 0, 1, 2, 3]
 * Step 1: n = 7.
 * Step 2: lower_bound for 1 finds the first positive at index 4 (element 1), so firstP = 4.
 * Step 3: lower_bound for 0 finds the first non-negative at index 3 (element 0), so firstN = 3.
 * Step 4: Calculate positive count: 7 - 4 = 3.
 * Step 5: Calculate negative count: 3 (elements before index 3).
 * Step 6: Return max(3, 3) which is 3.
 */

/************************************************** Java **************************************************/

// Approach 1: Use two lambda predicates with streams to filter and count positive and negative numbers, then return the maximum count.
// Time Complexity: O(n) - Each element in the array is processed once by the stream operations.
// Space Complexity: O(1) - Only a constant amount of extra space is used.
class Solution {
    public int maximumCount(int[] nums) {
        // Lambda predicate to check if a number is positive
        IntPredicate lambdaP = num->num > 0;
        // Lambda predicate to check if a number is negative
        IntPredicate lambdaN = num->num < 0;

        // Count positive numbers using stream filter with lambdaP
        int positiveCount = (int)Arrays.stream(nums).filter(lambdaP).count();
        // Count negative numbers using stream filter with lambdaN
        int negativeCount = (int)Arrays.stream(nums).filter(lambdaN).count();

        // Return the maximum count between positive and negative numbers
        return Math.max(positiveCount, negativeCount);
    }
}

/*
 * Dry Run:
 * Input: nums = [-3, -2, -1, 0, 1, 2, 3]
 * Step 1: lambdaP filters positive numbers: [1, 2, 3] => positiveCount = 3
 * Step 2: lambdaN filters negative numbers: [-3, -2, -1] => negativeCount = 3
 * Step 3: Math.max(positiveCount, negativeCount) returns 3.
 */

// Approach 2: Use a custom binary search (apnaLowerB) to find the first index where elements are greater than or equal to a target value.
// For positive numbers, we search for the first index with a value >= 1 (first positive number),
// and for negatives, we search for the first index with a value >= 0 (first non-negative, which indicates the end of negatives).
// Time Complexity: O(log(n)) - Each binary search operation runs in logarithmic time.
// Space Complexity: O(1) - Only a constant amount of extra space is used.
class Solution {
    public int maximumCount(int[] nums) {
        int n = nums.length;

        // Find the first index where the element is >= 1 (first positive number)
        int firstP = apnaLowerB(nums, 1); // >= 1
        // Find the first index where the element is >= 0 (first non-negative number)
        int firstN = apnaLowerB(nums, 0); // >= 0

        // The count of positive numbers is n - firstP and the count of negative numbers is firstN.
        // Return the maximum of these two counts.
        return Math.max(n - firstP, firstN);
    }
    // Custom binary search to find the first index where nums[index] >= target.
    public int apnaLowerB(int[] nums, int target) {
        int l      = 0;
        int r      = nums.length - 1;
        int result = nums.length;  // Default value if no element satisfies the condition

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] < target) {
                // If the current element is less than target, search the right half.
                l = mid + 1;
            } else {
                // Found an element >= target, update result and search in the left half for an earlier occurrence.
                result = mid;
                r      = mid - 1;
            }
        }
        // Example: for nums = {0, 0, 0, 0} and target = 0, result will be 0.
        return result;
    }
}

/*
 * Dry Run:
 * Input: nums = [-3, -2, -1, 0, 1, 2, 3]
 * Step 1: n = 7.
 * Step 2: Call apnaLowerB(nums, 1) to find the first index where number >= 1.
 *      Binary search finds index 4 (element 1), so firstP = 4.
 * Step 3: Call apnaLowerB(nums, 0) to find the first index where number >= 0.
 *      Binary search finds index 3 (element 0), so firstN = 3.
 * Step 4: Positive count = n - firstP = 7 - 4 = 3.
 * Step 5: Negative count = firstN = 3.
 * Step 6: Return Math.max(3, 3) which is 3.
 */
