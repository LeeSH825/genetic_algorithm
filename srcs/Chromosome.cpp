#include "../includes/Chromosome.h"

// Iniitalizer
Chromosome::Chromosome(std::string _gene_encode_method)
{
	this->gene_encode_method = _gene_encode_method;
	this->gene_min = this->getGeneMin(_gene_encode_method);
	this->gene_max = this->getGeneMax(_gene_encode_method);
	this->geneCode = this->generaton_full_random();
}
Chromosome::Chromosome(int _length, std::string _gene_encode_method)
{
	this->length = _length;
	this->gene_encode_method = _gene_encode_method;
	this->gene_min = getGeneMin(_gene_encode_method);
	this->gene_max = getGeneMax(_gene_encode_method);
	this->geneCode = generaton_fixed_length(_length);				//TODO: generation method??
}

// Chromosome::~Chromosome()
// {
// 	delete[] geneCode;
// }

// Calculate params
int Chromosome::getGeneMin(std::string gene_method)
{
	if (!gene_method.compare("quaternary"))
		return 0;
	if (!gene_method.compare("int"))
		return 9;
	return 0;
}

int Chromosome::getGeneMax(std::string gene_method)
{
	if (!gene_method.compare("quaternary"))
		return 4;
	if (!gene_method.compare("int"))
		return 9;
	return 9;
}


// Generation
char *Chromosome::generaton_fixed_length(int _length)
{
	char *new_chromosome = new char[_length];
	for(int i=0; i < _length; i++){
		if (!this->gene_encode_method.compare("int"))
			new_chromosome[i] = int_random(gene_min, gene_max);
	}
	return new_chromosome;
}

char *Chromosome::generaton_full_random()
{
	this->length = int_random(0, 1000);								//TODO: 1000 -> limited range??
	char *new_geneCode = new char[this->length];
	for (int i=0; i < this->length; i++){
		if (!this->gene_encode_method.compare("int"))
			new_geneCode[i] = int_random(gene_min, gene_max);
	}
	return new_geneCode;
}


// Mutation
void Chromosome::mutation_simple(double mutation_rate)
{
	// make discrete distribution
	double percent[2] = {1, mutation_rate};
	while(1){
		if (percent[1] < 1){
			percent[0] *= 10;
			percent[1] *= 10;
		}
		else
			break;
	}

	// get random value with mutation rate
	int percent_int[2] = {(int)percent[0]-(int)percent[1], (int)percent[1]};
	for(int i=0; i < this->length; i++){
		if (roulette_wheel(percent_int, 2)){
			this->geneCode[i] = int_random(this->gene_min, this->gene_max);
		}
	}
}


// Print variables
void Chromosome::showGeneCode()
{
	for(int i=0; i < length; i++){
		std::cout << (int)geneCode[i] << ",";
		//std::cout << "length: " << this->length << "    ";
	}
}