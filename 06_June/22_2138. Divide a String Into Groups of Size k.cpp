/*
 * 2138. Divide a String Into Groups of Size k
 *
 * Easy
 *
 * A string s can be partitioned into groups of size k using the following procedure:
 * The first group consists of the first k characters of the string, the second group consists of the next k characters of the string, and so on. Each element can be a part of exactly one group.
 * For the last group, if the string does not have k characters remaining, a character fill is used to complete the group.
 * Note that the partition is done so that after removing the fill character from the last group (if it exists) and concatenating all the groups in order, the resultant string should be s.
 * Given the string s, the size of each group k and the character fill, return a string array denoting the composition of every group s has been divided into, using the above procedure.
 *
 * Example 1:
 * Input: s = "abcdefghi", k = 3, fill = "x"
 * Output: ["abc","def","ghi"]
 * Explanation:
 * The first 3 characters "abc" form the first group.
 * The next 3 characters "def" form the second group.
 * The last 3 characters "ghi" form the third group.
 * Since all groups can be completely filled by characters from the string, we do not need to use fill.
 * Thus, the groups formed are "abc", "def", and "ghi".
 *
 * Example 2:
 * Input: s = "abcdefghij", k = 3, fill = "x"
 * Output: ["abc","def","ghi","jxx"]
 * Explanation:
 * Similar to the previous example, we are forming the first three groups "abc", "def", and "ghi".
 * For the last group, we can only use the character 'j' from the string. To complete this group, we add 'x' twice.
 * Thus, the 4 groups formed are "abc", "def", "ghi", and "jxx".
 *
 * Constraints:
 * 1 <= s.length <= 100
 * s consists of lowercase English letters only.
 * 1 <= k <= 100
 * fill is a lowercase English letter.
 */

// Approach: Traverse the string in steps of k, slice out substrings of size k. If remaining characters are less than k, pad with fill character.
// Time Complexity: O(n) where n is the length of the string, as each character is processed exactly once.
// Space Complexity: O(n) for storing the resulting substrings in the output vector.
class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        int            n = s.length(); // Get the length of the input string
        vector<string> result;         // Result vector to store the groups

        int i = 0;

        while (i < n) {
            // Calculate the end index j for the current group (handle overflow)
            int j = ((i + k - 1) >= n) ? n - 1 : (i + k - 1);

            // Extract substring from i to j
            string temp = s.substr(i, j - i + 1);

            // If the substring is shorter than k, pad it with the fill character
            if (j - i + 1 < k) {
                int remain = k - (j - i + 1);
                temp += string(remain, fill);
            }

            // Add the formed group to result
            result.push_back(temp);

            // Move to the next group
            i += k;
        }
        return result;
    }
};

/*
 *
 * Dry Run
 * Input: s = "abcdefghij", k = 3, fill = 'x'
 * Step 1: i = 0, j = 2 -> temp = "abc" -> length is 3, no fill -> result = ["abc"]
 * Step 2: i = 3, j = 5 -> temp = "def" -> length is 3, no fill -> result = ["abc", "def"]
 * Step 3: i = 6, j = 8 -> temp = "ghi" -> length is 3, no fill -> result = ["abc", "def", "ghi"]
 * Step 4: i = 9, j = 9 -> temp = "j" -> length is 1, fill with 2 'x' -> temp = "jxx" -> result = ["abc", "def", "ghi", "jxx"]
 * Final result: ["abc", "def", "ghi", "jxx"]
 */
