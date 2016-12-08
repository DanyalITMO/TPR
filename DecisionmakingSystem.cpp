// DecisionmakingSystem.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Decisionmaking.h"
#include "iostream"

int _tmain(int argc, _TCHAR* argv[])
{
	Decionmaking temp;
	const responseDomination domination_response = temp.domination();

	for (const auto& i : domination_response)
	{
		std::cout << std::endl <<"row: "<< i.first << ":";
		for (const auto& arg : i.second)
		{
			std::cout<< arg<<",";
		}
	}
	system("Pause");
	return 0;
}

