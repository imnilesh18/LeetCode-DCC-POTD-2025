/*
 * 1948. Delete Duplicate Folders in System
 *
 * Hard
 *
 * Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.
 * For example, ["one", "two", "three"] represents the path "/one/two/three".
 * Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.
 *
 * For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
 * /a
 * /a/x
 * /a/x/y
 * /a/z
 * /b
 * /b/x
 * /b/x/y
 * /b/z
 * However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
 * Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
 *
 * Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.
 *
 * Example 1:
 * Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
 * Output: [["d"],["d","a"]]
 * Explanation: The file structure is as shown.
 * Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
 * folder named "b".
 *
 * Example 2:
 * Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
 * Output: [["c"],["c","b"],["a"],["a","b"]]
 * Explanation: The file structure is as shown.
 * Folders "/a/b/x" and "/w" (and their subfolders) are marked for deletion because they both contain an empty folder named "y".
 * Note that folders "/a" and "/c" are identical after the deletion, but they are not deleted because they were not marked beforehand.
 *
 * Example 3:
 * Input: paths = [["a","b"],["c","d"],["c"],["a"]]
 * Output: [["c"],["c","d"],["a"],["a","b"]]
 * Explanation: All folders are unique in the file system.
 * Note that the returned array can be in a different order as the order does not matter.
 *
 * Constraints:
 * 1 <= paths.length <= 2 * 10^4
 * 1 <= paths[i].length <= 500
 * 1 <= paths[i][j].length <= 10
 * 1 <= sum(paths[i][j].length) <= 2 * 10^5
 * path[i][j] consists of lowercase English letters.
 * No two paths lead to the same folder.
 * For any folder not at the root level, its parent folder will also be in the input.
 */

// Approach: Build a Trie to represent the file system. Use a post-order DFS to serialize each folder's sub-structure into a unique string. Count these serialized strings in a hash map. Use a pre-order DFS to traverse the trie again and delete any folder whose serialized sub-structure appears more than once. Finally, perform another pre-order DFS on the modified trie to collect the paths of the remaining folders.
// Time Complexity: O(N * L * C * log(C)), where N is the total number of paths, L is the average path length, and C is the average number of children per node. The bottleneck is sorting children's paths during serialization.
// Space Complexity: O(N * L), for storing the Trie and the serialized path strings in the hash map.
class Solution {
public:
    // Define the structure for a Trie Node
    struct Node {
        string                       val;       // The name of the folder
        string                       subFolder; // A serialized string representing the entire subfolder structure
        unordered_map<string, Node*> children;  // Map from folder name to the child Node
    };

    // Helper function to create a new Trie Node
    Node* getNode(string val) {
        Node* temp = new Node();

        temp->val       = val;
        temp->subFolder = "";
        return temp;
    }
    // Function to insert a path into the Trie
    void insert(Node* root, vector<string>& path) {
        for (auto& folder : path) {
            // If the child folder doesn't exist, create it
            if (!root->children.count(folder)) {
                root->children[folder] = getNode(folder);
            }
            // Move to the child node
            root = root->children[folder];
        }
    }
    // Post-order DFS to serialize subfolder structures and count them
    string populateNodes(Node* root, unordered_map<string, int>& subFolderMap) {
        // Base case: if a folder is empty, its structure is empty
        if (root->children.empty()) {
            return "";
        }

        vector<pair<string, string>> subFolderPaths;

        // Recursively call for all children to get their serialized structures
        for (auto&[childName, child] : root->children) {
            string subFolderResult = populateNodes(child, subFolderMap);
            subFolderPaths.push_back({ childName, subFolderResult });
        }

        // Sort the children by name to ensure canonical representation
        // e.g., /a/x and /a/y is the same structure as /a/y and /a/x
        sort(begin(subFolderPaths), end(subFolderPaths));

        // Construct the serialized string for the current node's subfolder structure
        string completePath = "";
        for (auto& [childName, childPath] : subFolderPaths) {
            completePath += "(" + childName + childPath + ")";
        }

        // Store the serialized string in the current node
        root->subFolder = completePath;

        // If the structure is not empty, count its occurrence
        if (!completePath.empty()) {
            subFolderMap[completePath]++;
        }

        return completePath;
    }
    // Pre-order DFS to remove nodes that represent duplicate folders
    void removeDuplicates(Node* root, unordered_map<string, int>& subFolderMap) {
        // Use an iterator to safely erase while iterating
        for (auto it = root->children.begin(); it != root->children.end(); ) {
            Node* child = it->second;

            // Check if the child's subfolder structure is marked for deletion (count > 1)
            // A non-empty check is important because we don't delete folders just for being empty
            if (!child->subFolder.empty() && subFolderMap[child->subFolder] > 1) {
                // Erase the duplicate child node and its entire subtree
                it = root->children.erase(it);
            } else {
                // If not a duplicate, recurse to check its children
                removeDuplicates(child, subFolderMap);
                it++;
            }
        }
    }
    // Pre-order DFS to construct the final list of paths from the pruned Trie
    void constructResult(Node* root, vector<string>& path, vector<vector<string>>& result) {
        for (auto& [childName, child] : root->children) {
            // Add current folder to path
            path.push_back(childName);
            // This is a valid, remaining folder, so add its path to the result
            result.push_back(path);
            // Recurse to its children
            constructResult(child, path, result);
            // Backtrack to explore other branches
            path.pop_back();
        }
    }
    // Main function to orchestrate the deletion process
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        // Create the root of the Trie
        Node* root = getNode("/");

        // Step 1: Construct the Trie from the input paths
        for (auto& path : paths) {
            insert(root, path);
        }

        // Step 2: Serialize subfolder structures and populate the frequency map
        unordered_map<string, int> subFolderMap;
        populateNodes(root, subFolderMap);

        // Step 3: Remove all folders that are duplicates
        removeDuplicates(root, subFolderMap);

        // Step 4: Construct the result from the pruned Trie
        vector<vector<string>> result;
        vector<string>          path;
        constructResult(root, path, result);

        return result;
    }
};

/*
 * Dry Run with Example 1: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
 *
 * 1. Build Trie:
 * The code constructs a Trie representing the file structure.
 * - root
 * - "a" -> "b"
 * - "c" -> "b"
 * - "d" -> "a"
 *
 * 2. `populateNodes` (Post-order Traversal to Serialize and Count):
 * - Traverses from leaves up to the root.
 * - For node "/a/b": No children. Returns serialized string `""`.
 * - For node "/c/b": No children. Returns `""`.
 * - For node "/d/a": No children. Returns `""`.
 * - For node "/a": Has one child "b". The serialized string for "b" is `""`.
 * - `completePath` for "/a" becomes `"(b)"`.
 * - `a->subFolder` = `"(b)"`.
 * - `subFolderMap["(b)"]` is incremented to 1.
 * - For node "/c": Has one child "b". The serialized string for "b" is `""`.
 * - `completePath` for "/c" becomes `"(b)"`.
 * - `c->subFolder` = `"(b)"`.
 * - `subFolderMap["(b)"]` is incremented to 2.
 * - For node "/d": Has one child "a". The serialized string for "a" is `""`.
 * - `completePath` for "/d" becomes `"(a)"`.
 * - `d->subFolder` = `"(a)"`.
 * - `subFolderMap["(a)"]` is incremented to 1.
 * - At the end of this step, `subFolderMap` is `{ "(b)": 2, "(a)": 1 }`.
 *
 * 3. `removeDuplicates` (Pre-order Traversal to Prune):
 * - Starts from the `root`.
 * - Checks `root`'s child "a":
 * - `a->subFolder` is `"(b)"`. `subFolderMap["(b)"]` is 2, which is > 1.
 * - The node "a" and its children (like "b") are deleted from the trie.
 * - Checks `root`'s child "c":
 * - `c->subFolder` is `"(b)"`. `subFolderMap["(b)"]` is 2, which is > 1.
 * - The node "c" and its children are deleted.
 * - Checks `root`'s child "d":
 * - `d->subFolder` is `"(a)"`. `subFolderMap["(a)"]` is 1. Not a duplicate.
 * - The node "d" is kept.
 * - Recursively calls `removeDuplicates` on "d". "d" has a child "a".
 * - Check "d"'s child "a": `d/a->subFolder` is `""`. The `subFolder` is empty, so it's not checked against the map. The node is kept.
 *
 * 4. Final Trie Structure:
 * - root
 * - "d" -> "a"
 *
 * 5. `constructResult` (Pre-order Traversal to Build Result):
 * - Traverses the pruned Trie.
 * - Visits "d": path becomes `["d"]`. Adds `["d"]` to `result`.
 * - Visits "d"'s child "a": path becomes `["d", "a"]`. Adds `["d", "a"]` to `result`.
 *
 * 6. Final Output:
 * `[["d"], ["d", "a"]]`
 */
