#include "../includes/whole_includes.h"

int fitness_sum(int *chromosome, int chromosome_size)
{
    int sum = 0;

    for(int i=0; i < chromosome_size; i++){
        sum += chromosome[i];
    }
    return sum;
}

int fitness_sum2Value(int *chromosome, int chromosome_size, int value)
{
    int sum = 0;

    for(int i=0; i < chromosome_size; i++){
        sum += chromosome[i];
    }
    return 90-abs(sum-value);
}