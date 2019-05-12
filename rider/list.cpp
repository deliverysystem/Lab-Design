#include "list.h"


template<typename T>
List<T>::void init(){
    head->next = tailer;
    tailer->pred = head;
    head->pred = nullptr;
    tailer->next = nullptr;
    _size = 0;
}

template<typename T>
List<T>::int clear();
{

}

template<typename T>
List<T>::void copyNodes (ListNode<T>* ,int );

template<typename T>
List<T>::void InsertAsf(T const& e);

template<typename T>
List<T>::void InsertAsl(T const& e);

template<typename T>
ListNode<T>* List<T>::InsertAsf(ListNode<T>* ,T const& e);

template<typename T>
ListNode<T>* List<T>::InsertAsl(ListNode<T>* ,T const& e); 

template<typename T>
List<T>::void remove(Rank r);

template<typename T>
List<T>::void removeRange(Rank lo,Rank hi);
	   
template<typename T>
List<T>::void exchange(Rank r, T const& e);
	  
template<typename T>
List<T>::ListNode<T>* Rangesort(Rank lo,Rank hi);

template<typename T>
List<T>::ListNode<T>* sort();

