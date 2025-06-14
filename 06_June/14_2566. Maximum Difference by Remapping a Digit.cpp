/*
 * 2566. Maximum Difference by Remapping a Digit
 *
 * Easy
 *
 * You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
 * Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
 * Notes:
 * When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
 * Bob can remap a digit to itself, in which case num does not change.
 * Bob can remap different digits for obtaining minimum and maximum values respectively.
 * The resulting number after remapping can contain leading zeroes.
 *
 * Example 1:
 * Input: num = 11891
 * Output: 99009
 * Explanation:
 * To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
 * To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
 * The difference between these two numbers is 99009.
 *
 * Example 2:
 * Input: num = 90
 * Output: 99
 * Explanation:
 * The maximum value that can be returned by the function is 99 (if 0 is replaced by 9) and the minimum value that can be returned by the function is 0 (if 9 is replaced by 0).
 * Thus, we return 99.
 *
 * Constraints:
 * 1 <= num <= 10^8
 */

/************************************************************ C++ ************************************************/

// Approach: Convert number to string, try replacing one digit with '9' for max and one digit with '0' for min to get max and min values, then return their difference.
// Time Complexity: O(n) where n is the number of digits in the number (max 9), due to scanning and replacing characters.
// Space Complexity: O(n) for storing two strings representing the number.
class Solution {
public:
    int minMaxDifference(int num) {
        string str1 = to_string(num);                 // convert number to string for max manipulation
        string str2 = str1;                           // duplicate the string for min manipulation

        int idx = str1.find_first_not_of('9');        // find the first digit that is not '9'

        if (idx != string::npos) {                    // if such a digit exists
            char ch = str1[idx];                      // store that digit
            replace(begin(str1), end(str1), ch, '9'); // replace all occurrences of it with '9' for max value
        }

        char ch = str2[0];                        // for min value, take the first digit
        replace(begin(str2), end(str2), ch, '0'); // replace all occurrences of it with '0'

        return stoi(str1) - stoi(str2);           // return difference between max and min values
    }
};

/*
 *
 * Dry Run
 *
 * Input: num = 11891
 * Step 1: Convert num to string => str1 = "11891", str2 = "11891"
 * Step 2: Find first non-'9' digit => str1[0] = '1', so idx = 0
 * Step 3: Replace all '1' in str1 with '9' => str1 = "99899"
 * Step 4: Take first digit in str2, which is '1', and replace all '1' with '0' => str2 = "00890"
 * Step 5: Convert both to integer => stoi(str1) = 99899, stoi(str2) = 890 (leading zeros are ignored)
 * Step 6: Return the difference => 99899 - 890 = 99009
 * Output: 99009
 */

/************************************************************ JAVA ************************************************/

// Approach: Convert number to string, replace one digit with '9' for max value and one digit with '0' for min value, then calculate the difference.
// Time Complexity: O(n), where n is the number of digits (up to 9), due to scanning and replacing characters in the string.
// Space Complexity: O(n), for storing the number as two strings.
class Solution {
    public int minMaxDifference(int num) {
        String str1 = Integer.toString(num); // Convert num to string for max manipulation
        String str2 = str1;                  // Copy the same string for min manipulation

        int idx = 0;

        // Find the first digit that is not '9'
        for (int i = 0; i < str1.length(); i++) {
            if (str1.charAt(i) != '9') {
                idx = i; // Save index of the digit to be replaced
                break;
            }
        }

        // If a non-'9' digit was found, replace it with '9' to get maximum value
        if (idx < str1.length()) {
            str1 = str1.replace(str1.charAt(idx), '9');
        }

        // Replace all occurrences of the first digit with '0' to get minimum value
        str2 = str2.replace(str2.charAt(0), '0');

        // Return the difference between max and min values
        return Integer.parseInt(str1) - Integer.parseInt(str2);
    }
}

/*
 *
 * Dry Run
 *
 * Input: num = 11891
 * Step 1: str1 = "11891", str2 = "11891"
 * Step 2: Loop to find first non-'9' digit: str1[0] = '1' => idx = 0
 * Step 3: Replace all '1' in str1 with '9' => str1 = "99899"
 * Step 4: Replace all '1' in str2 (first digit) with '0' => str2 = "00890"
 * Step 5: Integer.parseInt(str1) = 99899, Integer.parseInt(str2) = 890
 * Step 6: Return 99899 - 890 = 99009
 * Output: 99009
 */
