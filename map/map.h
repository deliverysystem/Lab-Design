#ifndef MAP_H
#define MAP_H
#include "point.h"
#include <iostream>
#include"controller.h"
using namespace std;

class Map{
   public:
	void init(){		
		int i=0;
		int j=0;
		int k=0;
 		for(x=0;x<=32;x+=4)
 		    for(y=0;y<=64;y+=8)			//打印地图 
   		    {
  	 	        point c(x,y);
   	 	        c.Printmap();
    		}
    	for(i=0;i<=99;i++)				//将地图上所有点全部标记为1 
    		for(j=0;j<=99;j++){
    			Graph[i][j]=1;
			}
    	for(i=0;i<=34;i++)				//将纵路上坐标变为0 
    		for(j=5;j<=61;j+=8)
    		{
    			for(k=j;k<=j+2;k++)
					Graph[i][k]=0; 
		}
		for(i=3;i<=31;i+=4)				//将横路上坐标变为0 
    		for(j=0;j<=68;j++)
    		{
				Graph[i][j]=0; 
		}
	}
     int x,y;
	 //用于记录某个位置是餐厅还是住所 餐厅为1,住所为0
};

#endif // MAP_H
