#include <stdio.h>


int main()
{
	int arr[] = {257,2};
	char * ptr_c = (char*)arr;
	int * ptr_i = arr;

	printf("*ptr_c (arr[0])= %d\n", *ptr_c);
	printf("*ptr_c (arr[0])= %d", *ptr_i);

}
