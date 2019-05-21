#ifndef LIST_H
#define LIST_H
#include "listnode.h"

class List{
  	public:
  	 	int _size; 
  	 	ListNode *header,*tailer;
  	
  	 	void init();// 鍒濆鍖栧垪琛?鏈変竴涓猦eader 涓€涓猼ailer 閮芥病鏈夎祴鍊?鍙槸璧峰埌涓€涓ご鑺傜偣灏捐妭鐐圭殑浣滅敤
  	 	void clear();// 娓呯┖
  	 	
 	
 	 	List() { init();}
    	void copyNodes(ListNode* p, int n); //杩欎釜鏄负浜嗕笅涓€涓嚱鏁版湇鍔＄殑
		List(List const& L);//鏋勯€犻摼琛ㄦ椂鍙互鐩存帴澶嶅埗涓€涓摼琛ㄥ埌鍙︿竴涓摼琛ㄩ噷闈?
    

	 	~List();
		 int size() const { return _size; } //杩斿洖閾捐〃鐨勫ぇ灏?璋冪敤鐨勬椂鍊? len=Path.size()
		 bool empty() const { return _size <= 0 ;}//閾捐〃鏄惁涓虹┖, 娉ㄦ剰 閾捐〃鐨刪eader 鍜?tailer 涓嶇畻鍦╯ize閲?
     		ListNode* first()  const{
        		return _size == 0 ? NULL : header->next;
    		}
     		ListNode* last() const{
        		return _size == 0 ? NULL : tailer->pred;
    		}
	    void InsertAsl(ListNode* p);//鎻掑叆鍒版渶鍚庨潰 
	    void remove(ListNode* p);// 鍒犻櫎
		void operator = (const List& A)//璧嬪€艰繍绠楃閲嶈浇  渚嬪 A鏄竴涓狶ist B鏄竴涓狶ist  A=B 灏辨槸鎶夿鐩存帴璧嬪€肩粰A
		{
			  clear();
		      ListNode* temp = A.first();
		      while(temp!=A.last()){
			  	this->InsertAsl(temp);
			  	temp = temp->next;
		      }
		}	  	  
};

#endif 
