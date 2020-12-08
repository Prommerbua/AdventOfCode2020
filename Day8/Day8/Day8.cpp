// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

void ReadInputDay6(const std::string path);

enum operation
{
	acc,
	jmp,
	nop
};

operation ConvertStringToOperation(std::string string)
{
	if (string == "acc") return acc;
	if (string == "jmp") return jmp;
	if (string == "nop") return nop;
}

struct Instruction
{
	Instruction() {  }

	operation operation;
	int32_t argument;
	bool executed = false;
};

std::vector<Instruction> instructions;
int32_t accumulator = 0;

int main()
{
	ReadInputDay6("input.txt");

	//Part 1
	for (int i = 0; i < instructions.size(); ++i)
	{
		if (instructions[i].executed == true)
		{
			std::cout << accumulator << std::endl;
			break;
		}

		instructions[i].executed = true;
		switch (instructions[i].operation)
		{
		case acc:
			accumulator += instructions[i].argument;
			break;
		case jmp:
			i += instructions[i].argument - 1;
			break;
		case nop:
			break;
		}
	}

	//reset
	accumulator = 0;
	for (int i = 0; i < instructions.size(); ++i)
	{
		instructions[i].executed = false;
	}
	//Part 2

	for (int i = 0; i < instructions.size(); ++i)
	{
		accumulator = 0;
		if (instructions[i].operation == jmp) instructions[i].operation = nop;
		else if (instructions[i].operation == nop) instructions[i].operation = jmp;


		for (int j = 0; j < instructions.size(); ++j)
		{
			if (j == instructions.size() - 1)
			{
				instructions[j].executed = true;
				switch (instructions[j].operation)
				{
				case acc:
					accumulator += instructions[j].argument;
					break;
				case jmp:
					j += instructions[j].argument - 1;
					break;
				case nop:
					break;
				}
				std::cout << accumulator;
				exit(0);
			}
			
			if (instructions[j].executed == true)
			{
				//infinite loop --> reset;
				if (instructions[i].operation == jmp) instructions[i].operation = nop;
				else if (instructions[i].operation == nop) instructions[i].operation = jmp;

				for (int k = 0; k < instructions.size(); ++k)
				{
					instructions[k].executed = false;
				}
				break;
			}

			instructions[j].executed = true;
			switch (instructions[j].operation)
			{
			case acc:
				accumulator += instructions[j].argument;
				break;
			case jmp:
				j += instructions[j].argument - 1;
				break;
			case nop:
				break;
			}
		}
	}
}

void ReadInputDay6(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;
	char delimiter = ' ';
	while (std::getline(inFile, line))
	{
		Instruction instruction;
		auto operation = line.substr(0, line.find(delimiter));
		int32_t argument = stoi(line.substr(line.find(delimiter) + 1, line.length() - line.find(delimiter)));

		instruction.operation = ConvertStringToOperation(operation);
		instruction.argument = argument;
		instructions.push_back(instruction);
	}
}
