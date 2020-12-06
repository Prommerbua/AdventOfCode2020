// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

void ReadInputDay6PuzzleOne(const std::string path);
void ReadInputDay6PuzzleTwo(const std::string path);


int main()
{
	ReadInputDay6PuzzleTwo("input.txt");
}

void ReadInputDay6PuzzleOne(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;

	bool questions[26] = { false };
	uint32_t sum = 0;
	while (std::getline(inFile, line))
	{
		if (line.empty())
		{
			uint32_t count = 0;
			for (int i = 0; i < 26; ++i)
			{
				if (questions[i]) count++;
			}
			sum += count;
			memset(questions, false, sizeof(questions));
		}

		for (int i = 0; i < line.length(); ++i)
		{
			auto element = toupper(line[i]);
			int index = static_cast<int>(element - 'A' + 1) - 1;

			questions[index] = true;
		}
	}

	uint32_t count = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (questions[i]) count++;
	}
	sum += count;
	std::cout << sum;
}

void ReadInputDay6PuzzleTwo(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;

	int questions[26] = { false };
	uint32_t sum = 0;
	int peopleInGroup = 0;
	while (std::getline(inFile, line))
	{
		if (line.empty())
		{
			uint32_t count = 0;
			for (int i = 0; i < 26; ++i)
			{
				if (questions[i] == peopleInGroup) count++;
			}
			sum += count;
			memset(questions, 0, sizeof(questions));
			peopleInGroup = 0;
		}else
		{
			peopleInGroup++;
			for (int i = 0; i < line.length(); ++i)
			{
				auto element = toupper(line[i]);
				int index = static_cast<int>(element - 'A' + 1) - 1;

				questions[index]++;
			}
		}
	}

	uint32_t count = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (questions[i] == peopleInGroup) count++;
	}
	sum += count;
	std::cout << sum;
}