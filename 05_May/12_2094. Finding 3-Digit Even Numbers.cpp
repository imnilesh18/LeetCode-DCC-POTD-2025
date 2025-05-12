/*
 * 2094. Finding 3-Digit Even Numbers
 *
 * Easy
 *
 * You are given an integer array digits, where each element is a digit. The array may contain duplicates.
 * You need to find all the unique integers that follow the given requirements:
 * The integer consists of the concatenation of three elements from digits in any arbitrary order.
 * The integer does not have leading zeros.
 * The integer is even.
 * For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
 * Return a sorted array of the unique integers.
 *
 * Example 1:
 * Input: digits = [2,1,3,0]
 * Output: [102,120,130,132,210,230,302,310,312,320]
 * Explanation: All the possible integers that follow the requirements are in the output array.
 * Notice that there are no odd integers or integers with leading zeros.
 *
 * Example 2:
 * Input: digits = [2,2,8,8,2]
 * Output: [222,228,282,288,822,828,882]
 * Explanation: The same digit can be used as many times as it appears in digits.
 * In this example, the digit 8 is used twice each time in 288, 828, and 882.
 *
 * Example 3:
 * Input: digits = [3,7,5]
 * Output: []
 * Explanation: No even integers can be formed using the given digits.
 *
 * Constraints:
 * 3 <= digits.length <= 100
 * 0 <= digits[i] <= 9
 */

// Approach: Use frequency count of digits and iterate through all valid 3-digit combinations ensuring no leading zero and last digit is even.
// Time Complexity: O(1) - As we iterate through a fixed number of 3-digit combinations (max 9*10*5).
// Space Complexity: O(1) - Uses fixed size arrays regardless of input size.
class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> result;            // Stores the valid 3-digit even numbers
        vector<int> mp(10, 0);         // Frequency map to count occurrences of digits (0-9)

        // Count the frequency of each digit
        for (int& digit : digits) {
            mp[digit]++;
        }

        // First digit of 3-digit number (hundreds place) cannot be zero
        for (int i = 1; i <= 9; i++) {
            if (mp[i] == 0) {
                continue;              // Skip if digit not present
            }
            mp[i]--;                   // Use one occurrence of digit i

            // Second digit (tens place)
            for (int j = 0; j <= 9; j++) {
                if (mp[j] == 0) {
                    continue;
                }
                mp[j]--;               // Use one occurrence of digit j

                // Third digit (units place) must be even
                for (int k = 0; k <= 8; k += 2) {
                    if (mp[k] == 0) {
                        continue;
                    }
                    mp[k]--;           // Use one occurrence of digit k

                    // Form the number and add to result
                    int num = i * 100 + j * 10 + k;
                    result.push_back(num);

                    mp[k]++;           // Backtrack: restore digit k
                }
                mp[j]++;               // Backtrack: restore digit j
            }
            mp[i]++;                   // Backtrack: restore digit i
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: digits = [2,1,3,0]
 *
 * Step 1: Count frequency of digits
 * mp = [1,1,1,1,0,0,0,0,0,0]  // digits 0,1,2,3 occur once
 *
 * Step 2: Try all 3-digit combinations where:
 * - i ≠ 0 (hundreds digit)
 * - k is even (units digit)
 *
 * Iteration 1:
 * i = 1 (mp[1]--)
 * j = 0 (mp[0]--)
 *  k = 2 → num = 102 → result = [102]
 * j = 2 (mp[2]--)
 *  k = 0 → num = 120 → result = [102,120]
 * j = 3 (mp[3]--)
 *  k = 0 → num = 130, k = 2 → num = 132 → result = [...130,132]
 *
 * Continue this for i = 2, i = 3...
 *
 * Final Output: [102,120,130,132,210,230,302,310,312,320]
 *
 *
 */
