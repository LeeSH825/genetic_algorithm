#include "../includes/whole_includes.h"

int *end_flag_sum(int **parent, int *fitness_arr, int num_parent, int size)
{

    int best_fitness_val = 0;
    int best_fitness_idx = 0;
    for(int i=0; i<num_parent; i++){
        fitness_arr[i] = fitness_sum(parent[i], size);
        if (fitness_arr[i] >= best_fitness_val){
            best_fitness_val = fitness_arr[i];
            best_fitness_idx = i;
        }
        //cout << "fitness" << i << ":" << fitness_arr[i] << "\n";
    }
    int *ret = new int[2];
    ret[0] = best_fitness_idx;
    ret[1] = best_fitness_val;
    return (ret);
}

int *end_flag_sum2Value(int **parent, int *fitness_arr, int num_parent, int size, int value)
{
    int best_fitness_val = 0;
    int best_fitness_idx = 0;
    for (int i=0; i<num_parent; i++){
        fitness_arr[i] = fitness_sum2Value(parent[i], size, value);
        if (fitness_arr[i] >= best_fitness_val){
            best_fitness_val = fitness_arr[i];
            best_fitness_val = i;
        }
    }
    int *ret = new int[2];
    ret[0] = best_fitness_idx;
    ret[1] = best_fitness_val;
    return (ret);
}