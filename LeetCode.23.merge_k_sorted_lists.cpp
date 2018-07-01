/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <cstdint>
#include <algorithm>

struct MyStruct {
    int i;
    int v;
};

bool comp_func (int a, int b) {
    return (a < b);
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = new ListNode(0);
        ListNode *cn;
        ListNode *pn = head;
        
        vector<int> all_nums;
        
        for(int i=0; i<lists.size(); ++i) {
            ListNode *p = lists[i];
            while(p) {
                all_nums.push_back(p->val);
                p = p->next;
            }
        }
        
        sort(all_nums.begin(), all_nums.end(), comp_func);
        
        for(int i=0; i<all_nums.size(); ++i) {
            cn = new ListNode(all_nums[i]);
            pn->next = cn;
            pn = cn;
        }
        cn = head;
        head = head->next;
        delete cn;
        return head;
    }
};

/* ------------------------------------------------------------
 * limited memory solution
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <cstdint>
#include <algorithm>

struct MyStruct {
    int i;
    int v;
};

bool comp_func (int a, int b) {
    return (a < b);
}

class Solution {
    void mergeTwoLists(ListNode** pl1, ListNode* l2) {
        ListNode *pn = NULL;
        ListNode *cn = *pl1;
        ListNode *pn2 = NULL;
        ListNode *cn2 = l2;
        int flag;
        
        if(cn==NULL) {
            *pl1 = l2;
            return;
        }
        
        while(cn2) {
            flag = 0;
            while(cn && cn->val <= cn2->val) {
                flag = 1;
                pn = cn;
                cn = cn->next;
            }
            if(flag) {
                pn->next = cn2;
                if(cn==NULL) {
                    break;
                }
            }
            flag = 0;
            while(cn2 && cn2->val <= cn->val) {
                flag = 1;
                pn2 = cn2;
                cn2 = cn2->next;
            }
            if(flag) {
                pn2->next = cn;
                if(cn == *pl1) {
                    *pl1 = l2;
                }
            }
        }
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = NULL;
        for(int i=0; i<lists.size(); ++i) {
            mergeTwoLists(&head, lists[i]);
        }
        return head;
    }
};
