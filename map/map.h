#ifndef MAP_H
#define MAP_H
#include "point.h"
#include <iostream>
using namespace std;

class Map{
   public:
	void init(){
    for(x=0;x<60;x+=6)
     for(y=0;y<80;y+=8)
       {
           point c(x,y);
           if(Graph[x][y])
              c.PrintCanteen();
           else 
              c.PrintResidence();
       }
    }
     int x,y;
     int Graph[60][60];//���ڼ�¼ĳ��λ���ǲ�������ס�� ����Ϊ1,ס��Ϊ0
};

#endif // MAP_H
