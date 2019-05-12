#ifndef RIDER_H
#define RIDER_H
#include "tools.h"
#include "point.h"
#include "menu.h"

using namespace std;

class Rider{
  private:
    int x,y;
    int t1;
    List<Menu> waitlist;
    int finishednum;
    int unfinishednum;
    int total;
    //运动范围;

  public:
    Rider() {}
    Rider(int x,int y):x(x),y(y);
    void CalculatePath();
    void PrintState();
    ~Rider() {}

}

#endif //RIDER_H