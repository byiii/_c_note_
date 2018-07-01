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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0);
        ListNode *cn;
        ListNode *pn = head;
        while(l1 || l2) {
            while(l2 && (l1==NULL || l1->val >= l2->val)) {
                cn = new ListNode(l2->val);
                pn->next = cn;
                pn = cn;
                l2 = l2->next;
            }
            while(l1 && (l2==NULL || l2->val > l1->val)) {
                cn = new ListNode(l1->val);
                pn->next = cn;
                pn = cn;
                l1 = l1->next;
            }
        }
        cn = head;
        head = head->next;
        delete cn;
        return head;
    }
};
