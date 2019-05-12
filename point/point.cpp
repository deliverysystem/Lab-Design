#include "point.h" 
#include "tools.h" 
#include <cstdio> 
#include <iostream>

void point::clear(){
	setCursorPosition(x,y);
	std::cout<<" "; 
};

void point::PrintRider(){
	setCursorPosition(x,y);
	std::cout<<"*";
};

void point::PrintCanteen(){
	setCursorPosition(x,y);
	std::cout<<"------"<<endl;
	std::cout<<"|餐厅|"<<endl;
	srd::cout<<"------";
	setCurSorPosition(x,y);
}

void point::PrintResidence(){
	setCursorPosition(x,y);
	std::cout<<"------"<<endl;
	std::cout<<"|住所|"<<endl;
	srd::cout<<"------";
	setCurSorPosition(x,y);
}
