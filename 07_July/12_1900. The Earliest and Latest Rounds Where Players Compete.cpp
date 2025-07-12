/*
 * 1900. The Earliest and Latest Rounds Where Players Compete
 *
 * Hard
 *
 * There is a tournament where n players are participating. The players are standing in a single row and are numbered from 1 to n based on their initial standing position (player 1 is the first player in the row, player 2 is the second player in the row, etc.).
 *
 * The tournament consists of multiple rounds (starting from round number 1). In each round, the ith player from the front of the row competes against the ith player from the end of the row, and the winner advances to the next round. When the number of players is odd for the current round, the player in the middle automatically advances to the next round.
 *
 * For example, if the row consists of players 1, 2, 4, 6, 7
 * Player 1 competes against player 7.
 * Player 2 competes against player 6.
 * Player 4 automatically advances to the next round.
 * After each round is over, the winners are lined back up in the row based on the original ordering assigned to them initially (ascending order).
 *
 * The players numbered firstPlayer and secondPlayer are the best in the tournament. They can win against any other player before they compete against each other. If any two other players compete against each other, either of them might win, and thus you may choose the outcome of this round.
 *
 * Given the integers n, firstPlayer, and secondPlayer, return an integer array containing two values, the earliest possible round number and the latest possible round number in which these two players will compete against each other, respectively.
 *
 * Example 1:
 * Input: n = 11, firstPlayer = 2, secondPlayer = 4
 * Output: [3,4]
 * Explanation:
 * One possible scenario which leads to the earliest round number:
 * First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
 * Second round: 2, 3, 4, 5, 6, 11
 * Third round: 2, 3, 4
 * One possible scenario which leads to the latest round number:
 * First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
 * Second round: 1, 2, 3, 4, 5, 6
 * Third round: 1, 2, 4
 * Fourth round: 2, 4
 *
 * Example 2:
 * Input: n = 5, firstPlayer = 1, secondPlayer = 5
 * Output: [1,1]
 * Explanation: The players numbered 1 and 5 compete in the first round.
 * There is no way to make them compete in any other round.
 *
 * Constraints:
 * 2 <= n <= 28
 * 1 <= firstPlayer < secondPlayer <= n
 */

// Approach: Recursive simulation of tournament with branching on possible survivor positions.
// Time Complexity: T(n) = n^2 * T(n/2), due to nested loops and recursive calls on half size each time.
// Space Complexity: O(log n), ignoring system recursion stack as no extra space is explicitly used.
class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int left  = firstPlayer;  // Player 1
        int right = secondPlayer; // Player 2

        // If both players are facing each other directly (mirror positions), they meet in round 1
        if (left == n - right + 1) {
            return { 1, 1 };
        }

        // Normalize the players so left is always the smaller of the two (for symmetric calculation)
        if (left > n - right + 1) {
            int temp = n - left + 1;
            left  = n - right + 1;
            right = temp;
        }

        int minRound = n;                        // initialize to maximum possible rounds
        int maxRound = 1;                        // initialize to minimum possible rounds

        int nextRoundPlayersCount = (n + 1) / 2; // number of players that will survive to next round

        // Case 1: Both players are on the same side of the bracket
        if (right <= nextRoundPlayersCount) {
            int countLeft = left - 1;              // players to the left of player1
            int midCount  = right - left - 1;      // players between player1 and player2

            // Try all combinations of survivors before and between player1 and player2
            for (int survivorsLeft = 0; survivorsLeft <= countLeft; survivorsLeft++) {
                for (int survivorsMid = 0; survivorsMid <= midCount; survivorsMid++) {
                    int pos1 = survivorsLeft + 1;       // new position of player1 in next round
                    int pos2 = pos1 + survivorsMid + 1; // new position of player2 in next round

                    // Recursive call for the next round
                    vector<int> tempResult = earliestAndLatest(nextRoundPlayersCount, pos1, pos2);

                    // Update min and max rounds
                    minRound = min(minRound, tempResult[0] + 1);
                    maxRound = max(maxRound, tempResult[1] + 1);
                }
            }
        }
        // Case 2: Players are on opposite ends and can only meet eventually
        else {
            int fightsRight    = n - right + 1;           // number of players from right
            int countLeft      = left - 1;                // players before player1
            int midCount       = fightsRight - left - 1;  // middle players that can change outcome
            int remainMidCount = right - fightsRight - 1; // remaining players in between

            // Try all possible combinations of survivor placements
            for (int survivorsLeft = 0; survivorsLeft <= countLeft; survivorsLeft++) {
                for (int survivorsMid = 0; survivorsMid <= midCount; survivorsMid++) {
                    int pos1 = survivorsLeft + 1;                                  // new position of player1
                    int pos2 = pos1 + survivorsMid + (remainMidCount + 1) / 2 + 1; // position of player2

                    // Recursive call for next round
                    vector<int> tempResult = earliestAndLatest(nextRoundPlayersCount, pos1, pos2);

                    // Update min and max rounds
                    minRound = min(minRound, tempResult[0] + 1);
                    maxRound = max(maxRound, tempResult[1] + 1);
                }
            }
        }

        return { minRound, maxRound };
    }
};

/*
 *
 * Dry Run
 *
 * Input: n = 11, firstPlayer = 2, secondPlayer = 4
 * Round 1: Players are [1,2,3,4,5,6,7,8,9,10,11]
 * Matchups: (1 vs 11), (2 vs 10), (3 vs 9), (4 vs 8), (5 vs 7), (6 auto advances)
 * Survivors (one case): [2,3,4,5,6,11]
 *
 * Round 2: [2,3,4,5,6,11] → matchups: (2 vs 11), (3 vs 6), (4 vs 5)
 * Survivors (one case): [2,3,4]
 *
 * Round 3: [2,3,4] → matchups: (2 vs 4), (3 auto advances)
 * So players 2 and 4 meet in **Round 3** (earliest)
 *
 * For latest: allow both to survive as long as possible by manipulating other match results
 * One such path:
 * Round 1 → Survivors: [1,2,3,4,5,6]
 * Round 2 → Survivors: [1,2,4]
 * Round 3 → Survivors: [2,4]
 * They meet in **Round 4** (latest)
 *
 */
