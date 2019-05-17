#include "point.h" 
#include "tools.h" 
#include <cstdio> 
#include <iostream>
using namespace std;
void point::clear(){
	SetCursorPosition(x,y);
	std::cout<<" "; 
};

void point::PrintRider(){
	SetCursorPosition(x,y);
	std::cout<<"*";
};

void point::PrintCanteen(){
	SetCursorPosition(x,y);
	std::cout<<"-----"<<endl;
	SetCursorPosition(x+1,y);
	std::cout<<"|   |"<<endl;
	SetCursorPosition(x+2,y);
	std::cout<<"-----";
	SetCursorPosition(x,y);
}

void point::PrintResidence(){
	SetCursorPosition(x,y);
	std::cout<<"-----"<<endl;
	SetCursorPosition(x+1,y);
	std::cout<<"|   |"<<endl;
	SetCursorPosition(x+2,y);
	std::cout<<"-----";
	SetCursorPosition(x,y);
}
