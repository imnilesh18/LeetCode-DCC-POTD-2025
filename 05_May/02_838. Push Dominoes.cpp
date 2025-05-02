/*
 * 838. Push Dominoes
 *
 * Medium
 *
 * There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
 * After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
 * When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
 * For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
 * You are given a string dominoes representing the initial state where:
 * dominoes[i] = 'L', if the ith domino has been pushed to the left,
 * dominoes[i] = 'R', if the ith domino has been pushed to the right, and
 * dominoes[i] = '.', if the ith domino has not been pushed.
 * Return a string representing the final state.
 *
 * Example 1:
 * Input: dominoes = "RR.L"
 * Output: "RR.L"
 * Explanation: The first domino expends no additional force on the second domino.
 *
 * Example 2:
 * Input: dominoes = ".L.R...LR..L.."
 * Output: "LL.RR.LLRRLL.."
 *
 * Constraints:
 * n == dominoes.length
 * 1 <= n <= 10^5
 * dominoes[i] is either 'L', 'R', or '.'.
 */

// Approach: Precompute the nearest 'L' to the right and 'R' to the left for each position. Decide the final state of each domino by comparing distances from nearest 'L' and 'R'.
// Time Complexity: O(n) – Single pass to compute nearest 'L' and 'R', and a final pass to compute result.
// Space Complexity: O(n) – Extra space used for rightClosestL and leftClosestR arrays.
class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.length();

        // Arrays to store the index of the closest 'L' to the right and closest 'R' to the left
        vector<int> rightClosestL(n);
        vector<int> leftClosestR(n);

        // Moving right to left to fill rightClosestL
        for (int i = n - 1; i >= 0; i--) {
            if (dominoes[i] == 'L') {
                rightClosestL[i] = i;                                       // current domino is 'L'
            }else if (dominoes[i] == '.')                                                                      {
                rightClosestL[i] = (i < n - 1) ? rightClosestL[i + 1] : -1; // inherit value from right
            }else                                                                                                          {
                rightClosestL[i] = -1;                                      // current is 'R', so no 'L' influence from right
            }
        }

        // Moving left to right to fill leftClosestR
        for (int i = 0; i < n; i++) {
            if (dominoes[i] == 'R') {
                leftClosestR[i] = i;                                  // current domino is 'R'
            }else if (dominoes[i] == '.')                                                                     {
                leftClosestR[i] = (i > 0) ? leftClosestR[i - 1] : -1; // inherit value from left
            }else                                                                                                     {
                leftClosestR[i] = -1;                                 // current is 'L', so no 'R' influence from left
            }
        }

        string result(n, ' ');     // placeholder for result

        // Determine final state of each domino
        for (int i = 0; i < n; i++) {
            int distRightL = (rightClosestL[i] == -1) ? INT_MAX : abs(i - rightClosestL[i]);
            int distLeftR  = (leftClosestR[i] == -1) ? INT_MAX : abs(i - leftClosestR[i]);

            if (rightClosestL[i] == leftClosestR[i]) {
                result[i] = '.';                                  // no force applied
            }else if (rightClosestL[i] == -1)                                                            {
                result[i] = 'R';                                  // only 'R' is influencing
            }else if (leftClosestR[i] == -1)                                                                   {
                result[i] = 'L';                                  // only 'L' is influencing
            }else if (distLeftR == distRightL)                                                                   {
                result[i] = '.';                                  // equal force from both sides
            }else                                                                      {
                result[i] = (distRightL < distLeftR) ? 'L' : 'R'; // whichever is closer applies force
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: ".L.R...LR..L.."
 *
 * Step 1: rightClosestL:
 * [L index closest from the right for each position]
 * [ 1, 1, -1, -1, 8, 8, 8, 8, -1, 11, 11, 11, -1, -1]
 *
 * Step 2: leftClosestR:
 * [-1, -1, 2, 2, 2, -1, -1, 7, 7, 7, -1, -1, -1, -1]
 *
 * Now process each position:
 * - i=0: No 'R', closest 'L' at 1 → dist=1 → result[0]='L'
 * - i=1: dominoes[1]='L' → result[1]='L'
 * - i=2: dominoes[2]='.' → R@2, L=not found → result[2]='R'
 * - i=3: dominoes[3]='R' → result[3]='R'
 * - i=4: no 'R' and L@8 → result[4]='.'
 * - i=5: no 'R' and L@8 → result[5]='.'
 * - i=6: no 'R' and L@8 → result[6]='L'
 * - i=7: L@8, R@7 → equidistant → result[7]='.'
 * - i=8: dominoes[8]='L' → result[8]='L'
 * - i=9: R@7 → result[9]='R'
 * - i=10: R@7 and L@11 → R is closer → result[10]='R'
 * - i=11: dominoes[11]='L' → result[11]='L'
 * - i=12: L@11, no R → result[12]='L'
 * - i=13: no R or L → result[13]='.'
 *
 * Output: "LL.RR.LLRRLL.."
 *
 */
