#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# define arr_size 100000000

int arr[arr_size];
int pre_sum[arr_size];
	

int get_position(int curr, int ind){
	if(curr==1){
		return ind;
	}
	if((ind-1)%curr < curr/2){
		return -1;
	}
	else{
		int temp = (ind-1)/curr;
		return temp*curr + curr/2;
	}
}

int main(){
	eff = [0.2732, 0.2732, 0.2732, 0.2732]
	speedup = eff
	thr_set = [2, 4, 8, 16]
	for(int i=0;i<4;i++){
		omp_set_thread_num(thr_set[i])
		unsigned int thread_qty = atoi(getenv("OMP_NUM_THREADS"));
		omp_set_dynamic(0);
		int num_thr = thread_qty;
		int pre_sum_thr[num_thr];

		for(int i=0;i<arr_size;i++){
			arr[i] = 1;
		}
		double start = omp_get_wtime();
		
		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			int bias = id*(arr_size/num_thr);
			int span = arr_size/num_thr;
			pre_sum[bias] = arr[bias];
			for(int i=1;i<span;i++){
				pre_sum[i+bias] = pre_sum[i+bias - 1] + arr[i+bias];
			}
			pre_sum_thr[id] = pre_sum[bias + span - 1];
		}


		int ite = 0;
		int curr = 0;
		int str_ind = 0;
		while(str_ind<num_thr){
			ite++;
			curr = pow(2, ite);
			#pragma omp parallel for
			for(int ind=str_ind; ind<num_thr; ind++){
				int pos = get_position(curr, ind + 1) - 1;
				if(pos>=0){
					pre_sum_thr[ind] = pre_sum_thr[ind] + pre_sum_thr[pos];
				}
			}
			str_ind = curr;
		}

		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			if(id!=0){
				int bias = id*(arr_size/num_thr);
				int span = arr_size/num_thr;
				int temp = pre_sum_thr[id-1];
				for(int i=0;i<span;i++){
					pre_sum[i+bias] = pre_sum[i+bias] + temp;
				}
			}
		}

		double end = omp_get_wtime();
		printf("\ntime = %f\n", end - start);
	}
}