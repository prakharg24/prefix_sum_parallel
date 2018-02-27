#include "iostream"
#include "vector"
#include "ctime"
#include "omp.h"

using namespace std;

vector<int> calcPrefixSum(vector<int> input, int num_threads){
    omp_set_num_threads(num_threads);
    int len = input.size();
    int curr = 1;

    while(curr<len){
        #pragma omp parallel for
        for(int ind=2*curr-1; ind<len; ind=ind+2*curr){
            input[ind] = input[ind] + input[ind - curr];
        }
        curr = 2*curr;
    }

    int temp_sum = input[len-1];
    input[len-1] = 0;

    while(curr>1){
        curr = curr/2;
        #pragma omp parallel for
        for(int ind=2*curr-1; ind<len;ind = ind + 2*curr){
            int temp_val = input[ind];
            input[ind] = input[ind] + input[ind - curr];
            input[ind - curr] = temp_val;
        }
    }

    input.push_back(temp_sum);
    input.erase(input.begin());
    return input;
}
