/*
 * 1718. Construct the Lexicographically Largest Valid Sequence
 *
 * Given an integer n, find a sequence that satisfies all of the following:
 *
 * The integer 1 occurs once in the sequence.
 * Each integer between 2 and n occurs twice in the sequence.
 * For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
 * The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
 *
 * Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.
 *
 * A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
 *
 * Example 1:
 * Input: n = 3
 * Output: [3,1,2,3,2]
 * Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
 *
 * Example 2:
 * Input: n = 5
 * Output: [5,3,1,4,3,5,2,4,2]
 *
 * Constraints:
 * 1 <= n <= 20
 */

// Approach: Backtracking with recursion to fill the sequence positions by trying numbers from n down to 1, ensuring that for numbers >1, the two occurrences are placed exactly num indices apart.
// T.C: O(n!) - Worst-case exponential time due to exploring all valid placements.
// S.C: O(n) - Uses additional space for the recursion call stack and auxiliary arrays.
class Solution {
public:
   // Recursive helper function to build the sequence starting from index i.
   bool solve(int i, int n, vector<int>& result, vector<bool>& used) {
      // If we have filled all positions, a valid sequence is constructed.
      if (i >= result.size()) {
         return true;
      }

      // If the current index is already filled, move to the next index.
      if (result[i] != -1) {
         return solve(i + 1, n, result, used);
      }

      // Try placing numbers from n down to 1 for lexicographical largeness.
      for (int num = n; num >= 1; num--) {
         // Skip the number if it has already been used.
         if (used[num]) {
            continue;
         }

         // Mark the number as used and assign it to the current index.
         used[num] = true;
         result[i] = num;

         // For number 1, only one occurrence is needed.
         if (num == 1) {
            if (solve(i + 1, n, result, used)) {
               return true;
            }
         } else {
            // For numbers greater than 1, the second occurrence must be placed exactly num indices apart.
            int j = i + num;
            // Ensure the target index is within bounds and unoccupied.
            if (j < result.size() && result[j] == -1) {
               result[j] = num;           // Place the second occurrence.
               if (solve(i + 1, n, result, used)) {
                  return true;
               }
               // Backtrack: Remove the second occurrence if it didn't lead to a solution.
               result[j] = -1;
            }
         }

         // Backtrack: Unmark the number and clear the current index.
         used[num] = false;
         result[i] = -1;
      }

      // Return false if no valid placement can be made from this state.
      return false;
   }

   vector<int> constructDistancedSequence(int n) {
      // Initialize the result vector with 2*n - 1 positions filled with -1.
      vector<int> result(2 * n - 1, -1);
      // 'used' vector to track if a number is already placed; index 0 is unused.
      vector<bool> used(n + 1, false);

      // Begin the recursive backtracking from index 0.
      solve(0, n, result, used);
      return result;
   }
};

/*
 * DRY RUN
 * Example: n = 3
 * Initial result array (size = 2*3 - 1 = 5): [-1, -1, -1, -1, -1]
 * used array: [false, false, false, false]   (indices 0 to 3, 0 unused)
 *
 * Call: solve(0, 3, result, used)
 * i = 0, result[0] = -1
 * Try num = 3:
 *  Mark used[3] = true; set result[0] = 3
 *  Since num != 1, calculate j = 0 + 3 = 3.
 *  Check result[3] is -1 and within bounds; set result[3] = 3.
 *  Current result: [3, -1, -1, 3, -1]
 *  Call: solve(1, 3, result, used)
 *    i = 1, result[1] = -1
 *    Try num = 3: already used, skip.
 *    Try num = 2:
 *      Mark used[2] = true; set result[1] = 2
 *      Since num != 1, calculate j = 1 + 2 = 3.
 *      result[3] is already 3, so placement fails.
 *      Backtrack: unmark used[2] = false; reset result[1] = -1.
 *    Try num = 1:
 *      Mark used[1] = true; set result[1] = 1
 *      For num = 1, only one occurrence is needed.
 *      Call: solve(2, 3, result, used)
 *        i = 2, result[2] = -1
 *        Try num = 3: used, skip.
 *        Try num = 2:
 *          Mark used[2] = true; set result[2] = 2
 *          Since num != 1, calculate j = 2 + 2 = 4.
 *          Check result[4] is -1; set result[4] = 2.
 *          Current result: [3, 1, 2, 3, 2]
 *          Call: solve(3, 3, result, used)
 *            i = 3, result[3] = 3 (already filled), so call solve(4, 3, result, used)
 *              i = 4, result[4] = 2 (already filled), so call solve(5, 3, result, used)
 *                i = 5, i >= result.size() (5), return true.
 *          The call returns true, unwinding all recursion.
 ********** DRY RUN END **********
 */
