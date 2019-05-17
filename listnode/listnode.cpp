#include "listnode.h"

ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, pred, this);    //����4��ָ���ָ��
	pred->next = p;
	pred = p;
	return p;
}//����һ���½ڵ㣬��Ϊ��ǰ�ڵ��ǰ�������÷���  node->insertAsPred(x,y,t)

ListNode* ListNode::insertAsSucc(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, this, next);
	next->next = p;
	next = p;
	return p;
}//����һ���½ڵ㣬��Ϊ��ǰ�ڵ�ĺ�̣����÷���  node->insertAsSucc(x,y,t)
