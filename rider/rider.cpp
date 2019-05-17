#include "rider.h"
#include "menu.h"
#include "controller.h"
#define INF 0x3f3f3f3f
#define The_ith(this,i) waitlist[i];
//#define The_ith(this,minid) waitlist[minid];
//#define The_ith(this,cnt) waitlist[cnt];

//下面出现的this 是指向当前rider 的一个指针

inline int min(int a,int b)
{
	return a<b? a:b;
}

int Rider::Manhatten(point* A,point* B)
{
    return  abs(A->x-B->x)+abs(A->y-B->y);
}

void Rider::GeneratePath(point* Now,struct menu* now, int T)
{
//T 是要变的 
    if(!now->get)
     {
            int disx = abs(Now->x-now->x1);
            int disy = abs(Now->y-now->y1);
                int Length = disx + disy;
                        //向上还是向下
                        for(int dx=0;dx<=disx;dx++)
                            {
                            	ListNode* temp;
                                if(Now->x-now->x1<0)
                                    temp = new ListNode(Now->x+dx,Now->y,dx+T);
                                else if(Now->x-now->x1>0)
                                    temp = new ListNode(Now->x-dx,Now->y,dx+T);
                                Path.InsertAsl(temp);
                            }
                        int X;
                        if(Now->x-now->x1<0)
                        	X = Now->x+disx;
                        else 
                        	X = Now->x-disx;
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                            	ListNode* temp;
                                if(Now->y-now->y1<0)
                                     temp = new ListNode(X,Now->y+dy,dy+T);
                                else if(Now->y-now->y1>0)
                                    temp = new ListNode(X,Now->y-dy,dy+T);
                                Path.InsertAsl(temp);
                            }
     }
     else {
            int disx = abs(Now->x-now->x2);
                int disy = abs(Now->y-now->y2);
                int Length = disx + disy;
                	    //想上还是向下 
                       for(int dx=0;dx<=disx;dx++)
                            {
                            	ListNode* temp; 
                                if(Now->x-now->x2<0)
                                    temp = new ListNode(Now->x+dx,Now->y,dx+T);
                                else if(Now->x-now->x2>0)
                                    temp = new ListNode(Now->x-dx,Now->y,dx+T);
                                Path.InsertAsl(temp);
                            }
                        int X;
                        if(Now->x-now->x2<0)
                        	X = Now->x+disx;
                        else 
                        	X = Now->x-disx;
                        // 下面的T要变 
                        //向左还是向右
                        for(int dy=1;dy<=disy;dy++)
                            {
                            	ListNode* temp;
                                if(Now->y-now->y2<0)
                                    temp = new ListNode(X,Now->y+dy,dy+T);
                                else if(Now->y-now->y2>0)
                                    temp = new ListNode(X,Now->y-dy,dy+T);
                                Path.InsertAsl(temp);
                            }
     }
}


int Rider:: CalculatePath(struct menu* newmenu){
    OldPath=Path;//先把现在的路径存下来 
    Path.clear();//清空路径 
    int Nowx = this->x;
    int Nowy = this->y;//取出骑手的坐标 
    point* ts = new point(Nowx,Nowy);//构造骑手point 
    
    //计算订单数 
    struct menu* temp = waitlist;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        temp = temp->nextmenu;
    }
    
    waitlist[cnt].nextmenu=newmenu;//先把新订单加入链表 
    cnt+=1;//订单数+1 
    
    int T = sysclock;
    if(cnt==1) {
	    GeneratePath(ts,newmenu,T);
	    //先取餐
	    point* A = new point(waitlist[1].x1, waitlist[1].y1);
	     T += Manhatten(ts,A);
             ts = A;
            waitlist[1].get=1;
	    //再送餐
	    GeneratePath(ts,newmenu,T);
	    point* B = new point(waitlist[1].x2, waitlist[1].y2);
	    T += Manhatten(ts,B);
            ts = B;
            waitlist[1].reach=1;
    }//只有新加入的订单一个单 
	
	
	// 除了最后一个单不确定之外 ，其余的订单都已经被分配好了，但是不一定骑手已经取到了餐，所以需要记一下已经取到餐的订单 ,也就是说骑手要遍历所有没有到过的点使得时间最短并且每个点按时到达
    else if(cnt>1){
        //必须知道目前的那些订单骑手已经取过餐了 设其有m 个 那么 2*n-m则为剩下的点数 其中 n-m个点代表餐馆 只有先到达这n-m个点 才能到达对应的目的
        for(int i=1;i<=2*cnt;i++)
            {	
                //对所有可达的点 求最小值 然后加入Path就行 ,最朴素
                int minid=0;
                int mind=INF;
                for(int i=1;i<=cnt;i++)
                    {
                        if( waitlist[i].get&&!(waitlist[i].reach))//对于已经取到餐的订单
                            {
                            	point* B = new point(waitlist[i].x2, waitlist[i].y2);
                                if(mind<Manhatten(ts,B))
                                    minid = i;
                                mind= min(mind,Manhatten(ts,B));
                            }
                        else if(!(waitlist[i].get)){//对于未取到的订单
                        		point* A = new point(waitlist[i].x1, waitlist[i].y1);
                                if(mind<Manhatten(ts,A))
                                    minid = i;
                               mind = min(mind,Manhatten(ts,A));      
                        }
                    }
		if(minid==0) break;
               // GeneratePath(ts,waitlist[minid],T);
                if(!(waitlist[minid].get))
                    {
                    	point* B = new point(waitlist[minid].x2, waitlist[minid].y2);
                        T += Manhatten(ts,B);
                        ts = B;
                         waitlist[minid].reach=1;
                    }
                else 
                    {
                    	point* A = new point(waitlist[i].x1, waitlist[i].y1);
                        T += Manhatten(ts,A);
                        ts = A;
                         waitlist[minid].get=1;
                    }
                   
            }
    }
    
    //计算现在路径的时间 
    T = sysclock;
    T += Path._size; 
	
	//交换现在的路径和原来的路径 
    List transition(OldPath);
    OldPath = Path; 
    Path = transition;
	cnt = cnt-1;
    waitlist[cnt].nextmenu=NULL;//从waitlist里面删除newmenu
    return T;
    
}

void Rider::AddTOWaitlist(struct menu* newmenu)//将新的订单添加进waitlist 
{
    struct menu* temp = waitlist;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        temp = temp->nextmenu;
    }
	waitlist[cnt].nextmenu=newmenu;//将newmenu加入waitlist
	
	Path = OldPath; //OldPath是当时假设有此单时算出的路径，这时真的有了这一单，直接用OldPath覆盖Path 
}

//对于时间不够的订单 不能按照上述条件来做.

