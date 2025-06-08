/*
 * 3170. Lexicographically Minimum String After Removing Stars
 *
 * Medium
 *
 * You are given a string s. It may contain any number of '*' characters. Your task is to remove all '*' characters.
 * While there is a '*', do the following operation:
 * Delete the leftmost '*' and the smallest non-'*' character to its left. If there are several smallest characters, you can delete any of them.
 * Return the lexicographically smallest resulting string after removing all '*' characters.
 *
 * Example 1:
 * Input: s = "aaba*"
 * Output: "aab"
 * Explanation:
 * We should delete one of the 'a' characters with '*'. If we choose s[3], s becomes the lexicographically smallest.
 *
 * Example 2:
 * Input: s = "abc"
 * Output: "abc"
 * Explanation:
 * There is no '*' in the string.
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s consists only of lowercase English letters and '*'.
 * The input is generated such that it is possible to delete all '*' characters.
 */

// Approach: Use a min-heap (priority queue) to always remove the smallest character before a '*'.
// Time Complexity: O(n log n), where n is the length of the string, due to push and pop operations in the priority queue.
// Space Complexity: O(n), for storing the priority queue and result string.
class Solution {
public:

    typedef pair<char, int> P; // Pair of character and its index
    struct comp {
        // Custom comparator: smaller character comes first, and if equal, earlier index has higher priority
        bool operator()(P& p1, P& p2) {
            if (p1.first == p2.first) {
                return p1.second < p2.second;
            }
            return p1.first > p2.first;
        }
    };

    string clearStars(string s) {
        int n = s.length();

        priority_queue<P, vector<P>, comp> pq; // Min-heap to store characters with their indices

        for (int i = 0; i < n; i++) {
            if (s[i] != '*') {
                pq.push({ s[i], i });      // Push normal characters with their indices
            } else {
                int idx = pq.top().second; // Get index of the smallest char before '*'
                pq.pop();                  // Remove the smallest character
                s[idx] = '*';              // Mark that character as deleted
            }
        }

        string result = "";
        for (int i = 0; i < n; i++) {
            if (s[i] != '*') {
                result.push_back(s[i]); // Build the final string with non-'*' characters
            }
        }
        return result; // Return the lexicographically smallest result
    }
};

/*
 *
 * Dry Run
 * Input: s = "aaba*"
 *
 * Initial string: "aaba*"
 * Step 1: i = 0 -> char = 'a' → pq = [('a', 0)]
 * Step 2: i = 1 -> char = 'a' → pq = [('a', 0), ('a', 1)]
 * Step 3: i = 2 -> char = 'b' → pq = [('a', 0), ('a', 1), ('b', 2)]
 * Step 4: i = 3 -> char = 'a' → pq = [('a', 0), ('a', 1), ('b', 2), ('a', 3)]
 * Step 5: i = 4 -> char = '*'
 * → pop smallest = ('a', 0) → mark s[0] = '*'
 * → updated string: "*aba*"
 *
 * Final pass to remove '*':
 * result = "aab"
 *
 * Output: "aab"
 *
 */
