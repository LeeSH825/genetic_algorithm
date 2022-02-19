#include "../includes/Gene_Pod.h"


Gene_Pod::Gene_Pod(int generation_number, int population_size, double _mutation_rate, std::string _gene_encode_method, std::string _fitness_method)
{
	this->num_generation = generation_number;
	this->num_population = population_size;
	this->mutation_rate = _mutation_rate;
	this->fitness = new double [population_size];
	this->gene_pool = new Chromosome*[population_size];
	this->gene_encode_method = _gene_encode_method;
	this->fitness_method = _fitness_method;

	//this->save_file = NULL;
}

// Gene_Pod::Gene_Pod(int generation_number, int population_size, double _mutation_rate, std::ofstream save_path)
// {
// 	this->num_generation = generation_number;
// 	this->num_population = population_size;
// 	this->mutation_rate = _mutation_rate;
// 	this->fitness = new double [population_size];
// 	this->gene_pool = new Chromosome*[population_size];
// 	// this->save_file = save_path;				TODO: ofstream override??
// }

// Gene_Pod::~Gene_Pod()
// {
// 	for(int i=0; i < num_population; i++){
// 		delete[] gene_pool[i];
// 	}
// 	delete[] fitness;
// }

double Gene_Pod::fitness_avg()
{
	// calculate average of fitness
	double sum_fit = 0.0;
	for(int i=0; i < this->num_population; i++){
		sum_fit += fitness[i];
	}
	return (double)sum_fit/this->num_population;
}

int Gene_Pod::best_Chromosome_idx()
{
	double best_fitness_val = 0;
	int best_fitness_idx = 0;
	for (int i=0; i < this->num_population; i++){
		if (fitness[i] >= best_fitness_val){
			best_fitness_idx = i;
			best_fitness_val = fitness[i];
		}
	}
	return best_fitness_idx;
}

void Gene_Pod::init_population()
{
	//TODO: howto just class container->initialize each sector? ?????is it wight to do??????
	for(int i=0; i < this->num_population; i++){
		Chromosome *temp = new Chromosome(this->gene_encode_method);
		this->gene_pool[i] = temp;
	}
}

void Gene_Pod::init_population(int chromosome_size)								//TODO: in Generic way??
{
	for(int i=0; i < this->num_population; i++){
		Chromosome *temp = new Chromosome(chromosome_size, this->gene_encode_method);
		this->gene_pool[i] = temp;
	}
}

void Gene_Pod::set_population(Chromosome **pool, int pool_size)
{
	// for(int i=0; i < pool_size; i++){
	// 	this->gene_pool[i] = &(pool[i]);
	// }
	this->gene_pool = pool;
}

// Calculate Fitness
void Gene_Pod::calc_fitness(std::string calc_method)
{
	// TODO: how to take several methods?? by using strcmp?
	if (!calc_method.compare("sum2Value")){
		for(int i=0; i < num_population; i++){
			fitness[i] = fitness_sum2Value(*gene_pool[i], 40);		// TODO: instead of 40 (fixed value?)
		}
	}
	if (!calc_method.compare("sum")){
		for(int i=0; i < this->num_population; i++){
			fitness[i] = fitness_sum(*gene_pool[i]);
		}
	}
}

double Gene_Pod::fitness_sum(Chromosome individual)
{
	int sum = 0;
	int _length = individual.getLength();
	char *_geneCode = individual.getGeneCode();
	for(int i=0; i < _length; i++){
		sum += (int)_geneCode[i];
	}
	return (double)sum;
}

double Gene_Pod::fitness_sum2Value(Chromosome individual, int value)
{
	int sum = 0;
	int _length = individual.getLength();
	char *_geneCode = individual.getGeneCode();
	for(int i=0; i < _length; i++){
		sum += (int)_geneCode[i];
	}
	return (double)90-abs(sum-value);
}

// Cross
Chromosome Gene_Pod::selRoulette_Gene()
{
	std::vector<double> probList;
	for (int i=0; i < this->num_population; i++){
		probList.push_back(this->fitness[i]);
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<int> d{ probList.cbegin(), probList.cend() };
	return ((*gene_pool[d(gen)]));				//TODO: how to apply this pointer
}

Chromosome *Gene_Pod::cross_simple(Chromosome parent1, Chromosome parent2)
{
	int crossPoint1 = int_random(0, parent1.getLength());
	int crossPoint2 = int_random(0, parent2.getLength());
	Chromosome *child = new Chromosome;
	int child_length = crossPoint1+(parent2.getLength()-crossPoint2);
	child->setLength(child_length);
	char *geneCode_child = new char [child_length];
	
	for (int i=0; i < child_length; i++){
		if (i < crossPoint1)
			geneCode_child[i] = parent1.getGeneCode()[i];
		else
			geneCode_child[i] = parent2.getGeneCode()[crossPoint2++];
	}
	child->setGeneCode(geneCode_child);

	return (child);
}

Chromosome *Gene_Pod::cross_simple(Chromosome parent1, Chromosome parent2, int _length)
{
	int crossPoint1 = int_random(0, parent1.getLength());
	int crossPoint2 = int_random(0, parent2.getLength());
	Chromosome *child = new Chromosome;
	int child_length = crossPoint1+(parent2.getLength()-crossPoint2);
	child->setLength(child_length);
	char *geneCode_child = new char [child_length];
	
	for (int i=0; i < child_length; i++){
		if (i < _length && crossPoint2 < parent2.getLength()){
			if (i < crossPoint1)
				geneCode_child[i] = parent1.getGeneCode()[i];
			else
				geneCode_child[i] = parent2.getGeneCode()[crossPoint2++];
		}
	}

	child->setGeneCode(geneCode_child);

	return (child);
}


Chromosome **Gene_Pod::recombination_whole()									//TODO: about next generation's population?
{
	this->num_population_next = num_population;
	Chromosome **gene_next_pool = new Chromosome *[this->num_population_next];
	//Chromosome *individual_next_pool = new Chromosome [this->num_population];
	for(int i=0; i < this->num_population_next; i++){
		gene_next_pool[i] = cross_simple(selRoulette_Gene(), selRoulette_Gene(), 10);
		gene_next_pool[i]->mutation_simple(this->mutation_rate);
	}
	
	return gene_next_pool;
}

Gene_Pod *Gene_Pod::succeeding_generation(Chromosome **next_gene)
{
	//Gene_Pod *next_gen = new Gene_Pod;
	Gene_Pod *next_gen = new Gene_Pod(this->num_generation+1, this->num_population_next, this->mutation_rate, this->gene_encode_method, this->fitness_method);
	next_gen->set_population(next_gene, next_gen->num_population_next);
	return (next_gen);
}

void Gene_Pod::report()
{
	std::cout << "Generation [ " << this->num_generation << " ] Report:" << std::endl;
	std::cout << "population: " << this->num_population << std::endl;
	std::cout << "mutation_rate: " << this->mutation_rate << std::endl;
	std::cout << "fitness_avg: " << this->fitness_avg() << std::endl;
	std::cout << "best Chromosome: ";
	gene_pool[this->best_Chromosome_idx()]->showGeneCode();
	std::cout << " with fitness: " << fitness[this->best_Chromosome_idx()];
	std::cout << std::endl << std::endl;
}