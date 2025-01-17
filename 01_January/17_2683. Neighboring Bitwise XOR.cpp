/*
 * 2683. Neighboring Bitwise XOR
 *
 * A 0-indexed array derived with length n is derived by computing the bitwise XOR (⊕) of adjacent values in a binary array original of length n.
 * Specifically, for each index i in the range [0, n - 1]:
 * If i = n - 1, then derived[i] = original[i] ⊕ original[0].
 * Otherwise, derived[i] = original[i] ⊕ original[i + 1].
 * Given an array derived, your task is to determine whether there exists a valid binary array original that could have formed derived.
 * Return true if such an array exists or false otherwise.
 * A binary array is an array containing only 0's and 1's
 *
 * Example 1:
 * Input: derived = [1,1,0]
 * Output: true
 * Explanation: A valid original array that gives derived is [0,1,0].
 * derived[0] = original[0] ⊕ original[1] = 0 ⊕ 1 = 1
 * derived[1] = original[1] ⊕ original[2] = 1 ⊕ 0 = 1
 * derived[2] = original[2] ⊕ original[0] = 0 ⊕ 0 = 0
 *
 * Example 2:
 * Input: derived = [1,1]
 * Output: true
 * Explanation: A valid original array that gives derived is [0,1].
 * derived[0] = original[0] ⊕ original[1] = 1
 * derived[1] = original[1] ⊕ original[0] = 1
 *
 * Example 3:
 * Input: derived = [1,0]
 * Output: false
 * Explanation: There is no valid original array that gives derived.
 *
 * Constraints:
 * n == derived.length
 * 1 <= n <= 10^5
 * The values in derived are either 0's or 1's
 */

// Approach 1: Try constructing original array twice (with first element as 0 and 1) and verify if it satisfies the circular XOR condition.
// TC: O(n) where n is the length of derived array as we traverse it twice.
// SC: O(n) to store the original array.
class Solution {
public:
   bool doesValidArrayExist(vector<int>& derived){
      int n = derived.size();

      // Try with original[0] = 0
      vector<int> original(n);

      original[0] = 0;    // First attempt: set first element to 0

      // Generate the rest of original array using XOR with derived values
      for (int i = 0; i < n - 1; i++) {
         // For each i, original[i+1] = original[i] ⊕ derived[i]
         original[i + 1] = original[i] ^ derived[i];
      }

      // Check if the circular condition is satisfied
      // derived[n-1] should equal original[n-1] ⊕ original[0]
      if (original[n - 1] ^ original[0] == derived[n - 1]) {
         return true;
      }

      // If first attempt failed, try with original[0] = 1
      original[0] = 1;    // Second attempt: set first element to 1

      // Generate the rest of original array again
      for (int i = 0; i < n - 1; i++) {
         original[i + 1] = original[i] ^ derived[i];
      }

      // Check circular condition again
      if (original[n - 1] ^ original[0] == derived[n - 1]) {
         return true;
      }

      // If both attempts fail, no valid original array exists
      return false;
   }
};

// Approach 2: XOR all elements in derived array - must be 0 for valid original array to exist since each original element appears twice in derived calculations.
// TC: O(n) where n is the length of derived array as we traverse it once.
// SC: O(1) as we only use a single variable regardless of input size.
class Solution {
public:
   bool doesValidArrayExist(vector<int>& derived){
      // Initialize XOR accumulator
      int XOR = 0;

      // Take XOR of all elements in derived array
      // If original array exists, XOR of all derived elements must be 0
      // Because each original[i] appears twice in derived array's calculations
      // (once with original[i-1] and once with original[i+1])
      for (int&x : derived) {
         XOR = (XOR ^ x);
      }

      // If XOR is 0, a valid original array exists
      // If XOR is 1, no valid original array can exist
      return XOR == 0;
   }
};
