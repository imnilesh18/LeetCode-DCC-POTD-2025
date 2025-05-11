/*
 * 1550. Three Consecutive Odds
 *
 * Easy
 *
 * Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.
 *
 * Example 1:
 * Input: arr = [2,6,4,1]
 * Output: false
 * Explanation: There are no three consecutive odds.
 *
 * Example 2:
 * Input: arr = [1,2,34,3,4,5,7,23,12]
 * Output: true
 * Explanation: [5,7,23] are three consecutive odds.
 *
 * Constraints:
 * 1 <= arr.length <= 1000
 * 1 <= arr[i] <= 1000
 */

// Approach 1: Iterate through the array and check every group of 3 consecutive numbers to see if all are odd.
// Time Complexity: O(n) - We traverse the array once, checking each triplet in linear time.
// Space Complexity: O(1) - No extra space is used, just a few variables.
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size();               // Store the size of the input array

        for (int i = 0; i < n - 2; i++) { // Loop until the third last element
            // Check if the current, next, and next to next elements are all odd
            if ((arr[i] % 2 == 1) && (arr[i + 1] % 2 == 1) && (arr[i + 2] % 2 == 1)) {
                return true; // If all three are odd, return true
            }
        }
        return false; // If no such triplet is found, return false
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 34, 3, 4, 5, 7, 23, 12]
 * Step-by-step iteration:
 * i = 0 -> [1, 2, 34] => 1 is odd, 2 is even => Not valid
 * i = 1 -> [2, 34, 3] => 2 is even => Not valid
 * i = 2 -> [34, 3, 4] => 34 is even => Not valid
 * i = 3 -> [3, 4, 5] => 3 is odd, 4 is even => Not valid
 * i = 4 -> [4, 5, 7] => 4 is even => Not valid
 * i = 5 -> [5, 7, 23] => all are odd => Valid => return true
 *
 * Output: true
 *
 */

// Approach 2: Traverse the array and maintain a counter for consecutive odd numbers; reset if an even is found.
// Time Complexity: O(n) - The array is traversed once from start to end.
// Space Complexity: O(1) - Only a single integer counter is used for tracking odds.
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n        = arr.size(); // Get the size of the array
        int oddCount = 0;          // Counter to track consecutive odd numbers

        for (int i = 0; i < n; i++) {
            // Check if current number is odd
            if (arr[i] % 2 == 1) {
                oddCount++;   // Increment counter if odd
            } else {
                oddCount = 0; // Reset counter if even
            }

            // If 3 consecutive odds are found, return true
            if (oddCount == 3) {
                return true;
            }
        }

        // No such sequence found
        return false;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 34, 3, 4, 5, 7, 23, 12]
 *
 * Initialization:
 * oddCount = 0
 *
 * Iteration:
 * i = 0 -> arr[i] = 1 (odd) => oddCount = 1
 * i = 1 -> arr[i] = 2 (even) => oddCount = 0
 * i = 2 -> arr[i] = 34 (even) => oddCount = 0
 * i = 3 -> arr[i] = 3 (odd) => oddCount = 1
 * i = 4 -> arr[i] = 4 (even) => oddCount = 0
 * i = 5 -> arr[i] = 5 (odd) => oddCount = 1
 * i = 6 -> arr[i] = 7 (odd) => oddCount = 2
 * i = 7 -> arr[i] = 23 (odd) => oddCount = 3 => return true
 *
 * Output: true
 *
 */

// Approach 3: Loop through the array and check if the product of every triplet is odd, which implies all three numbers are odd.
// Time Complexity: O(n) - We check each triplet in the array once.
// Space Complexity: O(1) - Constant space used for the product variable.
class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size(); // Get the size of the array

        // Loop through the array up to the third-to-last element
        for (int i = 0; i < n - 2; i++) {
            int product = arr[i] * arr[i + 1] * arr[i + 2]; // Multiply three consecutive elements

            // Check if the product is odd (i.e., all three numbers must be odd)
            if (product % 2 == 1) {
                return true;                   // If product is odd, return true
            }
        }

        return false; // No such triplet found
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 34, 3, 4, 5, 7, 23, 12]
 *
 * Iteration:
 * i = 0 -> [1, 2, 34] -> product = 1*2*34 = 68 => even => skip
 * i = 1 -> [2, 34, 3] -> product = 2*34*3 = 204 => even => skip
 * i = 2 -> [34, 3, 4] -> product = 34*3*4 = 408 => even => skip
 * i = 3 -> [3, 4, 5] -> product = 3*4*5 = 60 => even => skip
 * i = 4 -> [4, 5, 7] -> product = 4*5*7 = 140 => even => skip
 * i = 5 -> [5, 7, 23] -> product = 5*7*23 = 805 => odd => return true
 *
 * Output: true
 *
 */
