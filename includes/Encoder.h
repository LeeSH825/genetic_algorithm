#pragma once
#include "whole_includes.h"

class Encoder
{
	private:
		std::string gene_encode_method;
		int code_length;
	public:
		Encoder();
		Encoder(std::string _gene_encode_method){this->gene_encode_method = _gene_encode_method;};

		void setMethod(std::string _gene_encode_method){this->gene_encode_method = _gene_encode_method;};
		void setCodeLength(int _length){this->code_length = _length;};
		

		std::string getEncoderMethod(){return this->gene_encode_method;};
		int getCodeLength(){return this->code_length;};
		
};