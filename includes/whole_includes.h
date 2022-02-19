#pragma once
#ifndef WHOLE_INCLUDES_H_
#define WHOLE_INCLUDES_H_

// common headers
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>

#include "Chromosome.h"
//#include "Gene_Pod.h"




// srcs/cross.cpp
int *cross_simple(int *parent1, int *parent2, int chromosome_size);
int *cross_simple_percent(int *parent1, int *parent2, int chromosome_size);

// srcs/end_flag.cpp
int *end_flag_sum(int **parent, int *fitness_arr, int num_parent, int size);
int *end_flag_sum2Value(int **parent, int *fitness_arr, int num_parent, int size, int value);

// srcs/fitness.cpp
int fitness_sum(int *chromosome, int chromosome_size);
int fitness_sum2Value(int *chromosome, int chromosome_size, int value);

// srcs/generation.cpp
int *int_fixed_size_generation(int chromosome_size, int range_min, int range_max);

// srcs/mutation.cpp
int *mutation_simple(int *chromosome, int chromosome_size, double mutation_rate);

// srcs/selection.cpp
int *selection_roulette(int **chromosome,  int *chromosome_fitness, int chromosome_num);

//srcs/utils.cpp
int int_random(int range_min, int range_max);
int roulette_wheel(int *prob, int prob_num);

#endif