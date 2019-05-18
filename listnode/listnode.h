#ifndef LISTNODE_H
#define LISTNODE_H
#include <cstdio>

class ListNode{
	public:
    int x,y;
    int t;
    ListNode *pred,*next;
    ListNode(){}
    ListNode(int x,int y,int t,ListNode* p=NULL,ListNode* n=NULL): x(x),y(y),t(t),pred(p),next(n) {}//???ˉ * 

     ListNode* insertAsPred(const int& x,const int& y,const int& t);
	 ListNode* insertAsSucc(const int& x,const int& y,const int& t); 
}; 


#endif 
