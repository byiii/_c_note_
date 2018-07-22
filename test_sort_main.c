#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tinytest.h"

#include "insert_sort.h"
#include "merge_sort.h"
#include "bubble_sort.h"
#include "heap_sort.h"

#define MAX_NUMBER 100

void gen_random_seq(int *arr, int n) 
{
	int i = 0;
	for(; i<n; ++i) {
		*(arr + i) = rand() % MAX_NUMBER + 1;
	}
}

int test_sorted_seq(int *arr, int n) 
{
	int res = 1;
	int i;
	for(i=0; i<n-1; ++i) {
		if(*(arr+i) > *(arr+i+1)) {
			res = 0;
			break;
		}
	}
	return res;
}

void show_seq(int *arr, int n) 
{
    int i;
    for(i=0; i<n; ++i) 
    	printf("%d-", *(arr + i));
    printf("\n");
}

void test_insert_sort() 
{
    int arr[51];
    int n = 51;
    
    gen_random_seq(&arr[0], n);
    insert_sort(&arr[0], n);
    show_seq(arr, n);
    
    ASSERT("insert sort:", test_sorted_seq(&arr[0], n));
}

void test_merge_sort_recur()
{
	int arr[43];
	int n = 43;
	int *sorted = NULL;

	gen_random_seq(arr, n);
	show_seq(arr, n);
	
	sorted = merge_sort_recur(arr, n);
	show_seq(sorted, n);
    
    ASSERT("merge sort:", test_sorted_seq(sorted, n));
    
    free(sorted);
}

void test_bubble_sort() 
{
    int arr[51];
    int n = 51;
    
    gen_random_seq(&arr[0], n);
    bubble_sort(&arr[0], n);
    show_seq(arr, n);
    
    ASSERT("bubble sort:", test_sorted_seq(&arr[0], n));
}

void test_find_sum_x()
{
    int arr[51];
    int n = 51;
    
    gen_random_seq(&arr[0], n);
    show_seq(arr, n);
    
    ASSERT("find sum x:", find_sum_x(&arr[0], n, 131));
}

void test_max_heapify() 
{
    int arr[10] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int n = 10;

    max_heapify(arr, 10, 1);	
    
    printf("test max_heapify: ");
    show_seq(arr, n);
    
    ASSERT("max_heapify: ", 1);
}

void test_heap_sort() 
{
    int arr[51];
    int n = 51;
    
    gen_random_seq(&arr[0], n);
    heap_sort_desend(&arr[0], n);
    show_seq(arr, n);
    
    heap_sort(&arr[0], n);
    show_seq(arr, n);
    
    ASSERT("heap sort:", test_sorted_seq(&arr[0], n));
}

/* ****************************************
 */
int main(int argc, char *argv[]) 
{
	int i;
	srand(time(NULL));
	
	printf("hello. \n");
	
	for(i=0; i<50; ++i) {
	RUN(test_insert_sort);
	RUN(test_merge_sort_recur);
	RUN(test_bubble_sort);
	RUN(test_find_sum_x);
	RUN(test_max_heapify);
	RUN(test_heap_sort);
	}
	
	return TEST_REPORT();
}
