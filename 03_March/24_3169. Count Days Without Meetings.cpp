/*
 * 3169. Count Days Without Meetings
 *
 * You are given a positive integer days representing the total number of days an employee is available for work (starting from day 1). You are also given a 2D array meetings of size n where, meetings[i] = [start_i, end_i] represents the starting and ending days of meeting i (inclusive).
 *
 * Return the count of days when the employee is available for work but no meetings are scheduled.
 *
 * Note: The meetings may overlap.
 *
 * Example 1:
 * Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
 * Output: 2
 * Explanation:
 * There is no meeting scheduled on the 4th and 8th days.
 *
 * Example 2:
 * Input: days = 5, meetings = [[2,4],[1,3]]
 * Output: 1
 * Explanation:
 * There is no meeting scheduled on the 5th day.
 *
 * Example 3:
 * Input: days = 6, meetings = [[1,6]]
 * Output: 0
 * Explanation:
 * Meetings are scheduled for all working days.
 *
 * Constraints:
 * 1 <= days <= 109
 * 1 <= meetings.length <= 10^5
 * meetings[i].length == 2
 * 1 <= meetings[i][0] <= meetings[i][1] <= days
 */

// Approach: Sort the meetings and then iterate through them, counting gaps between the end of the previous meeting and the start of the current one.
// Time Complexity: O(n log n) due to sorting, where n is the number of meetings.
// Space Complexity: O(1) extra space (ignoring the input storage).
class Solution {
public:
    int countDays(int days, vector<vector<int> >& meetings) {
        int n = meetings.size();

        // Sort meetings by their start day (and end day implicitly)
        sort(begin(meetings), end(meetings));

        int result = 0;
        int end    = 0; // Keeps track of the last day covered by meetings

        // Iterate over each meeting
        for (auto& meet : meetings) {
            // If there is a gap between the end of the last meeting and the current meeting's start
            if (meet[0] > end + 1) {
                // Add the gap (number of free days between meetings)
                result += meet[0] - end - 1;
            }
            // Update the end day to the maximum of the current end or the current meeting's end
            end = max(end, meet[1]);
        }

        // If there are days after the last meeting, add them to the result
        if (days > end) {
            result += days - end;
        }

        return result;
    }
};

/*
 * Dry Run:
 * Assume days = 10, meetings = [[5,7],[1,3],[9,10]]
 * 1. After sorting: meetings = [[1,3], [5,7], [9,10]]; end = 0, result = 0.
 * 2. For meeting [1,3]:
 * - Check: 1 > 0 + 1? (1 > 1) -> false, no gap.
 * - Update end = max(0, 3) = 3.
 * 3. For meeting [5,7]:
 * - Check: 5 > 3 + 1? (5 > 4) -> true, gap exists.
 * - Gap days = 5 - 3 - 1 = 1; result becomes 1.
 * - Update end = max(3, 7) = 7.
 * 4. For meeting [9,10]:
 * - Check: 9 > 7 + 1? (9 > 8) -> true, gap exists.
 * - Gap days = 9 - 7 - 1 = 1; result becomes 2.
 * - Update end = max(7, 10) = 10.
 * 5. Post loop: Check if days > end: 10 > 10? -> false.
 * Final result = 2 free days.
 */
