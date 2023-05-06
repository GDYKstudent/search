#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"

/*
	 ɾ���ı��ʾ���ɾ����ĳ������֮���Ǹ���ȱ����ֱ��ǰ����ֱ�Ӻ���������
	 �Դ�����ֱ���������ݵ������

	 ���ε�ȫ��������������������һ�������������м�ɾȥһ�����������������߻����ұ�
	 �����ݲ��룬�Դ�����������ݵĵ���
*/



//��Ҷ�ӽ�����ж������ɾ������ʱ��ɾ��������ж������
rbt* shirk_tsb(rbt* s)
{
	if ((s->tn == 1 && !s->ri && !s->le) || (s->tn == 2 && s->c == 1 && !s->ri) || (s->tn == 2 && s->c == 0 && !s->ri && !s->le))//Ҷ�ӽ�� ��2-3���� 2 3 Ҷ�ӽ�������
		return s;
	else
	{
		s->n = s->ri->n;
		return shirk_tsb(s->ri);
	}
}

//������������
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

//�����ṩ��Ҷ�ӽ�� ���������������� Ȼ���Ӧ����ɾ������
ds* get_d_t(rbt* s)
{
	//��ʼ��������Ϣ
	ds* d = (ds*)malloc(sizeof(ds));
	d->arr = (int*)malloc(sizeof(int) * 6);
	int i = 0;
	for (i = 0; i < 6; i++)
		d->arr[i] = nothing;

	//��������
	rbt* t = s->tf;//�����Ǻ���

	rbt* tb;//�ֵ�

	if (s->k_tf)//1
		tb = t->le;
	else
		tb = t->ri;

	if (t->tn == 1 && tb->tn == 1)//��1��2  ������2����µ���������������״̬
	{
		d->arr = NULL;

		//������ ���ر�������֮�� �������Ʊ�Ӧ���߽��͵��µĲ�ƽ�� ��������
		tb->c = 0, tb->k_tf = -1, tb->tn = 2, tb->bn = 0,
			t->bn = 1, t->tn = 2, t->ri = NULL;

		if (tb->n > t->n)//����
		{
			t->le = tb;
			int n = t->n;
			t->n = tb->n;
			tb->n = n;
		}
		free(s);

		d->bt = t->tf;//�����Ǻ�ɫ���Ҳ�����ǿս��
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
	else//������֮����Ȼ�����Ǹ��е�
	{
		//�׸�
		if (s->k_tf)//1
			t->ri = NULL;
		else
			t->le = NULL;

		free(s);

		//ȷ����������
		if (t->c == 0)
			t = t->tf;

		d->bt = t;
		d->bn = t->bn;
		i = 0;
		D_ctree(t, d->arr, &i);//��ȡ��������
	}
	return d;

}

//����һ�����������к����������
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
			input_rbt(in, arr[i]);//����
		i++;
	}
	//�����ȷ
	check_rbt_ture(in);
	return in;
}

//��Ǻ��� ����Ǹ��������ĺڽڵ�ֵ
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
		else	//�����Ҷ��
		{
			//�����������
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
			//����
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

//���ƽ���� �����ز�ƽ������
rbt* check_balance(rbt* t)
{
	int i = 0;
	int n = 0;
	int sum = 0;
	rbt* error = NULL;

	//������ָ������� ȫ��-->Ҷ�ӽ��    ȫ����--->��ͨ���
	if (t->ri)
		n = 1;
	else
		n = 0;

	if (n)//��ͨ��� ���ÿ�����ӵ����
	{
		int max = nothing;
		int b_equal = 0;
		int d_equal = 0;

		//���� �ݹ�鿴���к���
		if (t->tn == 1)//2���
		{
			error = check_balance(t->le);//��
			if (error)
				return error;
			else
			{
				error = check_balance(t->ri);//��
				if (error)
					return error;
				else
				{
					//�ж����һ����
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
					//�ж�ƽ��һ����
					if (!(!t->le->b && !t->ri->b))
						b_equal = 1;
				}
			}
		}
		else//3���
		{
			error = check_balance(t->le->le);//����
			if (error)
				return error;
			else
			{
				error = check_balance(t->le->ri);//����
				if (error)
					return error;
				else
				{
					error = check_balance(t->ri);//����
					if (error)
						return error;
					else
					{
						//�ж����һ����
						if (t->le->le->bn == t->ri->bn && t->ri->bn == t->le->ri->bn)//�����ط��ڽڵ㶼��ͬ
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

							t->bn = max + 1;//����
							t->le->bn = max;//��
							t->b = 1;
							t->le->b = 1;

							d_equal = 1;
						}
						//�ж�ƽ��һ����
						if (!(!t->le->le->b && !t->le->ri->b))
							b_equal = 1;
					}
				}
			}
		}

		//�����ܽ�
		// be  de
		if (d_equal && !b_equal)//01 ˵�����ǹؼ����
			return t;
		else if (!d_equal && !b_equal)//00 ˵������û���������ͨ���
			return NULL;
		else//11��10 ������ֵ���� �����˵���ҵ��Դ����������ش���
		{
			printf("�군�������ݹ麯��˼·�������ش��󣡣�������������������������������\n");
			return NULL;
		}

	}
	else//�ص���Ϣ
	{
		if (t->c)
			t->bn = 1;
		else
			t->bn = 0;
		t->b = 0;
		return NULL;
	}


}

//Ѱ���Ǹ����ʵĵط��븸�׺ϲ�
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

//��������  �ϲ��ͷ��Ѳ���
cmtr* mix_better_rbt(rbt* t, int tm)//���غϲ���         t�����������ĸ�  n�Ǹ����n�����Ӻϲ�
{
	if (t)
	{
		cmtr* nt = make_cmtr_one();//�ϲ���
		nt->k_tf = t->k_tf;
		nt->tf = t->tf;
		int i = 0;
		//�ܷ�����5������10�����  ���ϲ���  ��ԭ��
		if (tm == 1)
		{
			rbt* red = t->le;
			//�ϲ����Ӳ���
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
			//��������
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
			//��������
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
	//��һ���������
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
			//��
			red->le = c->tsrr[0];//������
			red->ri = c->tsrr[1];
			c->tsrr[0]->tf = red, c->tsrr[0]->k_tf = 0;//���ϸ�
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
			//��
			le->le = c->tsrr[0], le->ri = c->tsrr[1];
			c->tsrr[0]->tf = le, c->tsrr[1]->tf = le;
			c->tsrr[0]->k_tf = 0, c->tsrr[1]->k_tf = 1;
			//��
			ri->le = c->tsrr[2], ri->ri = c->tsrr[3];
			c->tsrr[2]->tf = ri, c->tsrr[3]->tf = ri;
			c->tsrr[2]->k_tf = 0, c->tsrr[3]->k_tf = 1;
			//��
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
			//��
			ble->le = red;
			red->k_tf = -1, red->tf = ble;
			red->tn = 2, red->c = 0;

			red->le = c->tsrr[0], red->ri = c->tsrr[1];
			c->tsrr[0]->tf = red, c->tsrr[1]->tf = red;
			c->tsrr[0]->k_tf = 0, c->tsrr[1]->k_tf = 1;

			ble->ri = c->tsrr[2];
			c->tsrr[2]->tf = ble, c->tsrr[2]->k_tf = 1;


			//��
			ri->le = c->tsrr[3], ri->ri = c->tsrr[4];
			c->tsrr[3]->tf = ri, c->tsrr[4]->tf = ri;
			c->tsrr[3]->k_tf = 0, c->tsrr[4]->k_tf = 1;

			//��
			b->le = ble, b->ri = ri;
			ble->tf = b, ri->tf = b;
			ble->k_tf = 0, ri->k_tf = 1;

			b->tn = 1, ble->tn = 2, ri->tn = 1;
			b->c = 1, ble->c = 1, ri->c = 1;

		}
		break;

	}

	//����һ��b��ȥ��
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

//��������ݴ� ���ṩ����������� ���޺ú� ���ݵ���һ�� ���Դ˷�ʽһֱ���ϻ��� ��ֱ�������
void reback_arb(arb* a, rbt* t)
{
	int i = 0;
	//�ȱ��һ����Ϣ
	D_d(a->rp);
	rbt* tb = t;//��������
	int tm = 0;//�ϲ��������
	cmtr* out = NULL;//���غϲ���
	rbt* to = NULL;//��麯�����ش�������
   //�ϲ�������ȫ������Ⱥ��� Ȼ����ѳ��� �����Ų����� �����µ�����
	while (1)
	{
		//���ڴ����to���з�������
		while (1)
		{
			//���
			to = check_balance(tb);
			//1.��ȡ��Ҫ�ϲ��ĺ���λ��
			if (to)
			{
				tb = to;//�ռ�������
				tm = find_who(tb);//�ҵ��ĸ������븸�׺ϲ�
				//find_who����ֻ�����һ�����������������к��� ���������� ���ǵݹ麯��
				//�������⺢������λ�� 3��� 1 2 3   2��� 4 5     Ȼ���Ӧȥ������
				break;
			}
			else
			{
				//ע�� ����Ļ��� ˭�������ĸ��׽�� ������һ������ �Ǹ������Ƕ������� 2����3���
				//�ں�������� �Ǿͱض��Ǻ�ɫ��� ���ݵ����в�������Ҳ�ǻ������д�� ����������Ū��
				tb = tb->tf;//����
				if (!tb)
					return;//���ݵ����ڵ�  Ψһ�ĳ���
				if (tb->c == 0)
					tb = tb->tf;
			}
		}
		//�ϲ������
		out = mix_better_rbt(tb, tm);
		tb = break_better_rbt(out, a);
	}
}

//ɾ������
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
				(s->tn == 2 && s->c == 0 && !s->ri && !s->le))//Ҷ�ӽ�� ��2-3���� 2 3 Ҷ�ӽ�������
				gs = s;
			else
			{
				//�к��ӽ�� ��Ҫ��ж������
				//���￼�ǵ�Ч���ڿռ����õ����� ���㲻������ڵ���������ж ����ͳһ�ú�̽����ж 
				//ֱ����ж��Ҷ�ӽ��
				gs = shirk_tsb(s);

			}

			rbt* fa = s->tf;

			//�������ദ��ɾ����㣨ȫ��Ҷ�ӽ��������
			if (gs->tn == 2)
			{
				if (!gs->c)//��
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
					//��ȡ�������
					ds* out = get_d_t(gs);
					rbt* la = out->bt;//������

					//����
					if (out->arr)//����Ҫ��������� ���ֵ� ���ϰֵ����
					{
						arb* ab = rebuild(out->arr);
						if (ab->rp->bn != out->bn)
							printf("���棡���������麯�����������޷����ϵĴ���\n");
						//��ν�����������
						if (!la->tf)//������
						{
							a->rp = ab->rp;
							a->an = ab->an;
							delete_ctree(la);//ɾȥ������
							return;
						}
						else
						{
							rbt* latf = la->tf;
							//���������׽���µ���������
							if (la->k_tf)
								latf->ri = ab->rp;
							else
								latf->le = ab->rp;
							ab->rp->tf = la->tf;
							ab->rp->k_tf = la->k_tf;
							delete_ctree(la);//ɾȥ������
							return;
						}
					}
					else//û����Ҫ��������� ˵���Ѿ�Ҫ���������� ������ݴ�
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
			printf("δ�ҵ���عؼ���\n");

		return;
	}
	else
	{
		printf("��Ϊ�գ��޷�����ɾ������\n");
		return;
	}
}

