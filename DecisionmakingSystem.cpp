// DecisionmakingSystem.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Decisionmaking.h"
#include "iostream"
#include <algorithm>


int _tmain(int argc, _TCHAR* argv[])
{
	Decionmaking temp;

	std::cout << "domination";
	const responseDomination domination_response = temp.domination();
	
	for (const auto& i : domination_response)
	{
		std::cout << std::endl <<"table: "<< i.first + 1 << ":";
		for (const auto& arg : i.second)
		{
			std::cout<< arg+1<<",";
		}
	}

	std::cout << std::endl;
	std::cout << "blocking";
	const responseDomination domination_blocking = temp.blocking();

	for (const auto& i : domination_blocking)
	{
		std::cout << std::endl << "table: " << i.first + 1 << ":";
		for (const auto& arg : i.second)
		{
			std::cout << arg + 1 << ",";
		}
	}

	temp.tournamentMechanism();
	
	system("Pause");
	return 0;
}

