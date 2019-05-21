#include "list.h"
#include<stdio.h>
#include<stdlib.h>
void List::init(){
    header = (ListNode*)malloc(sizeof(ListNode));
    tailer = (ListNode*)malloc(sizeof(ListNode));
    header->next = tailer;
    tailer->pred = header;
    header->pred = NULL;
    tailer->next = NULL;
    _size = 0;
}

void List::copyNodes(ListNode* p, int n) { //O(n)
        init(); //创建头、尾哨兵节点并做初始化
        while (n--) { //将起自p的n项依次作为末节点插入
            InsertAsl(p);
            p = p->next;
        }
}

List::List(List const& L){  
        copyNodes( L.first(), L._size ); 
}

void List::clear()
{
	while ( 0 < _size ) remove ( header->next ); 
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
