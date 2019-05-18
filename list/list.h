#ifndef LIST_H
#define LIST_H
#include "listnode.h"

class List{
  	public:
  	 	int _size; 
  	 	ListNode *header,*tailer;
  	
  	 	void init();// 初始化列表 有一个header 一个tailer 都没有赋值 只是起到一个头节点尾节点的作用
  	 	void clear();// 清空
  	 	
 	
 	 	List() { init();}
    	void copyNodes(ListNode* p, int n); //这个是为了下一个函数服务的
		List(List const& L);//构造链表时可以直接复制一个链表到另一个链表里面
    

	 	~List();
		 int size() const { return _size; } //返回链表的大小 调用的时候  len=Path.size()
		 bool empty() const { return _size <= 0 ;}//链表是否为空, 注意 链表的header 和 tailer 不算在size里
     		ListNode* first()  const{
        		return _size == 0 ? NULL : header->next;
    		}
     		ListNode* last() const{
        		return _size == 0 ? NULL : tailer->pred;
    		}
	        void InsertAsl(ListNode* p);//插入到最后面 
	        void remove(ListNode* p);// 删除
		List& operator =(const List& A)//赋值运算符重载  例如 A是一个List B是一个List  A=B 就是把B直接赋值给A
		{
		      this->_size = A.size();
		      ListNode* temp = A.first();
		      while(temp!=A.last()){
			  this->InsertAsl(temp);
			  temp = temp->next;
		      }
		      return *this;
		}	  	 
};

#endif 
