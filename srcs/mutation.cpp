#include "../includes/whole_includes.h"

using namespace std;

int *mutation_simple(int *chromosome, int chromosome_size, double mutation_rate)
{
    int *mutated_chromosome = new int[chromosome_size];

    double percent[2] = {1, mutation_rate};
    while(1){
        if (percent[1] <1){
            percent[0] *= 10;
            percent[1] *= 10;
        }
        else
            break;
    }
    int percent_int[2] = {(int)percent[0], (int)percent[1]};
    for(int i=0; i< chromosome_size; i++){
        if (roulette_wheel(percent_int, 2)){
            mutated_chromosome[i] = int_random(0, 9);
            //cout <<"mutation~";
        }
        else
            mutated_chromosome[i] = chromosome[i];
    }
    return (mutated_chromosome);
}