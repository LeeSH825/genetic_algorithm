#include "./includes/Chromosome.h"
#include "./includes/Gene_Pod.h"
#include "./includes/whole_includes.h"
#include "./includes/flags.h"

using namespace std;
int main(int argc, char *argv[])
{
	int size = 10;
	int population = 100;
	int generation = 100;
	double mutation_rate = 0.001;
	std::string gene_encode_method = "int";
	std::string fitness_method = "sum2Value";

	//  Parsing
	cout << "Gene Pod Settings:" << endl;
	const flags::args args(argc, argv);
	const auto size_parsed = args.get<int>("size");
	if (size_parsed){
		size = *size_parsed;
		cout << "size: " << size << endl;
	}
	else
		cout << "size: " << size << "(default)" << endl;

	const auto population_parsed = args.get<int>("population");
	if (population_parsed){
		population = *population_parsed;
		cout << "num_parent: " << population << endl;
	}
	else
		cout << "num_parent: " << population << "(defalut)" << endl;

	const auto generation_parsed = args.get<int>("generation");
	if (generation_parsed){
		generation = *generation_parsed;
		cout << "genertion_num: " << generation << endl;
	}
	else 
		cout << "genertion_num: " << generation << "(default)" << endl;

	const auto mutation_rate_parsed = args.get<double>("mutation_rate");
	if (mutation_rate_parsed){
		mutation_rate = *mutation_rate_parsed;
		cout << "mutation_rate: " << mutation_rate << endl;
	}
	else 
		cout << "mutation_rate: " << mutation_rate << "(default)" << endl;

	const auto encode_parsed = args.get<std::string>("gene_encode");
	if (encode_parsed){
		gene_encode_method = *encode_parsed;
		cout << "gene_encode_method: " << gene_encode_method << endl;
	}
	else 
		cout << "gene_encode_method: " << gene_encode_method << "(default)" << endl;

	const auto fitness_parsed = args.get<std::string>("fitness");
	if (fitness_parsed){
		fitness_method = *fitness_parsed;
		cout << "fitness_method: " << fitness_method << endl;
	}
	else 
		cout << "fitness_method: " << fitness_method << "(default)" << endl;
	cout << endl;
	
	Gene_Pod *pod = new Gene_Pod [generation];
	pod[0] = Gene_Pod(0, population, mutation_rate, gene_encode_method, fitness_method);
	pod[0].init_population(size);
	// pod[0].report();
	//pod[0].calc_fitness("sum2Value");
	// pod[0].report();
	for (int i=1; i < generation; i++){
		pod[i-1].calc_fitness(fitness_method);
	 	pod[i-1].report();

	 	//pod[i+1] = *pod[i].succeeding_generation(pod[i].recombination_whole());

		pod[i] = Gene_Pod(i, population, mutation_rate, gene_encode_method, fitness_method);
		pod[i].set_population(pod[i-1].recombination_whole(), population);
	 }
	 pod[generation-1].calc_fitness(fitness_method);
	 pod[generation-1].report();
}