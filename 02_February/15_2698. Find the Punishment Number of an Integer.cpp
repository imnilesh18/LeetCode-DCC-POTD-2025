/*
 * 2698. Find the Punishment Number of an Integer
 *
 * Given a positive integer n, return the punishment number of n.
 * The punishment number of n is defined as the sum of the squares of all integers i such that:
 * 1 <= i <= n
 * The decimal representation of i * i can be partitioned into contiguous substrings such that the sum of the integer values of these substrings equals i.
 *
 * Example 1:
 * Input: n = 10
 * Output: 182
 * Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
 * - 1 since 1 * 1 = 1
 * - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
 * - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
 * Hence, the punishment number of 10 is 1 + 81 + 100 = 182
 *
 * Example 2:
 * Input: n = 37
 * Output: 1478
 * Explanation: There are exactly 4 integers i in the range [1, 37] that satisfy the conditions in the statement:
 * - 1 since 1 * 1 = 1.
 * - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 + 1.
 * - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 + 0.
 * - 36 since 36 * 36 = 1296 and 1296 can be partitioned into 1 + 29 + 6.
 *
 * Hence, the punishment number of 37 is 1 + 81 + 100 + 1296 = 1478
 * Constraints:
 * 1 <= n <= 1000
 */

// Approach: For each integer i from 1 to n, compute i*i and use recursion (check) to explore all ways to partition the digits of i*i into contiguous substrings, checking if any partition sums to i.
// TC: O(n * 4^d) where d is the number of digits in i*i; although exponential in d, d is small.
// SC: O(d) due to recursion depth (d is the number of digits in i*i).
class Solution {
public:
   // Recursive function to check if the square (sq) can be partitioned such that the sum of the chosen parts plus currSum equals num.
   bool check(int sq, int currSum, int num) {
      // If there are no more digits left, check if the accumulated sum equals the target number.
      if (sq == 0) {
         return currSum == num;
      }
      // Try partitions of size 1, 2, 3, and 4 digits.
      return check(sq / 10, currSum + sq % 10, num) ||
             check(sq / 100, currSum + sq % 100, num) ||
             check(sq / 1000, currSum + sq % 1000, num) ||
             check(sq / 10000, currSum + sq % 10000, num);
   }

   // Function to compute the punishment number for n.
   int punishmentNumber(int n) {
      int punish = 0;

      // Iterate over all integers from 1 to n.
      for (int num = 1; num <= n; num++) {
         int sq = num * num;
         // If the square can be partitioned such that its parts sum to num, add the square to the punishment number.
         if (check(sq, 0, num)) {
            punish += sq;
         }
      }
      return punish;
   }
};

/*
 * Dry run:
 * Example: n = 10
 *
 * For num = 1:
 * sq = 1 * 1 = 1
 * Call check(1, 0, 1)
 *  -> call check(1 / 10, 0 + (1 % 10), 1) = check(0, 1, 1)
 *  -> since sq == 0, returns (1 == 1) which is true
 * Thus, 1 qualifies and contributes 1 to the punishment number.
 *
 * For num = 9:
 * sq = 9 * 9 = 81
 * Call check(81, 0, 9)
 *  -> First branch: check(81 / 10, 0 + (81 % 10), 9) = check(8, 1, 9)
 *       -> In check(8, 1, 9): call check(8 / 10, 1 + (8 % 10), 9) = check(0, 9, 9)
 *       -> returns true because (9 == 9)
 * Thus, 9 qualifies and contributes 81 to the punishment number.
 *
 * For num = 10:
 * sq = 10 * 10 = 100
 * Call check(100, 0, 10)
 *  -> First branch: check(100 / 10, 0 + (100 % 10), 10) = check(10, 0, 10)
 *       -> In check(10, 0, 10):
 *           -> First branch: check(10 / 10, 0 + (10 % 10), 10) = check(1, 0, 10)
 *                 -> In check(1, 0, 10): call check(1 / 10, 0 + (1 % 10), 10) = check(0, 1, 10)
 *                 -> returns false since 1 != 10
 *           -> Second branch: check(10 / 100, 0 + (10 % 100), 10) = check(0, 10, 10)
 *                 -> returns true because (10 == 10)
 * Thus, 10 qualifies and contributes 100 to the punishment number.
 *
 * Final punishment number for n = 10 is 1 + 81 + 100 = 182.
 */
