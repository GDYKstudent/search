#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"

//打印函数

//层次遍历
void make_queue_rbt(que_r* qt, int k, int num)//0是给予初始num元素队列  1是扩容num元素的队列
{
	rbt** g = NULL;
	int lcp = qt->cp;
	int nf = 0, nr = 0;
	int i = 0;

	if (k)//1即是扩容
	{
		qt->cp = qt->cp + num;
		g = (rbt**)malloc(sizeof(rbt*) * qt->cp);
		int i = 0;
		//元素出队到新的队列
		while (1)
		{
			g[i] = qt->base[qt->front];
			qt->front = (qt->front + 1) % lcp;
			if (qt->front == qt->rear)
				break;
			i++;
		}
		i++;
		free(qt->base);
		qt->rear = i;
		qt->front = 0;
		qt->base = g;
	}
	else//初始化
	{
		qt->cp = num;
		qt->base = (rbt**)malloc(sizeof(rbt*) * qt->cp);
		for (i = 0; i < qt->cp; i++)
			qt->base[i] = NULL;
		qt->front = 0;
		qt->rear = 0;
	}
	return;

}
void level_printf_rbt(rbt* t, int n)
{
	if (t)
	{
		//初始化队列
		que_r q;
		rbt* r = NULL;

		make_queue_rbt(&q, 0, 10);
		q.base[0] = t;
		q.rear = (q.rear + 1) % q.cp;
		int i = 0;
		int level = 0;

		int kr = 0, kf = 0, c = 0;
		rbt* t1 = NULL;
		printf("所含数据量:  %d\n", n);
		while (1)
		{
			//打印队列全部内容
			level++;
			//printf("第%d层:", level);
			t1 = q.base[0];
			if (level == 1)
				printf("%d(%d,%d,%d)\n", t1->n, t1->bn, t1->b, t1->c);
			kr = q.rear, kf = q.front, c = q.cp;
			while (kf != kr)
			{
				t1 = q.base[kf];
				if (t1->le || t1->ri)
				{
					if (t1->le)
						printf("%d(%d,%d,%d) ", t1->le->n, t1->le->bn, t1->le->b, t1->le->c);
					printf("  ");
					if (t1->ri)
						printf("%d(%d,%d,%d) ", t1->ri->n, t1->ri->bn, t1->ri->b, t1->ri->c);
				}
				//printf("<%d>", t1->cn + t1->tn);
				printf("---");
				kf = (kf + 1) % c;
			}

			printf("\n");

			//挑选入队
			r = q.base[(q.rear - 1) % q.cp];
			while (1)
			{
				t1 = q.base[q.front];
				if (1)
				{
					if (t1->le)
					{
						q.base[q.rear] = t1->le;
						q.rear = (q.rear + 1) % q.cp;
					}
					if (t1->ri)
					{
						q.base[q.rear] = t1->ri;
						q.rear = (q.rear + 1) % q.cp;
					}

					//可能需要扩容
					if ((q.rear + 2) % q.cp == q.front)
						make_queue_rbt(&q, 1, 10);

				}

				q.front = (q.front + 1) % q.cp;
				if (q.base[q.front - 1] == r)
					break;
			}
			//队列为空 直接结束
			if (q.front == q.rear)
				break;
		}
		return;
	}
	else
		printf("空树警告！！！！\n\n");

	return;
}

//遍历子树，获取删除后序列
void D_ctree(rbt* t, int* arr, int* i)
{
	if (t)
	{
		if (t->le)
			D_ctree(t->le, arr, i);
		arr[*i] = t->n;
		printf(" %d", t->n);
		*i = *i + 1;
		if (t->ri)
			D_ctree(t->ri, arr, i);
		return;
	}
	return;
}












//正确性的检查
//遍历排查和计数
int D_rbt(rbt* t, int* r, int* be)
{
	if (t)
	{
		if (t->c == 0)
		{
			if (t->le)
				if (!t->le->c)
					*r = 1;
			if (t->ri)
				if (!t->ri->c)
					*r = 1;
		}
		if (!t->le && !t->ri)
		{
			t->b = 0;
			t->bn = t->c;
			return 1;
		}
		else
		{
			int lebn = 0;
			int ribn = 0;
			int len = 0;
			int rin = 0;
			int sum = 0;
			if (t->le)
			{
				len += D_rbt(t->le, r, be);
				lebn = t->le->bn;
			}
			if (t->ri)
			{
				rin += D_rbt(t->ri, r, be);
				ribn = t->ri->bn;
			}
			if ((lebn != ribn) && lebn && ribn)
			{
				t->b = 1;
				if (lebn > ribn)
					t->bn = lebn;
				else
					t->bn = ribn;
				*be = 1;
			}
			else
			{
				t->b = 0;
				if (lebn)
					t->bn = lebn;
				else
					t->bn = ribn;
			}
			if (t->c)
				t->bn++;
			return (len + rin + 1);

		}
	}
	else
		return 0;
}
int check_rbt_ture(arb* a)//全符合返回0 全不符合返回 245
{
	//红黑树定义：
	//1.每个结点不是黑就是红   2.根结点是黑的      3.最后的叶子结点的孩子们都是黑色的
	//4.如果一个结点是红色的那么他的孩子就一定是黑色的
	//5.从任意一个结点出发到叶子结点所经历的黑色结点是一样的

	//其实 1 3 这两个条件是理所当然的 就不用考虑了
	int red = 0, bn_equel = 0;
	a->an = D_rbt(a->rp, &red, &bn_equel);
	printf("红黑树正确性检测--->");
	if (a->an)
	{
		int error = 0;
		//2
		if (a->rp->c == 0)
		{
			error += 200;
			printf("根节点是红的！！！！\n");
		}
		//4 5

		//判断
		if (red)
		{
			printf("违背条件4：如果一个结点是红色的那么他的孩子就一定是黑色的，不符合\n");
			error += 40;
		}
		if (bn_equel)
		{
			printf("违背条件5.从任意一个结点出发到根结点所经历的黑色结点是一样的，不符合\n");
			error += 5;
		}

		if (!error)
			printf("红黑树合格!!!!\n");

		return error;

	}
	else
		printf("是一棵空树\n");
}
