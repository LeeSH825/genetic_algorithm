#pragma once
#include "Chromosome.h"

class npu_Chromosome: public Chromosome
{
	private:
		int node_num;

		char* generation_adjList();

	public:
		npu_Chromosome(){};
		void setNodeNum(int num){this->node_num = num;};


};

char* npu_Chromosome::generation_adjList(){

	// Generate AdjList
	std::vector<std::vector<int>> temp;
	for(int i=0; i < this->node_num; i++){
		int j = 0;
		std::vector<int> temp_row;
		// temp_row.push_back(i);
		while(1){
			j += this->random(0, this->node_num);
			if (j >= this->node_num)
				break;
			else
				temp_row.push_back(j);
		}
		temp.push_back(temp_row);
		temp_row.clear();
	}

	// Flatten to 1 long DNA
	std::vector<std::string> dna;
	for (int i=0; i < temp.size(); i++){
		dna.push_back("000");		// meaning: "000" => start of dna
		dna.push_back("001");		// meaning; "001" => array bracket
		dna.push_back("002");		// meaning: "002" => element separator (recognize as integer)
		for(int j = 0; j < temp[i].size(); j++){
			std::cout << temp[i][j] << " ";
		}
		std::cout << std::endl;
	}
}