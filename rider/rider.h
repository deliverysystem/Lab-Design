#ifndef RIDER_H
#define RIDER_H
#include "tools.h"
#include "point.h"
#include "menu.h"
#include "list.h"

class Rider{
  private:
    int exist;
    int x,y;
    Point A(x,y);
    Menu* waitlist;
    List Path;
    int receive;//骑手的接单数
    int achieve;//骑手的完成数
    int overtime;//骑手超时数

    //运动范围;

  public:
    Point A(int x,int y):x(x),y(y);
    Rider() {}
    Rider(int x,int y):x(x),y(y);
    void CalculatePath(Menu* newlist);
    int Manhatten(Point x,Point y);
    void GeneratePath(Point A,int id);
    void PrintState();
    int AllThingsDone();//返回送完最后一单的时间
    ~Rider() {}
    friend Menu;
}

#endif //RIDER_H
