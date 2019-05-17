#ifndef RIDER_H
#define RIDER_H

#include "tools.h"
#include "point.h"
#include "menu.h"

class ListNode{
	public:
    int x,y;
    int t;
    ListNode *pred,*next;
    ListNode(){}
    ListNode(int x,int y,int t,ListNode* p=NULL,ListNode* n=NULL): x(x),y(y),t(t),pred(p),next(n) {}//改动 * 

    ListNode* insertAsPred (const int& x,const int& y,const int& t);
	  ListNode* insertAsSucc (const int& x,const int& y,const int& t); 
}; 

ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, pred, this);    //更新4个指针的指向
	pred->next = p;
	pred = p;
	return p;
};//插入一个新节点，作为当前节点的前驱，调用方法  node->insertAsPred(x,y,t)

ListNode* ListNode::insertAsSucc(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, this, next);
	next->next = p;
	next = p;
	return p;
}//插入一个新节点，作为当前节点的后继，调用方法  node->insertAsSucc(x,y,t)

class List{
  	private:
  	 	int _size; 
  	 	ListNode *header,*tailer;
  	protected:
  	 	void init();// 初始化列表 有一个header 一个tailer 都没有赋值 只是起到一个头节点尾节点的作用
  	 	void clear();// 清空
  	 	
 	public:
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

class Rider{
  public:
    int x,y;
    point A(int x,int y);
    List Path,OldPath;
    int receive;//骑手的接单数
    int achieve;//骑手的完成数
    int overtime;//骑手超时数
    Rider() {}
    Rider(int x,int y):x(x),y(y) {}
    int exist;
    struct menu* waitlist;
    int CalculatePath(struct menu* newmenu);//试算送完最后一单的时间
    int Manhatten(point x,point y);
    void GeneratePath(point A,int id);
    void AddTOWaitlist(struct menu* newmenu);//将新的订单添加进waitlist
    ~Rider() {}
    //friend class Menu;
    friend class List;
};

#endif
