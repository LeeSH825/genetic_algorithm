//#include "whole_includes.h"
// #include "Chromosome.h"

// #include <fstream>
#pragma once
#include "whole_includes.h"
#include "Chromosome.h"
class Gene_Pod
{
	private:
		// default params
		int num_generation;
		int num_population;
		int num_population_next;
		double mutation_rate;
		std::string gene_encode_method;
		std::string fitness_method;
		//std::ofstream save_file;

		// data
		Chromosome **gene_pool;
		double *fitness;

		// simulator internal function
		//   utils
		double fitness_avg();
		int best_Chromosome_idx();

		//   cross
		Chromosome *cross_simple(Chromosome parent1, Chromosome parent2);
		Chromosome *cross_simple(Chromosome parent1, Chromosome parent2, int _lengrh);
		Chromosome *cross_simple_percent(Chromosome parent1, Chromosome parent2);

		//   selection
		Chromosome selRoulette_Gene();

		//   fitness
		double fitness_sum(Chromosome individual);
		double fitness_sum2Value(Chromosome individual, int value);


	public:
		// simulator external function
		Gene_Pod(){};
		Gene_Pod(int generation_number, int population_size, double _mutation_rate, std::string _gene_encode_method, std::string _fitness_method);

		//~Gene_Pod();

		//Gene_Pod(int generation_number, int popuplation_size, double _mutation_rate, std::ofstream save_path);
		void init_population();
		void init_population(int chromosome_size);
		void set_population(Chromosome **pool, int pool_size);
		void calc_fitness(std::string calc_method);
		Chromosome **recombination_whole();
		Gene_Pod *succeeding_generation(Chromosome **next_gen);

		void report();
		void report_record();


};