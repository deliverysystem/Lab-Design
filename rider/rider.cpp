#include "rider.h"
#include "menu.h"
#include "controller.h"
#define INF 0x3f3f3f3f
#define The_ith(this,i) waitlist[i];
//#define The_ith(this,minid) waitlist[minid];
//#define The_ith(this,cnt) waitlist[cnt];

//������ֵ�this ��ָ��ǰrider ��һ��ָ��

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
//T ��Ҫ��� 
    if(!now->get)
     {
            int disx = abs(Now->x-now->x1);
            int disy = abs(Now->y-now->y1);
                int Length = disx + disy;
                        //���ϻ�������
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
                        //����������
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
                	    //���ϻ������� 
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
                        // �����TҪ�� 
                        //����������
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
    OldPath=Path;//�Ȱ����ڵ�·�������� 
    Path.clear();//���·�� 
    int Nowx = this->x;
    int Nowy = this->y;//ȡ�����ֵ����� 
    point* ts = new point(Nowx,Nowy);//��������point 
    
    //���㶩���� 
    struct menu* temp = waitlist;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        temp = temp->nextmenu;
    }
    
    waitlist[cnt].nextmenu=newmenu;//�Ȱ��¶����������� 
    cnt+=1;//������+1 
    
    int T = sysclock;
    if(cnt==1) {
	    GeneratePath(ts,newmenu,T);
	    //��ȡ��
	    point* A = new point(waitlist[1].x1, waitlist[1].y1);
	     T += Manhatten(ts,A);
             ts = A;
            waitlist[1].get=1;
	    //���Ͳ�
	    GeneratePath(ts,newmenu,T);
	    point* B = new point(waitlist[1].x2, waitlist[1].y2);
	    T += Manhatten(ts,B);
            ts = B;
            waitlist[1].reach=1;
    }//ֻ���¼���Ķ���һ���� 
	
	
	// �������һ������ȷ��֮�� ������Ķ������Ѿ���������ˣ����ǲ�һ�������Ѿ�ȡ���˲ͣ�������Ҫ��һ���Ѿ�ȡ���͵Ķ��� ,Ҳ����˵����Ҫ��������û�е����ĵ�ʹ��ʱ����̲���ÿ���㰴ʱ����
    else if(cnt>1){
        //����֪��Ŀǰ����Щ���������Ѿ�ȡ������ ������m �� ��ô 2*n-m��Ϊʣ�µĵ��� ���� n-m�������͹� ֻ���ȵ�����n-m���� ���ܵ����Ӧ��Ŀ��
        for(int i=1;i<=2*cnt;i++)
            {	
                //�����пɴ�ĵ� ����Сֵ Ȼ�����Path���� ,������
                int minid=0;
                int mind=INF;
                for(int i=1;i<=cnt;i++)
                    {
                        if( waitlist[i].get&&!(waitlist[i].reach))//�����Ѿ�ȡ���͵Ķ���
                            {
                            	point* B = new point(waitlist[i].x2, waitlist[i].y2);
                                if(mind<Manhatten(ts,B))
                                    minid = i;
                                mind= min(mind,Manhatten(ts,B));
                            }
                        else if(!(waitlist[i].get)){//����δȡ���Ķ���
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
    
    //��������·����ʱ�� 
    T = sysclock;
    T += Path._size; 
	
	//�������ڵ�·����ԭ����·�� 
    List transition(OldPath);
    OldPath = Path; 
    Path = transition;
	cnt = cnt-1;
    waitlist[cnt].nextmenu=NULL;//��waitlist����ɾ��newmenu
    return T;
    
}

void Rider::AddTOWaitlist(struct menu* newmenu)//���µĶ�����ӽ�waitlist 
{
    struct menu* temp = waitlist;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        temp = temp->nextmenu;
    }
	waitlist[cnt].nextmenu=newmenu;//��newmenu����waitlist
	
	Path = OldPath; //OldPath�ǵ�ʱ�����д˵�ʱ�����·������ʱ���������һ����ֱ����OldPath����Path 
}

//����ʱ�䲻���Ķ��� ���ܰ���������������.

