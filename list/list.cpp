#include "list.h"

void List::init(){
    header = new ListNode();
    tailer = new ListNode();
    header->next = tailer;
    tailer->pred = header;
    header->pred = NULL;
    tailer->next = NULL;
    _size = 0;
}

void List::copyNodes(ListNode* p, int n) { //O(n)
        init(); //����ͷ��β�ڱ��ڵ㲢����ʼ��
        while (n--) { //������p��n��������Ϊĩ�ڵ����
            InsertAsl(p);
            p = p->next;
        }
}

List::List(List const& L){  
        copyNodes( L.first(), L._size ); 
}

void List::clear()
{
		int oldSize = _size;
		while (header->next != tailer)
			remove(header->next);
}

void List::InsertAsl(ListNode* p)
{
		_size++;	
		tailer->insertAsPred(p->x,p->y,p->t);	
}

void List::remove(ListNode* p)
{	
	p->pred->next = p->next;
	p->next->pred = p->pred;
	_size--;
	delete p;
}

List::~List()
{
		clear();   
		delete header;
		delete tailer;
}

