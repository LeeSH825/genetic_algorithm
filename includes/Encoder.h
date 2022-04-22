#pragma once
#include "whole_includes.h"
#include "parseJSON.h"
// #include <vector>

// Decoder -> Ribosome


class Encoder: parseJSON
{
	private:
		std::string gene_encode_method;
		int code_length;
		std::vector<vector<int>> adj_list;
		
	public:
		Encoder();
		Encoder(std::string _gene_encode_method){this->gene_encode_method = _gene_encode_method;};

		void setMethod(std::string _gene_encode_method){this->gene_encode_method = _gene_encode_method;};
		void setCodeLength(int _length){this->code_length = _length;};
		
		std::string getEncoderMethod(){return this->gene_encode_method;};
		int getCodeLength(){return this->code_length;};
		
		void getAdjavencylist();


};

void Encoder::getAdjavencylist(){
	for(std::vector<std::string>::iterator iter = this->get_root_vec().begin(); iter != this->get_root_vec().end(); iter++){
		std::vector<int> temp_row;
		while(1){
			if ((*iter).compare("array_end")){
				adj_list.push_back(temp_row);
				break;
			}
			else{
				temp_row.push_back(std::stoi(*iter));
			}
			++iter;
		}
	}
}