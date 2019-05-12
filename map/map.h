#ifndef MAP_H
#define MAP_H
#include "point.h"
#include <iostream>
using namespace std;

class Map{
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
    private:
     int x,y;
     int Graph[60][60];//用于记录某个位置是餐厅还是住所 餐厅为1,住所为0
}

#endif // MAP_H