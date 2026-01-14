https://leetcode.com/problems/merge-two-sorted-lists/

```
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){
        ListNode* dummy = new ListNode(-1);
        ListNode* temp = dummy;

        while(list1!=nullptr && list2!=nullptr){
            if(list1->val <= list2->val){
                temp->next = list1;
                list1 = list1->next;
            }
            else{
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        
        if(list1) temp->next = list1;
        if(list2) temp->next = list2;

        ListNode* head = dummy->next;
        delete dummy;

        return head;
    }
};
```


Return -> [[Linked List]]

