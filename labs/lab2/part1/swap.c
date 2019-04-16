/*
 * swap.c
 * Copyright (C) 2019 vdelaplainess <vdelaplainess@arch>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>

void swap(int *p1, int *p2)
{
	int temp = *p1;
	*p1=*p2;
	*p2=temp;

}

