#include "rider.h"
#include "menu.h"
#include "map.h" 
#include <ctime>
#include "controller.h"
#define N 999
#define INF 0x3f3f3f3f
//#define The_ith(this,i) waitlist[i];
//#define The_ith(this,minid) waitlist[minid];
//#define The_ith(this,cnt) waitlist[cnt];

//下面出现的this 是指向当前rider 的一个指针

inline int min(int a,int b)
{
	return a<b? a:b;
}

int Rider::Manhatten(point* A,point* B)
{
	if(A->x==B->x){
		if(A->y<B->y)
		 B->y = B->y-4;
		else if(A->y>B->y)
	     B->y = B->y+4;
		return abs(A->y-B->y+4)/8+1;
	}
	else if (A->y==B->y){
		if(A->x<B->x)
		 B->x=B->x-2;
		else 
		 B->x=B->x+2;
		return abs(A->x-B->x+2)/4+1;
	}
	else{	
			if(A->x<B->x)
				B->x=B->x-2;
			else if(A->x>B->x)
				B->x=B->x+2;
			int disy = abs(A->y-B->y);
			if(disy%8==0)
				return disy/8+abs(A->x-B->x)/4;
			else
				return	disy/8+1+abs(A->x-B->x-2)/4;
		}
}//曼哈顿距离

int Rider::Calcux(point* A,point* B)
{
	return abs(A->x-B->x);
}

int Rider::Calcuy(point* A,point* B)
{
	return abs(A->y-B->y);
}

int Rider::CalculatePath(struct menu* newmenu){
    OldPath=Path;//先把现在的路径存下来 
    Path.clear();
    int Nowx = this->x;
    int Nowy = this->y;//取出骑手的坐标 
    point* ts = new point(Nowx,Nowy);//构造骑手point 
    
    //计算订单数 
    struct menu* temp = waitlist->nextmenu;
    int cnt=0;
    while(temp!=NULL){
        temp = temp->nextmenu;
        cnt++;
    }
    
    The_ith(this,cnt)->nextmenu=newmenu;//先把新订单加入链表 
    cnt+=1;//订单数+1 
    
    int T = sysclock;
    if(cnt==1) {
		//先取餐 
	    GeneratePath(ts,newmenu,T);    
	    point* A = new point(newmenu->x1, newmenu->y1);
	     T += Manhatten(ts,A);
             ts = A;
            waitlist[1].get=1;
	    //再送餐
	    GeneratePath(ts,newmenu,T);
	    point* B = new point(newmenu->x2, newmenu->y2);
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
                        if( The_ith(this,i)->get&&!(The_ith(this,i)->reach))//对于已经取到餐的订单
                            {
                            	point* B = new point(The_ith(this,i)->x2, The_ith(this,i)->y2);
                                if(mind<Manhatten(ts,B))
		                            minid = i;
                                mind= min(mind,Manhatten(ts,B));
                            }
                        else if(!(The_ith(this,i)->get)){//对于未取到的订单
                        		point* A = new point(The_ith(this,i)->x1, The_ith(this,i)->y1);
                                if(mind<Manhatten(ts,A))
                                    minid = i;
                               mind = min(mind,Manhatten(ts,A));      
                        }
                    }
		if(minid==0) break;
               // GeneratePath(ts,The_ith(this,minid),T);
                if(!(The_ith(this,minid)->get))
                    {
                    	point* B = new point(The_ith(this,minid)->x2, The_ith(this,minid)->y2);
                        T += Manhatten(ts,B);
                        ts = B;
                         The_ith(this,minid)->get=1;
                    }
                else 
                    {
                    	point* A = new point(The_ith(this,minid)->x1, The_ith(this,minid)->y1);
                        T += Manhatten(ts,A);
                        ts = A;
                         The_ith(this,minid)->reach=1;
                    }                 
            }
    }
    
    //计算现在路径的时间 
    T = sysclock;
    T += Path._size; 
	
	//交换现在的路径和原来的路径 
    List transition = Path;
    OldPath = Path; 
    Path = transition;
	cnt = cnt-1;
    The_ith(this,cnt)->nextmenu=NULL;//从waitlist里面删除newmenu
    return T;
    
}

//对于时间不够的订单 不能按照上述条件来做.
void Rider::generfunc(point* Now,struct menu* now,int disx,int disy,int idx,int idy,int T)
{
	if(!Graph[Now->x][Now->y+2])//可以先走y就先走y 
		{
			if(disy%8==0)//y方向距离是8的倍数 
			{
				if(disx==0)
					for(int dy=0;dy<=disy;dy+=8)
						{
							ListNode* temp = new ListNode(Now->x,Now->y+dy*idy,T++);
							Path.InsertAsl(temp);
						}
				else{
					int dy;
						for(dy=0;dy<=disy-8;dy+=8)
						{	
							ListNode* temp = new ListNode(Now->x,Now->y+dy*idy,T++);
							Path.InsertAsl(temp);
						}
					Now->y = Now->y+dy*idy-4*idy;//
						for(int dx=2;dx<=disx;dx+=4)
						{
		
							ListNode* temp = new ListNode(Now->x+dx*idx,Now->y,T++);
							Path.InsertAsl(temp);
						}
						ListNode* temp = new ListNode(now->x1-2*idx,now->y1,T);//-2?+2
						Path.InsertAsl(temp);
					}
				//骑手在房子上面
				//骑手沿y方向走到最远的路口 然后走disx 然后再走剩下的disy
			}
			else//y方向的距离不是8的倍数
			{
				int dy=0;
				T = sysclock;
				for(dy=0;dy<=(disy/8)*8;dy+=8)
					{
						ListNode* temp = new ListNode(Now->x,Now->y+dy*idy,T++);
						Path.InsertAsl(temp);
					}
				Now->y=Now->y+(dy-4)*idy;
				for(int dx=2;dx<=disx;dx+=4)
					{
						ListNode* temp = new ListNode(Now->x+dx*idx,Now->y,T++);
						Path.InsertAsl(temp);
					}
				//走到最后一个路口，走完disx 
			} 
	    }
	else//不可以先走y 那就先走x
		{//类似的将上一段的y换成x 
			if(disx%4==0)//x方向距离是4的倍数 
			{
				//骑手在房子右边 
				if(disy==0)
					for(int dx=0;dx<=disx;dx+=4)
						{
							ListNode* temp = new ListNode(Now->x+dx*idx,Now->y,T++);
							Path.InsertAsl(temp);
						}
				else{
					int dy;
						for(dy=0;dy<=disy-8;dy+=8)
						{
							ListNode* temp = new ListNode(Now->x,Now->y+dy*idy,T++);
							Path.InsertAsl(temp);
						}
					Now->y = Now->y+dy*idy-4*idy;
						for(int dx=2;dx<=disx;dx+=4)
						{
							ListNode* temp = new ListNode(Now->x+dx*idx,Now->y,T++);
							Path.InsertAsl(temp);
						}
						ListNode* temp = new ListNode(now->x1-2*idx,now->y1,T);
						Path.InsertAsl(temp);
					}
				//骑手沿x方向走到最远的路口 然后走disy 然后再走剩下的disx
			}
			else//x方向的距离不是4的倍数
			{
				int dx=0;
				T = sysclock;
				for(dx=0;dx<=(disx/4)*4;dx+=4)
					{
						ListNode* temp = new ListNode(Now->x+dx*idx,Now->y,T++);
						Path.InsertAsl(temp);
					}
				Now->x=Now->x+(dx-2)*idx;
				for(int dy=4;dy<=disy;dy+=8)
					{
						ListNode* temp = new ListNode(Now->x,Now->y+dy*idy,T++);
						Path.InsertAsl(temp);
					}
				//走到最后一个路口，走disy 走完剩下的disx
			} 
		}
}

void Rider::GeneratePath(point* Now,struct menu* now, int T)
{
	int Nowx = this->x;
    int Nowy = this->y;//取出骑手的坐标 
    point* ts = new point(Nowx,Nowy);//构造骑手point 
	srand(time(NULL));
	int disx,disy;
	if(!now->get)
		{
			if(Now->x<now->x1)//在上方 
				{
					if(Now->y<now->y1)//在左上方 
						{
						 // 向右向下走 
					      double probablity = rand() % (N + 1) / (float)(N + 1);
					       if(probablity<0.5) //走A  
							{
								point* A1 = new point(now->x1-2,now->y1);
								int disx = Calcux(ts,A1);
								int disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,1,1,T);							
							}
						   else //走B 
							{
								point* A2 = new point(now->x1,now->y1-4);
								int disx = Calcux(ts,A2);
								int disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,1,1,T);
							}
						}
				
					else if(Nowy==now->y1)//在正上方 
					 	{
					 		int id=1;
					 		ListNode* temp = new ListNode(Now->x,Now->y,T++);
					 		Path.InsertAsl(temp); 
					 		point* A1 = new point(now->x1,now->y1-4);
					 		disx = Calcux(ts,A1);
							disy = Calcuy(ts,A1);
							for(int dx=2;dx<=disx;dx+=4)
								{
									ListNode* temp = new ListNode(Now->x+dx*id,Now->y-4,T++);
									Path.InsertAsl(temp);
								}
							ListNode* tmp = new ListNode(now->x1,now->y1,T);
							Path.InsertAsl(tmp);
						 }
						 
					else if(Now->y<now->y1)//在右上方 
						{
							double probablity = rand() % (N + 1) / (float)(N + 1);
							if(probablity<0.5)
							{
								point* A1 = new point(now->x1-2,now->y1);
								disx = Calcux(ts,A1),disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,1,-1,T);
							}
							else
							{
								point* A2 = new point(now->x1,now->y1+4);
								disx = Calcux(ts,A2),disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,1,-1,T);
							}
						}
				}
			else if(Now->x==now->x1){
				int id;
				if(Now->y<now->y1) //正左方 
					id=1;
				else
					id=-1;//正右
				ListNode* temp = new ListNode(Now->x,Now->y,T++);
				Path.InsertAsl(temp);
		 		point* A1 = new point(now->x1,now->y1-4*id);
		 		disx = Calcux(ts,A1);
				disy = Calcuy(ts,A1);
				for(int dy=4;dy<=disy;dy+=8)
					{
						ListNode* temp = new ListNode(Now->x-2,Now->y+dy*id,T++);
						Path.InsertAsl(temp);
					}
				ListNode* tmp = new ListNode(now->x1,now->y1,T);
				Path.InsertAsl(tmp);
			} 	
			else if(Now->x>now->x1){//在下方 
					if(Now->y<now->y1)//左下方 
						{
						 double probablity = rand() % (N + 1) / (float)(N + 1);
					       if(probablity<0.5) 
							{
								point* A1 = new point(now->x1+2,now->y1);
								disx = Calcux(ts,A1),disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,-1,1,T);
							}
						   else
							{
								point* A2 = new point(now->x1,now->y1-4);
								disx = Calcux(ts,A2),disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,-1,1,T);
							}
						}
					else if(Now->y==now->y1){//正下方 
						int id=-1;
					 		ListNode* temp = new ListNode(Now->x,Now->y,T++);
					 		Path.InsertAsl(temp);
					 		point* A1 = new point(now->x1,now->y1-4);
					 		disx = Calcux(ts,A1);
							disy = Calcuy(ts,A1);
							for(int dx=2;dx<=disx;dx+=4)
								{
									ListNode* tmp = new ListNode(Now->x+dx*id,Now->y-4,T++);
									Path.InsertAsl(tmp);
								}
							ListNode* tmp = new ListNode(now->x1,now->y1,T);
							Path.InsertAsl(tmp);
					}
					else if(Now->y>now->y1)//右下方 
						{
							double probablity = rand() % (N + 1) / (float)(N + 1);
							if(probablity<0.5)
							{
								point* A1 = new point(now->x1+2,now->y1);
								disx = Calcux(ts,A1),disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,-1,-1,T);
							}
							else
							{
								point* A2 = new point(now->x1,now->y1+4);
								disx = Calcux(ts,A2),disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,-1,-1,T);
							}
						}
					}
		}
		
	else if(now->get && !now->reach){
				if(Now->x<now->x2)//在上方 
				{
					if(Now->y<now->y2)//在左上方 
						{
						 // 向右向下走 
					      double probablity = rand() % (N + 1) / (float)(N + 1);
					       if(probablity<0.5) //走A  
							{
								point* A1 = new point(now->x2-2,now->y2);
								disx = Calcux(ts,A1);
								disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,1,1,T);		
							}
						   else //走B 
							{
								point* A2 = new point(now->x2,now->y2-4);
								disx = Calcux(ts,A2);
								disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,1,1,T);		
							}
						}
					
					else if(Now->y==now->y2)//在正上方
					 	{
					 		int id=1;
					 		ListNode* temp = new ListNode(Now->x,Now->y,T++);
					 		Path.InsertAsl(temp);
					 		point* A2 = new point(now->x2,now->y2-4);
					 		disx = Calcux(ts,A2);
							disy = Calcuy(ts,A2);
							for(int dx=2;dx<=disx;dx+=4)
								{
									ListNode* tmp = new ListNode(Now->x+dx*id,Now->y-4,T++);
									Path.InsertAsl(tmp);
								}
							ListNode* tmp = new ListNode(now->x2,now->y2,T);
							Path.InsertAsl(tmp);
						 }
						 
					else if(Now->y<now->y2)//在右上方 
						{
							double probablity = rand() % (N + 1) / (float)(N + 1);
							if(probablity<0.5)
							{
								point* A1 = new point(now->x2-2,now->y2);
								disx = Calcux(ts,A1);
								disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,1,-1,T);		
							}
							else
							{
								point* A2 = new point(now->x2,now->y2+4);
								disx = Calcux(ts,A2);
								disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,1,-1,T);		
							}
						}
				}
				
			else if(Now->x==now->x2){
				int id;
				if(Now->y<now->y2)
					id=1;
				else
					id=-1;//正右方 
				ListNode* temp = new ListNode(Now->x,Now->y,T++);
				Path.InsertAsl(temp);
		 		point* A2 = new point(now->x2,now->y2-4*id);
		 		disx = Calcux(ts,A2);
				disy = Calcuy(ts,A2);
				for(int dy=4;dy<=disy;dy+=8)
					{
						ListNode* temp = new ListNode(Now->x-2,Now->y+dy*id,T++);
						Path.InsertAsl(temp);
					}
				ListNode* tmp = new ListNode(now->x2,now->y2,T);
				Path.InsertAsl(tmp);
			}
				
			else if(Now->x>now->x2){//在下方 
					if(Now->y<now->y2)//左下方 
						{
						 double probablity = rand() % (N + 1) / (float)(N + 1);
					       if(probablity<0.5) 
							{
								point* A1 = new point(now->x2+2,now->y2);
								disx = Calcux(ts,A1);
								disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,-1,1,T);		
							}
						   else
							{
								point* A2 = new point(now->x2,now->y2-4);
								disx = Calcux(ts,A2);
								disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,-1,1,T);		
							}
						}
					else if(Now->y==now->y2)//在正下方
					 	{
							int id=-1;
					 		ListNode* temp = new ListNode(Now->x,Now->y,T++);
					 		Path.InsertAsl(temp);
					 		point* A2 = new point(now->x2,now->y2-4);
					 		disx = Calcux(ts,A2);
							disy = Calcuy(ts,A2);
							for(int dx=2;dx<=disx;dx+=4)
								{
									ListNode* tmp = new ListNode(Now->x+dx*id,Now->y-4,T++);
									Path.InsertAsl(tmp);
								}
							ListNode* tmp = new ListNode(now->x2,now->y2,T);
							Path.InsertAsl(tmp);
						 }
					else if(Now->y>now->y2)//右下方 
						{
							double probablity = rand() % (N + 1) / (float)(N + 1);
							if(probablity<0.5)
							{
								point* A1 = new point(now->x2+2,now->y2);
								disx = Calcux(ts,A1);
								disy = Calcuy(ts,A1);
								generfunc(Now,now,disx,disy,-1,-1,T);		
							}
							else
							{
								point* A2 = new point(now->x2,now->y2+4);
								disx = Calcux(ts,A2);
								disy = Calcuy(ts,A2);
								generfunc(Now,now,disx,disy,-1,-1,T);		
							}
						}
					}
		}
	//如果现在骑手的左边右边是墙 那么他应该先走x方向
	//反之，那么他应该先走y方向
	//然后看一下现在位置和目标坐标的差  disx为x方向的差 disy为y方向的差
	//如果 disy%4==0 说明要么他走直线 要么他就会在路口处拐弯 (差别在于disx 等不等于0)
	//如果 disx%8==0 说明要么他竖着走 要么就会拐弯// 这个在于 如果先走的是y方向 那么disx应该要么=0 要么绝对不会是4的倍数 
}

void Rider::AddTOWaitlist(struct menu* newmenu)//将新的订单添加进waitlist 
{
	Path = OldPath; //OldPath是当时假设有此单时算出的路径，这时真的有了这一单，直接用OldPath覆盖Path 
}
