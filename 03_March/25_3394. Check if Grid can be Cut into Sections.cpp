/*
 * 3394. Check if Grid can be Cut into Sections
 * (Solve First- LeetCode: 56. Merge Intervals)
 *
 * You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:
 * (startx, starty): The bottom-left corner of the rectangle.
 * (endx, endy): The top-right corner of the rectangle.
 * Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
 * Each of the three resulting sections formed by the cuts contains at least one rectangle.
 * Every rectangle belongs to exactly one section.
 * Return true if such cuts can be made; otherwise, return false.
 *
 * Example 1:
 * Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
 * Output: true
 * Explanation:
 * The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.
 *
 * Example 2:
 * Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
 * Output: true
 * Explanation:
 * We can make vertical cuts at x = 2 and x = 3. Hence, output is true.
 *
 * Example 3:
 * Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
 * Output: false
 * Explanation:
 * We cannot make two horizontal or two vertical cuts that satisfy the conditions. Hence, output is false.
 *
 * Constraints:
 * 3 <= n <= 10^9
 * 3 <= rectangles.length <= 10^5
 * 0 <= rectangles[i][0] < rectangles[i][2] <= n
 * 0 <= rectangles[i][1] < rectangles[i][3] <= n
 * No two rectangles overlap.
 */

// Approach: Extract horizontal (x-range) and vertical (y-range) projections of each rectangle and merge overlapping intervals; if either projection results in 3 or more disjoint segments, it means the grid can be cut into three sections with each section having at least one rectangle.
// Time Complexity: O(m log m) per projection, where m is the number of rectangles (due to sorting).
// Space Complexity: O(m) for storing the interval projections and merged intervals.
class Solution {
public:
    // Merge overlapping intervals in a given list
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Sort intervals based on their starting point
        sort(begin(intervals), end(intervals));

        vector<vector<int>> result;
        // Initialize result with the first interval
        result.push_back(intervals[0]);

        // Iterate over the remaining intervals
        for (int i = 1; i < n; i++) {
            // If the current interval overlaps with the last interval in result (using '<' as defined in problem)
            if (intervals[i][0] < result.back()[1]) {
                // Merge intervals by updating the end of the last interval to the maximum end
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                // If no overlap, add the current interval as a new segment
                result.push_back(intervals[i]);
            }
        }
        return result;
    }

    // Check if the grid can be cut into 3 sections using either horizontal or vertical cuts
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        vector<vector<int>> hor;     // Horizontal projections: x-range intervals
        vector<vector<int>> vert;    // Vertical projections: y-range intervals

        // Extract x-range and y-range for each rectangle
        for (auto& coord : rectangles) {
            int x1 = coord[0];
            int y1 = coord[1];
            int x2 = coord[2];
            int y2 = coord[3];

            hor.push_back({ x1, x2 });
            vert.push_back({ y1, y2 });
        }

        // Merge the x-range intervals for horizontal cut checking
        vector<vector<int>> result1 = merge(hor);
        // If merging results in 3 or more segments, valid horizontal cuts exist
        if (result1.size() >= 3) {
            return true;
        }

        // Merge the y-range intervals for vertical cut checking
        vector<vector<int>> result2 = merge(vert);
        // If merging results in 3 or more segments, valid vertical cuts exist
        return result2.size() >= 3;
    }
};

/*
 * Dry Run:
 * Example: n = 5, rectangles = [[1,0,5,2], [0,2,2,4], [3,2,5,3], [0,4,4,5]]
 * Step 1: Build projections:
 *  hor = [[1,5], [0,2], [3,5], [0,4]]
 *  vert = [[0,2], [2,4], [2,3], [4,5]]
 * Step 2: Merge horizontal intervals (hor):
 *  Sorted hor = [[0,2], [0,4], [1,5], [3,5]]
 *  Merging process:
 *    - Start with [0,2]
 *    - Next [0,4] overlaps with [0,2] => merge into [0,4]
 *    - [1,5] overlaps with [0,4] => merge into [0,5]
 *    - [3,5] overlaps with [0,5] => remains [0,5]
 *  Merged hor result = [[0,5]] (only one segment)
 * Step 3: Since merged hor segments < 3, check vertical intervals (vert):
 *  Sorted vert = [[0,2], [2,3], [2,4], [4,5]]
 *  Merging process:
 *    - Start with [0,2]
 *    - [2,3] does not overlap with [0,2] (using strict <, so new segment) => segments: [[0,2], [2,3]]
 *    - [2,4] overlaps with [2,3] => merge into [2,4] => segments: [[0,2], [2,4]]
 *    - [4,5] does not overlap with [2,4] => add new segment => segments: [[0,2], [2,4], [4,5]]
 *  Merged vert result = [[0,2], [2,4], [4,5]] (three segments)
 * Step 4: Since vertical merged segments count is 3, return true.
 * Final Output: true
 */
