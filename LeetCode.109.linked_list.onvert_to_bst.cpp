/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/* recursive, O(n) time with O(n) space.
 */

class Solution {
public:
    TreeNode* buildBST(int *arr, int len) {
        TreeNode *root = new TreeNode(0);
        if(len == 1) {
            root->val = *arr;
            return root;
        }
        if(len == 2) {
            root->val = *(arr+1);
            root->left = new TreeNode(*arr);
            return root;
        }
        if(len == 3) {
            root->val = *(arr+1);
            root->left = new TreeNode(*arr);
            root->right = new TreeNode(*(arr+2));
            return root;
        }
        
        root->val = *(arr+len/2);
        if(len%2==0) {
            root->left = buildBST(arr, len/2);
            root->right = buildBST(arr+len/2+1, len/2-1);
        } else {
            root->left = buildBST(arr, len/2);
            root->right = buildBST(arr+len/2+1, len/2);
        }
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        int len = 0;
        int i = 0;
        int *arr;
        ListNode *p = head;
        while(p) {
            ++len;
            p = p->next;
        }
        arr = new int[len];
        p = head;
        while(p) {
            *(arr+i) = p->val;
            p = p->next;
            ++i;
        }
        
        if(len == 0) return nullptr;
        return buildBST(arr, len);
    }
};