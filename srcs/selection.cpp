#include "../includes/whole_includes.h"

int *selection_roulette(int **chromosome,  int *chromosome_fitness, int chromosome_num)
{
    return (chromosome[roulette_wheel(chromosome_fitness, chromosome_num)]);
}