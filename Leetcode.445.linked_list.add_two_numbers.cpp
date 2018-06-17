/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


/* use only linked list, O(n) time, with O(n) extra space.
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        int len1 = 0;
        int len2 = 0;
        ListNode *p;
        ListNode *w = new ListNode(0);
        ListNode *t = new ListNode(0);
        int s = 0;
        while(p1) {
            ++len1;
            p1 = p1->next;
        }
        while(p2) {
            ++len2;
            p2 = p2->next;
        }
        p1 = l1;
        p2 = l2;
        while(len1>len2) {
            t->val = p1->val;
            p = new ListNode(0);
            p->next = t;
            t = p;
            p1 = p1->next;
            --len1;
        }
        while(len2>len1) {
            t->val = p2->val;
            p = new ListNode(0);
            p->next = t;
            t = p;
            p2 = p2->next;
            --len2;
        }
        while(len1) {
            s = p1->val + p2->val;
            t->val = s;
            p = new ListNode(0);
            p->next = t;
            t = p;
            p1 = p1->next;
            p2 = p2->next;
            --len1;
        } 
        s = 0;
        t = t->next;
        while(t) {
            s += t->val;
            w->val = s % 10;
            s /= 10;
            p = new ListNode(0);
            p->next = w;
            w = p;
            t = t->next;
        }
        if(s) {
            w->val = s;
            return w;
        }
        return w->next;
    }
};