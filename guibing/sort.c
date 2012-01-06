#include <stdio.h>

int order(int *src, int *ptr, int *arr)
{
	int i = 0;
	int m = 5, n = 4;

	while(m > 0 && n > 0)
	{
		if(*src > *ptr)
		{
			arr[i++] = *ptr;
			ptr++;
			n--;
		}
		else
		{
			arr[i++] = *src;
			src++;
			m--;
		}
	}
	while(m > 0)
		arr[i++] = src[m--];
	while(n > 0)
		arr[i++] = ptr[n--];
	return 0;
}

int main(void)
{
	int a[5] = {1, 3, 5, 7, 9};
	int b[4] = {2, 4, 6, 11};
	int array[9] ;
	int i = 0;

	order(a, b, array);

	for(i = 0; i < 10; i++)
		printf("%3d", array[i]);
	putchar('\n');
	return 0;
}
