/*
 * 2033. Minimum Operations to Make a Uni-Value Grid
 *
 * You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.
 *
 * A uni-value grid is a grid where all the elements of it are equal.
 *
 * Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.
 *
 * Example 1:
 * Input: grid = [[2,4],[6,8]], x = 2
 * Output: 4
 * Explanation: We can make every element equal to 4 by doing the following:
 * - Add x to 2 once.
 * - Subtract x from 6 once.
 * - Subtract x from 8 twice.
 * A total of 4 operations were used.
 *
 * Example 2:
 * Input: grid = [[1,5],[2,3]], x = 1
 * Output: 5
 * Explanation: We can make every element equal to 3.
 *
 * Example 3:
 * Input: grid = [[1,2],[3,4]], x = 2
 * Output: -1
 * Explanation: It is impossible to make every element equal.
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10^5
 * 1 <= m * n <= 10^5
 * 1 <= x, grid[i][j] <= 10^4
 */

// Approach:
// 1. Flatten the 2D grid into a 1D vector to simplify processing of all elements.
// 2. Determine a target value (median) that minimizes the total operations required to make all elements equal.
//    - The median is chosen because minimizing the absolute differences to a central value minimizes the sum of operations.
// 3. For each element, check if the difference between the element and the target is divisible by x.
//    - If not, it's impossible to equalize the grid (return -1).
// 4. Sum up the number of operations needed (|target - element| / x) for all elements.
// Note: The median can be obtained either by sorting the entire vector (O(L log L)) or using nth_element (O(L)).
//       Both approaches are valid, but nth_element is more efficient.
// Time Complexity: O(m*n + L log L) using sort (or O(m*n) using nth_element), where L = m*n.
// Space Complexity: O(m*n) for storing all grid elements in a vector.
class Solution {
public:
    int minOperations(vector<vector<int> >& grid, int x) {
        // Get the number of rows in the grid.
        int m = grid.size();
        // Get the number of columns in the grid (assume at least one row exists).
        int n = grid[0].size();

        // Create a vector to store all the elements from the grid in a flattened format.
        vector<int> vec;

        // Loop over each row.
        for (int i = 0; i < m; i++) {
            // Loop over each column in the current row.
            for (int j = 0; j < n; j++) {
                // Push the element at grid[i][j] into the vector.
                vec.push_back(grid[i][j]);     // O(m*n)
            }
        }

        // L represents the total number of elements in the grid.
        int L = vec.size();

        // Obtain the median element, which is the optimal target value.
        // Method 1: Sorting the vector (this is straightforward and makes it easy to get the median).
        // sort(begin(vec), end(vec));     // O(L log L)
        // Uncomment the next line to use an alternative approach:
        // Method 2: Using nth_element to find the median in O(L) time. This rearranges the vector so that the element
        // at position L/2 is the median, but does not fully sort the vector.
        nth_element(begin(vec), begin(vec) + L / 2, end(vec));   // O(L)
        // The two methods are provided for flexibility. Sorting is simple to understand, while nth_element is more efficient.
        // Example rearrangements:
        // For an initial vector {4, 2, 8, 6}:
        // Sorting:   {2, 4, 6, 8}
        // nth_element may produce a similar arrangement ensuring the median is at vec[L/2].

        // Select the median element as the target value for making the grid uniform.
        int target = vec[L / 2];

        // Initialize the result which will hold the total number of operations.
        int result = 0;
        // Loop through each element in the flattened vector to calculate the required operations.
        for (int& num : vec) {
            // Check if the difference between the current element and the target is divisible by x.
            // This is essential because you can only add or subtract multiples of x.
            // If num % x does not equal target % x, then (target - num) is not a multiple of x.
            if (num % x != target % x) {
                // If the condition fails, return -1 because it's impossible to convert num to target by adding/subtracting x.
                return -1;
            }
            // Calculate the number of operations needed for this element.
            // The number of operations is given by the absolute difference divided by x.
            result += abs(target - num) / x;
        }
        // Return the total number of operations required to make all elements equal.
        return result;
    }
};

/*
 * Dry Run:
 * -----------
 * Input: grid = [[2,4],[6,8]], x = 2
 *
 * Step 1: Flatten the grid into a vector.
 *  - Original grid:
 *       [2, 4]
 *       [6, 8]
 *  - After flattening, vec = [2, 4, 6, 8]
 *
 * Step 2: Determine the median value to be used as the target.
 *  - Using sort, the vector becomes: [2, 4, 6, 8]
 *  - L = 4 (total number of elements)
 *  - The median (target) is chosen as vec[L/2] = vec[2] = 6.
 *    (Note: Using nth_element might yield the same target in this case, as both approaches aim to get the median.)
 *
 * Step 3: Check if each element can be converted to the target and count the operations.
 *  - For num = 2:
 *       Check: 2 % 2 == 6 % 2  ->  0 == 0  (Valid)
 *       Operations = abs(6 - 2) / 2 = 4 / 2 = 2
 *  - For num = 4:
 *       Check: 4 % 2 == 6 % 2  ->  0 == 0  (Valid)
 *       Operations = abs(6 - 4) / 2 = 2 / 2 = 1
 *  - For num = 6:
 *       Check: 6 % 2 == 6 % 2  ->  0 == 0  (Valid)
 *       Operations = abs(6 - 6) / 2 = 0 / 2 = 0
 *  - For num = 8:
 *       Check: 8 % 2 == 6 % 2  ->  0 == 0  (Valid)
 *       Operations = abs(6 - 8) / 2 = 2 / 2 = 1
 *  - Total operations = 2 + 1 + 0 + 1 = 4
 *
 * Step 4: The function returns 4, which is the minimum number of operations required.
 *
 * -----------
 * Detailed Derivation Explanation:
 * -----------
 * a + x + x + x = target
 *  - For an element 'a' in the grid, if we add the value x three times, we reach the target.
 *  - This is written as: a + 3x = target.
 *  - Rearranging, we obtain: 3x = target - a.
 *  - Dividing both sides by x (and assuming x is not 0), we get:
 *        (target - a) / x = 3.
 *  - This shows that (target - a) must be a multiple of x, meaning (target - a) % x = 0.   --- eqn(1)
 *
 * Similarly, for another element 'b' in the grid:
 *  - We must have (target - b) % x = 0 for it to be possible to convert b into target with additions or subtractions of x.
 *  - Even if the difference (target - b) is negative, the divisibility condition still applies when we consider its absolute value:
 *        abs(target - b) % x = 0.  --- eqn(2)
 *
 * Thus, for any two elements a and b in the grid:
 *  - Both (target - a) and (target - b) must be divisible by x.
 *  - This implies that the remainders when a and b are divided by x must be the same as the remainder when target is divided by x.
 *  - In other words, target % x should equal a % x and also equal b % x.
 *
 * Expanding the expression for element 'a':
 *  - Write (target - a) as k*x for some integer k.
 *  - Then, target can be expressed as: target = k*x + a.
 *  - Taking modulo x on both sides:
 *        target % x = (k*x + a) % x.
 *  - Since k*x is divisible by x, (k*x) % x = 0.
 *  - Thus, we have: target % x = (0 + a % x) % x = a % x.
 *  - Similarly, this holds for any element b in the grid: target % x = b % x.
 *
 * Conclusion:
 *  - Every element in the grid must have the same remainder when divided by x.
 *  - If any element does not satisfy this condition, it is impossible to make the grid uni-value using the allowed operations.
 *  - Therefore, if we detect any element with a different remainder, we return -1.
 *
 * This derivation is critical to ensuring that the problem's constraint on operation feasibility is properly checked before summing the required operations.
 */
