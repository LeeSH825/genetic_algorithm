//#include "whole_includes.h"
//#include <string>
#pragma once
#include "whole_includes.h"

class Chromosome
{
	private:
		// default params
		int length;
		int gene_min;
		int gene_max;

		// actual data
		char *geneCode;
		std::string gene_encode_method;

		// set gene_params       TODO: int -> char convert
		int getGeneMin(std::string gene_method);
		int getGeneMax(std::string gene_method);

		// generation
		char *generaton_fixed_length(int _length);
		char *generaton_full_random();


	public:
		//    Initializer
		Chromosome(){};
		Chromosome(std::string _gene_encode_method);
		Chromosome(int _length, std::string _gene_encode_method);

		//~Chromosome();

		//    set internal variables
		void setLength(int _length){this->length = _length;};
		void setGeneCode(char *_geneCode){this->geneCode = _geneCode;};
		void setGeneCode(){this->geneCode = this->generaton_fixed_length(this->length);};					//TODO: if this thing blow away?

		//    export internal variables
		char *getGeneCode(){return this->geneCode;};
		std::string getEncodeMethod(){return this->gene_encode_method;};
		int getLength(){return this->length;};

		//   mutation
		void mutation_simple(double mutation_rate);

		//   print internal variables
		void showGeneCode();
};