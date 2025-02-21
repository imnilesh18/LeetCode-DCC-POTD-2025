/*
 * 1261. Find Elements in a Contaminated Binary Tree
 *
 * Given a binary tree with the following rules:
 *
 * root.val == 0
 * For any treeNode:
 * If treeNode.val has a value x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
 * If treeNode.val has a value x and treeNode.right != null, then treeNode.right.val == 2 * x + 2
 * Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.
 *
 * Implement the FindElements class:
 *
 * FindElements(TreeNode* root) Initializes the object with a contaminated binary tree and recovers it.
 * bool find(int target) Returns true if the target value exists in the recovered binary tree.
 *
 *
 * Example 1:
 * Input
 * ["FindElements","find","find"]
 * [[[-1,null,-1]],[1],[2]]
 * Output
 * [null,false,true]
 * Explanation
 * FindElements findElements = new FindElements([-1,null,-1]);
 * findElements.find(1); // return False
 * findElements.find(2); // return True
 *
 * Example 2:
 * Input
 * ["FindElements","find","find","find"]
 * [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
 * Output
 * [null,true,true,false]
 * Explanation
 * FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
 * findElements.find(1); // return True
 * findElements.find(3); // return True
 * findElements.find(5); // return False
 *
 * Example 3:
 * Input
 * ["FindElements","find","find","find","find"]
 * [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
 * Output
 * [null,true,false,false,true]
 * Explanation
 * FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
 * findElements.find(2); // return True
 * findElements.find(3); // return False
 * findElements.find(4); // return False
 * findElements.find(5); // return True
 *
 * Constraints:
 * TreeNode.val == -1
 * The height of the binary tree is less than or equal to 20
 * The total number of nodes is between [1, 10^4]
 * Total calls of find() is between [1, 10^4]
 * 0 <= target <= 10^6
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

// Approach 1 (DFS): Use DFS to recover tree values and store them in an unordered_set for O(1) lookup during find queries.
// TC: O(n) for DFS traversal during recovery and O(1) per find() call, where n is the number of nodes.
// SC: O(n) for the unordered_set and the recursion stack in the worst-case scenario.
class FindElements {
public:
   unordered_set<int> st;      // Hash set to store recovered node values

   // DFS helper function to recover the tree.
   void dfs(TreeNode* root, int x) {
      if (!root) {       // If the node is null, return.
         return;
      }
      root->val = x;               // Recover the current node's value.
      st.insert(x);                // Insert the recovered value into the set.
      dfs(root->left, 2 * x + 1);  // Recover the left child using the given formula.
      dfs(root->right, 2 * x + 2); // Recover the right child using the given formula.
   }

   // Constructor: Recovers the tree starting from the contaminated root.
   FindElements(TreeNode* root) {
      st.clear();               // Clear the set to ensure it's empty.
      dfs(root, 0);             // Start DFS recovery from the root with value 0.
   }

   // find method: Checks if the target value exists in the recovered tree.
   bool find(int target) {
      return st.count(target);       // Return true if target is in the set, else false.
   }
};

/*
 * Dry Run
 * Given tree: [-1, null, -1]
 *
 * Step 1: Constructor is called with the root (-1).
 *  - Call dfs(root, 0)
 * Node is not null: Set root->val = 0 and insert 0 into the set.
 * Call dfs(root->left, 2*0+1 = 1):
 *          - root->left is null -> return.
 * Call dfs(root->right, 2*0+2 = 2):
 *          - Node is not null: Set root->right->val = 2 and insert 2 into the set.
 *          - Call dfs(root->right->left, 2*2+1 = 5):
 *              - Node is null -> return.
 *          - Call dfs(root->right->right, 2*2+2 = 6):
 *              - Node is null -> return.
 * After DFS: Set contains {0, 2}.
 *
 * Step 2: find(1) is called.
 *  - 1 is not in the set -> returns false.
 * Step 3: find(2) is called.
 *  - 2 is in the set -> returns true.
 */

// Approach 2 (BFS): Use BFS to recover tree values and store them in an unordered_set for O(1) lookup during find queries.
// TC: O(n) for BFS traversal during recovery and O(1) per find() call, where n is the number of nodes.
// SC: O(n) for the unordered_set and the queue used for BFS traversal.
class FindElements {
public:
   unordered_set<int> st;      // Hash set to store recovered node values

   // BFS helper function to recover the tree.
   void bfs(TreeNode* root, int x) {
      queue<TreeNode*> que;                      // Queue for BFS traversal.

      root->val = x;                             // Recover the root node's value.
      que.push(root);                            // Push the root into the queue.

      while (!que.empty()) {                     // Process nodes until the queue is empty.
         TreeNode* temp = que.front();           // Get the front node from the queue.
         que.pop();                              // Remove the node from the queue.

         st.insert(temp->val);                   // Insert the recovered value into the set.

         if (temp->left) {                       // If the left child exists:
            temp->left->val = 2 * temp->val + 1; // Recover left child's value.
            que.push(temp->left);                // Add the left child to the queue.
         }

         if (temp->right) {                       // If the right child exists:
            temp->right->val = 2 * temp->val + 2; // Recover right child's value.
            que.push(temp->right);                // Add the right child to the queue.
         }
      }
   }

   // Constructor: Recovers the tree starting from the contaminated root.
   FindElements(TreeNode* root) {
      st.clear();            // Clear the set to ensure it's empty.
      bfs(root, 0);          // Start BFS recovery from the root with value 0.
   }

   // find method: Checks if the target value exists in the recovered tree.
   bool find(int target) {
      return st.count(target);       // Return true if target is in the set, else false.
   }
};

/*
 * Dry Run
 * Given tree: [-1, -1, -1]
 *
 * Step 1: Constructor is called with the root (-1).
 *  - Call bfs(root, 0)
 * Set root->val = 0 and push root into the queue.
 * While loop begins:
 *          - Pop root from the queue, insert 0 into the set.
 *          - For root's left child:
 *              > Set left->val = 2*0+1 = 1, push left child into the queue.
 *          - For root's right child:
 *              > Set right->val = 2*0+2 = 2, push right child into the queue.
 * Next iteration:
 *          - Pop left child from the queue, insert 1 into the set.
 *          - Left child has no children, so nothing more is added.
 * Next iteration:
 *          - Pop right child from the queue, insert 2 into the set.
 *          - Right child has no children, so nothing more is added.
 * After BFS: Set contains {0, 1, 2}.
 *
 * Step 2: find(1) is called.
 *  - 1 is in the set -> returns true.
 * Step 3: find(3) is called.
 *  - 3 is not in the set -> returns false.
 */
