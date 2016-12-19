#include "stdafx.h"
#include "Decisionmaking.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

Decionmaking::Decionmaking()
{	
	criterions.insert(criterions.end(), {
		std::pair<std::string, float>("Price", 0.25),
		std::pair<std::string, float>("Traffic capacity", 0.25),
		std::pair<std::string, float>("Bandwidth", 0.1),
		std::pair<std::string, float>("Antennas", 0.1),
		std::pair<std::string, float>("Transmitter power", 0.15),
		std::pair<std::string, float>("Protocols and standards", 0.15)
	});

	options.insert(options.end(), {
		"ASUS RT-N12 VP",
		"TP-LINK TL-WR841N",
		"WiFi Zyxel Keenetic Viva",
		"ASUS RT-N18U ",
		"TP-LINK Archer C2"
	});

	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 0, 1, 1, 1}),
		(std::vector < byte > {1, 0, 1, 1, 1}),
		(std::vector < byte > {0, 0, 0, 1, 1}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 0, 0, 1, 0})
	});

	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 1, 0, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 1, 0, 0, 0}),
		(std::vector < byte > {1, 1, 1, 0, 0}),
		(std::vector < byte > {1, 1, 1, 1, 0})
	});
	
	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {1, 1, 1, 1, 0})
	});

	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 0, 1, 0, 0}),
		(std::vector < byte > {0, 0, 1, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {1, 1, 1, 0, 1}),
		(std::vector < byte > {1, 1, 1, 0, 0})
	});
	
	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 0, 1, 0, 0}),
		(std::vector < byte > {0, 0, 1, 1, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 0, 1, 0, 0}),
		(std::vector < byte > {1, 0, 1, 1, 0})
	});

	preferenceTables.push_back(std::vector < std::vector<byte> > {
		(std::vector < byte > {0, 1, 1, 1, 0}),
		(std::vector < byte > {0, 0, 1, 0, 0}),
		(std::vector < byte > {0, 0, 0, 0, 0}),
		(std::vector < byte > {0, 1, 1, 0, 0}),
		(std::vector < byte > {1, 1, 1, 1, 0})
	});


}


const responseDomination Decionmaking::domination()
{
	responseDomination response;
	std::vector<int> row_sum;

	for (int number_of_table = 0; number_of_table < preferenceTables.size(); number_of_table++)
	{
		row_sum.clear();
	
		for (auto& row_from_table : preferenceTables[number_of_table])
		{
			row_sum.push_back(std::accumulate(row_from_table.begin(), row_from_table.end(), 0));
		}

		size_t max_sum = *std::max_element(row_sum.begin(), row_sum.end());
		std::vector<int> row_indices;

		for (int i = 0; i < row_sum.size(); i++)
		{
			if (row_sum[i] == max_sum)
			{
				row_indices.push_back(i);
			}
		}

		response.push_back(std::pair<int, std::vector<int>>(number_of_table, row_indices));
	}
	return response;
}


const responseDomination Decionmaking::blocking()
{
	responseDomination response;
	std::vector<int> column_sum;

	for (int number_of_table = 0; number_of_table < preferenceTables.size(); number_of_table++)
	{
		column_sum.clear();

		for (int i = 0; i < preferenceTables[number_of_table].size(); i++)
		{
			size_t sum = 0;

			std::for_each(preferenceTables[number_of_table].begin(), preferenceTables[number_of_table].end(), [&i, &sum](auto& row) {
				sum += row.at(i);
			});

			column_sum.push_back(sum);
		}

		size_t min_sum = *std::min_element(column_sum.begin(), column_sum.end());
		std::vector<int> column_indices;

		for (int i = 0; i < column_sum.size(); i++)
		{
			if (column_sum[i] == min_sum)
			{
				column_indices.push_back(i);
			}
		}

		response.push_back(std::pair<int, std::vector<int>>(number_of_table, column_indices));
	}
	return response;
}

void Decionmaking::tournamentMechanism()
{
	std::vector<std::vector<double>> AllSummVectors;


	for (int number_of_table = 0; number_of_table < preferenceTables.size(); number_of_table++)
	{
		std::vector<double> row_sum;

		for (auto& row_from_table : preferenceTables[number_of_table])
		{
			row_sum.push_back(std::accumulate(row_from_table.begin(), row_from_table.end(), 0) * criterions[number_of_table].second);
		}

		AllSummVectors.push_back(std::move(row_sum));
	}
	
	//print first table
//--
	std::cout<<std::endl << std::setw(30) << " ";
	for (auto& i : options)
	{
		std::cout << std::setw(25) << i;
	}
	for (int i = 0; i < AllSummVectors.size(); i++)
	{
		std::cout << std::endl;
		std::cout << std::setw(30) << criterions.at(i).first;
		for (const auto& arg : AllSummVectors.at(i))
		{
			std::cout<<std::setw(25) << arg;
		}
	}
	std::cout << std::endl << std::endl;
//---	
		
	std::vector<std::pair<std::string, double>> TMPair;

	for (int i = 0; i < options.size(); i++)
	{
		double sum = 0;

		std::for_each(AllSummVectors.begin(), AllSummVectors.end(), [&i, &sum](auto& row) {
			sum += row.at(i);
		});

		TMPair.push_back(std::pair<std::string, double>(options.at(i), sum));
	}
	
	std::sort(TMPair.begin(), TMPair.end(), [](const auto& arg1, const auto& arg2) {
		return arg1.second > arg2.second;
	});
	for (auto& i : TMPair)
	{
		std::cout << i.first << ":" << i.second << std::endl;
	}
}

