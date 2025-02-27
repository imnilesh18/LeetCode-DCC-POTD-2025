/*
 * 873. Length of Longest Fibonacci Subsequence
 *
 * A sequence x1, x2, ..., xn is Fibonacci-like if:
 * n >= 3
 * xi + xi+1 == xi+2 for all i + 2 <= n
 * Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.
 * A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].
 *
 * Example 1:
 * Input: arr = [1,2,3,4,5,6,7,8]
 * Output: 5
 * Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
 *
 * Example 2:
 * Input: arr = [1,3,7,11,12,14,18]
 * Output: 3
 * Explanation: The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].
 *
 * Constraints:
 * 3 <= arr.length <= 1000
 * 1 <= arr[i] < arr[i + 1] <= 10^9
 */

// Approach 1 (Recursion): For every pair (j, k) in arr, recursively extend the Fibonacci-like sequence by finding the previous element (arr[k] - arr[j]) using a hash map; update the maximum sequence length.
// TC: O(n² * L) where L is the length of the longest Fibonacci-like sequence (due to recursion on each pair).
// SC: O(n) for the hash map and recursion stack.
class Solution {
public:
   // Recursive helper function that returns the length of the Fibonacci-like sequence ending with arr[j] and arr[k]
   int solve(int j, int k, vector<int>& arr, unordered_map<int, int>& mp) {
      int target = arr[k] - arr[j];       // Compute the expected previous element in the sequence

      // If the target exists in the array and its index is before j, continue the sequence
      if (mp.count(target) && mp[target] < j) {
         int i = mp[target];              // Retrieve the index of the target element
         return solve(i, j, arr, mp) + 1; // Recursively extend the sequence and add 1 for the current element
      }
      // Base case: if no valid previous element, the current sequence length is 2 (elements arr[j] and arr[k])
      return 2;
   }

   int lenLongestFibSubseq(vector<int>& arr) {
      int n = arr.size();
      unordered_map<int, int> mp;

      // Build a hash map to store each element's value and its index for O(1) lookup
      for (int i = 0; i < n; i++) {
         mp[arr[i]] = i;
      }

      int max_length = 0;
      // Consider every pair (j, k) as potential last two elements of a Fibonacci-like sequence
      for (int j = 1; j < n; j++) {
         for (int k = j + 1; k < n; k++) {
            int length = solve(j, k, arr, mp); // Get the length of the sequence ending with arr[j] and arr[k]
            if (length >= 3) {                 // Only consider valid sequences of length at least 3
               max_length = max(max_length, length);
            }
         }
      }

      return max_length;       // Return the length of the longest Fibonacci-like subsequence found (or 0 if none)
   }
};

/*
 * DRY RUN:
 * Input: arr = [1, 2, 3, 5, 8]
 * Mapping: {1:0, 2:1, 3:2, 5:3, 8:4}
 *
 * Pair (1, 2):*
 * - solve(j=0, k=1) -> target = 2 - 1 = 1.
 * - 1 is at index 0, but index 0 is not less than 0; returns 2.
 *
 * Pair (2, 3):*
 * - solve(j=1, k=2) -> target = 3 - 2 = 1.
 * - 1 is found at index 0 (which is < 1); call solve(j=0, k=1) returns 2.
 * - So, length = 2 + 1 = 3.
 *
 * Pair (3, 5):*
 * - solve(j=2, k=3) -> target = 5 - 3 = 2.
 * - 2 is found at index 1 (which is < 2); call solve(j=1, k=2) returns 3.
 * - So, length = 3 + 1 = 4.
 *
 * Pair (5, 8):*
 * - solve(j=3, k=4) -> target = 8 - 5 = 3.
 * - 3 is found at index 2 (which is < 3); call solve(j=2, k=3) returns 4.
 * - So, length = 4 + 1 = 5.
 *
 * Maximum length found = 5.
 */

// Approach 2 (Recursion + Memoization): Use recursion with memoization to extend Fibonacci-like sequences by finding the expected previous element using a hash map and storing intermediate results in a 2D table.
// TC: O(n² * L) where L is the maximum sequence length, as each pair (j, k) is computed once.
// SC: O(n²) for the memoization table plus O(n) for the recursion stack and hashmap.
class Solution {
public:
   // Recursive helper function that returns the length of the Fibonacci-like sequence ending with arr[j] and arr[k]
   int solve(int j, int k, vector<int>& arr, unordered_map<int, int>& mp, vector<vector<int> >& t) {
      if (t[j][k] != -1) {      // Return memoized result if already computed
         return t[j][k];
      }
      int target = arr[k] - arr[j];       // Compute the expected previous element in the sequence
      // If the target exists and its index is less than j, extend the sequence recursively
      if (mp.count(target) && mp[target] < j) {
         int i = mp[target];
         return t[j][k] = solve(i, j, arr, mp, t) + 1;        // Memoize and return the extended sequence length
      }
      // Base case: no valid previous element found, so sequence length is 2 (only arr[j] and arr[k])
      return t[j][k] = 2;
   }

   int lenLongestFibSubseq(vector<int>& arr) {
      int n = arr.size();
      unordered_map<int, int> mp;
      // Initialize a 2D memoization table with -1 for each pair (j, k)
      vector<vector<int> > t(n, vector<int>(n, -1));

      // Build a hash map for quick lookup of each element's index
      for (int i = 0; i < n; i++) {
         mp[arr[i]] = i;
      }

      int max_length = 0;
      // Iterate over all possible pairs (j, k) as potential ending elements of a Fibonacci-like sequence
      for (int j = 1; j < n; j++) {
         for (int k = j + 1; k < n; k++) {
            int length = solve(j, k, arr, mp, t); // Get the sequence length for the pair (j, k)
            if (length >= 3) {                    // Valid sequence must have at least 3 elements
               max_length = max(max_length, length);
            }
         }
      }
      return max_length;
   }
};

/*
 * DRY RUN:
 * Input: arr = [1, 2, 3, 5, 8]
 * Mapping: {1:0, 2:1, 3:2, 5:3, 8:4}
 * Memoization table initialized with -1.
 *
 * Pair (1, 2):
 * solve(j=0, k=1) -> target = 2 - 1 = 1.
 * 1 exists at index 0, but index 0 is not less than 0; returns 2; t[0][1]=2.
 *
 * Pair (2, 3):
 * solve(j=1, k=2) -> target = 3 - 2 = 1.
 * 1 found at index 0 (<1); calls solve(j=0, k=1) which returns 2.
 * So, length = 2 + 1 = 3; t[1][2]=3.
 *
 * Pair (3, 5):
 * solve(j=2, k=3) -> target = 5 - 3 = 2.
 * 2 found at index 1 (<2); calls solve(j=1, k=2) which returns 3.
 * So, length = 3 + 1 = 4; t[2][3]=4.
 *
 * Pair (5, 8):
 * solve(j=3, k=4) -> target = 8 - 5 = 3.
 * 3 found at index 2 (<3); calls solve(j=2, k=3) which returns 4.
 * So, length = 4 + 1 = 5; t[3][4]=5.
 *
 * Maximum length found = 5.
 */

// Approach 3 (Bottom Up Approach): Use bottom-up dynamic programming by iterating over all pairs (j, k) and updating the DP table based on previously computed results to build Fibonacci-like sequences.
// TC: O(n²) because we iterate over all pairs (j, k) with constant time operations per pair.
// SC: O(n²) for the DP table and O(n) for the hashmap used for quick lookups.
class Solution {
public:
   int lenLongestFibSubseq(vector<int>& arr) {
      int n = arr.size();

      // Build a hashmap to store each element's value and its index for O(1) lookups.
      unordered_map<int, int> mp;

      for (int i = 0; i < n; i++) {
         mp[arr[i]] = i;
      }

      // Initialize the DP table with base value 2 for every pair (j, k),
      // since any two numbers form a sequence of length 2.
      vector<vector<int> > t(n, vector<int>(n, 2));

      int max_length = 0;
      // Iterate over all possible pairs (j, k) as potential last two elements of a Fibonacci-like sequence.
      for (int j = 1; j < n; j++) {
         for (int k = j + 1; k < n; k++) {
            // Calculate the expected previous element in the sequence.
            int target = arr[k] - arr[j];
            // If the target exists and its index is less than j, update the DP table.
            if (mp.count(target) && mp[target] < j) {
               int i = mp[target];
               t[j][k] = t[i][j] + 1;
            }
            // Update the maximum length found so far.
            max_length = max(max_length, t[j][k]);
         }
      }

      // Return the maximum sequence length if it's at least 3; otherwise, return 0.
      return max_length >= 3 ? max_length : 0;
   }
};

/*
 * DRY RUN:
 * Input: arr = [1, 2, 3, 5, 8]
 * Mapping: {1:0, 2:1, 3:2, 5:3, 8:4}
 * DP table initial state: All t[i][j] = 2
 *
 * Pair (1, 2) => j=0, k=1:
 *  target = 2 - 1 = 1; no valid index (<0), so t[0][1] remains 2.
 * Pair (2, 3) => j=1, k=2:
 *  target = 3 - 2 = 1; found at index 0 (<1), so t[1][2] = t[0][1] + 1 = 3.
 * Pair (3, 5) => j=2, k=3:
 *  target = 5 - 3 = 2; found at index 1 (<2), so t[2][3] = t[1][2] + 1 = 4.
 * Pair (5, 8) => j=3, k=4:
 *  target = 8 - 5 = 3; found at index 2 (<3), so t[3][4] = t[2][3] + 1 = 5.
 * Maximum length found = 5.
 */
