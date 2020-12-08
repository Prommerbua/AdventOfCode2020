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

	std::vector<std::pair<uint32_t, std::function<Bag()>>> containsBags;

	std::string toString() const
	{
		return attribute_ + color_;
	}
};

bool operator==(const Bag& a, const Bag& b) { return a.attribute_ == b.attribute_ && a.color_ == b.color_; }

Bag readOneBagFromString(std::string bagString)
{
	return Bag(bagString.substr(0, bagString.find(' ')), bagString.substr(bagString.find(' ') + 1, bagString.find(' ') - bagString.length()));
}

std::vector<std::pair<uint32_t, Bag>> readMultipleBagsFromString(std::string bagString)
{
	std::vector<std::pair<uint32_t, Bag>> bags;
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
			bags.push_back(std::pair<uint32_t, Bag>(numberOfBags, bag));

			bagString.erase(0, pos + 2);
		}

		uint32_t numberOfBags = bagString[0] - '0';
		bagString.erase(0, 2);
		std::string attribute, color;

		attribute = bagString.substr(0, bagString.find(' '));
		bagString.erase(0, attribute.length() + 1);
		color = bagString.substr(0, bagString.find(' '));

		Bag bag(attribute, color);
		bags.push_back(std::pair<uint32_t, Bag>(numberOfBags, bag));

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
		bags.push_back(std::pair<uint32_t, Bag>(numberOfBags, bag));
	}
	return bags;
}

std::vector<Bag> shinyBags;
std::map<std::string, Bag> allBags;


uint32_t CountIndividualBags(Bag currentBag)
{
	uint32_t result = 1;
	for (auto current_bag : currentBag.containsBags)
	{
		result += current_bag.first * CountIndividualBags(current_bag.second());

	}
	return result;
}

int main()
{
	ReadInputDay7PuzzleTwo("input.txt");
	auto shinyBag = allBags["shinygold"];
	std::cout << CountIndividualBags(shinyBag) - 1;
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

	//Bag bag("shiny", "gold");


	while (std::getline(inFile, line))
	{
		std::string delimiter = "contain";
		std::string firstBag = line.substr(0, line.find(delimiter));
		std::string otherBags = line.substr(line.find(delimiter), line.length() - line.find(delimiter));

		rtrim(firstBag.erase(firstBag.find("bags"), 4));
		Bag newBag = readOneBagFromString(firstBag);

		std::string key = newBag.toString();
		allBags[key] = newBag;

		auto bags = readMultipleBagsFromString(otherBags);

		for (auto bag : bags)
		{
			allBags[key].containsBags.push_back(std::pair<uint32_t, std::function<Bag()>>(bag.first, [bag]()->Bag
				{
					auto key = bag.second.toString();
					return allBags.at(key);
				}));
		}
	}
}