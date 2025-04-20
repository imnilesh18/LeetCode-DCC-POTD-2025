/*
 * 781. Rabbits in Forest
 *
 * Medium
 *
 * There is a forest with an unknown number of rabbits. We asked n rabbits "How many rabbits have the same color as you?" and collected the answers in an integer array answers where answers[i] is the answer of the ith rabbit.
 * Given the array answers, return the minimum number of rabbits that could be in the forest.
 *
 * Example 1:
 * Input: answers = [1,1,2]
 * Output: 5
 * Explanation:
 * The two rabbits that answered "1" could both be the same color, say red.
 * The rabbit that answered "2" can't be red or the answers would be inconsistent.
 * Say the rabbit that answered "2" was blue.
 * Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
 * The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.
 *
 * Example 2:
 * Input: answers = [10,10,10]
 * Output: 11
 *
 * Constraints:
 * 1 <= answers.length <= 1000
 * 0 <= answers[i] < 1000
 */

// Approach: Use a hashmap to count how many times each answer appears. For each unique answer `x`, we calculate how many groups of size (x+1) are needed to accommodate the rabbits that answered `x`.
// Time Complexity: O(n) where n is the number of elements in the input array, because we iterate through the array and the map.
// Space Complexity: O(n) in the worst case if all answers are unique and stored in the map.
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> mp;       // map to count occurrences of each answer

        for (int& x : answers) {
            mp[x]++;        // count how many rabbits gave the same answer
        }

        int total = 0;

        for (auto& it : mp) {
            int x     = it.first;                            // answer of the rabbit
            int count = it.second;                           // how many rabbits gave this answer

            int groupSize = (x + 1);                         // each rabbit with answer x is in a group of (x+1) rabbits
            int groups    = ceil((double)count / groupSize); // number of full groups needed

            total += groups * (groupSize);                   // total rabbits = number of groups * size of each group
        }
        return total;                                        // return the minimum number of rabbits that could be in the forest
    }
};

/*
 *
 * Dry Run
 * Input: answers = [1,1,2]
 *
 * Step 1: Count frequencies
 * mp = {1: 2, 2: 1}
 *
 * Processing key = 1:
 *  count = 2, groupSize = 2 (since 1+1), groups = ceil(2/2) = 1
 *  total += 1 * 2 = 2
 *
 * Processing key = 2:
 *  count = 1, groupSize = 3 (since 2+1), groups = ceil(1/3) = 1
 *  total += 1 * 3 = 3
 *
 * Final total = 2 + 3 = 5
 * Output: 5
 *
 */
