#include "listnode.h"
#include <stdlib.h>
ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); 
	p->next = pred->next;
	pred->next = p;
	p->next = pred;
	pred = p;
	return p;
}
