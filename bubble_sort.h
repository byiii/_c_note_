#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

void bubble_sort(int *arr, int n)
{
	int i, j;
	int tmp;
	int *p;
	int *pe;
	
	if(arr == NULL) return;
	if(n == 0) return;
	
	for(i=0; i<n; ++i) {
		pe = arr + n - i - 1;
		p = arr;
		while(p != pe) {
			if(*(p+1) < *p) {
				tmp = *p;
				*p = *(p+1);
				*(++p) = tmp;
			} else {
				++p;
			}
		}
	}
}


#endif /* BUBBLE_SORT_H_ */
