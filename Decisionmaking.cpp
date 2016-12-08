#include "stdafx.h"
#include "Decisionmaking.h"
#include <iostream>
#include <algorithm>
#include <numeric>

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
			if (row_sum[i] >= max_sum)
			{
				max_sum = row_sum[i];
				row_indices.push_back(i);
			}
		}

		response.push_back(std::pair<int, std::vector<int>>(number_of_table, row_indices));
	}
	return response;
}