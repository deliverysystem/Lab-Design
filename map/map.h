#ifndef MAP_H
#define MAP_H
#include "point.h"
#include <iostream>
using namespace std;

class Map{
   public:
	void init(){
    for(x=0;x<=32;x+=4)
     for(y=0;y<=64;y+=8)
       {
           point c(x,y);
           if(Graph[x][y])
              c.PrintCanteen();
           else 
              c.PrintResidence();
       }
    }
     int x,y;
     int Graph[60][60];//用于记录某个位置是餐厅还是住所 餐厅为1,住所为0
};

#endif // MAP_H
