/*
 * 2115. Find All Possible Recipes from Given Supplies
 *
 * You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.
 *
 * You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.
 *
 * Return a list of all the recipes that you can create. You may return the answer in any order.
 *
 * Note that two recipes may contain each other in their ingredients.
 *
 * Example 1:
 * Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
 * Output: ["bread"]
 * Explanation:
 * We can create "bread" since we have the ingredients "yeast" and "flour".
 *
 * Example 2:
 * Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
 * Output: ["bread","sandwich"]
 * Explanation:
 * We can create "bread" since we have the ingredients "yeast" and "flour".
 * We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
 *
 * Example 3:
 * Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
 * Output: ["bread","sandwich","burger"]
 * Explanation:
 * We can create "bread" since we have the ingredients "yeast" and "flour".
 * We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
 * We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".
 *
 * Constraints:
 * n == recipes.length == ingredients.length
 * 1 <= n <= 100
 * 1 <= ingredients[i].length, supplies.length <= 100
 * 1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
 * recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
 * All the values of recipes and supplies combined are unique.
 * Each ingredients[i] does not contain any duplicate values.
 */

// Approach 1 (Brute Force): Iterate over all recipes repeatedly until no more recipes can be cooked by checking if all required ingredients (including cooked recipes) are available.
// Time Complexity: O(n^2 * m) - In worst case, each recipe is checked multiple times, where n is the number of recipes and m is the average number of ingredients per recipe.
// Space Complexity: O(s + n) - Using extra space for the supplies set (s elements) and a cooked boolean array (n elements).
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string> >& ingredients, vector<string>& supplies) {
        int                   n = recipes.size();                 // number of recipes
        vector<string>        result;                             // to store the final list of cookable recipes
        unordered_set<string> st(begin(supplies), end(supplies)); // store initial supplies for O(1) lookup
        vector<bool>          cooked(n, false);                   // track which recipes have been cooked

        int count = n;                                            // iterate at most n times to ensure all possible recipes are cooked

        while (count--) {                                         // loop n times
            for (int j = 0; j < n; j++) {                         // iterate over each recipe
                if (cooked[j]) {                                  // if the recipe is already cooked, skip it
                    continue;
                }

                bool canCook = true;                              // flag to check if current recipe can be cooked
                for (int k = 0; k < ingredients[j].size(); k++) { // check all ingredients required for recipe[j]
                    if (!st.count(ingredients[j][k])) {           // if an ingredient is missing
                        canCook = false;                          // cannot cook this recipe
                        break;                                    // break out of the ingredient loop
                    }
                }

                if (canCook) {                    // if all ingredients are available
                    st.insert(recipes[j]);        // add the recipe to the available supplies
                    result.push_back(recipes[j]); // add to the result list
                    cooked[j] = true;             // mark recipe as cooked
                }
            }
        }
        return result;     // return all possible recipes that can be cooked
    }
};

/*
 * Dry Run:
 * Input:
 * recipes = ["bread", "sandwich"]
 * ingredients = [["yeast","flour"], ["bread","meat"]]
 * supplies = ["yeast", "flour", "meat"]
 *
 * Iteration 1:
 * - Check recipe "bread":
 *    Ingredients "yeast" and "flour" are in supplies.
 *    => Cook "bread", add "bread" to supplies.
 * - Check recipe "sandwich":
 *    Ingredients "bread" and "meat": "bread" now available from cooked recipes, "meat" is in supplies.
 *    => Cook "sandwich", add "sandwich" to supplies.
 *
 * Output:
 * ["bread", "sandwich"]
 */

// Approach 2 (Optimal Approach): Use Topological Sorting where we treat ingredients not initially available as prerequisites for recipes; recipes with zero remaining prerequisites can be cooked.
// Time Complexity: O(n + m + S) where n is the number of recipes, m is the total number of ingredients in recipes, and S is the number of supplies.
// Space Complexity: O(n + S) due to storing the indegree array, adjacency list, and supplies set.
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string> >& ingredients, vector<string>& supplies) {
        int n = recipes.size();                                   // number of recipes
        unordered_set<string> st(begin(supplies), end(supplies)); // set of initial supplies for O(1) lookup

        // Build graph: for each ingredient not in supplies, map the ingredient to the recipes that require it.
        unordered_map<string, vector<int> > adj; // ingredient -> list of recipe indices that depend on it

        vector<int> indegree(n, 0);              // indegree count for each recipe (number of ingredients needed that are not available as supplies)

        for (int i = 0; i < n; i++) {
            for (string& ing : ingredients[i]) {
                if (!st.count(ing)) {      // if the ingredient is not available in supplies
                    adj[ing].push_back(i); // add an edge from this ingredient to the recipe i
                    indegree[i]++;         // increment indegree for recipe i
                }
            }
        }

        // Initialize queue with recipes that can be cooked immediately (indegree is 0)
        queue<int> que;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                que.push(i);
            }
        }

        vector<string> result;     // to store the final list of cookable recipes
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            string recipe = recipes[i];
            result.push_back(recipe);     // recipe can be cooked, so add it to the result

            // For each recipe that depends on the current cooked recipe
            for (int& idx : adj[recipe]) {
                indegree[idx]--;     // reduce the number of missing ingredients for that recipe
                if (indegree[idx] == 0) {
                    que.push(idx);   // if all ingredients are now available, push into the queue
                }
            }
        }

        return result;     // return all recipes that can be cooked
    }
};

/*
 * Dry Run:
 * Input:
 * recipes = ["bread", "sandwich"]
 * ingredients = [["yeast", "flour"], ["bread", "meat"]]
 * supplies = ["yeast", "flour", "meat"]
 *
 * Step 1: Build Graph & indegree array:
 * For "bread":
 *  - "yeast" and "flour" are in supplies, so indegree remains 0.
 * For "sandwich":
 *  - "bread" is not in supplies → add edge: "bread" -> recipe 1; indegree becomes 1.
 *  - "meat" is in supplies.
 * Graph (adjacency list):
 *  "bread": [1]
 * Indegree array:
 *  [0, 1]
 *
 * Step 2: Initialize Queue:
 * - Recipe "bread" (index 0) has indegree 0 → queue = [0]
 *
 * Step 3: Process Queue:
 * - Pop recipe at index 0 ("bread"), add "bread" to result.
 * - For each recipe in adj["bread"]:
 *    Recipe at index 1 ("sandwich"): decrement indegree from 1 to 0.
 *    Since indegree becomes 0, push "sandwich" into queue.
 * - Pop recipe "sandwich" from queue, add it to result.
 *
 * Output:
 * ["bread", "sandwich"]
 */
