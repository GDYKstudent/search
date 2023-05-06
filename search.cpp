#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"


//  搜查函数， n是欲查找的数据
sgr* search_tsb(int n, rbt* t) 
{
	if (t)
	{
		if (n == t->n)
		{
			//printf("插入值已经存在\n");
			return NULL;
		}
		else
		{
			sgr* s = NULL;

			if (n < t->n)//小于
			{
				if (t->le)
				{
					s = search_tsb(n, t->le);
					return s;
				}
				else
				{
					if (t->c == 1)//黑结点
					{
						s = (sgr*)malloc(sizeof(sgr));
						s->bt = t;
						s->n = 1;
						s->t = 1;
						return s;
					}
					else//红结点
					{
						s = (sgr*)malloc(sizeof(sgr));
						s->bt = t->tf;
						s->n = 2;
						s->t = 1;
						return s;
					}
				}
			}
			else//大于
			{
				if (t->ri)
				{
					s = search_tsb(n, t->ri);
					return s;
				}
				else
				{
					if (t->c == 1)//黑结点
					{
						if (t->le == NULL)
						{
							s = (sgr*)malloc(sizeof(sgr));
							s->bt = t;
							s->n = 1;
							s->t = 2;
							return s;

						}
						else
						{
							s = (sgr*)malloc(sizeof(sgr));
							s->bt = t;
							s->n = 2;
							s->t = 3;
							return s;

						}
					}
					else//红结点
					{
						s = (sgr*)malloc(sizeof(sgr));
						s->bt = t->tf;
						s->n = 2;
						s->t = 2;
						return s;

					}
				}

			}




		}
	}
	else
	{
		printf("一颗空树\n");
		return NULL;
	}
}


//删除辅助搜查函数
rbt* search_d_tsb(int n, rbt* t)
{
	if (t)
	{
		if (t->n == n)
			return t;

		if (!t->le && !t->ri)
			return NULL;
		else
		{
			if (n < t->n)
				return search_d_tsb(n, t->le);
			else
				return search_d_tsb(n, t->ri);
		}
	}
	else
		return NULL;
}
