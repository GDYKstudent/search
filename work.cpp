#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"

int text(const void* e1, const void* e2)
{
	return *((int*)e1) - *((int*)e2);
}
//�������һ�����ַ�ΧΪ 0~num_range, Ԫ�ظ���Ϊn �� ��С�������������
int* make_rand_int_2(int n)
{
	int* arr = (int*)malloc(sizeof(int) * n);
	int i = 0;
	int m = 0, k = 0;
	srand((unsigned int)time(NULL));
	int j = 0;
	while (i < n)
	{
		//printf("%d\n", m);
		m = rand() % num_range;
		//for (j = 0; j < i; j++)
		//	if (m == arr[j])
		//		k = 1;
		//if (!k)
		//{
		//	arr[i] = m;
		//	k = 0;
		//	i++;
		//}


		arr[i] = m + i;
		i++;
	}

	//while (i < n)
	//{
	//	arr[i] = i;
	//	i++;
	//}
	 //��qsort������������
	qsort(arr, n, sizeof(int), text);

	//���ݹ���ʱû��Ҫ��ӡ

	//for (i = 0; i < n; i++)
	//{
	//	printf(" %d", arr[i]);
	//	if (!(i % 10) && i)
	//		printf("\n");
	//}
	//printf("\n");
	return arr;
}



/*
* ʵ���Է���     ���棺����һǧ���������Ҫ14������ṹ��ɾ��һ������ֻ��Ҫ 1s~1ms  ֮���ʱ��
* ����ע�͵��ܶ�� printf ��Ϣ����Ϊ���Ǹ���д����ʱ�������Ͳ��Եģ�
	����һЩ���ο��ӻ��ĺ�����������������ò�Ҫ����100��������ͼ���ÿ�֮�⣬��Ӱ������
*/
int main()
{
	int j = 0;
	while (1)
	{
		printf("��%d��ʵ��\n\n", j);
		srand((unsigned int)time(NULL));

		int NUM = 10000000;//���ƽ�����

		arb as;
		as.rp = NULL;
		as.an = 0;
		int i = 0;
		int in = 0;
		//int arr[20] = {17,22,28,37,41,48,52,54,56,59,81,87,92,94,97,98};
		int* arr = make_rand_int_2(NUM);

		time_t t1 = clock();
		printf("\n\n");
		//һ������
		while (i < NUM)
		{
			//printf("��%d�β��룺%d\n", i + 1, arr[i]);
			input_rbt(&as, arr[i]);

			//check_rbt_ture(&as);
			//printf("--------------------\n");
			
			//level_printf_rbt(as.rp, as.an);
			i++;
			//printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			//printf("�������������\n");
			//printf("\n\n");
			//getchar();
		}
		time_t t2 = clock();
		printf("����һ��%dԪ�صĺ�����ķѵ�ʱ��:  %d ��",NUM, (t2 - t1) / 1000);

		//����ɾ��
		printf("\n\n\n\n");
		i = 0;
		int NDL = 20;//����ɾ������


		while (i < NDL)
		{
			time_t t3 = clock();

			printf("��%d��ɾ����%d\n", i + 1, arr[i]);
			delete_rbt(&as, arr[i]);
			//check_rbt_ture(&as);
			//level_printf_rbt(as.rp, as.an);

			//printf("--------------------\n");
			i++;
			printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			printf("���������ɾ��\n");
			printf("\n\n");

			time_t t4 = clock();
			printf("ɾ��һ��Ԫ�����ķѵ�ʱ��:  %d ms", (t4 - t3));

			getchar();

		}
		printf("\n���� , Ŀǰ��������� ���� Ӧ���������������,��������ٸ�һ����������\n");
		getchar();
		system("cls");
	}



	return 0;
}
