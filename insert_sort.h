#ifndef INSERT_SORT_H_
#define INSERT_SORT_H_

#include <stdio.h>

void insert_sort(int *arr, int n) {
	int i, j;
	int key;
	
	if(arr == NULL) return;
	
	for(i=1; i<n; ++i) {
	    key = *(arr + i);
	    for(j = i-1; j>=0 && *(arr + j) > key; --j) {
	        *(arr + j + 1) = *(arr + j);
	    }
	    *(arr + j + 1) = key;
	}
}

#endif /* INSERT_SORT_H_ */
