#include "listnode.h"

ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, pred, this);    //更新4个指针的指向
	pred->next = p;
	pred = p;
	return p;
}//插入一个新节点，作为当前节点的前驱，调用方法  node->insertAsPred(x,y,t)

ListNode* ListNode::insertAsSucc(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, this, next);
	next->next = p;
	next = p;
	return p;
}//插入一个新节点，作为当前节点的后继，调用方法  node->insertAsSucc(x,y,t)
