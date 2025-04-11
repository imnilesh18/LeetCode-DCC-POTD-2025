/*
 * 2843. Count Symmetric Integers
 *
 * Easy
 *
 * You are given two positive integers low and high.
 * An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
 * Return the number of symmetric integers in the range [low, high].
 *
 * Example 1:
 * Input: low = 1, high = 100
 * Output: 9
 * Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
 *
 * Example 2:
 * Input: low = 1200, high = 1230
 * Output: 4
 * Explanation: There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and 1230.
 *
 * Constraints:
 * 1 <= low <= high <= 10^4
 */

// Approach 1 (Brute Force): Convert each number to a string, then if it has an even number of digits, split it into two halves,
//           sum the digits in each half, and check if these sums are equal. If equal, increment the count of symmetric integers.
// Time Complexity: O(N * L), where N = (high - low + 1) and L is the maximum number of digits (which is constant here, at most 4 for 10^4).
// Space Complexity: O(L) for converting the number to a string, where L is the number of digits.
class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int count = 0;      // Counter for symmetric integers

        // Iterate over every number in the range [low, high]
        for (int num = low; num <= high; num++) {
            // Convert the number to a string to easily extract digits
            string s = to_string(num);
            int    l = s.length();   // Length of the number in digits

            // If the number of digits is odd, it cannot be symmetric (must have an even number of digits)
            if (l % 2 != 0) {
                continue;
            }

            int leftSum  = 0;      // Sum of the first half of the digits
            int rightSum = 0;      // Sum of the second half of the digits

            // Sum the first half digits
            for (int i = 0; i < l / 2; i++) {
                leftSum += s[i] - '0';
            }

            // Sum the second half digits
            for (int i = l / 2; i < l; i++) {
                rightSum += s[i] - '0';
            }

            // If both halves have the same sum, the integer is symmetric; increment count
            if (leftSum == rightSum) {
                count++;
            }
        }

        return count;      // Return the total count of symmetric integers
    }
};

/*
 *
 * Dry Run Example 1: num = 44
 *
 * Given: num = 44
 * Convert to string: s = "44", l = 2 (even number of digits).
 *
 * Calculate left half:
 *   For i = 0 to (2/2 - 1) i.e., i = 0:
 *     leftSum += s[0] - '0' => leftSum = 4
 *
 * Calculate right half:
 *   For i = 1 to 1:
 *     rightSum += s[1] - '0' => rightSum = 4
 *
 * Since leftSum (4) equals rightSum (4), 44 is symmetric.
 * Count is incremented.
 *
 * Dry Run Example 2: num = 1212
 *
 * Given: num = 1212
 * Convert to string: s = "1212", l = 4 (even number of digits).
 *
 * Calculate left half:
 *   For i = 0 to (4/2 - 1) i.e., i = 0 and 1:
 *     i = 0: leftSum += s[0] - '0' => leftSum = 1  (s[0] is '1')
 *     i = 1: leftSum += s[1] - '0' => leftSum = 1 + 2 = 3  (s[1] is '2')
 *
 * Calculate right half:
 *   For i = 2 to 3:
 *     i = 2: rightSum += s[2] - '0' => rightSum = 1  (s[2] is '1')
 *     i = 3: rightSum += s[3] - '0' => rightSum = 1 + 2 = 3  (s[3] is '2')
 *
 * Since leftSum (3) equals rightSum (3), 1212 is symmetric.
 * Count is incremented.
 *
 */

/******************************************** Approach 2 ******************************************************/

// Intuition:

/*
 * Constraint:
 * 1 <= low <= high <= 10^4
 *
 * This means the input range can go up to 10,000.
 *
 * ---------------------------------------------------------
 * Even-Digit Constraint:
 * ---------------------------------------------------------
 * Since the problem requires us to split the number into two equal halves, the integer must have an even number of digits. In our constraint (up to 10^4), the possible lengths for symmetric integers are:
 *  - 2 digits
 *  - 4 digits
 *
 * (Note: 6-digit numbers are not possible under the given constraint.)
 *
 * ---------------------------------------------------------
 * 2-Digit Symmetric Integers:
 * ---------------------------------------------------------
 * For 2-digit numbers, the symmetric integers are those where the sum of the first half (the first digit) is equal to the sum of the second half (the second digit).
 *
 * Observation:
 *  - A 2-digit integer is symmetric if the two digits are equal.
 *  - Therefore, symmetric 2-digit numbers are exactly the multiples of 11.
 *
 * The valid 2-digit symmetric integers are:
 *  11, 22, 33, 44, 55, 66, 77, 88, 99
 *
 * These numbers cover the range from 10 to 99.
 *
 * - If the number is a 2-digit number (10 <= num <= 99), then the symmetric integers are those that are multiples of 11. In this case:
 *     if (10 <= num && num <= 99 && num % 11 == 0) {
 *         count++;
 *     }
 *
 * ---------------------------------------------------------
 * 4-Digit Symmetric Integers:
 * ---------------------------------------------------------
 * For 4-digit numbers, an integer x is symmetric if the sum of the first two digits equals the sum of the last two digits.
 *
 * Example:
 *  Consider the number 1212.
 *
 *  To extract each digit, we can perform the following operations:
 *     - First digit = 1212 / 1000 = 1
 *     - Second digit = (1212 / 100) % 10
 *                    = 12 % 10 = 2  (since 1212/100 gives 12)
 *
 *  Now, the sum of the first half (first and second digits):
 *     1 + 2 = 3
 *
 *     - Third digit = (1212 / 10) % 10
 *                   = 121 % 10 = 1  (since 1212/10 gives 121)
 *     - Fourth digit = (1212 / 1) % 10
 *                    = 1212 % 10 = 2
 *
 *  Sum of the second half (third and fourth digits):
 *     1 + 2 = 3
 *
 * Since both halves sum to 3, the number 1212 is symmetric.
 *
 * ---------------------------------------------------------
 * How We Extract Digits for 4-Digit Numbers:
 * ---------------------------------------------------------
 * For a 4-digit number 'num', the operations to extract each digit are:
 *  - 1st digit: num / 1000
 *  - 2nd digit: (num / 100) % 10
 *  - 3rd digit: (num / 10) % 10
 *  - 4th digit: num % 10   (or equivalently, (num / 1) % 10)
 *
 * These operations allow us to get each digit in constant time, and then we can check if the sum of the first two equals the sum of the last two.
 * - If the number is a 4-digit number (1000 <= num <= 9999), then:
 *  1. Extract the first digit by: num / 1000.
 *  2. Extract the second digit by: (num / 100) % 10.
 *  3. Calculate the sum of the first half: first digit + second digit.
 *  4. Extract the third digit by: (num / 10) % 10.
 *  5. Extract the fourth digit by: num % 10.
 *  6. Calculate the sum of the second half: third digit + fourth digit.
 *  7. If both sums are equal, the number is symmetric.
 *
 * ---------------------------------------------------------
 * Approach Summary:
 * ---------------------------------------------------------
 * - If the number is a 2-digit number (10 <= num <= 99), then the symmetric integers are those that are multiples of 11. In this case:
 *     if (10 <= num && num <= 99 && num % 11 == 0) {
 *         count++;
 *     }
 * - If the number is a 4-digit number (1000 <= num <= 9999), then:
 *  1. Extract the first digit by: num / 1000.
 *  2. Extract the second digit by: (num / 100) % 10.
 *  3. Calculate the sum of the first half: first digit + second digit.
 *  4. Extract the third digit by: (num / 10) % 10.
 *  5. Extract the fourth digit by: num % 10.
 *  6. Calculate the sum of the second half: third digit + fourth digit.
 *  7. If both sums are equal, the number is symmetric.
 *
 * By using these steps, we can efficiently determine if a given integer is symmetric.
 */

// Approach 2: Iterate over all integers in [low, high] and check if each integer is symmetric.
//            For 2-digit numbers, check if the number is a multiple of 11 (i.e., both digits are equal).
//            For 4-digit numbers, extract the digits and check if the sum of the first two equals the sum of the last two.
// Time Complexity: O(high - low + 1), since we examine each number in the range.
// Space Complexity: O(1), as no extra space is used besides fixed variables.
class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int count = 0;      // Counter for symmetric integers

        // Iterate over every number in the range [low, high]
        for (int num = low; num <= high; num++) {
            // Check for 2-digit symmetric numbers: They are multiples of 11 (e.g., 11,22,...,99)
            if (num >= 10 && num <= 99 && num % 11 == 0) {
                count++;
            }
            // Check for 4-digit symmetric numbers
            else if (num >= 1000 && num <= 9999) {
                int first  = num / 1000;              // Get the first digit
                int second = (num / 100) % 10;        // Get the second digit

                int third  = (num / 10) % 10;         // Get the third digit
                int fourth = num % 10;                // Get the fourth digit

                // Check if the sum of the first two digits equals the sum of the last two digits
                if (first + second == third + fourth) {
                    count++;
                }
            }
        }

        return count;      // Return the count of symmetric integers found
    }
};

/*
 *
 * Dry Run Example 1: num = 44 (2-digit number)
 *
 * Given: num = 44
 * Check: Is 44 a 2-digit number? Yes, since 10 <= 44 <= 99.
 *       Check if 44 % 11 == 0:
 *           44 % 11 = 0 → True.
 *       Therefore, 44 is symmetric.
 *       Count is incremented.
 *
 * Dry Run Example 2: num = 1212 (4-digit number)
 *
 * Given: num = 1212
 * Check: Is 1212 between 1000 and 9999? Yes.
 *
 * Extract digits:
 *    first = 1212 / 1000 = 1
 *    second = (1212 / 100) % 10 = (12) % 10 = 2
 *    third = (1212 / 10) % 10 = (121) % 10 = 1
 *    fourth = 1212 % 10 = 2
 *
 * Compute sums:
 *    Sum of first half = first + second = 1 + 2 = 3
 *    Sum of second half = third + fourth = 1 + 2 = 3
 *
 * Check equality:
 *    3 == 3 → True, so 1212 is symmetric.
 *    Count is incremented.
 *
 */
