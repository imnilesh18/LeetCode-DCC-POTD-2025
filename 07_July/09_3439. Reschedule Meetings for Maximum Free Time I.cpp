/*
 * 3439. Reschedule Meetings for Maximum Free Time I
 *
 * Medium
 *
 * You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.
 * You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].
 * You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.
 * The relative order of all the meetings should stay the same and they should remain non-overlapping.
 * Return the maximum amount of free time possible after rearranging the meetings.
 * Note that the meetings can not be rescheduled to a time outside the event.
 *
 * Example 1:
 * Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
 * Output: 2
 * Explanation:
 * Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
 *
 * Example 2:
 * Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
 * Output: 6
 * Explanation:
 * Reschedule the meeting at [2, 4] to [1, 3], leaving no meetings during the time [3, 9].
 *
 * Example 3:
 * Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
 * Output: 0
 *
 * Explanation:
 * There is no time during the event not occupied by meetings.
 *
 * Constraints:
 * 1 <= eventTime <= 10^9
 * n == startTime.length == endTime.length
 * 2 <= n <= 10^5
 * 1 <= k <= n
 * 0 <= startTime[i] < endTime[i] <= eventTime
 * endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
 */

// Approach: Sliding Window – build an array of free gaps and find the maximum sum over any window of size k+1 to simulate removing k meetings.
// Time Complexity: O(n) – single pass sliding window over the gaps.
// Space Complexity: O(k) – aside from the freeArray of size n, only O(1) additional variables dependent on k are used.
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<int> freeArray; // store durations of free gaps

        // gap before the first meeting
        freeArray.push_back(startTime[0]);

        // gaps between consecutive meetings
        for (int i = 1; i < startTime.size(); i++) {
            freeArray.push_back(startTime[i] - endTime[i - 1]);
        }

        // gap after the last meeting
        freeArray.push_back(eventTime - endTime[endTime.size() - 1]);

        // Khandani sliding window to merge at most k removed meetings ⇒ window size = k+1 gaps
        int i       = 0;        // left pointer
        int j       = 0;        // right pointer
        int maxSum  = 0;        // best merged free time found
        int currSum = 0;        // current window sum

        int n = freeArray.size();
        while (j < n) {
            currSum += freeArray[j];                     // include gap at j

            // if window larger than k+1 gaps, shrink from left
            if (i < n && j - i + 1 > k + 1) {
                currSum -= freeArray[i];                 // remove gap at i
                i++;                                     // move left pointer
            }

            maxSum = max(maxSum, currSum);               // update maximum
            j++;                                         // expand to next gap
        }

        return maxSum;
    }
};

/*
 *
 * Dry Run
 *
 * Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
 *
 * 1. Build freeArray:
 *    freeArray = [ startTime[0]=0,
 *                  startTime[1]-endTime[0]=2-1=1,
 *                  startTime[2]-endTime[1]=9-4=5,
 *                  eventTime-endTime[2]=10-10=0 ]
 *    ⇒ freeArray = [0, 1, 5, 0]
 *
 * 2. windowSize = k + 1 = 2
 *    Initialize i=0, j=0, currSum=0, maxSum=0
 *
 * 3. Iterate j from 0 to 3:
 *    j=0: currSum=0; window size=1 ≤2 ⇒ maxSum=0
 *    j=1: currSum=0+1=1; window size=2 ⇒ maxSum=1
 *    j=2: currSum=1+5=6; window size=3>2 ⇒ subtract freeArray[0]=0, i=1; currSum=6; maxSum=6
 *    j=3: currSum=6+0=6; window size=3>2 ⇒ subtract freeArray[1]=1, i=2; currSum=5; maxSum=6
 *
 * Final result = 6
 *
 */