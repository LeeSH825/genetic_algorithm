#include "../includes/whole_includes.h"

int *int_fixed_size_generation(int chromosome_size, int range_min, int range_max)
{
	int *new_chromosome = new int[chromosome_size];

	for(int i=0; i < chromosome_size; i++){
		new_chromosome[i] = int_random(range_min, range_max);
	}
	return new_chromosome;
}