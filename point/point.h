#ifndef POINT_H
#define POINT_H

class point{
public:
	point(){}
	point(int x,int y): x(x),y(y) {}
	int getX() {return this->x;};
	int getY() {return this->y;};
	void clear();
	void PrintRider();
	void PrintCanteen();//′òó?2íìü
	void PrintResidence();//′òó?×??ù
	void changeposi(int fx,int fy){
		x=fx,y=fy;
	};
	bool operator == (const point & a){
		return (a.x==x)&&(a.y==y);
	};
	~point(){}
	int x,y;
};


#endif 
