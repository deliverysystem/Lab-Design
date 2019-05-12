#ifndef LIST_H
#defien LIST_H

template<typename T>
class ListNode{
    T data;
    ListNode<T> *pred,*next;
    ListNode(){}
    ListNode(T x,ListNode<T>* p=nullptr,ListNode<T>* n=nullptr): data(x)),pred(p),next(n) {}

    ListNode<T>* insertAsPred (T const& e);
	ListNode<T>* insertAssucc (T const& e); 
}

template<typename T> listNode<T>* listNode<T>::insertAsPred(const T& e)
{
	listNode<T> *p = new listNode<T>(e, pred, this);    //更新4个指针的指向
	pred->succ = p;
	pred = p;
	return p;
}

template<typename T> listNode<T>* listNode<T>::insertAsSucc(const T& e)
{
	listNode<T> *p = new listNode<T>(e, this, succ);
	succ->pred = p;
	succ = p;
	return p;
}

template <typename T> class List{
  	private:
  	 	int _size; 
  	 	ListNode<T>* header,trailer;
  	protected:
  	 	void init();
  	 	int clear();
  	 	void copyNodes (ListNode<T>* ,int );
  	 	
 	public:
 	 	List() { init();}
		List(List<T> const& L)；
		List(List<T>,Rank r,int n); 
		List(ListNode<T>* p,int n);

	 	~List();
		 Rank size() const { return _size; }
		 bool empty() const { return _size <= 0 ;}
		 T& operator[] (Rank r) const; 
		 ListNode<T>* first() const { return header->succ ;} 
		 ListNode<T>* last() const { return trailer->pred ;}
		 bool vaild (ListNode<T>* p)
		 {
		     return p&&(trailer !=p )&&( header !=p) ;
		 }
	

		void InsertAsf(T const& e);
		void InsertAsl(T const& e);
		ListNode<T>* InsertAsf(ListNode<T>* ,T const& e);
		ListNode<T>* InsertAsl(ListNode<T>* ,T const& e); 
	  
	    void remove(Rank r);
	    void removeRange(Rank lo,Rank hi);
	   
	    void exchange(Rank r, T const& e);
	  
	    ListNode<T>* Rangesort(Rank lo,Rank hi);
	    ListNode<T>* sort();
	   
	    ListNode<T>* deduplicated(Rank lo,Rank hi);
	    ListNode<T>* Unique(Rank lo,Rank hi);
	  
	   	ListNode<T>* find(T const& e ,Rank lo, Rank hi); 
	
	    reverse();
	  	 
};

#endif LIST_H