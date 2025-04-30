/*
 * 1295. Find Numbers with Even Number of Digits
 *
 * Easy
 *
 * Given an array nums of integers, return how many of them contain an even number of digits.
 *
 * Example 1:
 * Input: nums = [12,345,2,6,7896]
 * Output: 2
 * Explanation:
 * 12 contains 2 digits (even number of digits).
 * 345 contains 3 digits (odd number of digits).
 * 2 contains 1 digit (odd number of digits).
 * 6 contains 1 digit (odd number of digits).
 * 7896 contains 4 digits (even number of digits).
 * Therefore only 12 and 7896 contain an even number of digits.
 *
 * Example 2:
 * Input: nums = [555,901,482,1771]
 * Output: 1
 * Explanation:
 * Only 1771 contains an even number of digits.
 *
 * Constraints:
 * 1 <= nums.length <= 500
 * 1 <= nums[i] <= 10^5
 */

// Approach 1: Traverse each number in the array and count its digits by dividing by 10. If the digit count is even, increment the result.
// Time Complexity: O(N * D), where N is the number of elements and D is the number of digits per element (max 6), effectively O(N)
// Space Complexity: O(1), as no extra space is used apart from a few variables
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int n      = nums.size(); // Get the size of the input array
        int result = 0;           // This variable will store the count of numbers with even number of digits

        for (int i = 0; i < n; i++) {
            int num   = nums[i]; // Current number to process
            int count = 0;       // Count digits in the current number

            while (num) {
                num = num / 10; // Remove the last digit
                count++;        // Increment digit count
            }

            if (count % 2 == 0) { // If digit count is even
                result++;         // Increment result
            }
        }

        return result;     // Return the final count
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [12, 345, 2, 6, 7896]
 *
 * i = 0: num = 12 → count = 2 → even → result = 1
 * i = 1: num = 345 → count = 3 → odd → result = 1
 * i = 2: num = 2 → count = 1 → odd → result = 1
 * i = 3: num = 6 → count = 1 → odd → result = 1
 * i = 4: num = 7896 → count = 4 → even → result = 2
 *
 * Output: 2
 *
 */

// Approach 2: Convert each number to a string and check if its length is even
// Time Complexity: O(n * log10m), where n = number of elements, m = max number value (since converting to string is log10 based)
// Space Complexity: O(1), no extra space apart from temporary string
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int result = 0;     // Stores count of numbers with even number of digits

        for (int num : nums) {
            string str = to_string(num); // Convert number to string
            if (str.length() % 2 == 0) { // Check if the length (i.e., digit count) is even
                result++;                // Increment result if condition is met
            }
        }

        return result;     // Return the final count
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [555, 901, 482, 1771]
 *
 * num = 555 → str = "555" → length = 3 → odd → result = 0
 * num = 901 → str = "901" → length = 3 → odd → result = 0
 * num = 482 → str = "482" → length = 3 → odd → result = 0
 * num = 1771 → str = "1771" → length = 4 → even → result = 1
 *
 * Output: 1
 *
 */

// Approach 3: Use floor(log10(num)) + 1 to count digits directly without string conversion or division
// Time Complexity: O(n), assuming floor(log10(num)) is a constant time operation
// Space Complexity: O(1), as no extra space is used
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int result = 0; // Stores count of numbers with even number of digits

        for (int& num : nums) {
            int digitCount = floor(log10(num)) + 1; // Count digits using log10

            if (digitCount % 2 == 0) {              // Check if digit count is even
                result++;                           // Increment result if condition is satisfied
            }
        }

        return result; // Return the final count
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [12, 345, 2, 6, 7896]
 *
 * num = 12 → log10(12) ≈ 1.08 → floor(1.08) + 1 = 2 → even → result = 1
 * num = 345 → log10(345) ≈ 2.53 → floor(2.53) + 1 = 3 → odd → result = 1
 * num = 2 → log10(2) ≈ 0.3 → floor(0.3) + 1 = 1 → odd → result = 1
 * num = 6 → log10(6) ≈ 0.77 → floor(0.77) + 1 = 1 → odd → result = 1
 * num = 7896 → log10(7896) ≈ 3.89 → floor(3.89) + 1 = 4 → even → result = 2
 *
 * Output: 2
 *
 */

// Approach 4: Use ceil(log10(num+1)) to count digits; num+1 avoids log10(1) = 0 issue for single-digit numbers
// Time Complexity: O(n), assuming ceil(log10(num)) takes constant time
// Space Complexity: O(1), no extra space used
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int result = 0; // Stores count of numbers with even number of digits

        for (int& num : nums) {
            int digitCount = ceil(log10(num + 1)); // Compute digit count using ceil on log10(num + 1)

            if (digitCount % 2 == 0) {             // Check if digit count is even
                result++;                          // Increment result if condition is met
            }
        }

        return result; // Return the final count
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [12, 345, 2, 6, 7896]
 *
 * num = 12 → log10(13) ≈ 1.11 → ceil(1.11) = 2 → even → result = 1
 * num = 345 → log10(346) ≈ 2.54 → ceil(2.54) = 3 → odd → result = 1
 * num = 2 → log10(3) ≈ 0.47 → ceil(0.47) = 1 → odd → result = 1
 * num = 6 → log10(7) ≈ 0.84 → ceil(0.84) = 1 → odd → result = 1
 * num = 7896 → log10(7897) ≈ 3.89 → ceil(3.89) = 4 → even → result = 2
 *
 * Output: 2
 *
 */

// Approach 5: Use direct range checks based on constraints (1 <= nums[i] <= 10^5); only numbers with 2, 4, or 6 digits are valid
// Time Complexity: O(n), where n is the size of the input array
// Space Complexity: O(1), uses constant extra space
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int n      = nums.size(); // Size of input array
        int result = 0;           // Store count of numbers with even number of digits

        for (int i = 0; i < n; i++) {
            // Check if number has even digits: 2-digit, 4-digit, or exactly 6-digit (100000)
            if ((nums[i] >= 10 && nums[i] <= 99) ||
                (nums[i] >= 1000 && nums[i] <= 9999) ||
                (nums[i] == 100000)) {
                result++;     // Increment count if number satisfies any of the even-digit conditions
            }
        }

        return result;     // Return final count
    }
};

/*
 *
 * Dry Run
 *
 * Input: nums = [12, 345, 2, 6, 7896]
 *
 * nums[0] = 12 → in range 10–99 → result = 1
 * nums[1] = 345 → not in any valid range → result = 1
 * nums[2] = 2 → not in any valid range → result = 1
 * nums[3] = 6 → not in any valid range → result = 1
 * nums[4] = 7896 → in range 1000–9999 → result = 2
 *
 * Output: 2
 *
 */
