#include "list.h"


void List::init(){
    header = new ListNode();
    tailer = new ListNode();
    header->next = tailer;
    tailer->pred = head;
    header->pred = nullptr;
    tailer->next = nullptr;
    _size = 0;
}

int List::clear()
{
		int oldSize = _size;
		while (header->next != trailer)
			remove(header->next);
		return oldSize;
}

ListNode* List::insertAsPred(ListNode* p,const int& x,const int& y,const int& t)
{
		_size++;
		return p->insertAsPred(x,y,t);
}
	

ListNode* List::insertAsSucc(ListNode* p, const int& x,const int& y,const int& t)
{
		_size++;
		return p->insertAsSucc(x,y,t);
}

ListNode* List::InsertAsf(const int& x,const int& y,const int& t)
{	
		_size++;	
		ListNode *p = header->insertAsSucc(x,y,t);   
		return p;
}
	
ListNode* List::InsertAsl(const int& x,const int& y,const int& t)
{
		_size++;	
		ListNode *p = trailer->insertAsPred(x,y,t);	
		return p;	
}


ListNode* List::insert(Rank r, const int& x,const int& y,const int& t)
{
	ListNode *p=header;
	while (r--)
		{
			p = p->next;
		}
		return insertAsSucc(p, x,y,t);
}
	

void List::remove(ListNode* p)。
{	
	int x = p->x;
	int y = p->y;
	int t = p->t;
	p->pred->next = p->next;
	p->next->pred = p->pred;
	_size--;
	delete p;
}




