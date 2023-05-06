#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"
//给一个合并结点容器分配空间
cmtr* make_cmtr_one()
{
	cmtr* n = (cmtr*)malloc(sizeof(cmtr));
	n->nrr = (int*)malloc(sizeof(int) * u_tree_n);
	n->tsrr = (rbt**)malloc(sizeof(rbt*) * u_tree_p);
	n->tn = 0;
	n->bn = 0;
	n->k_tf = nothing;
	n->tf = NULL;
	//初始化
	int i = 0;
	for (i = 0; i < u_tree_n; i++)
		n->nrr[i] = nothing;
	for (i = 0; i < u_tree_p; i++)
		n->tsrr[i] = NULL;

	return n;
}
//给一个结点分配空间
rbt* make_rbt_one()
{
	rbt* n = (rbt*)malloc(sizeof(rbt));
	n->n = nothing;
	n->le = NULL;
	n->ri = NULL;
	n->c = 0;
	n->tn = nothing;
	n->tf = NULL;
	n->k_tf = nothing;
	n->bn = 0;
	n->b = 0;

	return n;
}



//操作一：融合函数。   如果融合出超重结点，将打包好返回合并器
cmtr* mix_rb(bor* b, arb* a)
{
	//printf("进入合并-->合并结点数值 mid:%d   \n", b->n);
	//直接更新结点
	rbt* in = b->in;
	//看看插入结点的类型
	if (b->tn == 1)//插入后不超重 返回空合并器
	{
		//对应类型去处理
		if (b->t == 1)
		{
			//新插结点
			rbt* t = make_rbt_one();
			t->n = b->n;
			t->c = 0;
			t->tn = 2;
			t->tf = in;
			t->k_tf = -1;//并且还是左边
			in->le = t;
			in->tn = 2;
			return NULL;
		}
		else
		{
			//新插结点反变主角
			rbt* t = make_rbt_one();
			in->tn = 2;
			t->n = b->n;
			t->c = 1;
			t->tn = 2;
			//关系整理
			t->tf = in->tf;
			t->k_tf = in->k_tf;
			if (t->tf)
			{
				if (t->k_tf)//1
					t->tf->ri = t;
				else//0
					t->tf->le = t;
			}
			else
			{
				a->rp = t;
			}

			t->le = in;
			in->tf = t;
			in->k_tf = -1;

			t->ri = b->ri;
			if (t->ri)
			{
				t->ri->tf = t;
				t->ri->k_tf = 1;
			}


			in->c = 0;
			in->ri = b->le;
			if (in->ri)
			{
				in->ri->tf = in;
				in->ri->k_tf = 1;
			}
			return NULL;

		}
	}
	else if (b->tn == 2)//插入后超重 返回三关键字合并器
	{
		cmtr* m = make_cmtr_one();
		//对应类型去处理
		switch (b->t)
		{
		case 1:
			if (1)
			{
				m->k_tf = in->k_tf;
				m->tf = in->tf;
				//数据域和指针域的完善
				m->nrr[0] = b->n, m->nrr[1] = in->le->n, m->nrr[2] = in->n;
				m->tsrr[0] = b->le, m->tsrr[1] = b->ri,
					m->tsrr[2] = in->le->ri, m->tsrr[3] = in->ri;

				m->tn = 3;
				return m;
			}
		case 2:
			if (1)
			{
				m->k_tf = in->k_tf;
				m->tf = in->tf;
				//数据域和指针域的完善
				m->nrr[0] = in->le->n, m->nrr[1] = b->n, m->nrr[2] = in->n;
				m->tsrr[0] = in->le->le, m->tsrr[1] = b->le,
					m->tsrr[2] = b->ri, m->tsrr[3] = in->ri;

				m->tn = 3;
				return m;
			}
		case 3:
			if (1)
			{
				m->k_tf = in->k_tf;
				m->tf = in->tf;
				//数据域和指针域的完善
				m->nrr[0] = in->le->n, m->nrr[1] = in->n, m->nrr[2] = b->n;
				m->tsrr[0] = in->le->le, m->tsrr[1] = in->le->ri,
					m->tsrr[2] = b->le, m->tsrr[3] = b->ri;

				m->tn = 3;
				return m;
			}

		}
	}

}


//分裂函数的附属：确定插入类型   解决bor的 in tn t 的填充
void get_ture_bo(bor* b, rbt* tf, int k_tf)
{
	if (tf->tn == 1)
	{
		b->in = tf;
		b->tn = 1;
		b->t = k_tf + 1;
	}
	else if (tf->tn == 2)
	{
		if (tf->c == 0)//红
		{
			b->in = tf->tf;
			b->tn = 2, b->t = k_tf + 1;
		}
		else//黑
		{
			b->in = tf;
			b->tn = 2;
			b->t = 3;

		}
	}
	return;
}
//操作二：分裂 返回中间结点的信息
bor* brea_out_rb(cmtr* s, arb* a)
{
	//将cmtr转变成为bor形式
	//printf("进入分裂-->");
	//printf("分裂结点:  %d  %d  %d \n", s->nrr[0], s->nrr[1], s->nrr[2]);

	rbt* tle = make_rbt_one();
	rbt* tri = make_rbt_one();

	tle->n = s->nrr[0];
	tle->le = s->tsrr[0], tle->ri = s->tsrr[1];
	if (tle->le)
	{
		tle->le->tf = tle;
		tle->le->k_tf = 0;
	}
	if (tle->ri)
	{
		tle->ri->tf = tle;
		tle->ri->k_tf = 1;
	}
	tle->bn = s->bn;
	tle->c = 1;
	tle->tn = 1;
	tle->b = 0;

	tri->n = s->nrr[2];
	tri->le = s->tsrr[2], tri->ri = s->tsrr[3];
	if (tri->le)
	{
		tri->le->tf = tri;
		tri->le->k_tf = 0;
	}
	if (tri->ri)
	{
		tri->ri->tf = tri;
		tri->ri->k_tf = 1;
	}
	tri->bn = s->bn;
	tri->c = 1;
	tri->tn = 1;
	tri->b = 0;

	if (s->tf)//有上级接管
	{
		bor* bo = (bor*)malloc(sizeof(bor));
		bo->n = s->nrr[1];
		bo->le = tle, bo->ri = tri;
		//bo确定函数
		get_ture_bo(bo, s->tf, s->k_tf);
		return bo;
	}
	else//无上级接管
	{
		rbt* tmi = make_rbt_one();
		tle->tf = tmi, tri->tf = tmi;
		tle->k_tf = 0, tri->k_tf = 1;
		tmi->n = s->nrr[1];
		tmi->le = tle, tmi->ri = tri;
		tmi->c = 1;
		tmi->tn = 1;
		tmi->bn = s->bn + 1;
		tmi->b = 0;
		free(a->rp);
		a->rp = tmi;
		return NULL;
	}
}


//新插入数据 n
void input_rbt(arb* a, int n)
{
	if (a->rp)
	{
		//查找在哪里
		sgr* s = search_tsb(n, a->rp);
		cmtr* out = NULL;
		if (s)
		{
			//printf("搜查所得：插入所在结点的关键字个数: %d ,插入处关键字值：%d \n", s->bt->tn, s->n);
			bor b;
			b.le = NULL;
			b.ri = NULL;
			b.n = n;
			b.in = s->bt;
			b.tn = s->n;

			b.t = s->t;

			bor* gb = &b;

			//仅插入全新关键字
			if (s->n != nothing)
			{
				while (1)//合并和分裂的循环
				{
					if (gb)
						out = mix_rb(gb, a);
					else
						break;

					if (out)
						gb = brea_out_rb(out, a);
					else
						break;
				}
			}


		}
		//else
		//	printf("抱歉，插入值已存在\n");

	}
	else
	{
		a->rp = make_rbt_one();
		a->rp->n = n;
		a->rp->le = NULL;
		a->rp->ri = NULL;
		a->rp->c = 1;
		a->rp->tn = 1;
		a->rp->bn = 1;
		a->rp->b = 0;
		return;
	}
}

