#pragma once

#include "../rapidjson-1.1.0/include/rapidjson/document.h"
#include "../rapidjson-1.1.0/include/rapidjson/filereadstream.h"
#include <vector>
#include <string>
#include <iostream>

using namespace rapidjson;
using std::vector;

class parseJSON
{
	private:
			Document root;
			char separator = ':';
			std::vector<std::string> root_vec;

			void print_doc(auto &v, int level);
			void print_array(auto &v, int level);

			void fill_doc(auto &v);
			void fill_array(auto &v);
			std::string parse_array(auto &v);


	public:
			parseJSON(){};
			parseJSON(std::vector<std::string> set_vec){this->root_vec = set_vec;};

			void set_vec(std::vector<std::string> set_vec){this->root_vec = set_vec;};
			void readFile(FILE *fp);
			void print_all();
			void fill_all();
			void print_vector(std::vector<std::string> vec);
			std::vector<std::string> get_root_vec(){return(this->root_vec);};
			std::vector<std::string> getValue(std::string str);
			

};

void parseJSON::print_array(auto &v, int level){
	if (v.IsInt())
		printf("%d", v.GetInt());
	else if (v.IsBool())
		printf("%s", v.GetBool() ? "true" : "false");
	else if (v.IsString())
		printf("%s", v.GetString());
	else if (v.IsDouble())
		printf("%lf", v.GetDouble());
	else if (v.IsArray()){
		for (auto &m : v.GetArray()){
			this->print_array(m, level);
			printf(",");
		}
	}
	else if (v.IsObject()){
		printf("\n");
		for (auto &m : v.GetObject()){
			for (int i=0; i<level; i++)
				printf("\t");
			this->print_doc(m, level+1);
			printf("\n");
		}
	}
}

void parseJSON::print_doc(auto& v, int level){
	// print name
	if (v.name.IsInt())
		printf("%d", v.name.GetInt());
	else if (v.name.IsBool())
		printf("%s", v.name.GetBool() ? "true" : "false");
	else if (v.name.IsString())
		printf("%s", v.name.GetString());
	else if (v.name.IsDouble())
		printf("%lf", v.name.GetDouble());

	// print separator
	printf("%c", this->separator);

	// print value
	if (v.value.IsInt())
		printf("%d", v.value.GetInt());
	else if (v.value.IsBool())
		printf("%s", v.value.GetBool() ? "true" : "false");
	else if (v.value.IsString())
		printf("%s", v.value.GetString());
	else if (v.value.IsDouble())
		printf("%lf", v.value.GetDouble());
	else if (v.value.IsArray()){
		for (auto &m : v.value.GetArray()){
			this->print_array(m, level);
			printf(",");
		}
	}
	else if (v.value.IsObject()){
		printf("\n");
		for (auto &m : v.value.GetObject()){
			for (int i=0; i<level; i++)
				printf("\t");
			this->print_doc(m, level+1);
			printf("\n");
		}
	}
}


void parseJSON::fill_array(auto &v){
	if (v.IsInt()){
		this->root_vec.push_back("int");
		this->root_vec.push_back((std::to_string(v.GetInt())));
	}
	else if (v.IsBool()){
		this->root_vec.push_back("bool");
		this->root_vec.push_back(v.GetBool() ? "true" : "false");
	}
	else if (v.IsString()){
		this->root_vec.push_back("string");
		this->root_vec.push_back(v.GetString());
	}
	else if (v.IsDouble()){
		this->root_vec.push_back("double");
		this->root_vec.push_back(std::to_string(v.GetDouble()));
	}
}

void parseJSON::fill_doc(auto &v){
	// fill name
	if (v.name.IsInt()){
		this->root_vec.push_back("int");
		this->root_vec.push_back((std::to_string(v.name.GetInt())));
	}
	else if (v.name.IsBool()){
		this->root_vec.push_back("bool");
		this->root_vec.push_back(v.name.GetBool() ? "true" : "false");
	}
	else if (v.name.IsString()){
		this->root_vec.push_back("string");
		this->root_vec.push_back(v.name.GetString());
	}
	else if (v.name.IsDouble()){
		this->root_vec.push_back("double");
		this->root_vec.push_back(std::to_string(v.name.GetDouble()));
	}

	// print separator
	// this->root_vec.push_back(":");

	// print value
		if (v.value.IsInt()){
		this->root_vec.push_back("int");
		this->root_vec.push_back((std::to_string(v.value.GetInt())));
	}
	else if (v.value.IsBool()){
		this->root_vec.push_back("bool");
		this->root_vec.push_back(v.value.GetBool() ? "true" : "false");
	}
	else if (v.value.IsString()){
		this->root_vec.push_back("string");
		this->root_vec.push_back(v.value.GetString());
	}
	else if (v.value.IsDouble()){
		this->root_vec.push_back("double");
		this->root_vec.push_back(std::to_string(v.value.GetDouble()));
	}
	else if (v.value.IsArray()){
		this->root_vec.push_back("array");
		for (auto &m : v.value.GetArray()){
			this->fill_array(m);
		}
		this->root_vec.push_back("array_end");
	}
	else if (v.value.IsObject()){
		this->root_vec.push_back("object");
		for (auto &m : v.value.GetObject()){
			this->fill_doc(m);
		}
		this->root_vec.push_back("object_end");
	}
}

void parseJSON::readFile(FILE *fp){
	char readbuffer[65536];
	FileReadStream is(fp, readbuffer, sizeof(readbuffer));
	this->root.ParseStream(is);
}

void parseJSON::print_all(){
	int level = 0;
	for(auto &m : this->root.GetObject()){
		this->print_doc(m, level);
	}
}

void parseJSON::fill_all(){
	for(auto &m : this->root.GetObject()){
		this->fill_doc(m);
	}
}

void parseJSON::print_vector(std::vector<std::string> vec){
	// std::vector<string>::iterator iter;
	for(std::vector<std::string>::iterator iter = vec.begin(); iter != vec.end(); iter++){
		std::cout << *iter << " ";
	}
}

std::string parseJSON::parse_array(auto &v){
	if (v.IsInt()){
		return((std::to_string(v.GetInt())));
	}
	else if (v.IsBool()){
		return(v.GetBool() ? "true" : "false");
	}
	else if (v.IsString()){
		return(v.GetString());
	}
	else if (v.IsDouble()){
		return(std::to_string(v.GetDouble()));
	}
	else
		return NULL;
}

std::vector<std::string> parseJSON::getValue(std::string str){
	std::vector<std::string> ret;
	if(this->root.HasMember(str.c_str())){
		if(this->root[str.c_str()].IsInt()){
			ret.push_back("int");
			ret.push_back(std::to_string(this->root[str.c_str()].GetInt()));
		}
		else if(this->root[str.c_str()].IsBool()){
			ret.push_back("bool");
			ret.push_back(this->root[str.c_str()].GetBool() ? "true" : "false");
		}
		else if (this->root[str.c_str()].IsString()){
			ret.push_back("string");
			ret.push_back(this->root[str.c_str()].GetString());
		}
		else if (this->root[str.c_str()].IsDouble()){
			ret.push_back("double");
			ret.push_back(std::to_string(this->root[str.c_str()].GetDouble()));
		}
		else if (this->root[str.c_str()].IsArray()){
			//TODO: what about combined array/
		ret.push_back("array");
		for (auto &m : this->root[str.c_str()].GetArray()){
			ret.push_back(parse_array(m));
		}
	}
	else if (this->root[str.c_str()].IsObject()){
		this->root_vec.push_back("object");
		for (auto &m : this->root[str.c_str()].GetObject()){
			;
			// TODO: fill this one!!!
		}
		}
	}
	return ret;
}