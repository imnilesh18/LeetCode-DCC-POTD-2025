/*
 * 1290. Convert Binary Number in a Linked List to Integer
 *
 * Easy
 *
 * Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.
 * Return the decimal value of the number in the linked list.
 * The most significant bit is at the head of the linked list.
 *
 * Example 1:
 * Input: head = [1,0,1]
 * Output: 5
 * Explanation: (101) in base 2 = (5) in base 10
 *
 * Example 2:
 * Input: head = [0]
 * Output: 0
 *
 * Constraints:
 * The Linked List is not empty.
 * Number of nodes will not exceed 30.
 * Each node's value is either 0 or 1.
 */

// Approach 1: Reverse the linked list and compute decimal using powers of 2 from left to right
// Time Complexity: O(n), where n is the number of nodes
// Space Complexity: O(1), ignoring recursion stack space
class Solution {
public:
    // Function to reverse the linked list recursively
    ListNode* reverseLL(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head; // Base case
        }

        ListNode* last = reverseLL(head->next); // Recursive call to reverse the rest
        head->next->next = head;                // Reverse the current pointer
        head->next       = NULL;                // Break the existing link
        return last;                            // Return new head
    }
    
    int getDecimalValue(ListNode* head) {
        head = reverseLL(head); // Step 1: Reverse the linked list

        int result = 0;
        int power  = 0;

        // Step 2: Traverse reversed list and calculate decimal
        while (head) {
            if (head->val == 1) {
                result += pow(2, power); // Add 2^power if bit is 1
            }
            power++;                     // Move to next bit
            head = head->next;
        }

        return result; // Return the final decimal result
    }
};

/*
 *
 * Dry Run (Approach 1)
 * Input: head = [1 -> 0 -> 1]
 * Reversed list: [1 <- 0 <- 1] → becomes [1 -> 0 -> 1]
 * Traversal:
 *  power = 0, head->val = 1 → result += 2^0 = 1
 *  power = 1, head->val = 0 → result unchanged
 *  power = 2, head->val = 1 → result += 2^2 = 4
 * Final result: 1 + 4 = 5
 *
 */

// Approach 2: Traverse linked list and use bitwise left shift and OR to form decimal
// Time Complexity: O(n), where n is the number of nodes
// Space Complexity: O(1)
class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int result = 0;

        // Traverse through each bit
        while (head) {
            result = (result << 1) | (head->val); // Shift result and add current bit
            head   = head->next;                  // Move to next node
        }

        return result; // Final decimal value
    }
};

/*
 *
 * Dry Run (Approach 2)
 * Input: head = [1 -> 0 -> 1]
 * Initial result = 0
 *  head->val = 1 → result = (0 << 1) | 1 = 1
 *  head->val = 0 → result = (1 << 1) | 0 = 2
 *  head->val = 1 → result = (2 << 1) | 1 = 5
 * Final result: 5
 *
 */
