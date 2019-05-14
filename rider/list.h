#ifndef LIST_H
#defien LIST_H

class ListNode{
    int x,y;
    int t;
    ListNode *pred,*next;
    ListNode(){}
    ListNode(int x,int y,int t,ListNode* p=nullptr,ListNode* n=nullptr): x(x),y(y),t(t),pred(p),next(n) {}

    ListNode* insertAsPred (const int& x,const int& y,const int& t);
	ListNode* insertAssucc (const int& x,const int& y,const int& t); 
}

ListNode* ListNode::insertAsPred(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, pred, this);    //更新4个指针的指向
	pred->next = p;
	pred = p;
	return p;
}

ListNode* listNode::insertAsSucc(const int& x,const int& y,const int& t)
{
	ListNode *p = new ListNode(x,y,t, this, next);
	succ->next = p;
	succ = p;
	return p;
}

class List{
  	private:
  	 	int _size; 
  	 	ListNode* header,trailer;
  	protected:
  	 	void init();
  	 	int clear();
  	 	
 	public:
 	 	List() { init();}
		List(List const& L)；


	 	~List();
		 Rank size() const { return _size; }
		 bool empty() const { return _size <= 0 ;}
		 //int& operator[] (Rank r) const; 
		 ListNode* first() const { return header->next ;} 
		 ListNode* last() const { return trailer->pred ;}
		 bool vaild (ListNode* p)
		 {
		     return p&&(trailer !=p )&&( header !=p) ;
		 }
	

		void InsertAsf(int const& e);
		void InsertAsl(int const& e);
		ListNode* InsertAsf(ListNode* ,int const& e);
		ListNode* InsertAsl(ListNode* ,int const& e); 
	  
	    void remove(Rank r);
	  	 
};

#endif LIST_H
