/*
 * 1432. Max Difference You Can Get From Changing an Integer
 *
 * Medium
 *
 * You are given an integer num. You will apply the following steps to num two separate times:
 * Pick a digit x (0 <= x <= 9).
 * Pick another digit y (0 <= y <= 9). Note y can be equal to x.
 * Replace all the occurrences of x in the decimal representation of num by y.
 * Let a and b be the two results from applying the operation to num independently.
 * Return the max difference between a and b.
 * Note that neither a nor b may have any leading zeros, and must not be 0.
 *
 * Example 1:
 * Input: num = 555
 * Output: 888
 * Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
 * The second time pick x = 5 and y = 1 and store the new integer in b.
 * We have now a = 999 and b = 111 and max difference = 888
 *
 * Example 2:
 * Input: num = 9
 * Output: 8
 * Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
 * The second time pick x = 9 and y = 1 and store the new integer in b.
 * We have now a = 9 and b = 1 and max difference = 8
 *
 * Constraints:
 * 1 <= num <= 10^8
 */

// Approach: Try to maximize the number by replacing first non-9 digit with 9; try to minimize by replacing first digit (if not 1) with 1, or others (if not 0) with 0.
// Time Complexity: O(n), where n is the number of digits in num, because we scan and replace digits at most twice.
// Space Complexity: O(n), due to the two string copies made from the number.
class Solution {
public:
    int maxDiff(int num) {
        string str1 = to_string(num);  // Convert number to string for easy manipulation
        string str2 = str1;            // Create a second copy for separate transformation

        // Maximize: replace the first non-9 digit with 9
        int idx = str1.find_first_not_of('9');  // Find first digit that is not 9

        if (idx != string::npos) {
            char ch = str1[idx];                      // Store that digit
            replace(begin(str1), end(str1), ch, '9'); // Replace all its occurrences with 9
        }

        // Minimize: try to make the number as small as possible without leading 0
        for (int i = 0; i < str2.length(); i++) {
            char ch = str2[i];

            if (i == 0) {
                if (ch != '1') {
                    replace(begin(str2), end(str2), ch, '1'); // Replace first digit with 1 if it's not 1
                    break;
                }
            } else if (ch != '0' && ch != str2[0]) {
                replace(begin(str2), end(str2), ch, '0'); // Replace other digits with 0 if not same as first
                break;
            }
        }

        return stoi(str1) - stoi(str2);  // Convert strings back to integers and return the difference
    }
};

/*
 *
 * Dry Run
 *
 * Input: num = 555
 * Step 1: Convert to string → str1 = "555", str2 = "555"
 *
 * Maximize:
 * - First non-9 digit = '5', replace all '5' with '9' → str1 = "999"
 *
 * Minimize:
 * - First digit = '5', not equal to '1', replace all '5' with '1' → str2 = "111"
 *
 * Final values: a = 999, b = 111
 * Return 999 - 111 = 888
 *
 */
