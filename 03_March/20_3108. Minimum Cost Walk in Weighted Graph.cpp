/*
 * 3108. Minimum Cost Walk in Weighted Graph
 *
 * There is an undirected weighted graph with n vertices labeled from 0 to n - 1.
 * You are given the integer n and an array edges, where edges[i] = [ui, vi, wi] indicates that there is an edge between vertices ui and vi with a weight of wi.
 * A walk on a graph is a sequence of vertices and edges. The walk starts and ends with a vertex, and each edge connects the vertex that comes before it and the vertex that comes after it. It's important to note that a walk may visit the same edge or vertex more than once.
 * The cost of a walk starting at node u and ending at node v is defined as the bitwise AND of the weights of the edges traversed during the walk. In other words, if the sequence of edge weights encountered during the walk is w0, w1, w2, ..., wk, then the cost is calculated as w0 & w1 & w2 & ... & wk, where & denotes the bitwise AND operator.
 * You are also given a 2D array query, where query[i] = [si, ti]. For each query, you need to find the minimum cost of the walk starting at vertex si and ending at vertex ti. If there exists no such walk, the answer is -1.
 * Return the array answer, where answer[i] denotes the minimum cost of a walk for query i.
 *
 * Example 1:
 * Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
 * Output: [1,-1]
 *
 * Explanation:
 * To achieve the cost of 1 in the first query, we need to move on the following edges: 0->1 (weight 7), 1->2 (weight 1), 2->1 (weight 1), 1->3 (weight 7).
 * In the second query, there is no walk between nodes 3 and 4, so the answer is -1.
 *
 * Example 2:
 * Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
 * zutput: [0]
 * Explanation:
 * To achieve the cost of 0 in the first query, we need to move on the following edges: 1->2 (weight 1), 2->1 (weight 6), 1->2 (weight 1).
 *
 * Constraints:
 * 2 <= n <= 10^5
 * 0 <= edges.length <= 10^5
 * edges[i].length == 3
 * 0 <= ui, vi <= n - 1
 * ui != vi
 * 0 <= wi <= 10^5
 * 1 <= query.length <= 10^5
 * query[i].length == 2
 * 0 <= si, ti <= n - 1
 * si != ti
 */

// Approach: We use the Union-Find (Disjoint Set Union) data structure to group connected components and maintain the minimum AND cost within each component.
// Time Complexity: O(E + Qα(n)), where E is the number of edges, Q is the number of queries, and α(n) (inverse Ackermann function) is nearly constant.
// Space Complexity: O(n), as we store parent and cost arrays.
class Solution {
public:

    vector<int> parent;     // Stores the parent of each node in the Union-Find structure

    // Find function with path compression
    int find(int x) {
        if (parent[x] == x) {
            return x;                       // If x is its own parent, return x
        }
        return parent[x] = find(parent[x]); // Path compression for optimization
    }
    // Union function to merge two components
    void Union(int x, int y) {
        parent[y] = x;     // Merge component y into component x
    }
    vector<int> minimumCost(int n, vector<vector<int> >& edges, vector<vector<int> >& query) {
        parent.resize(n);     // Resize parent array to store n elements
        vector<int> cost(n);  // Stores the "AND operation" cost of each connected component

        // Initialize the Union-Find structure
        for (int i = 0; i < n; i++) {
            parent[i] = i;     // Each node is its own parent initially
            cost[i]   = -1;    // Default cost for isolated components
        }

        // Process each edge and unite connected components
        for (auto& edge : edges) {
            int u = edge[0];                      // Start node
            int v = edge[1];                      // End node
            int w = edge[2];                      // Weight of the edge

            int parent_u = find(u);               // Find representative of u
            int parent_v = find(v);               // Find representative of v

            if (parent_u != parent_v) {           // If u and v belong to different components
                cost[parent_u] &= cost[parent_v]; // Update the cost of the merged component
                Union(parent_u, parent_v);        // Merge components
            }

            cost[parent_u] &= w;     // Update AND cost with current edge weight
        }

        vector<int> res;          // Stores results for each query
        for (auto& q : query) {
            int s = q[0];         // Start node in query
            int t = q[1];         // End node in query

            int p1 = find(s);     // Find representative of s
            int p2 = find(t);     // Find representative of t

            if (s == t) {         // If start and end nodes are the same, cost is 0
                res.push_back(0);
            }else if (p1 != p2) { // If s and t are in different components, return -1
                res.push_back(-1);
            }else{
                res.push_back(cost[p1]);     // Otherwise, return the minimum AND cost
            }
        }
        return res;     // Return the results for all queries
    }
};

/*
 * Dry Run
 *
 * Input:
 * n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
 *
 * Step 1: Initialize Union-Find structure
 * parent = [0, 1, 2, 3, 4]
 * cost   = [-1, -1, -1, -1, -1]
 *
 * Step 2: Process edges
 * Edge [0,1,7]: Merge 0 and 1 -> parent[1] = 0
 * Edge [1,3,7]: Merge 0 and 3 -> parent[3] = 0
 * Edge [1,2,1]: Merge 0 and 2 -> parent[2] = 0
 *
 * Updated parent array: [0, 0, 0, 0, 4]
 * Updated cost array:   [-1, -1, -1, -1, -1] (will update with AND operation)
 *
 * Step 3: Compute AND operation for cost:
 * - The AND operation results in `cost[0] = 1` for the connected component
 *
 * Step 4: Process Queries
 * Query [0,3]: 0 and 3 belong to the same component, return `cost[0] = 1`
 * Query [3,4]: 3 and 4 belong to different components, return `-1`
 *
 * Output: [1, -1]
 */
