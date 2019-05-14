#include "rider.h"
#include "menu.h"
#include "controller.h"
#define INF 0x3f3f3f3f

typedef The_ith(this,i) menu[i]; 
typedef The_ith(this,minid) menu[minid];

//下面出现的this 是指向当前rider 的一个指针

Rider::int Manhatten(point A,Point B)
{
    return  abs(A.x-B.x)+abs(A.y-B.y);
}

void Rider::GeneratePath(point Now,Menu* now, int T)
{
//T 是要变的 
    if(!now->get)
     {
            int disx = abs(Now.x-now->x1);
            int disy = abs(Now.y-now->y1);
                int Length = disx + disy;
                        //向上还是向下
                        for(int dx=0;dx<=disx;dx++)
                            {
                                if(Now.x-now.x1<0)
                                    ListNode* temp = new ListNode(Now.x+dx,Now.y,i+T);
                                else if(Now.x-now.x1>0)
                                    ListNode* temp = new ListNode(Now.x-dx,Now.y,i+T);
                                Path->InsertAsl(temp);
                            }
                        int X;
                        if(Now.x-now->x1<0)
                        	X = Now.x+disx;
                        else 
                        	X = Now.x-disx;
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                                if(Now.y-now.y1<0)
                                    ListNode* temp = new ListNode(X,Now.y+dy,i+T);
                                else if(Now.y-now.y1>0)
                                    ListNode* temp = new ListNode(X,Now.y-dy,i+T);
                                Path->InsertAsl(temp);
                            }
     }
     else {
            int disx = abs(Now.x-now->x2);
                int disy = abs(Now.y-now->y2);
                int Length = disx + disy;
                	    //想上还是向下 
                       for(int dx=0;dx<=disx;dx++)
                            {
                                if(Now.x-now->x2<0)
                                    ListNode* temp = new ListNode(Now.x+dx,Now.y,i+T);
                                else if(Now.x-now->x2>0)
                                    ListNode* temp = new ListNode(Now.x-dx,Now.y,i+T);
                                Path->InsertAsl(temp);
                            }
                        int X;
                        if(Now.x-now->x2<0)
                        	X = Now.x+disx;
                        else 
                        	X = Now.x-disx;
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                                if(Now.y-now->y2<0)
                                    ListNode* temp = new ListNode(X,Now.y+dy,i+T);
                                else if(Now.y-now->y2>0)
                                    ListNode* temp = new ListNode(X,Now.y-dy,i+T);
                                Path->InsertAsl(temp);
                            }
     }
}


Rider::void CalculatePath(Menu* newmenu){
    OldPath(Path);//先把现在的路径存下来 
    Path.clear();//清空路径 
    int Nowx = this->x;
    int Nowy = this->y;//取出骑手的坐标 
    point* ts = new point(Nowx,Nowy);//构造骑手point 
    
    //计算订单数 
    Menu* temp = waitlist;
    int cnt=0;
    while(temp!=nullptr){
        cnt++;
        temp = temp->next;
    }
    
    The_ith(this,cnt)->next=newmenu;//先把新订单加入链表 
    cnt+=1;//订单数+1 
    
    int T = systemclock;
    if(cnt==1) 
        GeneratePath(ts,newmenu,T); //只有新加入的订单一个单 
	
	
	// 除了最后一个单不确定之外 ，其余的订单都已经被分配好了，但是不一定骑手已经取到了餐，所以需要记一下已经取到餐的订单 ,也就是说骑手要遍历所有没有到过的点使得时间最短并且每个点按时到达
    else if(cnt>1){
        //必须知道目前的那些订单骑手已经取过餐了 设其有m 个 那么 2*n-m则为剩下的点数 其中 n-m个点代表餐馆 只有先到达这n-m个点 才能到达对应的目的
        for(int i=1;i<=cnt;i++)
            {	
                //对所有可达的点 求最小值 然后加入Path就行 ,最朴素
                int minid=0;
                int mind=INF;
                for(int i=0;i<=cnt;i++)
                    {
                        if( menu[i]->get&&!(menu[i]->reach))//对于已经取到餐的订单
                            {
                                if(mind<Manhatten(ts,(point)( menu[i]->x2, menu[i]->y2)))
                                    minid = i;
                                mind= min(mind,Manhatten(ts,(point)( menu[i]->x2, menu[i]->y2)));
                            }
                        else if(!(menu[i]->get)){//对于未取到的订单
                                if(mind<Manhatten(ts,(point)( menu[i]->x1, menu[i]->y1)))
                                    minid = i;
                               mind = min(mind,Manhatten(ts,(point)( menu[i]->x1, menu[i]->y1)));      
                        }
                    }
                GeneratePath(ts,menu[i],T);
                if( !(menu[minid]->get))
                    {
                        T += Manhatten(ts,(point)( menu[minid]->x2, menu[minid]->y2));
                        ts = (point)( menu[minid]->x2, menu[minid]->y2);
                         menu[minid]->reach=1;
                    }
                else 
                    {
                        T += Manhatten(ts,(point)( menu[minid]->x1, menu[minid]->y1));
                        ts = (point)( menu[minid]->x1, menu[minid]->y1);
                         menu[minid]->get=1;
                    }
                   
            }
    }
    
    //计算现在路径的时间 
	T = systemclock;
    T+ = Path->size(); 
	
	//交换现在的路径和原来的路径 
    List transition(OldPath);
    OldPath = Path; 
    Path = transition;

    The_ith(this,cnt-1)->next=nullptr;//从waitlist里面删除newmenu
    return T;
    
}

void Rider::AddTOWaitlist(Menu* newmenu)//将新的订单添加进waitlist 
{
	Menu* temp = waitlist;
    int cnt=0;
    while(temp!=nullptr){
        cnt++;
        temp = temp->next;
    }
	The_ith(this,cnt)->next=newmenu;//将newmenu加入waitlist
	
	Path = OldPath; //OldPath是当时假设有此单时算出的路径，这时真的有了这一单，直接用OldPath覆盖Path 
}

//对于时间不够的订单 不能按照上述条件来做.


