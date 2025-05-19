/*
 * 3024. Type of Triangle
 *
 * Easy
 *
 * You are given a 0-indexed integer array nums of size 3 which can form the sides of a triangle.
 * A triangle is called equilateral if it has all sides of equal length.
 * A triangle is called isosceles if it has exactly two sides of equal length.
 * A triangle is called scalene if all its sides are of different lengths.
 * Return a string representing the type of triangle that can be formed or "none" if it cannot form a triangle.
 *
 * Example 1:
 * Input: nums = [3,3,3]
 * Output: "equilateral"
 * Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.
 *
 * Example 2:
 * Input: nums = [3,4,5]
 * Output: "scalene"
 * Explanation:
 * nums[0] + nums[1] = 3 + 4 = 7, which is greater than nums[2] = 5.
 * nums[0] + nums[2] = 3 + 5 = 8, which is greater than nums[1] = 4.
 * nums[1] + nums[2] = 4 + 5 = 9, which is greater than nums[0] = 3.
 * Since the sum of the two sides is greater than the third side for all three cases, therefore, it can form a triangle.
 * As all the sides are of different lengths, it will form a scalene triangle.
 *
 * Constraints:
 * nums.length == 3
 * 1 <= nums[i] <= 100
 */

// Approach: Check triangle validity using triangle inequality, then determine type by comparing side lengths.
// Time Complexity: O(1) – Constant time as there are always 3 sides to compare.
// Space Complexity: O(1) – No extra space used.
class Solution {
public:
    string triangleType(vector<int>& nums) {
        // Check if the three sides can form a triangle using triangle inequality
        bool valid = (nums[0] + nums[1] > nums[2]) &&
                     (nums[0] + nums[2] > nums[1]) &&
                     (nums[1] + nums[2] > nums[0]);

        // If not a valid triangle, return "none"
        if (!valid) {
            return "none";
        }

        // If all three sides are equal, it's an equilateral triangle
        if (nums[0] == nums[1] && nums[1] == nums[2]) {
            return "equilateral";
        }
        // If all sides are different, it's a scalene triangle
        else if (nums[0] != nums[1] && nums[0] != nums[2] && nums[1] != nums[2]) {
            return "scalene";
        }

        // If exactly two sides are equal, it's an isosceles triangle
        return "isosceles";
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [3, 4, 5]
 * Step 1: Check triangle inequality:
 *         3 + 4 = 7 > 5 ✅
 *         3 + 5 = 8 > 4 ✅
 *         4 + 5 = 9 > 3 ✅
 *         => Valid triangle
 *
 * Step 2: Check side equality:
 *         3 != 4, 3 != 5, 4 != 5 => All sides different
 *         => It's a scalene triangle
 *
 * Output: "scalene"
 *
 */
