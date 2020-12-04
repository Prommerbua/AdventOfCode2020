#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::vector<std::vector<char>> Map;


void ReadInputDay3(const std::string path);
int TraverseMapPuzzleOne(std::vector<std::vector<char>> Map);
uint32_t TraverseMapPuzzleTwo(std::vector<std::vector<char>> Map);

int main()
{
	ReadInputDay3("input.txt");
	uint32_t count = TraverseMapPuzzleTwo(Map);
	std::cout << count;
}


void ReadInputDay3(const std::string path)
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
		std::vector<char> row;
		for (int i = 0; i < line.length(); ++i)
		{
			row.push_back(line[i]);
		}
		Map.push_back(row);
	}

	inFile.close();
}

int TraverseMapPuzzleOne(std::vector<std::vector<char>> Map)
{
	int currentPosition = 0;
	int row = 1;
	int treeCount = 0;
	while(row != Map.size())
	{
		currentPosition += 3;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount++;
		row++;
	}
	return treeCount;
}

uint32_t TraverseMapPuzzleTwo(std::vector<std::vector<char>> Map)
{
	int currentPosition = 0;
	int row = 1;
	int treeCount1 = 0;
	int treeCount2 = 0;
	int treeCount3 = 0;
	int treeCount4 = 0;
	int treeCount5 = 0;

	while (row != Map.size())
	{
		currentPosition += 1;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount1++;
		row++;
	}

	row = 1;
	currentPosition = 0;
	while (row != Map.size())
	{
		currentPosition += 3;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount2++;
		row++;
	}

	row = 1;
	currentPosition = 0;
	while (row != Map.size())
	{
		currentPosition += 5;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount3++;
		row++;
	}

	row = 1;
	currentPosition = 0;
	while (row != Map.size())
	{
		currentPosition += 7;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount4++;
		row++;
	}

	row = 2;
	currentPosition = 0;
	while (row < Map.size())
	{
		currentPosition += 1;
		if (currentPosition >= Map[row].size()) currentPosition %= Map[row].size();
		if (Map[row][currentPosition] == '#') treeCount5++;
		row += 2;
	}
	return treeCount1 * treeCount2 * treeCount3 * treeCount4 * treeCount5;;
}
