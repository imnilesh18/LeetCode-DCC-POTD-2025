/*
 * 3174. Clear Digits
 *
 * You are given a string s.
 * Your task is to remove all digits by doing this operation repeatedly:
 * Delete the first digit and the closest non-digit character to its left.
 * Return the resulting string after removing all digits.
 *
 * Example 1:
 * Input: s = "abc"
 * Output: "abc"
 * Explanation:
 * There is no digit in the string.
 *
 * Example 2:
 * Input: s = "cb34"
 * Output: ""
 *
 * Explanation:
 * First, we apply the operation on s[2], and s becomes "c4".
 * Then we apply the operation on s[1], and s becomes "".
 *
 * Constraints:
 * 1 <= s.length <= 100
 * s consists only of lowercase English letters and digits.
 * The input is generated such that it is possible to delete all digits.
 */

// Approach 1: Iterate over the string and whenever a digit is found, remove it along with its closest preceding non-digit character.
// TC: O(n^2) - Each erase operation can take O(n) time and in the worst-case scenario, it might be called O(n) times.
// SC: O(1) - The algorithm modifies the string in place using constant extra space.
class Solution {
public:
   string clearDigits(string s) {
      int i = 0;

      // Traverse the string until we reach its end.
      while (i < s.length()) {
         // If the current character is a digit...
         if (isdigit(s[i])) {
            // ...remove the digit at index i.
            s.erase(i, 1);
            // If there is a character to the left, remove it as well.
            if (i - 1 >= 0) {
               s.erase(i - 1, 1);
               // Adjust the index to account for the removed character.
               i--;
            }
         } else {
            // If it's not a digit, simply move to the next character.
            i++;
         }
      }
      return s;
   }
};

/*
 * Dry Run
 * Input: "cb34"
 *
 * Step-by-Step:
 * 1. Initial string: "cb34", i = 0
 * 2. i = 0: Character 'c' is not a digit → increment i to 1.
 * 3. i = 1: Character 'b' is not a digit → increment i to 2.
 * 4. i = 2: Character '3' is a digit → remove '3' and its preceding character 'b':
 * - String becomes "c4"
 * - Adjust i to 1.
 * 5. i = 1: Character '4' is a digit → remove '4' and its preceding character 'c':
 * - String becomes ""
 * - Adjust i to 0.
 * 6. i = 0: End of string reached → exit loop.
 *
 * Output: ""
 * End Dry Run
 */

// Approach 2: Use a stack to store non-digit characters and remove the top element whenever a digit is encountered, then reverse the collected characters to form the final string.
// TC: O(n) - Each character is processed once and stack operations are O(1) on average.
// SC: O(n) - In the worst-case scenario, all characters are non-digits and stored in the stack.
class Solution {
public:
   string clearDigits(string s) {
      // Create a stack to store non-digit characters.
      stack<char> st;

      // Iterate over each character in the string.
      for (char&ch : s) {
         // If the current character is a digit...
         if (isdigit(ch)) {
            // ...pop the top non-digit character from the stack if available.
            if (!st.empty()) {
               st.pop();
            }
         } else {
            // If it's not a digit, push it onto the stack.
            st.push(ch);
         }
      }

      // Build the result string by collecting characters from the stack.
      string result = "";
      while (!st.empty()) {
         result.push_back(st.top());
         st.pop();
      }

      // Reverse the result to obtain the correct order.
      reverse(begin(result), end(result));

      return result;
   }
};

/*
 * Dry Run
 * Input: "a1bc2"
 *
 * Step-by-Step:
 * 1. Process 'a':
 * - 'a' is not a digit, push to stack.
 * - Stack: ['a']
 *
 * 2. Process '1':
 * - '1' is a digit, pop top of stack ('a').
 * - Stack: []
 *
 * 3. Process 'b':
 * - 'b' is not a digit, push to stack.
 * - Stack: ['b']
 *
 * 4. Process 'c':
 * - 'c' is not a digit, push to stack.
 * - Stack: ['b', 'c']
 *
 * 5. Process '2':
 * - '2' is a digit, pop top of stack ('c').
 * - Stack: ['b']
 *
 * Building the Result:
 * - Pop remaining elements from the stack to form the result string: "b"
 * - Reverse "b" (remains "b").
 *
 * Output: "b"
 ******** End Dry Run ********
 */

// Approach 3: Use the string as a stack to simulate the deletion process; for each digit encountered, remove the last letter.
// TC: O(n) - We process each character once, and push/pop operations are O(1).
// SC: O(n) - In the worst case, all characters are letters and stored in the result.
class Solution {
public:
   string clearDigits(string s) {
      // Use 'result' as a stack to simulate the deletion process.
      string result = "";

      // Iterate over each character in the input string.
      for (char&ch : s) {
         // If the character is a digit, remove the last non-digit character (if available).
         if (isdigit(ch)) {
            if (!result.empty()) {
               result.pop_back();
            }
         } else {
            // Otherwise, push the non-digit character onto the stack.
            result.push_back(ch);
         }
      }
      // Return the final string after processing.
      return result;
   }
};

/*
 * Dry Run
 * Input: "a1bc2"
 *
 * Step-by-Step:
 * 1. Process 'a': Not a digit → result = "a"
 * 2. Process '1': Digit → pop last character; result becomes ""
 * 3. Process 'b': Not a digit → result = "b"
 * 4. Process 'c': Not a digit → result = "bc"
 * 5. Process '2': Digit → pop last character; result becomes "b"
 *
 * Final Output: "b"
 ******** End Dry Run ********
 */

// Approach 4: Use two pointers where 'j' simulates the top of a stack; for each digit, decrement j to remove the last letter, otherwise copy the letter.
// TC: O(n) - Each character is processed exactly once.
// SC: O(1) - The result is built in-place with constant extra space.
class Solution {
public:
   string clearDigits(string s) {
      int n = s.length();       // n holds the length of the input string.
      int i = 0;                // 'i' is the fast pointer for iterating through the string.
      int j = 0;                // 'j' acts like the top index of a stack built within the string.

      // Process each character in the string.
      while (i < n) {
         if (isdigit(s[i])) {
            // If the current character is a digit, simulate a 'pop' by decrementing j,
            // ensuring j doesn't go below 0.
            j = max(j - 1, 0);
         } else {
            // If it's not a digit, place the character at the 'stack top' position and increment j.
            s[j] = s[i];
            j++;
         }
         // Move to the next character.
         i++;
      }

      // Return the substring from the beginning up to index j which represents the final result.
      return s.substr(0, j);
   }
};

/*
 * Dry Run
 * Input: "a1bc2"
 *
 * Step-by-Step:
 * 1. i = 0, j = 0: Process 'a' (non-digit) → s[0] = 'a', increment j to 1.
 * Current string: "a1bc2", j = 1.
 * 2. i = 1, j = 1: Process '1' (digit) → decrement j: j = max(1-1, 0) = 0.
 * Current string remains: "a1bc2", j = 0.
 * 3. i = 2, j = 0: Process 'b' (non-digit) → s[0] = 'b', increment j to 1.
 * Current string becomes: "b1bc2", j = 1.
 * 4. i = 3, j = 1: Process 'c' (non-digit) → s[1] = 'c', increment j to 2.
 * Current string becomes: "bcbc2", j = 2.
 * 5. i = 4, j = 2: Process '2' (digit) → decrement j: j = max(2-1, 0) = 1.
 * Current string remains: "bcbc2", j = 1.
 *
 * Final Result:
 * Return s.substr(0, j) which is s.substr(0, 1) = "b"
 ******** End Dry Run ********
 */
