#include "rider.h"
#include "list.h"
#include "menu.h"
#include "controller.h"

Rider::int 

Rider::void CalculatePath(Menu* waitlist){
    int Nowx = this->x;
    int Nowy = this->y;
    Menu* temp = waitlist->next;
    int cnt=0;
    while(temp!=tailer){
        cnt++;
        temp = temp->next;
    }
    if(cnt==1){  
        //取出menu[0]
        //如果该单未被取
                //餐馆的坐标menu[0].x1,menu[0].y1;
            //送餐地址的坐标 menu[0].x2,menu[0].y2;
                int disx = abs(Nowx-menu[0].x1);
                int disy = abs(Nowy-menu[0].y1);
                int Length = disx + disy;
                for(int i = 0 ;i<=Length;i++)//构造路径
                    {
                        for(int dx=1;dx<=disx;dx++)

                    } 
    }// 除了最后一个单不确定之外 ，其余的订单都已经被分配好了，但是不一定骑手已经取到了餐，所以需要记一下已经取到餐的订单 ,也就是说骑手要遍历所有没有到过的点使得时间最短并且每个点按时到达
    else if(cnt >1){
        //menu 里面记的是目前尚未被送到的订单
        //必须知道目前的
    }
}