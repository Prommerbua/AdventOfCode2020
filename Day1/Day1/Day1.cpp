// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> ReadInputFile(std::string path);

int main()
{
    std::cout << "Hello World!\n";
	auto numbers = ReadInputFile("input.txt");

	//Part One
	
    /*for (int i = 0; i < numbers.size(); ++i)
    {
	    for (int j = i + 1; j < numbers.size(); ++j)
	    {
		    if(numbers[i] + numbers[j] == 2020)
		    {
				std::cout << "First number: " << numbers[i] << std::endl;
				std::cout << "Second number: " << numbers[j] << std::endl;
				std::cout << "Result: " << numbers[i] * numbers[j] << std::endl;
				exit(2);
		    }
	    }
    }*/

	//Part Two
	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = i + 1; j < numbers.size(); ++j)
		{
			for (int k = j + 1; k < numbers.size(); ++k)
			{
				if (numbers[i] + numbers[j] + numbers[k] == 2020)
				{
					std::cout << "First number: " << numbers[i] << std::endl;
					std::cout << "Second number: " << numbers[j] << std::endl;
					std::cout << "Second number: " << numbers[k] << std::endl;
					std::cout << "Result: " << numbers[i] * numbers[j] * numbers[k] << std::endl;
					exit(2);
				}
			}
		}
	}
}

std::vector<int> ReadInputFile(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if(!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}

	std::string line;
	std::vector<int> fileContent;
	
	while(std::getline(inFile, line))
	{
		
		fileContent.push_back(std::stoi(line));
	}

	inFile.close();
	return fileContent;
}
