#pragma once
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>

/*	
	我这里实现的是严重左倾红黑树 ，其演变自2 - 3树，因而该红黑树的操作原理也是套用2 - 3树的
	由于红黑树的左倾和右倾 都可以表示 2-3树的3结点，所以同一序列的数字对应生成的红黑树的结构不是唯一的
	其实红黑树有 左倾红黑树和右倾红黑树（这两个是结合2-3-4树原理的 ）、 变态AA树 、这是严重右倾红黑树（我这里的是严重左倾，结合2-3树的原理 ）
	我水平有限，这里仅是红黑树模型的代码实现，并且有很多不足之处，希望得到批评
*/
#define nothing -1234567
#define num_range RAND_MAX

//大容量工具树结点
#define u_tree_n 4
#define u_tree_p 5


//红黑树单个结点的结构
struct rbtree
{
	//主体
	int n;							//数据域
	rbtree* le;					//左孩子
	rbtree* ri;					//右孩子
	int c;							//颜色   0->red    1->black

	/*
		以下这些数据都是用于管理树形平衡的重要信息，因为我是完全模仿2 - 3树形的方法来管理红黑树的

		内存上的优化：
			可以将下面数据打包成一个结构体A，再使A的内存对齐尽量压缩，每个结点通过给予一个A类型的指针PA，来获取所需信息。
			由于每个结点都需要A类数据的信息，所以可以将A类数据用链表管理，每个结点将通过PA找到与之对应的信息，如此树形的整体结构将变得轻便。
		不过个人觉得这种改动是不痛不痒的。

		其次如果你真的想看懂我的代码是如何工作的，那将是我的不胜荣幸，不过建议你先观理解我  2-3 b 树的代码工作原理，否则我的代码将为你带来无尽的痛苦和愤怒
		同时这是我初学者时的代码风格，变量命名极其丑陋，晦涩难懂
		并且由于最初的粗心大意，这里处理的所有数据都是  int  类型，所以这里只是一个很简易的模型

	*/

	int tn;							//对应2-3树的结点类型  1即2结点  2即3结点
	rbtree* tf;					//本结点之父亲
	int k_tf;						//模仿2-3树的功能（本结点在其父亲的指针数组的下标）方便我判断  ----> 0   1  -1 nothing

	//参数
	int bn;							//以给结点为根的子树，其黑结点的总个数-->类似于 b树的深度
	int b;							//作为子树时提供的平衡参数
};
typedef rbtree rbt;

//红黑树之主体
struct arbtree
{
	rbt* rp;						//树的牵引

	int an;							//结点总数  （最后还是没有用上）
};
typedef arbtree arb;

/*
	23树层次遍历 ( 少用一个元素计数型队列）即可用空间元素为cp-1个
	其作用是将红黑树形打印的尽量可视化一点
*/
struct queue_rbt
{
	rbt** base;//队列主体
	int cp;

	int front;//队头
	int rear;//队尾

};
typedef queue_rbt que_r;

//查找返回数据
struct search_getr
{
	rbt* bt;//数据所在结点

	int n;//数据插入结点的类型

	int t;//对应种类
};
typedef search_getr sgr;
//结点分裂所得
struct break_outr
{
	int n;//数据值

	rbt* le;//左小
	rbt* ri;//右大

	rbt* in;//欲插结点   //主节点一定是黑色的

	int tn;//数据插入结点的类型

	int t;//对应形成结构的种类

};
typedef break_outr bor;
//合并结点容器
struct combine_many_tsbr
{
	//主体
	int* nrr;//数据域
	rbt** tsrr;//孩子指针域
	int tn;//关键字个数

	rbt* tf;//本结点之父亲
	int k_tf;//本结点在其父亲的指针数组的下标

	//参数
	int bn;//黑孩子个数  深度
};
typedef combine_many_tsbr cmtr;

//叶子结点分析删除类型 便于后续重组 返回信息
struct DS
{
	rbt* bt;//删除结点所在子树或是删除结点本身

	int* arr;//重组序列

	int bn;//重组前左右子树的黑色结点个数
};
typedef DS ds;



//函数合集

//给一个结点分配空间
rbt* make_rbt_one();
//给一个合并结点容器分配空间
cmtr* make_cmtr_one();


//插入辅助函数 搜查
sgr* search_tsb(int n, rbt* t);//n是欲查找数值  
//操作一：融合 不合规返回不合规结点
cmtr* mix_rb(bor* b, arb* a);
//分裂函数的附属：确定插入类型   解决bor的 in tn t 的填充
void get_ture_bo(bor* b, rbt* tf, int k_tf);
//操作二：分裂 返回中间结点的信息
bor* brea_out_rb(cmtr* s, arb* a);
//新插入数值n
void input_rbt(arb* a, int n);


//打印函数
//层次遍历
void make_queue_rbt(que_r* qt, int k, int num);//0是给予初始num元素队列  1是扩容num元素的队列
void level_printf_rbt(rbt* t, int n);
//正确性的检查
//遍历排查和计数
int D_rbt(rbt* t, int* r, int* be);
int check_rbt_ture(arb* a);//全符合返回0 全不符合返回 245


//删除辅助搜查函数
rbt* search_d_tsb(int n, rbt* t);
//非叶子结点推卸函数
rbt* shirk_tsb(rbt* s);
//遍历子树获取删除后序列
void D_ctree(rbt* t, int* arr, int* i);
//遍历销毁子树
void delete_ctree(rbt* t);
//根据提供的叶子结点 分析出子树的类型 然后对应哪种删除方案
ds* get_d_t(rbt* s);
//重组子树函数
arb* rebuild(int* arr);

//标记函数 标记各个子树的黑节点值
void D_d(rbt* t);
//检查平衡性 并返回不平衡子树
rbt* check_balance(rbt* t);
//寻找那个合适的地方与父亲合并
int find_who(rbt* t);

//大容量版  合并和分裂操作
cmtr* mix_better_rbt(rbt* t, int tm);//返回合并器         t是问题子树的根  n是根与第n个孩子合并
rbt* break_better_rbt(cmtr* c, arb* a);
//红黑树回溯大法 提供起点问题子树 修好后 回溯到上一级 以此方式一直向上回溯 直至根结点
void reback_arb(arb* a, rbt* t);
//删除函数
void delete_rbt(arb* a, int n);







