#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"


//  �Ѳ麯���� n�������ҵ�����
sgr* search_tsb(int n, rbt* t) 
{
	if (t)
	{
		if (n == t->n)
		{
			//printf("����ֵ�Ѿ�����\n");
			return NULL;
		}
		else
		{
			sgr* s = NULL;

			if (n < t->n)//С��
			{
				if (t->le)
				{
					s = search_tsb(n, t->le);
					return s;
				}
				else
				{
					if (t->c == 1)//�ڽ��
					{
						s = (sgr*)malloc(sizeof(sgr));
						s->bt = t;
						s->n = 1;
						s->t = 1;
						return s;
					}
					else//����
					{
						s = (sgr*)malloc(sizeof(sgr));
						s->bt = t->tf;
						s->n = 2;
						s->t = 1;
						return s;
					}
				}
			}
			else//����
			{
				if (t->ri)
				{
					s = search_tsb(n, t->ri);
					return s;
				}
				else
				{
					if (t->c == 1)//�ڽ��
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
					else//����
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
		printf("һ�ſ���\n");
		return NULL;
	}
}


//ɾ�������Ѳ麯��
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
