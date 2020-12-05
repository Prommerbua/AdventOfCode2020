// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::string> seats;

void ReadInputDay5(const std::string path);
uint32_t solvePuzzleOne();
uint32_t solvePuzzleTwo();

int main()
{
	ReadInputDay5("input.txt");
	std::cout << solvePuzzleTwo();
}

void ReadInputDay5(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;

	while (std::getline(inFile, line))
	{
		seats.push_back(line);
	}
}

uint32_t solvePuzzleOne()
{
	uint32_t maxID = 0;

	for (auto seat : seats)
	{
		uint32_t rowLowerBoundary = 0;
		uint32_t rowUpperBoundary = 127;
		uint32_t seatLowerBoundary = 0;
		uint32_t seatUpperBoundary = 7;

		uint32_t rowNumber;
		uint32_t seatNumber;

		for (int i = 0; i < seat.length(); ++i)
		{
			if (seat[i] == 'F')
			{
				rowUpperBoundary = floor(static_cast<float>(rowUpperBoundary + rowLowerBoundary) / 2);
			}
			else if (seat[i] == 'B')
			{
				rowLowerBoundary = ceil(static_cast<float>(rowUpperBoundary + rowLowerBoundary) / 2);
			}
			else if (seat[i] == 'L')
			{
				seatUpperBoundary = floor(static_cast<float>(seatUpperBoundary + seatLowerBoundary) / 2);
			}
			else if (seat[i] == 'R')
			{
				seatLowerBoundary = ceil(static_cast<float>(seatUpperBoundary + seatLowerBoundary) / 2);
			}

		}

		rowNumber = rowLowerBoundary;
		seatNumber = seatLowerBoundary;
		uint32_t id = rowNumber * 8 + seatNumber;
		if (id > maxID) maxID = id;
	}

	return maxID;
}

uint32_t solvePuzzleTwo()
{
	uint32_t myID = 0;
	bool occupiedSeats[128 * 8] = { false };

	for (auto seat : seats)
	{
		uint32_t rowLowerBoundary = 0;
		uint32_t rowUpperBoundary = 127;
		uint32_t seatLowerBoundary = 0;
		uint32_t seatUpperBoundary = 7;

		uint32_t rowNumber;
		uint32_t seatNumber;

		for (int i = 0; i < seat.length(); ++i)
		{
			if (seat[i] == 'F')
			{
				rowUpperBoundary = floor(static_cast<float>(rowUpperBoundary + rowLowerBoundary) / 2);
			}
			else if (seat[i] == 'B')
			{
				rowLowerBoundary = ceil(static_cast<float>(rowUpperBoundary + rowLowerBoundary) / 2);
			}
			else if (seat[i] == 'L')
			{
				seatUpperBoundary = floor(static_cast<float>(seatUpperBoundary + seatLowerBoundary) / 2);
			}
			else if (seat[i] == 'R')
			{
				seatLowerBoundary = ceil(static_cast<float>(seatUpperBoundary + seatLowerBoundary) / 2);
			}

		}

		rowNumber = rowLowerBoundary;
		seatNumber = seatLowerBoundary;
		uint32_t ID = rowNumber * 8 + seatNumber;
		occupiedSeats[ID] = true;

	}

	//ignore first and last entries
	for (int i = 1; i < 128*8-1; ++i)
	{
		if (occupiedSeats[i] == false && occupiedSeats[i - 1] == true && occupiedSeats[i + 1] == true) return i;
	}
}

