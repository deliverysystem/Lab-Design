#include "listnode.h"
#include <stdlib.h>
ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));    //鏇存柊4涓寚閽堢殑鎸囧悜
	s->pred=NULL;
	s->next=NULL;
	s->x=x;
	s->y=y;
	s->t=t;
	s->next = pred->next;
	pred->next = s;
	s->pred = pred;
	pred = s; 
	return s;
}
