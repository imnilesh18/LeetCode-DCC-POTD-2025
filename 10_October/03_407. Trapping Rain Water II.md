# 💧 407. Trapping Rain Water II

| Category   | Difficulty |
| :--------- | :--------- |
| Algorithms | `Hard`     |

<br>

[View Problem on LeetCode](https://leetcode.com/problems/trapping-rain-water-ii/)

---

### 🏷️ Tags

`Heap` `Priority Queue` `Breadth-First Search` `Matrix`

---

### 📖 Problem Statement

Given an `m x n` integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.

---

### 🖼️ Visual Example

<div align="center">
  <img src="https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg" alt="Trapping Rain Water II Example" width="400"/>
</div>

---

### 📊 Examples

| Input                                                                       | Output | Explanation                                                               |
| :-------------------------------------------------------------------------- | :----- | :------------------------------------------------------------------------ |
| `heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]`                   | `4`    | After the rain, water is trapped. The total volume of trapped water is 4. |
| `heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]` | `10`   | The water is trapped in the center, forming a 10-unit pond.               |

---

### ⛓️ Constraints

- `m == heightMap.length`
- `n == heightMap[i].length`
- `1 <= m, n <= 200`
- `0 <= heightMap[i][j] <= 2 * 10^4`

---

### 🤔 Approach and Intuition

The problem asks for the total volume of water that can be trapped in a 2D height map. Unlike the 1D version, water can flow in four directions. The key insight is to realize that the amount of water a cell can hold is limited by the lowest "wall" surrounding it.

Imagine the grid as a container. Water poured into it will be held by the outer walls. The water level will rise, but it can only rise as high as the lowest point on the boundary. If we think from the outside-in, the cells on the border of the grid form the initial container wall. These cells can't trap any water themselves; they only serve to hold water in.

This leads to an approach where we start from the boundary and move inwards. We need a way to always process the lowest part of the current boundary first, because that's the point where water would spill over. A **min-heap (Priority Queue)** is the perfect data structure for this.

1.  **Initialization**: We can start by adding all the cells on the grid's border to a min-heap. The heap will be prioritized by cell height. We also use a `visited` matrix to keep track of cells we've already processed.

2.  **Processing**: We then iteratively extract the cell with the minimum height from the heap. This cell represents the current "water level" or the lowest point in our expanding wall. Let's call its height `h`.

3.  **Expansion**: We explore the unvisited neighbors of this cell. For any neighbor, if its height is less than `h`, it means water can be trapped there. The amount of trapped water is `h - neighbor_height`. We add this volume to our total.

4.  **Updating the Boundary**: After visiting a neighbor, it effectively becomes part of the new boundary. We add this neighbor to the heap. The crucial part is what height to use when adding it. The new wall height at this position is not just the neighbor's original height, but the maximum of its own height and the current water level `h` (since it's now filled with water up to that level). This ensures that any further cells visited from this point will be contained by this new, higher wall.

We repeat this process until the heap is empty, meaning we have visited all possible cells that can trap water.

<details>
<summary>Click for a step-by-step walkthrough</summary>

1.  Create a min-priority queue to store `(height, row, col)` tuples.
2.  Create a `visited` matrix of the same dimensions, initialized to `false`.
3.  Add all cells on the four borders of the `heightMap` to the priority queue. Mark them as `visited`.
4.  Initialize a variable `trappedWater = 0`.
5.  Start a loop that continues as long as the priority queue is not empty.
6.  Inside the loop, extract the cell with the smallest height from the heap. Let this be `(h, r, c)`. This `h` is our current lowest wall height.
7.  Iterate through the four neighbors of `(r, c)`.
8.  For each neighbor `(nr, nc)`:
    - Check if it's within bounds and has not been visited.
    - If the neighbor's height `heightMap[nr][nc]` is less than `h`, it can trap water. Add `h - heightMap[nr][nc]` to `trappedWater`.
    - Mark the neighbor as visited.
    - Push the neighbor onto the heap. The height to push is `max(h, heightMap[nr][nc])`, because this cell is now part of the containing wall, and its effective height for trapping water further inland is at least `h`.
9.  After the loop finishes, `trappedWater` will hold the total volume. Return it.

</details>

---

### 💻 Solution Code (C++)

```cpp
// Intuition:
// The core idea is to treat the grid's boundaries as the initial walls of a container.
// Water can be trapped inside, limited by the lowest point on these walls. We can find this lowest
// point using a min-heap and expand inwards, calculating trapped water as we go.

// Approach:
// 1. Use a min-priority queue to store cells, prioritized by height.
// 2. Add all boundary cells to the priority queue and a `visited` set to avoid reprocessing.
// 3. While the queue is not empty, pop the cell with the minimum height. This cell acts as the
//    current "wall" height that contains the water.
// 4. Explore its unvisited neighbors. For any neighbor lower than the current wall height, it
//    traps water. Calculate this amount and add to the total.
// 5. Add the neighbor to the queue. Its new effective height for containing water is the maximum
//    of its original height and the current wall height. Mark it as visited.
// 6. Continue until all reachable cells are processed.

// Time Complexity: O(m * n * log(m * n))
// - Each of the m*n cells is pushed and popped from the priority queue at most once.
// - Each heap operation (push/pop) takes log(k) time, where k is the size of the heap.
// - The maximum size of the heap is m*n.

// Space Complexity: O(m * n)
// - The priority queue and the visited matrix can store up to m*n elements in the worst case.

class Solution {
public:
    // Define a type for cleaner code: {height, {row, col}}
    typedef pair<int, pair<int, int>> PP;

    // Directions for exploring neighbors (right, down, left, up)
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(); // Get number of rows
        int n = heightMap[0].size(); // Get number of columns

        // Min-heap to store boundary cells, smallest height on top
        priority_queue<PP, vector<PP>, greater<>> boundaryCells;

        // Visited matrix to keep track of processed cells
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Add left and right boundaries to the heap
        for (int r = 0; r < m; ++r) {
            for (int c : {0, n - 1}) {
                boundaryCells.push({heightMap[r][c], {r, c}});
                visited[r][c] = true;
            }
        }

        // Add top and bottom boundaries to the heap
        for (int c = 0; c < n; ++c) {
            for (int r : {0, m - 1}) {
                // Avoid adding corners twice
                if (!visited[r][c]) {
                    boundaryCells.push({heightMap[r][c], {r, c}});
                    visited[r][c] = true;
                }
            }
        }

        int trappedWater = 0; // Initialize total trapped water

        // Process cells from the heap until it's empty
        while (!boundaryCells.empty()) {
            // Get the cell with the minimum height from the boundary
            auto [height, cell] = boundaryCells.top();
            boundaryCells.pop();

            int i = cell.first;
            int j = cell.second;

            // Explore its 4 neighbors
            for (vector<int>& dir : directions) {
                int i_ = i + dir[0];
                int j_ = j + dir[1];

                // Check if neighbor is valid and not visited
                if (i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && !visited[i_][j_]) {

                    // Water trapped is the difference between the wall height and the cell's height
                    trappedWater += max(0, height - heightMap[i_][j_]);

                    // The new wall is the max of the current wall and the neighbor's height
                    // This new cell becomes part of the boundary for future calculations
                    boundaryCells.push({max(height, heightMap[i_][j_]), {i_, j_}});

                    // Mark neighbor as visited
                    visited[i_][j_] = true;
                }
            }
        }

        return trappedWater; // Return the total
    }
};

/*
*
* Dry Run
*
* Input: heightMap = [[1,4,3,1,3,2],
* [3,2,1,3,2,4],
* [2,3,3,2,3,1]]
*
* 1. Initialization:
* - Priority Queue (min-heap) `pq` is populated with all border cells:
* {1,(0,0)}, {1,(0,3)}, {1,(2,5)}, {2,(0,5)}, {2,(2,0)}, {3,(0,2)}, {3,(0,4)}, {3,(1,0)}, ...
* - `trappedWater` = 0.
*
* 2. Main Loop:
* - Pop {1,(0,0)}. Current wall height `h` = 1. Neighbors are (0,1) [4] and (1,0) [3]. Both are visited borders. No water trapped.
* - Pop {1,(0,3)}. Current `h` = 1. Neighbors are (0,2)[3], (0,4)[3] (borders) and (1,3)[3].
* - Neighbor (1,3) is unvisited. `heightMap[1][3]` is 3. Since `h` (1) < 3, no water trapped.
* - Push {max(1, 3), {1,3}} -> {3, {1,3}} to pq. Mark (1,3) visited.
* - Pop {1,(2,5)}. Current `h` = 1. Neighbors are visited.
* - ... a few more pops of 1s and 2s ...
* - Eventually, we pop a higher wall. Let's say we pop {3, {1,0}}. `h` = 3.
* - Explore neighbor (1,1) with height 2. It's unvisited.
* - `heightMap[1][1]` (2) < `h` (3). Water can be trapped.
* - `trappedWater` += 3 - 2 = 1.
* - Push {max(3, 2), {1,1}} -> {3, {1,1}} to pq. Mark (1,1) visited.
*
* 3. Continuing the process:
* - The algorithm continues to pop the minimum height from the `pq`, which now contains inner cells treated as new boundaries.
* - When we process the wall around cell (1,2) [height 1], the lowest surrounding wall height will be 3.
* - Let's say we pop {3, {some_neighbor_of_1,2}}. `h`=3. We visit (1,2).
* - `trappedWater` += 3 - 1 = 2.
* - Similarly for cell (2,3) [height 2], `trappedWater` += 3 - 2 = 1.
*
* 4. Final Result:
* - Total trapped water = 1 (at (1,1)) + 2 (at (1,2)) + 1 (at (2,3)) = 4.
*
*/
```

---

### 💻 Solution Code (Java)

```java
// Intuition:
// We can conceptualize the 2D grid as a landscape where the outer edges form an initial basin.
// By starting with these edges and always processing the lowest boundary point (using a min-heap),
// we can simulate filling the landscape with water. Any new cell we encounter that is lower than
// the current lowest boundary will trap water.

// Approach:
// 1. Create a min-priority queue to store cells as `int[]{height, row, col}`.
// 2. Initialize a `visited` boolean matrix.
// 3. Add all border cells to the priority queue and mark them as visited. This forms our initial set of "walls".
// 4. Loop while the priority queue is not empty:
//    a. Poll the cell with the minimum height. This height is the current water level.
//    b. For each of its four neighbors, if the neighbor is valid and unvisited:
//       i. Calculate trapped water: `max(0, current_water_level - neighbor_height)`.
//       ii. Add this to the total.
//       iii. Add the neighbor to the priority queue. Its effective height for containing more water is
//          `max(current_water_level, neighbor_height)`.
//       iv. Mark the neighbor as visited.
// 5. The loop ends when all reachable inner cells have been processed. Return the total water.

// Time Complexity: O(m * n * log(m * n))
// - Every cell is added to and removed from the priority queue at most once.
// - Each operation on the priority queue of size k takes O(log k).
// - The maximum size of the queue is m * n, leading to the complexity.

// Space Complexity: O(m * n)
// - For the priority queue storing the boundary cells and the `visited` matrix.

class Solution {
    public int trapRainWater(int[][] heightMap) {
        int m = heightMap.length;
        int n = heightMap[0].length;

        // Min-heap storing {height, row, col}, sorted by height
        PriorityQueue<int[]> boundaryCells = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));

        // Visited matrix to track processed cells
        boolean[][] visited = new boolean[m][n];

        // Add all boundary cells to the priority queue
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (row == 0 || row == m - 1 || col == 0 || col == n - 1) {
                    if (!visited[row][col]) {
                        boundaryCells.offer(new int[]{heightMap[row][col], row, col});
                        visited[row][col] = true;
                    }
                }
            }
        }

        int water = 0; // Total trapped water
        // Directions for neighbors: up, down, left, right
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Process cells from the lowest boundary point inwards
        while (!boundaryCells.isEmpty()) {
            int[] cell = boundaryCells.poll(); // Get cell with min height
            int height = cell[0];
            int i = cell[1];
            int j = cell[2];

            // Explore 4-directional neighbors
            for (int[] dir : directions) {
                int i_ = i + dir[0];
                int j_ = j + dir[1];

                // Check if the neighbor is within bounds and not yet visited
                if (i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && !visited[i_][j_]) {
                    // Trapped water is the difference between the current wall and the neighbor's height
                    water += Math.max(0, height - heightMap[i_][j_]);

                    // Add the neighbor to the boundary. Its new effective height is the max of
                    // its own height and the containing wall's height.
                    boundaryCells.offer(new int[]{Math.max(height, heightMap[i_][j_]), i_, j_});

                    // Mark as visited
                    visited[i_][j_] = true;
                }
            }
        }

        return water;
    }
}

/*
*
* Dry Run
*
* Input: heightMap = [[1,4,3,1,3,2],
* [3,2,1,3,2,4],
* [2,3,3,2,3,1]]
*
* 1. Initialization:
* - Priority Queue (min-heap) `pq` gets all unique border cells.
* pq will contain: {1,(0,0)}, {1,(0,3)}, {1,(2,5)}, {2,(0,5)}, {2,(2,0)}, ... etc.
* - `water` = 0.
*
* 2. Main Loop:
* - Poll {1,(0,0)}. `height` = 1. Its unvisited neighbors are none (all are borders).
* - Poll {1,(0,3)}. `height` = 1. Explore neighbor (1,3) [height 3].
* - Since neighbor height (3) > current `height` (1), no water is trapped.
* - Offer {max(1, 3), 1, 3} -> {3, 1, 3} to `pq`. Mark (1,3) visited.
* - ... After processing all 1s and 2s from the border ...
* - Let's say we poll {3, {1,0}}. `height` = 3.
* - Explore neighbor (1,1) [height 2]. It is unvisited.
* - `heightMap[1][1]` (2) is less than `height` (3).
* - `water` += 3 - 2 = 1.
* - Offer {max(3, 2), 1, 1} -> {3, 1, 1} to `pq`. Mark (1,1) visited.
*
* 3. Further Iterations:
* - The `pq` now contains inner cells that form a new, higher boundary.
* - Eventually, a cell like {3, {1,1}} will be polled. `height` = 3.
* - It will explore its neighbor (1,2) [height 1].
* - `heightMap[1][2]` (1) < `height` (3).
* - `water` += 3 - 1 = 2. (Total water = 1 + 2 = 3).
* - Offer {max(3, 1), 1, 2} -> {3, 1, 2} to `pq`.
* - The same logic applies to cell (2,3) [height 2], which will trap `3 - 2 = 1` unit of water. (Total water = 3 + 1 = 4).
*
* 4. Completion:
* - The loop terminates when all cells have been visited.
* - The final returned `water` is 4.
*
*/
```

---

### 💡 Key Insights

- **Boundary First Approach**: The problem is best solved from the outside-in. The outer boundary cells can never trap water; they only serve as the initial container walls.
- **Min-Heap for Lowest Wall**: A min-heap is essential for efficiently finding the lowest point on the current boundary. This point determines the maximum water level for the area it encloses.
- **Expanding Boundary**: As we process a low point on the wall and move to an inner cell, that inner cell (now potentially filled with some water) becomes part of the new, evolving boundary. Its effective height for containing water for its _own_ inner neighbors is the maximum of its physical height and the height of the water that just flowed in.

---

### 🚀 Further Exploration

- **Trapping Rain Water (1D)**: This is the simpler 1D version of the problem. Solving it helps build the intuition for using boundaries to trap water, though the solution uses a different technique (two pointers or dynamic programming).
- **Dijkstra's Algorithm Connection**: The approach used here is conceptually similar to Dijkstra's algorithm. We are always exploring from the "cheapest" (lowest height) cell, much like Dijkstra's explores from the node with the shortest path.

---

### 🔗 References

- [LeetCode Problem](https://leetcode.com/problems/trapping-rain-water-ii/)
- A great video explanation can often be found by searching for the problem name on YouTube.

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/trapping-rain-water-ii/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
