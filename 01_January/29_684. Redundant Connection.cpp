/*
 * 684. Redundant Connection
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
 *
 * Example 1:
 * Input: edges = [[1,2],[1,3],[2,3]]
 * Output: [2,3]
 *
 * Example 2:
 * Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
 * Output: [1,4]
 *
 * Constraints:
 * n == edges.length
 * 3 <= n <= 1000
 * edges[i].length == 2
 * 1 <= ai < bi <= edges.length
 * ai != bi
 * There are no repeated edges.
 * The given graph is connected.
 */

// Approach: Use DFS to check if an edge creates a cycle by maintaining an adjacency list and verifying if both nodes are already connected before adding the edge.  
// Time Complexity: O(n²) in the worst case, as for each edge, we may perform a full DFS traversal.  
// Space Complexity: O(n) for storing the adjacency list and visited array.  
class Solution {
public:
   bool dfs(unordered_map<int, vector<int> >&adj, int u, int v, vector<bool>& visited) {
      visited[u] = true; // Mark the current node as visited

      if (u == v) {      // If we reached the target node, return true
         return true;
      }

      // Explore all the neighbors of the current node
      for (int&ngbr : adj[u]) {
         if (visited[ngbr]) {     // Skip already visited nodes
            continue;
         }

         // Recursively check if a path exists from neighbor to v
         if (dfs(adj, ngbr, v, visited)) {
            return true;
         }
      }

      return false;    // No path found
   }

   vector<int> findRedundantConnection(vector<vector<int> >& edges) {
      int n = edges.size();                 // Number of edges (same as number of nodes)

      unordered_map<int, vector<int> > adj; // Adjacency list to represent the graph

      // Process each edge
      for (int i = 0; i < n; i++) {
         int u = edges[i][0];
         int v = edges[i][1];

         vector<bool> visited(n, false);     // Visited array for DFS

         // Check if u and v are already connected in the graph
         // If they are connected, adding this edge creates a cycle
         if (adj.find(u) != adj.end() && adj.find(v) != adj.end() && dfs(adj, u, v, visited)) {
            return edges[i];      // This is the redundant edge
         }

         // If no cycle is detected, add the edge to the adjacency list
         adj[u].push_back(v);
         adj[v].push_back(u);
      }

      return {};    // This should never be reached since there is always one redundant edge
   }
};
