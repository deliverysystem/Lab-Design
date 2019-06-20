#ifndef RIDER_H
#define RIDER_H

#include "tools.h"
#include "point.h"
#include "menu.h"
#include "list.h"
#include <graphics.h>
class Rider{
  public:
    int x,y;
    //point A(int a,int b):x(a),y(b) {
    void changeposi(int fx,int fy){
		x=fx,y=fy;
	};
    List Path,OldPath;
    int receive;//楠戞墜鐨勬帴鍗曟暟
    int achieve;//楠戞墜鐨勫畬鎴愭暟
    int overtime;//楠戞墜瓒呮椂鏁?
    PIMAGE Riderimg;
    Rider() {}
    Rider(int x,int y):x(x),y(y) {}
    int exist;
    struct menu* waitlist;
    int CalculatePath(struct menu* newmenu);//璇曠畻閫佸畬鏈€鍚庝竴鍗曠殑鏃堕棿
    int Manhatten(point* x,point* y);
    void GeneratePath(point* A,struct menu*,int t);
    void AddTOWaitlist(struct menu* newmenu);//灏嗘柊鐨勮鍗曟坊鍔犺繘waitlist
    void generfunc(point* Now,struct menu* now,int disx,int disy,int idx,int idy,int T);
    int Calcux(point* A,point* B);
    int Calcuy(point* A,point* B);
    ~Rider() {}
    //friend class Menu;
    friend class point;
    friend class List;
};

#endif
