#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include <stdio.h>

int _parent_h(int i)
{
	if(i == 0) return 0;
	return (i-1) >> 1;
}

int _left_h(int i)
{
	return (i<<1) + 1;
}

int _right_h(int i)
{
	return (i<<1) + 2;
}

void max_heapify(int *arr, int hs, int i)
{
	int l = _left_h(i);
	int r = _right_h(i);
	
	int largest = 0;
	int tmp = 0;
	
	if(l < hs && *(arr + l) > *(arr + i))
		largest = l;
	else 
	    largest = i;
	
	if(r < hs && *(arr + r) > *(arr + largest))
	    largest = r;
	
	/* printf("[%d, %d, %d]\n", l, r, largest); */
	
	if(largest != i) {
		tmp = *(arr + i);
		*(arr + i) = *(arr + largest);
		*(arr + largest) = tmp;
		
		max_heapify(arr, hs, largest);
	}
}

void build_max_heap(int *arr, int n, int hs)
{
	int i;
	for(i = (n>>1); i>=0; --i) {
		max_heapify(arr, hs, i);
	}
}

void heap_sort(int *arr, int n)
{
	int i;
	int j;
	int tmp;
	int hs;
	hs = n;
	
	build_max_heap(arr, n, hs);
	
	for(i = n-1; i > 0; --i) {
		tmp = *arr;
		*arr = *(arr + i);
		*(arr + i) = tmp;
		hs -= 1;
		max_heapify(arr, hs, 0);
	}
}


void min_heapify(int *arr, int hs, int i)
{
	int l = _left_h(i);
	int r = _right_h(i);
	
	int smallest = 0;
	int tmp = 0;
	
	if(l < hs && *(arr + l) < *(arr + i))
		smallest = l;
	else 
	    smallest = i;
	
	if(r < hs && *(arr + r) < *(arr + smallest))
	    smallest = r;
	
	/* printf("[%d, %d, %d]\n", l, r, largest); */
	
	if(smallest != i) {
		tmp = *(arr + i);
		*(arr + i) = *(arr + smallest);
		*(arr + smallest) = tmp;
		
		min_heapify(arr, hs, smallest);
	}
}

void build_min_heap(int *arr, int n, int hs)
{
	int i;
	for(i = (n>>1); i>=0; --i) {
		min_heapify(arr, hs, i);
	}
}

void heap_sort_desend(int *arr, int n)
{
	int i;
	int j;
	int tmp;
	int hs;
	hs = n;
	
	build_min_heap(arr, n, hs);
	
	for(i = n-1; i > 0; --i) {
		tmp = *arr;
		*arr = *(arr + i);
		*(arr + i) = tmp;
		hs -= 1;
		min_heapify(arr, hs, 0);
	}
}

#endif /* HEAP_SORT_H_ */
