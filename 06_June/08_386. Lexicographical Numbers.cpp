/*
 * 386. Lexicographical Numbers
 *
 * Medium
 *
 * Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
 * You must write an algorithm that runs in O(n) time and uses O(1) extra space.
 *
 * Example 1:
 * Input: n = 13
 * Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
 *
 * Example 2:
 * Input: n = 2
 * Output: [1,2]
 *
 * Constraints:
 * 1 <= n <= 5 * 10^4
 */

// Approach: Use DFS to build numbers in lexicographical order by traversing from 1 to 9, then recursively appending digits 0–9 to simulate lexicographical growth.
// Time Complexity: O(n), as each number from 1 to n is visited exactly once.
// Space Complexity: O(1) extra space (excluding the output vector), as recursion depth is at most log(n) and no additional structures are used.
class Solution {
public:
    void solve(int curr, int n, vector<int>& result) {
        if (curr > n) {
            return; // Stop if the current number exceeds n
        }

        result.push_back(curr); // Add the current number to the result

        for (int append = 0; append <= 9; append++) {
            int newNum = curr * 10 + append; // Try to append digits to form the next lexicographical number

            if (newNum > n) {
                return; // Stop early if the new number exceeds n
            }

            solve(newNum, n, result); // Recursively build the next number
        }
    }
    
    vector<int> lexicalOrder(int n) {
        vector<int> result;

        // Start DFS traversal from numbers 1 through 9
        for (int startNum = 1; startNum <= 9; startNum++) {
            solve(startNum, n, result);
        }

        return result; // Final result in lexicographical order
    }
};

/*
 *
 * Dry Run
 * Input: n = 13
 *
 * We start from 1 to 9 and recursively build:
 *
 * Start from 1:
 *  → push 1
 *  → try 10 → push 10
 *      → try 100 (stop, >13)
 *  → try 11 → push 11
 *      → try 110 (stop)
 *  → try 12 → push 12
 *      → try 120 (stop)
 *  → try 13 → push 13
 *      → try 130 (stop)
 * Start from 2:
 *  → push 2 (no deeper branch since 20 > 13)
 * Start from 3:
 *  → push 3
 * ...
 * Continue up to 9
 *
 * Result = [1,10,11,12,13,2,3,4,5,6,7,8,9]
 *
 */
