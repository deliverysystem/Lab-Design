#include "listnode.h"
#include <stdlib.h>
ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); 
	p->x=x;
	p->y=y;
	p->t=t;
	p->next = pred->next;
	pred->next = p;
	p->pred = pred;
	pred = p;
	return p;
}
