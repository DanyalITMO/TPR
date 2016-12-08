// DecisionmakingSystem.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Decisionmaking.h"
#include "iostream"

int _tmain(int argc, _TCHAR* argv[])
{
	Decionmaking temp;
	const std::vector<std::pair<std::string, int>> domination_response = temp.domination();

	std::cout << domination_response.size()<<std::endl;
	/*for (const auto& i : domination_response)
	{
		std::cout << i.first << "|" << i.second << std::endl;
	}*/
	system("Pause");
	return 0;
}

