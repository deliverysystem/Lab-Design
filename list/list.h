#ifndef LIST_H
#define LIST_H
#include "listnode.h"

class List{
  	public:
  	 	int _size; 
  	 	ListNode *header,*tailer;
  	
  	 	void init();// ��ʼ���б� ��һ��header һ��tailer ��û�и�ֵ ֻ����һ��ͷ�ڵ�β�ڵ������
  	 	void clear();// ���
  	 	
 	
 	 	List() { init();}
    	void copyNodes(ListNode* p, int n); //�����Ϊ����һ�����������
		List(List const& L);//��������ʱ����ֱ�Ӹ���һ��������һ����������
    

	 	~List();
		 int size() const { return _size; } //��������Ĵ�С ���õ�ʱ��  len=Path.size()
		 bool empty() const { return _size <= 0 ;}//�����Ƿ�Ϊ��, ע�� �����header �� tailer ������size��
     		ListNode* first()  const{
        		return _size == 0 ? NULL : header->next;
    		}
     		ListNode* last() const{
        		return _size == 0 ? NULL : tailer->pred;
    		}
	        void InsertAsl(ListNode* p);//���뵽����� 
	        void remove(ListNode* p);// ɾ��
		List& operator =(const List& A)//��ֵ���������  ���� A��һ��List B��һ��List  A=B ���ǰ�Bֱ�Ӹ�ֵ��A
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
