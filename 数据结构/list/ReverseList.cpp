/*反转链表
输入一个链表，反转链表后，输出新链表的表头。
/示例 输入{1，2，3} 输出{3，2，1}
*/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
      ListNode*cur=pHead;
      ListNode*prev=nullptr;
        while(cur!=nullptr){
           ListNode*pNext=cur->next;
            cur->next=prev;
            prev=cur;
            cur=pNext;
            }
       return prev;
    }
};
