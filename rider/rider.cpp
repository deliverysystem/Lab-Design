#include "rider.h"
#include "list.h"
#include "menu.h"
#include "controller.h"
#define INF 0x3f3f3f3f

Rider::int Manhatten(Point A,Point B)
{
    return  abs(A.x-B.x)+abs(A.y-B.y);
}

void Rider::GeneratePath(Point Now,int id ，int T)
{
//T 是要变的 
    if(!menu[id].get)
     {
            int disx = abs(Now.x-menu[id].x1);
                int disy = abs(Now.y-menu[id].y1);
                int Length = disx + disy;
                for(int i = 0 ;i<=Length;i++)//构造路径
                    {
                        //向上还是向下
                        for(int dx=0;dx<=disx;dx++)
                            {
                                if(Now.x-menu[id].x1<0)
                                    ListNode* temp = new ListNode(x+dx,y,i+T);
                                else if(Now.x-menu[id].x1>0)
                                    ListNode* temp = new ListNode(x+dx,y,i+T);
                                Path->InsertAsl(temp);
                            }
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                                if(Now.y-menu[id].y1<0)
                                    ListNode* temp = new ListNode(x+disx,y+dy,i+T);
                                else if(Now.y-menu[id].y1>0)
                                    ListNode* temp = new ListNode(x+disx,y-dy,i+T);
                                Path->InsertAsl(temp);
                            }
                          
                    } 
     }
     else {
            int disx = abs(Now.x-menu[id].x2);
                int disy = abs(Now.y-menu[id].y2);
                int Length = disx + disy;
                for(int i = 0 ;i<=Length;i++)//构造路径
                    {
                       for(int dx=0;dx<=disx;dx++)
                            {
                                if(Now.x-menu[id].x1<0)
                                    ListNode* temp = new ListNode(x+dx,y,i+T);
                                else if(Now.x-menu[id].x1>0)
                                    ListNode* temp = new ListNode(x+dx,y,i+T);
                                Path->InsertAsl(temp);
                            }
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                                if(Now.y-menu[id].y1<0)
                                    ListNode* temp = new ListNode(x+disx,y+dy,i+T);
                                else if(Now.y-menu[id].y1>0)
                                    ListNode* temp = new ListNode(x+disx,y-dy,i+T);
                                Path->InsertAsl(temp);
                            }
                    } 
     }
}


Rider::void CalculatePath(Menu* newlist){
    // 把newlist 加到waitlist末尾
    int Nowx = this->x;
    int Nowy = this->y;
    Point* ts = new Point(Nowx,Nowy);
    Menu* temp = waitlist->next;
    int cnt=0;
    while(temp!=tailer){
        cnt++;
        temp = temp->next;
    }
    int T = systemclock;
    if(cnt==1){  
        //取出menu[0]
        //如果该单未被取
                //餐馆的坐标menu[0].x1,menu[0].y1;
            //送餐地址的坐标 menu[0].x2,menu[0].y2;
            GeneratePath(ts,0，T); 

    }// 除了最后一个单不确定之外 ，其余的订单都已经被分配好了，但是不一定骑手已经取到了餐，所以需要记一下已经取到餐的订单 ,也就是说骑手要遍历所有没有到过的点使得时间最短并且每个点按时到达
    else if(cnt >1){
        //menu 里面记的是目前尚未被送到的订单
        //必须知道目前的那些订单骑手已经取过餐了 设其有m 个 那么 2*n-m则为剩下的点数 其中 n-m个点代表餐馆 只有先到达这n-m个点 才能到达对应的目的地
        //重载list[]运算符
        for(int i =0 ;i<=cnt;i++)
            {
                //对所有可达的点 求最小值 然后加入Path就行 ,最朴素
                int minid=0;
                int mind=INF;
                for(int i=0;i<cnt;i++)
                    {
                        if(menu[i].get&&!menu[i].reach)//对于已经取到餐的订单
                            {
                                if(mind<Manhatten(ts,(Point)(menu[i].x2,menu[i].y2)))
                                    minid = i;
                                mind=Manhatten(ts,(Point)(menu[i].x2,menu[i].y2));
                            }
                        else if(!menu[i].get){//对于未取到的订单
                                if(mind<Manhatten(ts,(Point)(menu[i].x1,menu[i].y1)))
                                    minid = i;
                               mind = min(mind,Manhatten(ts,(Point)(menu[i].x1,menu[i].y1)));      
                        }
                    }
                GeneratePath(ts,minid,T);
                if(menu[minid].get)
                    {
                        T += Manhatten(ts,(Point)(menu[minid].x2,menu[minid].y2));
                        ts = (Point)(menu[minid].x2,menu[minid].y2);
                        menu[minid].reach=1;
                    }
                else 
                    {
                        T += Manhatten(ts,(Point)(menu[minid].x1,menu[minid].y1));
                        ts = (Point)(menu[minid].x1,menu[minid].y1);
                        menu[minid].get=1;
                    }
                   
            }
    }
}

int Rider::AllThingsDone(){
    int total = systemclock ;
    ListNode* temp = header->next;
    while(temp!=tailer){
        total++;
        temp = temp->next;
    }
    return total;
}

//对于时间不够的订单 不能按照上述条件来做.

