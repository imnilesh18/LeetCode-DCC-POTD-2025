/*
 * 1976. Number of Ways to Arrive at Destination
 *
 * You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
 *
 * You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
 *
 * Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.
 *
 * Example 1:
 * Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
 * Output: 4
 * Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
 * The four ways to get there in 7 minutes are:
 * - 0 ➝ 6
 * - 0 ➝ 4 ➝ 6
 * - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
 * - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
 *
 * Example 2:
 * Input: n = 2, roads = [[1,0,10]]
 * Output: 1
 * Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.
 *
 * Constraints:
 * 1 <= n <= 200
 * n - 1 <= roads.length <= n * (n - 1) / 2
 * roads[i].length == 3
 * 0 <= ui, vi <= n - 1
 * 1 <= timei <= 10^9
 * ui != vi
 * There is at most one road connecting any two intersections.
 * You can reach any intersection from any other intersection.
 */

// Approach: We use a modified Dijkstra's algorithm to compute the shortest distance from node 0 to all other nodes while also counting the number of shortest paths.
// Time Complexity: O(E log V) – Each edge is relaxed in a priority queue that supports log(V) insertion/deletion.
// Space Complexity: O(V + E) – For storing the adjacency list, distance array, and path count array.
class Solution {
public:
    typedef pair<long long, int> P;
    int M = 1e9 + 7;

    int countPaths(int n, vector<vector<int>>& roads) {
        // Create an adjacency list for the graph: node -> {neighbor, travel time}
        unordered_map<int, vector<pair<int, int>>> adj;

        for (auto& road : roads) {
            int u    = road[0];
            int v    = road[1];
            int time = road[2];
            adj[u].push_back({ v, time });
            adj[v].push_back({ u, time });
        }

        // Priority queue to process nodes based on the shortest travel time (min-heap)
        priority_queue<P, vector<P>, greater<P>> pq;
        // Distance array to store the minimum travel time to each node, initialized with maximum values
        vector<long long> result(n, LLONG_MAX);
        // Array to count the number of shortest paths to each node, initialized to 0
        vector<int> pathCount(n, 0);     // S.C: O(V)

        // Initialize starting node 0: distance 0 and 1 way to reach it
        result[0]    = 0;
        pathCount[0] = 1;
        pq.push({ 0, 0 });   // {time, node}

        // Process nodes until the priority queue is empty
        while (!pq.empty()) {
            long long currTime = pq.top().first;
            int       currNode = pq.top().second;
            pq.pop();

            // Relaxation step for all neighbors of the current node
            for (auto& vec : adj[currNode]) {
                int ngbr     = vec.first;
                int roadTime = vec.second;

                // If a shorter path to neighbor is found, update distance and path count
                if (currTime + roadTime < result[ngbr]) {
                    result[ngbr] = currTime + roadTime;
                    pq.push({ result[ngbr], ngbr });
                    pathCount[ngbr] = pathCount[currNode];     // New shortest path found: inherit the count from current node
                }
                // If an equally short path is found, increment the path count
                else if (currTime + roadTime == result[ngbr]) {
                    pathCount[ngbr] = (pathCount[ngbr] + pathCount[currNode]) % M;
                }
            }
        }
        return pathCount[n - 1];     // Return the count of shortest paths to the destination node (n-1)
    }
};

/*
 * Dry Run:
 * Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
 *
 * 1. Build the graph (adjacency list):
 * 0: {(6,7), (1,2), (4,5)}
 * 1: {(0,2), (2,3), (3,3)}
 * 2: {(1,3), (5,1)}
 * 3: {(1,3), (5,1), (6,3)}
 * 4: {(0,5), (6,2)}
 * 5: {(3,1), (6,1), (2,1)}
 * 6: {(0,7), (3,3), (5,1), (4,2)}
 *
 * 2. Initialization:
 * result = [0, INF, INF, INF, INF, INF, INF]
 * pathCount = [1, 0, 0, 0, 0, 0, 0]
 * pq = {(0, 0)}
 *
 * 3. Process node 0 (time = 0):
 * - For neighbor 6 via road 7:
 *     New time = 0 + 7 = 7 < INF, update result[6] = 7, pathCount[6] = 1, push (7,6)
 * - For neighbor 1 via road 2:
 *     New time = 0 + 2 = 2 < INF, update result[1] = 2, pathCount[1] = 1, push (2,1)
 * - For neighbor 4 via road 5:
 *     New time = 0 + 5 = 5 < INF, update result[4] = 5, pathCount[4] = 1, push (5,4)
 * Current state:
 *     result = [0, 2, INF, INF, 5, INF, 7]
 *     pathCount = [1, 1, 0, 0, 1, 0, 1]
 *     pq = {(2,1), (5,4), (7,6)}
 *
 * 4. Process node 1 (time = 2):
 * - For neighbor 0 via road 2: 2+2=4 > result[0] (0), ignore.
 * - For neighbor 2 via road 3: 2+3=5 < INF, update result[2] = 5, pathCount[2] = 1, push (5,2)
 * - For neighbor 3 via road 3: 2+3=5 < INF, update result[3] = 5, pathCount[3] = 1, push (5,3)
 * Current state:
 *     result = [0, 2, 5, 5, 5, INF, 7]
 *     pathCount = [1, 1, 1, 1, 1, 0, 1]
 *     pq = {(5,2), (5,3), (5,4), (7,6)}
 *
 * 5. Process node 2 (time = 5):
 * - For neighbor 1 via road 3: 5+3=8 > result[1] (2), ignore.
 * - For neighbor 5 via road 1: 5+1=6 < INF, update result[5] = 6, pathCount[5] = 1, push (6,5)
 * Current state:
 *     result = [0, 2, 5, 5, 5, 6, 7]
 *     pathCount = [1, 1, 1, 1, 1, 1, 1]
 *     pq = {(5,3), (5,4), (6,5), (7,6)}
 *
 * 6. Process node 3 (time = 5):
 * - For neighbor 1 via road 3: 5+3=8 > result[1] (2), ignore.
 * - For neighbor 5 via road 1: 5+1=6 equals result[5] (6), update pathCount[5] = (1+1)%M = 2.
 * - For neighbor 6 via road 3: 5+3=8 > result[6] (7), ignore.
 * Current state:
 *     result = [0, 2, 5, 5, 5, 6, 7]
 *     pathCount = [1, 1, 1, 1, 1, 2, 1]
 *     pq = {(5,4), (6,5), (7,6)}
 *
 * 7. Process node 4 (time = 5):
 * - For neighbor 0 via road 5: 5+5=10 > result[0] (0), ignore.
 * - For neighbor 6 via road 2: 5+2=7 equals result[6] (7), update pathCount[6] = (1+1)%M = 2.
 * Current state:
 *     result = [0, 2, 5, 5, 5, 6, 7]
 *     pathCount = [1, 1, 1, 1, 1, 2, 2]
 *     pq = {(6,5), (7,6)}
 *
 * 8. Process node 5 (time = 6):
 * - For neighbor 3 via road 1: 6+1=7 > result[3] (5), ignore.
 * - For neighbor 6 via road 1: 6+1=7 equals result[6] (7), update pathCount[6] = (2+2)%M = 4.
 * - For neighbor 2 via road 1: 6+1=7 > result[2] (5), ignore.
 * Current state:
 *     result = [0, 2, 5, 5, 5, 6, 7]
 *     pathCount = [1, 1, 1, 1, 1, 2, 4]
 *     pq = {(7,6)}
 *
 * 9. Process node 6 (time = 7):
 * - All neighbors yield paths with time >= current known distances; no further updates.
 *
 * Final Answer:
 * Number of ways to reach node 6 = 4.
 */
