#pragma once
#include<string>
#include<vector>


using criterionsVector = std::vector<std::pair<std::string, float>>;
using optionsVector = std::vector<std::string>;
using byte = char;
using preferenceTablesVector = std::vector<std::vector<std::vector<byte>>>;


class Decionmaking
{
	criterionsVector criterions;
	optionsVector options;
	preferenceTablesVector preferenceTables;
public:
	Decionmaking();
	const std::vector<std::pair<std::string, int>> domination();
	//void print();
};

//
