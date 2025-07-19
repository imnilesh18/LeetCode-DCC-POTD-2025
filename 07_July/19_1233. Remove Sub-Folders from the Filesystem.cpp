/*
 * 1233. Remove Sub-Folders from the Filesystem
 *
 * Medium
 *
 * Given a list of folders folder, return the folders after removing all sub-folders in those folders. You may return the answer in any order.
 *
 * If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder of folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of "/a", but "/b" is not a sub-folder of "/a/b/c".
 *
 * The format of a path is one or more concatenated strings of the form: '/' followed by one or more lowercase English letters.
 *
 * For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are not.
 *
 * Example 1:
 * Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
 * Output: ["/a","/c/d","/c/f"]
 * Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
 *
 * Example 2:
 * Input: folder = ["/a","/a/b/c","/a/b/d"]
 * Output: ["/a"]
 * Explanation: Folders "/a/b/c" and "/a/b/d" will be removed because they are subfolders of "/a".
 *
 * Example 3:
 * Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
 * Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 *
 * Constraints:
 * 1 <= folder.length <= 4 * 10^4
 * 2 <= folder[i].length <= 100
 * folder[i] contains only lowercase letters and '/'.
 * folder[i] always starts with the character '/'.
 * Each folder name is unique.
 */

// Approach 1: Iterate through each folder. For each folder, check if any of its parent folders exist by repeatedly trimming the path string from the end. Use a hash set for efficient O(1) average time lookups of parent folders. If a parent is found, the current folder is a sub-folder and is ignored. Otherwise, it's a root folder and is added to the result.
// Time Complexity: O(n * L^2), where n is the number of folders and L is the max length of a folder path. For each of n folders, we might loop L times, and string operations inside take O(L).
// Space Complexity: O(n * L), where n is the number of folders and L is their average length, to store the folders in a hash set and the result vector.
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // Create a hash set for fast O(1) average time lookups of folder paths.
        unordered_set<string> st(begin(folder), end(folder));
        vector<string>        result;

        // Iterate through each folder in the input list.
        for (string& originalFolder : folder) {
            bool   isSubFolder = false;
            string currentPath = originalFolder;

            // Start checking for parent folders. The first find_last_of will remove the last part of the path.
            // We stop when the path becomes empty (e.g., after processing "/a", it becomes "").
            while (currentPath.find_last_of('/') > 0) {
                // Find the position of the last '/' to isolate the parent folder path.
                size_t position = currentPath.find_last_of('/');

                // Trim the string to get the parent path. e.g., "/a/b/c" -> "/a/b".
                currentPath = currentPath.substr(0, position);

                // Check if this parent path exists in our original set of folders.
                if (st.count(currentPath)) {
                    // If the parent exists, the original folder is a sub-folder.
                    isSubFolder = true;
                    // We found a parent, no need to check further up the directory tree.
                    break;
                }
            }

            // If the loop finished without finding any existing parent folder in the set...
            if (!isSubFolder) {
                // ...it means this is a root folder, so add the original path to the result.
                result.push_back(originalFolder);
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run for Example 1:
 *
 * Input: folder = ["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"]
 *
 * 1. Initialize `st` (unordered_set) with all folders: {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"}
 * 2. Initialize `result` vector: []
 *
 * --- Loop Start ---
 *
 * Iteration 1: originalFolder = "/a"
 * - currentPath = "/a"
 * - The `while` loop condition `currentPath.find_last_of('/') > 0` is false.
 * - `isSubFolder` remains false.
 * - Add "/a" to result. `result` is now ["/a"].
 *
 * Iteration 2: originalFolder = "/a/b"
 * - currentPath = "/a/b"
 * - `while` loop starts.
 * - Parent path becomes "/a".
 * - `st.count("/a")` is true.
 * - Set `isSubFolder = true` and `break`.
 * - `isSubFolder` is true, so nothing is added to result.
 *
 * Iteration 3: originalFolder = "/c/d"
 * - currentPath = "/c/d"
 * - `while` loop starts.
 * - Parent path becomes "/c".
 * - `st.count("/c")` is false.
 * - `while` loop continues with currentPath = "/c".
 * - The condition `currentPath.find_last_of('/') > 0` is now false. The loop terminates.
 * - `isSubFolder` remains false.
 * - Add "/c/d" to result. `result` is now ["/a", "/c/d"].
 *
 * Iteration 4: originalFolder = "/c/d/e"
 * - currentPath = "/c/d/e"
 * - `while` loop starts.
 * - Parent path becomes "/c/d".
 * - `st.count("/c/d")` is true.
 * - Set `isSubFolder = true` and `break`.
 * - `isSubFolder` is true, so nothing is added to result.
 *
 * Iteration 5: originalFolder = "/c/f"
 * - currentPath = "/c/f"
 * - `while` loop starts.
 * - Parent path becomes "/c".
 * - `st.count("/c")` is false.
 * - `while` loop continues with currentPath = "/c".
 * - The condition `currentPath.find_last_of('/') > 0` is now false. The loop terminates.
 * - `isSubFolder` remains false.
 * - Add "/c/f" to result. `result` is now ["/a", "/c/d", "/c/f"].
 *
 * --- Loop End ---
 *
 * Final Output: ["/a", "/c/d", "/c/f"]
 *
 */

// Approach 2: Sort the folder paths lexicographically. This places parent folders directly before their sub-folders. Iterate through the sorted list, comparing each folder only with the last valid root folder added to the result list. If the current folder is a sub-folder of the last root, ignore it. Otherwise, it's a new root folder, so add it to the result.
// Time Complexity: O(n * L * log n), where n is the number of folders and L is their average length. Sorting n strings dominates the complexity.
// Space Complexity: O(L) or O(log n) auxiliary space (for sorting and temp strings), not counting the O(n * L) space required for the output vector.
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // Sort the folders lexicographically. This is the key step.
        // E.g., ["/a/b", "/a"] becomes ["/a", "/a/b"].
        // A parent folder will always come before its sub-folder.
        sort(begin(folder), end(folder));
        vector<string> result;

        // The first folder in the sorted list is guaranteed to be a root folder, as no shorter path can precede it.
        // Original comment (Hindi): "sorted hai islie folder[0] ka koi parent nahi hoga"
        // Translation: "Since it's sorted, folder[0] won't have a parent."
        result.push_back(folder[0]);

        // Start from the second folder and compare with the last valid folder added to the result.
        for (int i = 1; i < folder.size(); i++) {
            string currFolder = folder[i];
            // Get the last valid root folder we added.
            string lastFolder = result.back();
            // Append a '/' to ensure we match a full path component.
            // This prevents incorrectly matching "/a/b" with a folder like "/ab".
            lastFolder += '/';

            // `currFolder.find(lastFolder)` checks if `currFolder` starts with `lastFolder`.
            // If it does, `find` returns 0. If it doesn't, it's not a sub-folder.
            if (currFolder.find(lastFolder) != 0) {
                // Not a sub-folder, so it's a new root. Add it to the result.
                result.push_back(currFolder);
            }
            // If it is a sub-folder (find returns 0), we do nothing and move to the next folder in the input list.
        }

        return result;
    }
};

/*
 *
 * Dry Run for Example 1:
 *
 * Input: folder = ["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"]
 *
 * 1. Sort `folder`. In this case, it's already sorted lexicographically:
 * `folder` remains ["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"].
 *
 * 2. Initialize `result` and add the first element: `result` = ["/a"].
 *
 * --- Loop Start (i = 1) ---
 *
 * Iteration 1: i = 1
 * - `currFolder` = "/a/b".
 * - `lastFolder` = `result.back()` = "/a".
 * - Append '/': `lastFolder` becomes "/a/".
 * - `"/a/b".find("/a/")` returns 0.
 * - The condition `(0 != 0)` is false. Do nothing.
 *
 * Iteration 2: i = 2
 * - `currFolder` = "/c/d".
 * - `lastFolder` = `result.back()` = "/a".
 * - Append '/': `lastFolder` becomes "/a/".
 * - `"/c/d".find("/a/")` does not return 0 (it returns npos).
 * - The condition `(npos != 0)` is true.
 * - Add "/c/d" to result. `result` is now ["/a", "/c/d"].
 *
 * Iteration 3: i = 3
 * - `currFolder` = "/c/d/e".
 * - `lastFolder` = `result.back()` = "/c/d".
 * - Append '/': `lastFolder` becomes "/c/d/".
 * - `"/c/d/e".find("/c/d/")` returns 0.
 * - The condition `(0 != 0)` is false. Do nothing.
 *
 * Iteration 4: i = 4
 * - `currFolder` = "/c/f".
 * - `lastFolder` = `result.back()` = "/c/d".
 * - Append '/': `lastFolder` becomes "/c/d/".
 * - `"/c/f".find("/c/d/")` does not return 0 (it returns npos).
 * - The condition `(npos != 0)` is true.
 * - Add "/c/f" to result. `result` is now ["/a", "/c/d", "/c/f"].
 *
 * --- Loop End ---
 *
 * Final Output: ["/a", "/c/d", "/c/f"]
 *
 */
