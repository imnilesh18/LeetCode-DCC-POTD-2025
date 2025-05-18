/*
 * 75. Sort Colors
 *
 * Medium
 *
 * Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
 * We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
 * You must solve this problem without using the library's sort function.
 *
 * Example 1:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * Example 2:
 *
 * Input: nums = [2,0,1]
 * Output: [0,1,2]
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 300
 * nums[i] is either 0, 1, or 2.
 *
 * Follow up: Could you come up with a one-pass algorithm using only constant extra space?
 */

/************************************************************ JAVA ************************************************/

// Approach: Dutch National Flag algorithm using three pointers (low, mid, high) to sort the array in one pass without extra space
// Time Complexity: O(n) - Each element is processed at most once
// Space Complexity: O(1) - No extra space is used apart from a few pointers
class Solution {
    public void swap(int[] a, int n1, int n2){
        int temp = a[n1]; // Swapping values at indices n1 and n2
        a[n1] = a[n2];
        a[n2] = temp;
    }

    public void sortColors(int[] a) {
        int n = a.length;
        int low = 0; // Points to the next position of 0
        int mid = 0; // Current element being checked
        int high = n -1; // Points to the next position of 2

        while(mid <= high){
            
            if(a[mid] == 0){
                swap(a, low, mid); // Swap current element with low index
                low++; // Move low pointer ahead
                mid++; // Move mid pointer ahead
            }

            else if(a[mid] == 1){
                mid++; // No swap needed, just move mid
            }

            else{
                swap(a, mid, high); // Swap current element with high index
                high--; // Move high pointer left
                // Do not move mid because swapped value at mid needs to be checked
            }
        }
    }
}

/*
 *
 * Dry Run
 *
 * Input: nums = [2, 0, 2, 1, 1, 0]
 * Initial: low = 0, mid = 0, high = 5
 *
 * Step 1: a[mid]=2 → swap(mid, high) → [0, 0, 2, 1, 1, 2], high = 4
 * Step 2: a[mid]=0 → swap(low, mid) → [0, 0, 2, 1, 1, 2], low = 1, mid = 1
 * Step 3: a[mid]=0 → swap(low, mid) → [0, 0, 2, 1, 1, 2], low = 2, mid = 2
 * Step 4: a[mid]=2 → swap(mid, high) → [0, 0, 1, 1, 2, 2], high = 3
 * Step 5: a[mid]=1 → mid = 3
 * Step 6: a[mid]=1 → mid = 4, mid > high → exit
 *
 * Final Output: [0, 0, 1, 1, 2, 2]
 */
