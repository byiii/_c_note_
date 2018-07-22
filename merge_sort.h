#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <stdio.h>

void merge_two_sorted_seq(int *seq_a, int n_a, int *seq_b, int n_b, int *res)
{
    int i_a, i_b, i_r;
    
    i_a = 0;
    i_b = 0;
    i_r = 0;
    
    while(i_a < n_a && i_b < n_b) {
        if(*(seq_a + i_a) <= *(seq_b + i_b)) {
            *(res + i_r++) = *(seq_a + i_a++);
        } else {
        	*(res + i_r++) = *(seq_b + i_b++);
        }
    }
    while(i_a < n_a) {
        *(res + i_r++) = *(seq_a + i_a++);
    }
    while(i_b < n_b) {
        *(res + i_r++) = *(seq_b + i_b++);
    }
}

int *merge_sort_recur(int *arr, int n)
{
	int *res;
	int *pa, *pb;
	
    if(n == 0) {
    	return NULL;
    }
    if(n == 1) {
    	res = (int *)malloc(1 * sizeof(int));
    	*res = *arr;
    	return res;
    }
    
    pa = merge_sort_recur(arr, n/2);
    pb = merge_sort_recur(arr+n/2, n-n/2);
    
    res = (int *)malloc(n * sizeof(int));
    merge_two_sorted_seq(pa, n/2, pb, n-n/2, res);
    
    free(pa);
    free(pb);
    return res;
}


int find_sum_x(int *arr, int n, int x)
{
	int *sorted;
	int *ps, *pe;
	int summ;
	int flag = 0;
	
	sorted = merge_sort_recur(arr, n);
	ps = sorted;
	pe = sorted + n - 1;
	
	while(ps < pe) {
		summ = *ps + *pe;
		if(summ == x) {
			flag = 1;
			printf(">> %d + %d = %d << \n", *ps, *pe, x);
			ps += 1;
		}
		if(summ > x) {
			pe -= 1;
		} else { /* (summ < x) */
			ps += 1;
		}
	}
	
	free(sorted);
	return flag;
}


#endif /* MERGE_SORT_H_ */
