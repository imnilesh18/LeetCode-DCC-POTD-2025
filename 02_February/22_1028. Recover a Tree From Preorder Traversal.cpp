/*
 * 1028. Recover a Tree From Preorder Traversal
 *
 * We run a preorder depth-first search (DFS) on the root of a binary tree.
 * At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.
 * If a node has only one child, that child is guaranteed to be the left child.
 * Given the output traversal of this traversal, recover the tree and return its root.
 *
 * Example 1:
 * Input: traversal = "1-2--3--4-5--6--7"
 * Output: [1,2,5,3,4,6,7]
 *
 * Example 2:
 * Input: traversal = "1-2--3---4-5--6---7"
 * Output: [1,2,5,3,null,6,null,4,null,7]
 *
 * Example 3:
 * Input: traversal = "1-401--349---90--88"
 * Output: [1,401,null,349,88,90]
 *
 * Constraints:
 * The number of nodes in the original tree is in the range [1, 1000].
 * 1 <= Node.val <= 10^9
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Approach: Recursively parse the traversal string by counting dashes to determine node depth, and then extract the numeric value to build the tree in preorder.
// TC: O(n) - Every character in the traversal string is processed exactly once.
// SC: O(n) - In the worst-case (skewed tree), the recursion call stack may reach a depth of n.
class Solution {
public:
   int n;      // Total length of the traversal string

   // Recursive helper function to construct the tree.
   // s: The traversal string.
   // i: Current index in the string (passed by reference).
   // depth: Expected depth for the current node.
   TreeNode* solve(string s, int& i, int depth) {
      if (i >= n) {      // Base case: if index exceeds string length, return nullptr.
         return nullptr;
      }

      int j = i;
      // Count the consecutive '-' characters to determine the current depth.
      while (j < n && s[j] == '-') {
         j++;
      }

      int dash = j - i;       // Number of dashes encountered.

      // If the counted dashes do not match the expected depth, this node does not belong here.
      if (dash != depth) {
         return nullptr;
      }

      // Move the index past the dashes.
      i += dash;

      int num = 0;
      // Parse the number (node value) from the string.
      while (i < n && isdigit(s[i])) {
         num = (num * 10) + (s[i] - '0');
         i++;
      }

      // Create a new tree node with the parsed value.
      TreeNode* root = new TreeNode(num);

      // Recursively construct the left subtree and then the right subtree.
      root->left  = solve(s, i, depth + 1);
      root->right = solve(s, i, depth + 1);

      return root;
   }

   // Main function to recover the tree from its preorder traversal string.
   TreeNode* recoverFromPreorder(string traversal) {
      n = traversal.length();
      int i     = 0;
      int depth = 0;
      return solve(traversal, i, depth);
   }
};

/*
 * Dry Run
 * Input: traversal = "1-2--3--4-5--6--7"
 *
 * Step 1: Call recoverFromPreorder("1-2--3--4-5--6--7")
 *      n = 19, i = 0, depth = 0.
 * Step 2: In solve(s, i, 0):
 *      - Count dashes: at i=0, no '-' found (dash=0, matches depth=0).
 *      - Parse number "1" -> Create TreeNode(1).
 * Step 3: For left child of node 1, call solve(s, i, 1):
 *      - At i=1, count dashes: one '-' found (dash=1, matches depth=1).
 *      - Parse number "2" -> Create TreeNode(2).
 * Step 4: For left child of node 2, call solve(s, i, 2):
 *      - At i=3, count dashes: two '-' found (dash=2, matches depth=2).
 *      - Parse number "3" -> Create TreeNode(3).
 * Step 5: For left and right children of node 3, calls with depth=3 find no matching dashes -> return nullptr.
 * Step 6: Back to node 2, for right child, call solve(s, i, 2):
 *      - At updated i, count dashes: two '-' found (matches depth=2).
 *      - Parse number "4" -> Create TreeNode(4) with no further children.
 * Step 7: Back to node 1, for right child, call solve(s, i, 1):
 *      - At updated i, count dashes: one '-' found (matches depth=1).
 *      - Parse number "5" -> Create TreeNode(5).
 * Step 8: For left child of node 5, call solve(s, i, 2):
 *      - At updated i, count dashes: two '-' found (matches depth=2).
 *      - Parse number "6" -> Create TreeNode(6).
 * Step 9: For right child of node 5, call solve(s, i, 2):
 *      - At updated i, count dashes: two '-' found (matches depth=2).
 *      - Parse number "7" -> Create TreeNode(7).
 * Final Tree Structure: [1,2,5,3,4,6,7]
 * End Dry Run
 */
