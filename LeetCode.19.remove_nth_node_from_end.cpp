/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p1, *p2, *pn;
        int i = 1;
        
        if(head == NULL) return NULL;
        if(head->next == NULL) return NULL;
        
        p1 = head;
        while(i++ < n) {
            p1 = p1->next;
        }
        if(p1->next == NULL) {
            return head->next;
        }
        
        p1 = p1->next;
        p2 = head;
        while(p1->next) {
            p1 = p1->next;
            p2 = p2->next;
        }
        p2->next = p2->next->next;
        
        return head;
    }
};
