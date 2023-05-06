#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"

/*
	 删除的本质就是删除掉某个数据之后，那个空缺就找直接前驱或直接后继来替代，
	 以此类推直至所有数据调整完毕

	 树形的全部结点中序遍历出来就是一串有序的数据嘛，中间删去一个，就再最靠近他的左边或是右边
	 将数据补入，以此完成其余数据的调整
*/



//非叶子结点的推卸函数，删除父亲时将删除操作推卸给孩子
rbt* shirk_tsb(rbt* s)
{
	if ((s->tn == 1 && !s->ri && !s->le) || (s->tn == 2 && s->c == 1 && !s->ri) || (s->tn == 2 && s->c == 0 && !s->ri && !s->le))//叶子结点 即2-3树的 2 3 叶子结点的特征
		return s;
	else
	{
		s->n = s->ri->n;
		return shirk_tsb(s->ri);
	}
}

//遍历销毁子树
void delete_ctree(rbt* t)
{
	if (t)
	{
		if (t->le)
			delete_ctree(t->le);
		if (t->ri)
			delete_ctree(t->ri);
		free(t);
	}
	return;
}

//根据提供的叶子结点 分析出子树的类型 然后对应哪种删除方案
ds* get_d_t(rbt* s)
{
	//初始化返回信息
	ds* d = (ds*)malloc(sizeof(ds));
	d->arr = (int*)malloc(sizeof(int) * 6);
	int i = 0;
	for (i = 0; i < 6; i++)
		d->arr[i] = nothing;

	//操作工具
	rbt* t = s->tf;//可能是红结点

	rbt* tb;//兄弟

	if (s->k_tf)//1
		tb = t->le;
	else
		tb = t->ri;

	if (t->tn == 1 && tb->tn == 1)//非1即2  这里是2结点下的满二叉子树穷困状态
	{
		d->arr = NULL;

		//降树高 返回被降子树之父 该子树势必应树高降低导致的不平衡 因而需调整
		tb->c = 0, tb->k_tf = -1, tb->tn = 2, tb->bn = 0,
			t->bn = 1, t->tn = 2, t->ri = NULL;

		if (tb->n > t->n)//在右
		{
			t->le = tb;
			int n = t->n;
			t->n = tb->n;
			tb->n = n;
		}
		free(s);

		d->bt = t->tf;//可能是红色结点也可能是空结点
		if (d->bt)
		{
			if (t->tf->c == 0)
				d->bt = d->bt->tf;
		}
		else
		{
			d->bt = t;
			d->bn = nothing;
		}

	}
	else//除上述之外显然都算是富有的
	{
		//亲父
		if (s->k_tf)//1
			t->ri = NULL;
		else
			t->le = NULL;

		free(s);

		//确立子树主父
		if (t->c == 0)
			t = t->tf;

		d->bt = t;
		d->bn = t->bn;
		i = 0;
		D_ctree(t, d->arr, &i);//获取重组序列
	}
	return d;

}

//输入一段子树的序列后，重组该子树
arb* rebuild(int* arr)
{
	int i = 0;
	arb* in = (arb*)malloc(sizeof(arb));
	in->rp = NULL;
	in->an = 0;
	while (1)
	{
		if (arr[i] == nothing)
			break;
		else
			input_rbt(in, arr[i]);//重组
		i++;
	}
	//检查真确
	check_rbt_ture(in);
	return in;
}

//标记函数 ，标记各个子树的黑节点值
void D_d(rbt* t)
{
	if (t)
	{
		int ri = 0, le = 0;

		if (!t->le && !t->ri)
		{
			if (t->c)
				t->bn = 1;
			else
				t->bn = 0;
			t->b = 0;
		}
		else	//处理非叶子
		{
			//标记左右子树
			if (t->le)
			{
				D_d(t->le);
				le = t->le->bn;
			}
			if (t->ri)
			{
				D_d(t->ri);
				ri = t->ri->bn;
			}
			//分析
			if (ri != le)
			{
				t->b = 1;
				int max;
				if (ri > le)
					max = ri;
				else
					max = le;
				if (t->c)
					t->bn = max + 1;
				else
					t->bn = max;
			}
			else
			{
				t->b = 0;
				if (t->c)
					t->bn = le + 1;
				else
					t->bn = le;
			}
		}
		return;

	}
	else
		return;
}

//检查平衡性 并返回不平衡子树
rbt* check_balance(rbt* t)
{
	int i = 0;
	int n = 0;
	int sum = 0;
	rbt* error = NULL;

	//检查结点的指针域情况 全空-->叶子结点    全不空--->普通结点
	if (t->ri)
		n = 1;
	else
		n = 0;

	if (n)//普通结点 检擦每个孩子的情况
	{
		int max = nothing;
		int b_equal = 0;
		int d_equal = 0;

		//调查 递归查看所有孩子
		if (t->tn == 1)//2结点
		{
			error = check_balance(t->le);//左
			if (error)
				return error;
			else
			{
				error = check_balance(t->ri);//右
				if (error)
					return error;
				else
				{
					//判断深度一致性
					if (t->le->bn == t->ri->bn)
					{
						t->bn = t->le->bn + 1;
						t->b = 0;
					}
					else
					{
						if (t->le->bn > t->ri->bn)
							max = t->le->bn;
						else
							max = t->ri->bn;
						t->bn = max + 1;
						d_equal = 1;
						t->b = 1;
					}
					//判断平衡一致性
					if (!(!t->le->b && !t->ri->b))
						b_equal = 1;
				}
			}
		}
		else//3结点
		{
			error = check_balance(t->le->le);//红左
			if (error)
				return error;
			else
			{
				error = check_balance(t->le->ri);//红右
				if (error)
					return error;
				else
				{
					error = check_balance(t->ri);//黑右
					if (error)
						return error;
					else
					{
						//判断深度一致性
						if (t->le->le->bn == t->ri->bn && t->ri->bn == t->le->ri->bn)//三个地方黑节点都相同
						{
							t->le->bn = t->le->le->bn;
							t->bn = t->le->le->bn + 1;
							t->le->b = 0, t->b = 0;
						}
						else
						{
							max = 0;
							if (max < t->le->le->bn)
								max = t->le->le->bn;
							if (max < t->le->ri->bn)
								max = t->le->ri->bn;
							if (max < t->ri->bn)
								max = t->ri->bn;

							t->bn = max + 1;//主父
							t->le->bn = max;//红
							t->b = 1;
							t->le->b = 1;

							d_equal = 1;
						}
						//判断平衡一致性
						if (!(!t->le->le->b && !t->le->ri->b))
							b_equal = 1;
					}
				}
			}
		}

		//分析总结
		// be  de
		if (d_equal && !b_equal)//01 说明这是关键结点
			return t;
		else if (!d_equal && !b_equal)//00 说明这是没有问题的普通结点
			return NULL;
		else//11和10 不会出现的情况 如果有说明我的自创方法有严重错误
		{
			printf("完蛋，子树递归函数思路出现严重错误！！！！！！！！！！！！！！！！！\n");
			return NULL;
		}

	}
	else//回调信息
	{
		if (t->c)
			t->bn = 1;
		else
			t->bn = 0;
		t->b = 0;
		return NULL;
	}


}

//寻找那个合适的地方与父亲合并
int find_who(rbt* t)
{
	int min = 0;
	if (t)
	{
		rbt* tri = t->ri;
		if (t->tn == 2)
		{
			int n = t->bn - 1;
			rbt* le1 = t->le->le;
			rbt* le2 = t->le->ri;
			if (le1->bn == n)
				return 1;
			if (le2->bn == n)
				return 2;
			if (tri->bn == n)
				return 3;
		}
		else
		{
			int n = t->bn - 1;
			rbt* le = t->le;
			if (le->bn == n)
				return 4;
			if (tri->bn == n)
				return 5;
		}
	}
	else
		return 0;

}

//大容量版  合并和分裂操作
cmtr* mix_better_rbt(rbt* t, int tm)//返回合并器         t是问题子树的根  n是根与第n个孩子合并
{
	if (t)
	{
		cmtr* nt = make_cmtr_one();//合并器
		nt->k_tf = t->k_tf;
		nt->tf = t->tf;
		int i = 0;
		//很繁琐的5个分类10种情况  填充合并器  请原谅
		if (tm == 1)
		{
			rbt* red = t->le;
			//合并孩子部分
			if (red->le->tn == 1)
			{
				nt->tsrr[i] = red->le->le;
				nt->nrr[i] = red->le->n;
				i++;//1
				nt->tsrr[i] = red->le->ri;
				nt->tn = 3;
			}
			else
			{
				nt->tsrr[i] = red->le->le->le;
				nt->nrr[i] = red->le->le->n;
				i++;//1
				nt->tsrr[i] = red->le->le->ri;
				nt->nrr[i] = red->le->n;
				i++;//2
				nt->tsrr[i] = red->le->ri;
				nt->tn = 4;
			}
			//子树部分
			nt->nrr[i] = red->n;
			i++;//3
			nt->tsrr[i] = red->ri;
			nt->nrr[i] = t->n;
			i++;//4
			nt->tsrr[i] = t->ri;

		}
		if (tm == 2)
		{
			rbt* red = t->le;
			nt->nrr[i] = red->n;//0
			nt->tsrr[i] = red->le;
			if (red->ri->tn == 1)
			{
				i++;//1
				nt->nrr[i] = red->ri->n;
				nt->tsrr[i] = red->ri->le;
				i++;//2
				nt->tsrr[i] = red->ri->ri;
				nt->nrr[i] = t->n;
				i++;//3
				nt->tsrr[i] = t->ri;
				nt->tn = 3;
			}
			else
			{
				i++;//1
				nt->nrr[i] = red->ri->le->n;
				nt->tsrr[i] = red->ri->le->le;
				i++;//2
				nt->tsrr[i] = red->ri->le->ri;
				nt->nrr[i] = red->ri->n;
				i++;//3
				nt->tsrr[i] = red->ri->ri;
				nt->nrr[i] = t->n;
				i++;
				nt->tsrr[i] = t->ri;
				nt->tn = 4;
			}
		}
		if (tm == 3)
		{
			rbt* red = t->le;
			//子树部分
			nt->nrr[i] = red->n;//0
			nt->tsrr[i] = red->le;
			i++;//1
			nt->tsrr[i] = red->ri;
			nt->nrr[i] = t->n;
			rbt* ba = t->ri;
			if (ba->tn == 1)
			{
				i++;//2
				nt->nrr[i] = ba->n;
				nt->tsrr[i] = ba->le;
				i++;
				nt->tsrr[i] = ba->ri;
				nt->tn = 3;
			}
			else
			{
				i++;//2
				nt->nrr[i] = ba->le->n;
				nt->tsrr[i] = ba->le->le;
				i++;//3
				nt->nrr[i] = ba->n;
				nt->tsrr[i] = ba->le->ri;
				i++;
				nt->tsrr[i] = ba->ri;
				nt->tn = 4;
			}



		}
		if (tm == 4)
		{
			rbt* le = t->le;
			if (le->tn == 1)
			{
				nt->tsrr[i] = le->le;//0
				nt->nrr[i] = le->n;
				i++;//1
				nt->tsrr[i] = le->ri;
				nt->tn = 2;
			}
			else
			{
				nt->tsrr[i] = le->le->le;//0
				nt->nrr[i] = le->le->n;
				i++;//1
				nt->tsrr[i] = le->le->ri;
				nt->nrr[i] = le->n;
				i++;//2
				nt->tsrr[i] = le->ri;
				nt->tn = 3;
			}
			nt->nrr[i] = t->n;
			i++;
			nt->tsrr[i] = t->ri;


		}
		if (tm == 5)
		{
			nt->tsrr[i] = t->le;//0
			nt->nrr[i] = t->n;
			i++;//1
			rbt* ri = t->ri;
			if (ri->tn == 1)
			{
				nt->tsrr[i] = ri->le;//1
				nt->nrr[i] = ri->n;
				i++;//2
				nt->tsrr[i] = ri->ri;
				nt->tn = 2;
			}
			else
			{
				nt->tsrr[i] = ri->le->le;//1
				nt->nrr[i] = ri->le->n;
				i++;//2
				nt->tsrr[i] = ri->le->ri;
				nt->nrr[i] = ri->n;
				i++;//3
				nt->tsrr[i] = ri->ri;
				nt->tn = 3;
			}
		}

		return nt;
	}

	return NULL;
}
rbt* break_better_rbt(cmtr* c, arb* a)
{
	//创一个子树结点
	rbt* b = make_rbt_one();
	int i = 0;
	switch (c->tn)
	{
	case 2:
		if (1)
		{
			rbt* red = make_rbt_one();
			red->n = c->nrr[0];
			b->n = c->nrr[1];
			//红
			red->le = c->tsrr[0];//父认子
			red->ri = c->tsrr[1];
			c->tsrr[0]->tf = red, c->tsrr[0]->k_tf = 0;//子认父
			c->tsrr[1]->tf = red, c->tsrr[1]->k_tf = 1;

			red->tf = b, red->k_tf = -1;

			b->le = red, b->ri = c->tsrr[2];
			c->tsrr[2]->tf = b, c->tsrr[2]->k_tf = 1;

			b->tn = 2, red->tn = 2;
			b->c = 1, red->c = 0;
		}
		break;
	case 3:
		if (1)
		{
			rbt* ri = make_rbt_one();
			rbt* le = make_rbt_one();

			le->n = c->nrr[0], b->n = c->nrr[1], ri->n = c->nrr[2];
			//左
			le->le = c->tsrr[0], le->ri = c->tsrr[1];
			c->tsrr[0]->tf = le, c->tsrr[1]->tf = le;
			c->tsrr[0]->k_tf = 0, c->tsrr[1]->k_tf = 1;
			//右
			ri->le = c->tsrr[2], ri->ri = c->tsrr[3];
			c->tsrr[2]->tf = ri, c->tsrr[3]->tf = ri;
			c->tsrr[2]->k_tf = 0, c->tsrr[3]->k_tf = 1;
			//中
			b->le = le, b->ri = ri;
			le->tf = b, ri->tf = b;
			le->k_tf = 0, ri->k_tf = 1;

			b->tn = 1, le->tn = 1, ri->tn = 1;
			b->c = 1, le->c = 1, ri->c = 1;
		}
		break;
	case 4:
		if (1)
		{
			rbt* ble = make_rbt_one();
			rbt* red = make_rbt_one();

			rbt* ri = make_rbt_one();

			red->n = c->nrr[0], ble->n = c->nrr[1], b->n = c->nrr[2], ri->n = c->nrr[3];
			//左
			ble->le = red;
			red->k_tf = -1, red->tf = ble;
			red->tn = 2, red->c = 0;

			red->le = c->tsrr[0], red->ri = c->tsrr[1];
			c->tsrr[0]->tf = red, c->tsrr[1]->tf = red;
			c->tsrr[0]->k_tf = 0, c->tsrr[1]->k_tf = 1;

			ble->ri = c->tsrr[2];
			c->tsrr[2]->tf = ble, c->tsrr[2]->k_tf = 1;


			//右
			ri->le = c->tsrr[3], ri->ri = c->tsrr[4];
			c->tsrr[3]->tf = ri, c->tsrr[4]->tf = ri;
			c->tsrr[3]->k_tf = 0, c->tsrr[4]->k_tf = 1;

			//中
			b->le = ble, b->ri = ri;
			ble->tf = b, ri->tf = b;
			ble->k_tf = 0, ri->k_tf = 1;

			b->tn = 1, ble->tn = 2, ri->tn = 1;
			b->c = 1, ble->c = 1, ri->c = 1;

		}
		break;

	}

	//处理一下b的去向
	if (c->tf)
	{
		b->k_tf = c->k_tf;
		b->tf = c->tf;

		if (c->k_tf)//1
			c->tf->ri = b;
		else
			c->tf->le = b;
		return b;
	}
	else
	{
		a->rp = b;
		return b;
	}
}

//红黑树回溯大法 ，提供起点问题子树 ，修好后， 回溯到上一级 ，以此方式一直向上回溯 ，直至根结点
void reback_arb(arb* a, rbt* t)
{
	int i = 0;
	//先标记一下信息
	D_d(a->rp);
	rbt* tb = t;//问题子树
	int tm = 0;//合并孩子序号
	cmtr* out = NULL;//返回合并器
	rbt* to = NULL;//检查函数返回错误子树
   //合并根结点和全部大深度孩子 然后分裂出来 反复排查重修 构成新的子树
	while (1)
	{
		//对于错误的to进行反复修正
		while (1)
		{
			//检查
			to = check_balance(tb);
			//1.获取需要合并的孩子位置
			if (to)
			{
				tb = to;//收集问题结点
				tm = find_who(tb);//找到哪个孩子与父亲合并
				//find_who函数只会遍历一下自子树根结点的所有孩子 不会再往下 不是递归函数
				//返回问题孩子所在位置 3结点 1 2 3   2结点 4 5     然后对应去处理即可
				break;
			}
			else
			{
				//注意 这里的回溯 谁是真正的父亲结点 来代表一个子树 那个结点就是二三树的 2结点或3结点
				//在红黑树里面 那就必定是黑色结点 回溯的所有操作函数也是基于这个写的 所以子树得弄对
				tb = tb->tf;//回溯
				if (!tb)
					return;//回溯到根节点  唯一的出口
				if (tb->c == 0)
					tb = tb->tf;
			}
		}
		//合并与分裂
		out = mix_better_rbt(tb, tm);
		tb = break_better_rbt(out, a);
	}
}

//删除函数
void delete_rbt(arb* a, int n)
{
	if (a->rp)
	{
		rbt* s = search_d_tsb(n, a->rp);
		rbt* gs = NULL;
		if (s)
		{
			if ((s->tn == 1 && !s->ri && !s->le) ||
				(s->tn == 2 && s->c == 1 && !s->ri) ||
				(s->tn == 2 && s->c == 0 && !s->ri && !s->le))//叶子结点 即2-3树的 2 3 叶子结点的特征
				gs = s;
			else
			{
				//有孩子结点 需要推卸给孩子
				//这里考虑到效率于空间利用的折中 打算不将往红节点多的子树推卸 而是统一用后继结点推卸 
				//直至推卸至叶子结点
				gs = shirk_tsb(s);

			}

			rbt* fa = s->tf;

			//二。分类处理删除结点（全是叶子结点的情况）
			if (gs->tn == 2)
			{
				if (!gs->c)//红
				{
					gs->tf->le = NULL;
					gs->tf->tn = 1;
					free(gs);
					return;
				}
				else
				{
					rbt* k = gs->tf;
					rbt* le = gs->le;

					if (gs->k_tf)//1
						k->ri = le;
					else
						k->le = le;

					le->k_tf = gs->k_tf;
					le->tf = k;
					le->tn = 1;
					le->bn = 1;
					le->c = 1;
					free(gs);
					return;
				}
			}
			if (gs->tn == 1)
			{
				if (fa)
				{
					//获取子树情况
					ds* out = get_d_t(gs);
					rbt* la = out->bt;//旧子树

					//分析
					if (out->arr)//有需要重组的数据 靠兄弟 靠老爸的情况
					{
						arb* ab = rebuild(out->arr);
						if (ab->rp->bn != out->bn)
							printf("警告！！！！重组函数方案出现无法意料的错误\n");
						//如何接收重组子树
						if (!la->tf)//到根了
						{
							a->rp = ab->rp;
							a->an = ab->an;
							delete_ctree(la);//删去旧子树
							return;
						}
						else
						{
							rbt* latf = la->tf;
							//旧子树父亲结果新的重组子树
							if (la->k_tf)
								latf->ri = ab->rp;
							else
								latf->le = ab->rp;
							ab->rp->tf = la->tf;
							ab->rp->k_tf = la->k_tf;
							delete_ctree(la);//删去旧子树
							return;
						}
					}
					else//没有需要重组的数据 说明已经要降低树高了 进入回溯大法
					{
						if (out->bn == nothing)
							a->rp = la;
						else
							reback_arb(a, la);
					}
					return;
				}
				else
				{
					free(a->rp);
					a->rp = NULL;
					a->an = 0;
					return;
				}


			}

		}
		else
			printf("未找到相关关键字\n");

		return;
	}
	else
	{
		printf("树为空，无法进行删除操作\n");
		return;
	}
}

