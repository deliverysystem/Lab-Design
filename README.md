# Lab-Design
## 《程序设计课程设计》实验报告
### 《外卖派单系统程序设计》概要设计<v1.0>


#### 一、用户界面设计[待定]
##### 1.1 用户界面
[图片,布局说明; 若有多种界面,请逐一说明]
##### 1.2 操作元素和操作效果
[操作元素图片]
[操作的上下文描述]
[操作后显示效果图片]
#### 二、高层数据结构设计
(包括：重要的数据常量定义、数据变量定义，即各模块要共享的数据类型和参数设计，相当于头文件内容，加文字描述)
##### 2.1全局常量/变量定义
	int sysclock;//系统时间变量
	int money;//金钱变量
	typedef struct menu{
			int x1;//骑手接餐地址横坐标
			int y1;//骑手接餐地址纵坐标
			int x2;//骑手送餐地址横坐标
			int y2;//骑手送餐地址纵坐标	
			int deadline;//这一单截止的时间 
			int *p;//指向骑手的指针
		
		}Menu;
	typedef struct rider{
		int exist;//判断该骑手存在 
		int x;//骑手当前位置横坐标
		int y;//骑手当前位置纵坐标
		int t1;//骑手这一单截止时间
		int receive;//骑手的接单数
		int achieve;//骑手的完成数 
		int overtime;//骑手超时数 
			Rider whichone();//分配订单函数
	}Rider;
##### 2.2 模块常量与变量定义
###### Tools.h文件中
	int cols//窗口长度
	int lines//窗口宽度
	int x, const int y//光标位置
###### Point.h文件中
	int x,y;//Point 的坐标
	Map.h文件中
	int x,y;//map中某像素点的坐标
	int Graph[60][60];//用于记录某个位置是餐厅还是住所 餐厅为1,住所为0
###### Rider.h文件中
	int x;//骑手当前位置横坐标
	int y;//骑手当前位置纵坐标
	int deadline //骑手这一单截止时间
	int receive;//骑手的接单数
	int achieve;//骑手的完成数
	int overtime;//骑手超时数
###### Menu.h文件中
	int x1;//骑手接餐地址横坐标
	int y1;//骑手接餐地址纵坐标
	int x2;//骑手送餐地址横坐标
	int y2;//骑手送餐地址纵坐标
	int deadline//这一单截止的时间 
###### Message.h文件中
	int money; //当前钱数
	rider location[];//每位骑手的位置
	int sum;// 接单数
	int accomplish;// 完成数
	int overtime;//超时数


#### 三、系统模块划分
 
##### 3.1模块功能简要描述及各模块函数说明：
	 ![1](https://github.com/deliverysystem/Lab-Design/blob/master/pic/1.png)
###### Step1.tools.h
	 1、	设置窗口大小函数
		void SetWindowSize(int cols, int lines);
	 2、	光标定位函数（用于打印房屋，骑手）
		void SetCursorPosition(int x, const int y)；
	 3、	颜色控制函数（用于突出地图上骑手的出发点）
		void SetBackColor();
###### Step2.point.h

	 1、打印一个房屋图案函数  ！！！
 		void PrintCanteen();//point的坐标为x,y 则打印出一个以左上角为(x,y)
		调用方法 point->PrintCanteen();
		房子中间至少要能放入两个汉字                          ------
		现在假设道路占3个				   |餐 厅|
 		void PrintResidence();//同理                        ------  如此规格的房屋
	 2、打印一个骑手图案函数
		void PrintRider()  用法 point->PrintRider()
												暂时设计的是打印一个*
	 3、清除输出功能函数（用于消灭上一时间骑手的图案）
		void clear() 用法 point->clear() ;
	 4、改变位置函数
		void changeposi(int fx,int fy);
###### Step3.map.h
	 1、打印地图函数（需用到point与tools的头文件）
		void init();
###### Step4.rider.h
	 1、	定义结构体数组（有多个骑手，rider[i]=1,没有则rider[i]=-1,从0开始代表第一个骑手，以此类推）rider ：

		int x;//骑手当前位置横坐标
		int y;//骑手当前位置纵坐标
		int deadline //骑手这一单截止时间
		menu订单结构体数组
		{int x1;//骑手接餐地址横坐标
		int y1;//骑手接餐地址纵坐标
		int x2;//骑手送餐地址横坐标
		int y2;//骑手送餐地址纵坐标
		 int deadline//这一单截止的时间 }

	Rider WhichOne()判断哪位骑手接单的函数
		包括：判断是用现有骑手接还是新雇佣骑手接单。 
	 a.若现有骑手接单是否要改变其运动范围。
  	 b.要新骑手接则添加新骑手
	//暴力计算找出每位骑手的耗时，让路径最短的骑手接之后传入rider文件中的函数进行操作。
	int *p//指向骑手的指针
	}
	a.	骑手行驶路径的算法函数
	void CalculatePath(Menu waitlist)
	（计算出行驶路径存储在骑手结构体的行驶路线中）
	a.	计算出最短路径
	b.	改变骑手结构体中的行驶路线//有可能只需要在原路径上加长，也有可能会销毁原来路径，产生一条新的路径
	c.	创建链表存储骑手的行驶路线（链表中每个单元的结构包含一个点的坐标）。//创建链表函数单独写
	List Path;
	h.骑手的接单数
	i.骑手的完成数
	j.骑手的超时数
	k.如若需要圈定骑手的运动范围，也可将骑手的运动范围添加在结构体里。
	}
	1、打印每位骑手的接单数、完成数、超时数的函数。
		//为破产考虑，若破产则需用到此函数
###### Step5.menu.h
	1.
	int x1;//骑手接餐地址横坐标
	int y1;//骑手接餐地址纵坐标
	int x2;//骑手送餐地址横坐标
	int y2;//骑手送餐地址纵坐标
	int deadline//这一单截止的时间 
	2.
	Rider WhichOne()判断哪位骑手接单的函数
		包括：判断是用现有骑手接还是新雇佣骑手接单。 
	a.若现有骑手接单是否要改变其运动范围。
        b.要新骑手接则添加新骑手
	//暴力计算找出每位骑手的耗时，让路径最短的骑手接之后传入rider文件中的函数进行操作。
	3.
	int *p//指向骑手的指针

###### Step6.message.h
	1.定义结构体message//为了存储需要显示在屏幕上的信息
	struct{
		当前钱数 int money;
		每位骑手的位置 rider location[];
		接单数 int sum;
		完成数 int accomplish;
		超时数 int overtime
	}
	2.打印信息的函数（用到tools.h与point.h）。
		void printmessage(message )
###### Step7.controller.h
	void start()
	1、“判断当前是否破产”函数
  	/若破产执行rider文件中的函数void bankruptcy(int money) 需要传入message中的money
	2、控制骑手移动的函数
	判断出骑手下一刻的坐标 //通过访问rider的数组或链表的当前位置的下一个位置
	删去骑手原来时刻的图案，在新坐标下打印骑手图案
	void printmove(rider a[],int size)
	需要传入骑手结构体和骑手当前的个数（即骑手数组的大小）
##### 3.2函数调用图示及说明
	 ![2](https://github.com/deliverysystem/Lab-Design/blob/master/pic/2.png)
 
##### 函数调用关系图说明：
1、main调用start,程序开始运行。
2、start首先调用init,打印地图。为了实现打印地图，init内再调用SetWindowSize、SetBackColor、SetCursorPosition、PrintCanteen、PrintRider五个函数。
3、打印地图完毕后，进入循环。start内调用bankruptcy判断是否破产，若破产调用performance按要求打印信息，跳出循环。
4、接着start调用WhichOne,判断哪位骑手接单，并调用CalculatePath修改骑手路径。
5、然后start调用printmove实现骑手的位置移动，需要调用clear清除骑手原位置，需要调用changeposi确定骑手现在位置，需要调用PrintRider在现位置上打印一个骑手图案。
6、最后start调用Printmessage打印当前信息。（当前钱数、每位骑手的位置、接单数、完成数、超时数）
7、其中PrintRider、PrintCanteen、Printmessage三个打印的函数都需要确定光标位置来确定打印位置，故都调用SetCursorPosition。


#### 四、高层算法设计
	 ![3](https://github.com/deliverysystem/Lab-Design/blob/master/pic/3.png)
