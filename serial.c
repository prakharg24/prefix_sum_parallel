#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# define arr_size 100000000

int arr[arr_size];
int pre_sum[arr_size];

int main(){
	for(int i=0;i<arr_size;i++){
		arr[i] = 1;
		pre_sum[i] = 0;
	}
	double start = omp_get_wtime();
	pre_sum[0] = arr[0];
	for(int i=1;i<arr_size;i++){
		pre_sum[i] = pre_sum[i-1] + arr[i];
	}
	double end = omp_get_wtime();
	
	printf("time = %f\n", end - start);
}