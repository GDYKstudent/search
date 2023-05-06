#define _CRT_SECURE_NO_WARNINGS
#include"tree_struct.h"

int text(const void* e1, const void* e2)
{
	return *((int*)e1) - *((int*)e2);
}
//随机生成一个数字范围为 0~num_range, 元素个数为n 的 自小到大排序的数组
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
	 //用qsort函数进行排序
	qsort(arr, n, sizeof(int), text);

	//数据过大时没必要打印

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
* 实用性仿真     报告：插入一千万个数据需要14秒来搭建结构，删除一个数据只需要 1s~1ms  之间的时间
* 这里注释掉很多的 printf 信息，因为那是给我写代码时做反馈和测试的，
	还有一些树形可视化的函数，建议结点数量最好不要超过100，否则视图不好看之外，还影响运行
*/
int main()
{
	int j = 0;
	while (1)
	{
		printf("第%d次实验\n\n", j);
		srand((unsigned int)time(NULL));

		int NUM = 10000000;//控制结点个数

		arb as;
		as.rp = NULL;
		as.an = 0;
		int i = 0;
		int in = 0;
		//int arr[20] = {17,22,28,37,41,48,52,54,56,59,81,87,92,94,97,98};
		int* arr = make_rand_int_2(NUM);

		time_t t1 = clock();
		printf("\n\n");
		//一。插入
		while (i < NUM)
		{
			//printf("第%d次插入：%d\n", i + 1, arr[i]);
			input_rbt(&as, arr[i]);

			//check_rbt_ture(&as);
			//printf("--------------------\n");
			
			//level_printf_rbt(as.rp, as.an);
			i++;
			//printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			//printf("任意键继续插入\n");
			//printf("\n\n");
			//getchar();
		}
		time_t t2 = clock();
		printf("生成一棵%d元素的红黑树耗费的时间:  %d 秒",NUM, (t2 - t1) / 1000);

		//二。删除
		printf("\n\n\n\n");
		i = 0;
		int NDL = 20;//控制删除个数


		while (i < NDL)
		{
			time_t t3 = clock();

			printf("第%d次删除：%d\n", i + 1, arr[i]);
			delete_rbt(&as, arr[i]);
			//check_rbt_ture(&as);
			//level_printf_rbt(as.rp, as.an);

			//printf("--------------------\n");
			i++;
			printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			printf("任意键继续删除\n");
			printf("\n\n");

			time_t t4 = clock();
			printf("删除一个元素所耗费的时间:  %d ms", (t4 - t3));

			getchar();

		}
		printf("\n结束 , 目前对于里面的 错误 应该算是清理完成了,按任意键再搞一棵新树来玩\n");
		getchar();
		system("cls");
	}



	return 0;
}
