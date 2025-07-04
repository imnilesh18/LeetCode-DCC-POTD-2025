/*
 * 3307. Find the K-th Character in String Game II
 *
 * Hard
 *
 * Alice and Bob are playing a game. Initially, Alice has a string word = "a".
 * You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.
 * Now Bob will ask Alice to perform all operations in sequence:
 * If operations[i] == 0, append a copy of word to itself.
 * If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
 * Return the value of the kth character in word after performing all the operations.
 *
 * Note that the character 'z' can be changed to 'a' in the second type of operation.
 *
 * Example 1:
 * Input: k = 5, operations = [0,0,0]
 * Output: "a"
 * Explanation:
 * Initially, word == "a". Alice performs the three operations as follows:
 * Appends "a" to "a", word becomes "aa".
 * Appends "aa" to "aa", word becomes "aaaa".
 * Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
 *
 * Example 2:
 * Input: k = 10, operations = [0,1,0,1]
 * Output: "b"
 * Explanation:
 * Initially, word == "a". Alice performs the four operations as follows:
 * Appends "a" to "a", word becomes "aa".
 * Appends "bb" to "aa", word becomes "aabb".
 * Appends "aabb" to "aabb", word becomes "aabbaabb".
 * Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".
 *
 * Constraints:
 * 1 <= k <= 1014
 * 1 <= operations.length <= 100
 * operations[i] is either 0 or 1.
 * The input is generated such that word has at least k characters after all operations.
 */

// Approach: Use recursion to track back where the k-th character came from without generating the full string.
// Time Complexity: O(log(k)) – At each recursive level, the string length doubles, so we go log(k) deep.
// Space Complexity: O(log(k)) – Due to recursive call stack.
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        // Base case: If k is 1, the result is the initial character 'a'
        if (k == 1) {
            return 'a';
        }

        int       n = operations.size(); // Get number of operations
        int       opType;                // To store the operation type where k-th character lies
        long long len = 1;               // Initial length of string "a" is 1
        long long newK;                  // Will store the position of k in previous step

        // Iterate through each operation to find when the length exceeds or matches k
        for (int i = 0; i < n; i++) {
            len *= 2;                    // Each operation doubles the string size
            if (len >= k) {              // Found the operation responsible for k-th character
                opType = operations[i];  // Store that operation type
                newK   = k - len / 2;    // Find the position in the previous version of string
                break;                   // Break since we only care about the first point when len >= k
            }
        }

        // Recursively get the character from the previous string version
        char res = kthCharacter(newK, operations);

        // If the operation was type 0 (copy same), return the character as is
        if (opType == 0) {
            return res;
        }

        // If operation was type 1 (shift characters), apply shift
        if (res == 'z') {
            return 'a';  // Wrap around 'z' to 'a'
        }
        return res + 1;  // Otherwise, return next character in alphabet
    }
};

/*
 *
 * Dry Run
 *
 * Input: k = 10, operations = [0, 1, 0, 1]
 *
 * Step-by-step:
 *
 * Initial word: "a" (length = 1)
 *
 * Operation 1 (0): "a" → "aa"              (length = 2)
 * Operation 2 (1): "aa" → "aabb"           (length = 4)
 * Operation 3 (0): "aabb" → "aabbaabb"     (length = 8)
 * Operation 4 (1): "aabbaabb" → "aabbaabbbbccbbcc" (length = 16)
 *
 * Now, we are looking for k = 10
 * After operations[3], len = 16 which >= 10, so we recurse to find character at (10 - 8 = 2)
 *
 * Now, k = 2, we move back to operations[2] (type 0)
 * After operations[2], len = 8 >= 2 → recurse to k = 2 - 4 = -2 (but k always >= 1 so base case not yet)
 * Eventually recurse to base case k = 1 → return 'a'
 *
 * Apply operations as we unwind:
 *  - opType 0 → res = 'a'
 *  - opType 1 → res = 'b' (shift 'a' to 'b')
 *
 * Final answer = 'b'
 *
 */
