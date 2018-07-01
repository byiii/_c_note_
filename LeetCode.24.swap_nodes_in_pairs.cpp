/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    void _swapPairs(ListNode* pre, ListNode* head) {
        ListNode *cn, *nn, *nnn;
        
        cn = head;
        if(cn==NULL) return;
        nn = cn->next;
        if(nn==NULL) return;
        nnn = nn->next;
        nn->next = cn;
        cn->next = nnn;
        
        pre->next = nn;
        _swapPairs(cn, nnn);
    }
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *new_head;
        new_head = new ListNode(0);
        new_head->next = head;
        
        _swapPairs(new_head, head);
        return new_head->next;
    }
};
