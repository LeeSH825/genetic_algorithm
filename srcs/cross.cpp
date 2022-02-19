#include "../includes/whole_includes.h"

int *cross_simple(int *parent1, int *parent2, int chromosome_size)
{
    int cross_point = int_random(0, chromosome_size);
    int *child = new int[chromosome_size];

    for (int i=0; i< chromosome_size; i++){
        if (i < cross_point)
            child[i] = parent1[i];
        else
            child[i]  = parent2[i];
    }
    return (child);
}

int *cross_simple_percent(int *parent1, int *parent2, int chromosome_size)
{
    int cross_point = int_random(0, chromosome_size);
    int *child = new int[chromosome_size];
	int *parent[2] = {parent1, parent2};

	int percent[2] = {7,3};
	if (roulette_wheel(percent, 2)){
		int idx1 = int_random(0, 1);
		for (int i=0; i<cross_point; i++){
			child[i] = parent[idx1][i];
		}
		int idx2 = int_random(0, 1);
		for (int i=cross_point; i<chromosome_size; i++){
			child[i] = parent[idx2][i];
		}
	}
	else{
		int idx = int_random(0,1);
		for (int i=0; i<chromosome_size; i++){
			child[i] = parent[idx][i];
		}
	}
	return (child);
}