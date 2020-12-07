// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <stack>

void ReadInputDay7PuzzleOne(const std::string path);
void ReadInputDay7PuzzleTwo(const std::string path);
void NextTry(const std::string path);
uint32_t CountIndividualBags();


// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

struct Bag
{
public:
	Bag() {  }
	friend bool operator==(const Bag& a, const Bag& b);

	Bag(std::string attribute, std::string color) : attribute_(std::move(attribute)), color_(std::move(color)) {  }

	std::string attribute_;
	std::string color_;

	std::map<uint32_t, Bag (*)()> containsBags;
};

bool operator==(const Bag& a, const Bag& b) { return a.attribute_ == b.attribute_ && a.color_ == b.color_; }

Bag readOneBagFromString(std::string bagString)
{
	return Bag(bagString.substr(0, bagString.find(' ')), bagString.substr(bagString.find(' ') + 1, bagString.find(' ') - bagString.length()));
}

std::map<uint32_t, Bag> readMultipleBagsFromString(std::string bagString)
{
	std::map<uint32_t, Bag> bags;
	trim(bagString.erase(bagString.find("contain"), 7));

	if (bagString.find("no other bags") != std::string::npos) return bags;

	//Multiple Bags
	if (bagString.find(',') != std::string::npos)
	{
		size_t pos = 0;
		std::string token;
		while ((pos = bagString.find(',')) != std::string::npos) {
			token = bagString.substr(0, pos);

			uint32_t numberOfBags = token[0] - '0';
			token.erase(0, 2);

			std::string attribute, color;

			attribute = token.substr(0, token.find(' '));
			token.erase(0, attribute.length() + 1);
			color = token.substr(0, token.find(' '));

			Bag bag(attribute, color);
			bags.insert(std::pair<uint32_t, Bag>(numberOfBags, bag));

			bagString.erase(0, pos + 2);
		}

		uint32_t numberOfBags = bagString[0] - '0';
		bagString.erase(0, 2);
		std::string attribute, color;

		attribute = bagString.substr(0, bagString.find(' '));
		bagString.erase(0, attribute.length() + 1);
		color = bagString.substr(0, bagString.find(' '));

		Bag bag(attribute, color);
		bags.insert(std::pair<uint32_t, Bag>(numberOfBags, bag));

	}
	else
	{
		uint32_t numberOfBags = bagString[0] - '0';
		bagString.erase(0, 2);
		std::string attribute, color;

		attribute = bagString.substr(0, bagString.find(' '));
		bagString.erase(0, attribute.length() + 1);
		color = bagString.substr(0, bagString.find(' '));

		Bag bag(attribute, color);
		bags.insert(std::pair<uint32_t, Bag>(numberOfBags, bag));
	}

	//Bag(bagString.substr(0, bagString.find(' ')), bagString.substr(bagString.find(' ') + 1, bagString.find(' ') - bagString.length()));
	return bags;
}

std::vector<Bag> shinyBags;
Bag* goldenBag;
uint32_t bagCount = 0;


int main()
{
	ReadInputDay7PuzzleTwo("example.txt");
	std::cout << CountIndividualBags();
}

void ReadInputDay7PuzzleOne(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;



	Bag bag("shiny", "gold");

	shinyBags.push_back(bag);

	while (std::getline(inFile, line))
	{
		std::string delimiter = "contain";
		std::string firstBag = line.substr(0, line.find(delimiter));
		std::string otherBags = line.substr(line.find(delimiter), line.length() - line.find(delimiter));

		for (Bag shinybag : shinyBags)
		{
			if (firstBag.find(shinybag.attribute_ + " " + shinybag.color_) != std::string::npos)
			{
				rtrim(firstBag.erase(firstBag.find("bags"), 4));
				Bag newBag = readOneBagFromString(firstBag);
				if (std::find(shinyBags.begin(), shinyBags.end(), newBag) == shinyBags.end())
				{
					shinyBags.push_back(newBag);
					inFile.seekg(0);
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void ReadInputDay7PuzzleTwo(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;



	Bag bag("shiny", "gold");
	uint32_t depth = 0;

	shinyBags.push_back(bag);

	while (std::getline(inFile, line))
	{
		std::string delimiter = "contain";
		std::string firstBag = line.substr(0, line.find(delimiter));
		std::string otherBags = line.substr(line.find(delimiter), line.length() - line.find(delimiter));

		
		for (uint32_t i = 0; i < shinyBags.size(); ++i)
		{
			if (firstBag.find(shinyBags[i].attribute_ + " " + shinyBags[i].color_) != std::string::npos)
			{
				rtrim(firstBag.erase(firstBag.find("bags"), 4));
				Bag newBag = readOneBagFromString(firstBag);
				if (std::find(shinyBags.begin(), shinyBags.end(), newBag) != shinyBags.end() && shinyBags[i].containsBags.empty())
				{




					
					auto bags = readMultipleBagsFromString(otherBags);
					if (bags.empty()) break;
					shinyBags[i].containsBags = bags;
					for (auto bag : bags)
					{
						if (std::find(shinyBags.begin(), shinyBags.end(), bag.second) == shinyBags.end())
						{
							shinyBags.push_back(bag.second);
						}
					}
					inFile.seekg(0);
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void NextTry(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}
	std::string line;

	Bag* currentBag = new Bag("shiny", "gold");

	while (currentBag != nullptr)
	{
		while (std::getline(inFile, line))
		{
			std::string delimiter = "contain";
			std::string firstPart = line.substr(0, line.find(delimiter));
			std::string secondPart = line.substr(line.find(delimiter), line.length() - line.find(delimiter));

			if (firstPart.find(currentBag->attribute_ + " " + currentBag->color_) != std::string::npos)
			{

			}
		}
	}

}


uint32_t CountIndividualBags()
{
	std::stack<std::pair<uint32_t, Bag>> stk;
	stk.push(std::pair<uint32_t, Bag>(1, shinyBags[0]));

	while(!stk.empty())
	{
		auto top = stk.top();
		stk.pop();

		
		for (auto containedBag : top.second.containsBags)
		{
			stk.push(containedBag);
		}
		
	}

	return bagCount;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
