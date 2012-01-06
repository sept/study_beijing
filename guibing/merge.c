/*********************************
 归并排序 的简化排序 思路
 **********************************/
#include<stdio.h>

void merge(int arr[], int brr[], int crr[])
{
	int i = 0, j = 0, k = 0;

	while(i < 6 && j < 4)
	{
		if(arr[i] < brr[j])
			crr[k++] = arr[i++];
		else
			crr[k++] = brr[j++];
	}

	while(i < 6)
		crr[k++] = arr[i++];
	while(j < 4)
		crr[k++] = brr[j++];
}

int main(void)
{
	int i;
	int arr[6] = {1, 4, 6, 9, 11, 22};
	int brr[4] = {2, 5, 8, 99};
	int crr[10] = {0};

//	printf("%d\n", sizeof(arr)/sizeof(arr[0]));
//	测出数组的长度
	merge(arr, brr, crr);

	for(i = 0; i < 10; i++)
		printf("%4d", crr[i]);
	printf("\n");
	return 0;
}
