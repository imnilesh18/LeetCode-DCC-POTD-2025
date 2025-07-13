/*
 * 2410. Maximum Matching of Players With Trainers
 *
 * Medium
 *
 * You are given a 0-indexed integer array players, where players[i] represents the ability of the ith player. You are also given a 0-indexed integer array trainers, where trainers[j] represents the training capacity of the jth trainer.
 * The ith player can match with the jth trainer if the player's ability is less than or equal to the trainer's training capacity. Additionally, the ith player can be matched with at most one trainer, and the jth trainer can be matched with at most one player.
 * Return the maximum number of matchings between players and trainers that satisfy these conditions.
 *
 * Example 1:
 * Input: players = [4,7,9], trainers = [8,2,5,8]
 * Output: 2
 * Explanation:
 * One of the ways we can form two matchings is as follows:
 * - players[0] can be matched with trainers[0] since 4 <= 8.
 * - players[1] can be matched with trainers[3] since 7 <= 8.
 * It can be proven that 2 is the maximum number of matchings that can be formed.
 *
 * Example 2:
 * Input: players = [1,1,1], trainers = [10]
 * Output: 1
 * Explanation:
 * The trainer can be matched with any of the 3 players.
 * Each player can only be matched with one trainer, so the maximum answer is 1.
 *
 * Constraints:
 * 1 <= players.length, trainers.length <= 10^5
 * 1 <= players[i], trainers[j] <= 10^9
 *
 * Note: This question is the same as 445: Assign Cookies.
 */

// Approach: Sort both arrays and use two pointers to greedily match the smallest possible player with the smallest suitable trainer.
// Time Complexity: O(m log m + n log n), where m = players.size() and n = trainers.size() due to sorting.
// Space Complexity: O(1), as no extra space is used apart from variables.
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        int m = players.size();
        int n = trainers.size();

        // Sort both arrays so we can match greedily from smallest to largest
        sort(begin(players), end(players));
        sort(begin(trainers), end(trainers));

        int count = 0; // To count number of successful matchings
        int i     = 0; // Pointer for players
        int j     = 0; // Pointer for trainers

        // Iterate through both arrays
        while (i < m && j < n) {
            // If current player can be matched with current trainer
            if (players[i] <= trainers[j]) {
                count++; // We have a match
                i++;     // Move to next player
            }
            j++;         // Move to next trainer regardless of match
        }

        return count; // Return total number of matches
    }
};

/*
 *
 * Dry Run
 *
 * Input:
 * players = [4, 7, 9]
 * trainers = [8, 2, 5, 8]
 *
 * After sorting:
 * players = [4, 7, 9]
 * trainers = [2, 5, 8, 8]
 *
 * Step 1: players[0]=4 <= trainers[0]=2 → No match → move j to 1
 * Step 2: players[0]=4 <= trainers[1]=5 → Match → count=1 → i=1, j=2
 * Step 3: players[1]=7 <= trainers[2]=8 → Match → count=2 → i=2, j=3
 * Step 4: players[2]=9 <= trainers[3]=8 → No match → j=4
 * Loop ends (j == 4)
 * Result: 2 matches
 *
 */
