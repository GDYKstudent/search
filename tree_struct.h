#pragma once
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>

/*	
	������ʵ�ֵ��������������� �����ݱ���2 - 3��������ú�����Ĳ���ԭ��Ҳ������2 - 3����
	���ں��������������� �����Ա�ʾ 2-3����3��㣬����ͬһ���е����ֶ�Ӧ���ɵĺ�����Ľṹ����Ψһ��
	��ʵ������� ���������������������������ǽ��2-3-4��ԭ��� ���� ��̬AA�� ������������������������������������㣬���2-3����ԭ�� ��
	��ˮƽ���ޣ�������Ǻ����ģ�͵Ĵ���ʵ�֣������кܶ಻��֮����ϣ���õ�����
*/
#define nothing -1234567
#define num_range RAND_MAX

//���������������
#define u_tree_n 4
#define u_tree_p 5


//������������Ľṹ
struct rbtree
{
	//����
	int n;							//������
	rbtree* le;					//����
	rbtree* ri;					//�Һ���
	int c;							//��ɫ   0->red    1->black

	/*
		������Щ���ݶ������ڹ�������ƽ�����Ҫ��Ϣ����Ϊ������ȫģ��2 - 3���εķ���������������

		�ڴ��ϵ��Ż���
			���Խ��������ݴ����һ���ṹ��A����ʹA���ڴ���뾡��ѹ����ÿ�����ͨ������һ��A���͵�ָ��PA������ȡ������Ϣ��
			����ÿ����㶼��ҪA�����ݵ���Ϣ�����Կ��Խ�A���������������ÿ����㽫ͨ��PA�ҵ���֮��Ӧ����Ϣ��������ε�����ṹ�������㡣
		�������˾������ָĶ��ǲ�ʹ�����ġ�

		������������뿴���ҵĴ�������ι����ģ��ǽ����ҵĲ�ʤ���ң������������ȹ������  2-3 b ���Ĵ��빤��ԭ�������ҵĴ��뽫Ϊ������޾���ʹ��ͷ�ŭ
		ͬʱ�����ҳ�ѧ��ʱ�Ĵ����񣬱������������ª����ɬ�Ѷ�
		������������Ĵ��Ĵ��⣬���ﴦ����������ݶ���  int  ���ͣ���������ֻ��һ���ܼ��׵�ģ��

	*/

	int tn;							//��Ӧ2-3���Ľ������  1��2���  2��3���
	rbtree* tf;					//�����֮����
	int k_tf;						//ģ��2-3���Ĺ��ܣ���������丸�׵�ָ��������±꣩�������ж�  ----> 0   1  -1 nothing

	//����
	int bn;							//�Ը����Ϊ������������ڽ����ܸ���-->������ b�������
	int b;							//��Ϊ����ʱ�ṩ��ƽ�����
};
typedef rbtree rbt;

//�����֮����
struct arbtree
{
	rbt* rp;						//����ǣ��

	int an;							//�������  �������û�����ϣ�
};
typedef arbtree arb;

/*
	23����α��� ( ����һ��Ԫ�ؼ����Ͷ��У������ÿռ�Ԫ��Ϊcp-1��
	�������ǽ�������δ�ӡ�ľ������ӻ�һ��
*/
struct queue_rbt
{
	rbt** base;//��������
	int cp;

	int front;//��ͷ
	int rear;//��β

};
typedef queue_rbt que_r;

//���ҷ�������
struct search_getr
{
	rbt* bt;//�������ڽ��

	int n;//���ݲ����������

	int t;//��Ӧ����
};
typedef search_getr sgr;
//����������
struct break_outr
{
	int n;//����ֵ

	rbt* le;//��С
	rbt* ri;//�Ҵ�

	rbt* in;//������   //���ڵ�һ���Ǻ�ɫ��

	int tn;//���ݲ����������

	int t;//��Ӧ�γɽṹ������

};
typedef break_outr bor;
//�ϲ��������
struct combine_many_tsbr
{
	//����
	int* nrr;//������
	rbt** tsrr;//����ָ����
	int tn;//�ؼ��ָ���

	rbt* tf;//�����֮����
	int k_tf;//��������丸�׵�ָ��������±�

	//����
	int bn;//�ں��Ӹ���  ���
};
typedef combine_many_tsbr cmtr;

//Ҷ�ӽ�����ɾ������ ���ں������� ������Ϣ
struct DS
{
	rbt* bt;//ɾ�����������������ɾ����㱾��

	int* arr;//��������

	int bn;//����ǰ���������ĺ�ɫ������
};
typedef DS ds;



//�����ϼ�

//��һ��������ռ�
rbt* make_rbt_one();
//��һ���ϲ������������ռ�
cmtr* make_cmtr_one();


//���븨������ �Ѳ�
sgr* search_tsb(int n, rbt* t);//n����������ֵ  
//����һ���ں� ���Ϲ淵�ز��Ϲ���
cmtr* mix_rb(bor* b, arb* a);
//���Ѻ����ĸ�����ȷ����������   ���bor�� in tn t �����
void get_ture_bo(bor* b, rbt* tf, int k_tf);
//������������ �����м������Ϣ
bor* brea_out_rb(cmtr* s, arb* a);
//�²�����ֵn
void input_rbt(arb* a, int n);


//��ӡ����
//��α���
void make_queue_rbt(que_r* qt, int k, int num);//0�Ǹ����ʼnumԪ�ض���  1������numԪ�صĶ���
void level_printf_rbt(rbt* t, int n);
//��ȷ�Եļ��
//�����Ų�ͼ���
int D_rbt(rbt* t, int* r, int* be);
int check_rbt_ture(arb* a);//ȫ���Ϸ���0 ȫ�����Ϸ��� 245


//ɾ�������Ѳ麯��
rbt* search_d_tsb(int n, rbt* t);
//��Ҷ�ӽ����ж����
rbt* shirk_tsb(rbt* s);
//����������ȡɾ��������
void D_ctree(rbt* t, int* arr, int* i);
//������������
void delete_ctree(rbt* t);
//�����ṩ��Ҷ�ӽ�� ���������������� Ȼ���Ӧ����ɾ������
ds* get_d_t(rbt* s);
//������������
arb* rebuild(int* arr);

//��Ǻ��� ��Ǹ��������ĺڽڵ�ֵ
void D_d(rbt* t);
//���ƽ���� �����ز�ƽ������
rbt* check_balance(rbt* t);
//Ѱ���Ǹ����ʵĵط��븸�׺ϲ�
int find_who(rbt* t);

//��������  �ϲ��ͷ��Ѳ���
cmtr* mix_better_rbt(rbt* t, int tm);//���غϲ���         t�����������ĸ�  n�Ǹ����n�����Ӻϲ�
rbt* break_better_rbt(cmtr* c, arb* a);
//��������ݴ� �ṩ����������� �޺ú� ���ݵ���һ�� �Դ˷�ʽһֱ���ϻ��� ֱ�������
void reback_arb(arb* a, rbt* t);
//ɾ������
void delete_rbt(arb* a, int n);







