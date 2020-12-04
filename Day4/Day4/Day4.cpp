// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>

void ReadInputDay4(const std::string path);


class Passport
{
public:
	bool isValidPuzzleOne()
	{
		if (fields.count("byr") && fields.count("iyr") && fields.count("eyr") && fields.count("hgt") && fields.count("hcl")
			&& fields.count("ecl") && fields.count("pid")) return true;
		else return false;
	}

	bool isValidPuzzleTwo()
	{
		bool byrCheck = false;
		bool iyrCheck = false;
		bool eyrCheck = false;
		bool hgtCheck = false;
		bool hclCheck = false;
		bool eclCheck = false;
		bool pidCheck = false;
		
		if(fields.count("byr"))
		{
			if (std::stoi(fields["byr"]) >= 1920 && std::stoi(fields["byr"]) <= 2002) byrCheck = true;
		}

		if (fields.count("iyr"))
		{
			if (std::stoi(fields["iyr"]) >= 2010 && std::stoi(fields["iyr"]) <= 2020) iyrCheck = true;
		}

		if (fields.count("eyr"))
		{
			if (std::stoi(fields["eyr"]) >= 2020 && std::stoi(fields["eyr"]) <= 2030) eyrCheck = true;
		}

		if (fields.count("hgt"))
		{
			if(fields["hgt"].find("cm") != std::string::npos)
			{
				if (std::stoi(fields["hgt"]) >= 150 && std::stoi(fields["hgt"]) <= 193) hgtCheck = true;
			}
			else if((fields["hgt"].find("in") != std::string::npos))
			{
				if (std::stoi(fields["hgt"]) >= 59 && std::stoi(fields["hgt"]) <= 76) hgtCheck = true;
			}
		}

		if (fields.count("hcl"))
		{
			if (std::regex_match(fields["hcl"], std::regex("[#][0-9a-f]{6}"))) hclCheck = true;
		}

		if (fields.count("ecl"))
		{
			if (fields["ecl"] == "amb" || fields["ecl"] == "blu" || fields["ecl"] == "brn" || fields["ecl"] == "gry"
				|| fields["ecl"] == "grn" || fields["ecl"] == "hzl" || fields["ecl"] == "oth") eclCheck = true;
		}

		if (fields.count("pid"))
		{
			if (std::regex_match(fields["pid"], std::regex("[0-9]{9}"))) pidCheck = true;
		}

		if (byrCheck && iyrCheck && eyrCheck && hgtCheck && hclCheck && eclCheck && pidCheck) return true;

		return false;
	}
	
	void AddPair(std::string key, std::string value)
	{
		//fields.insert(std::pair<std::string, std::string>(key, value));
		fields[key] = value;
	}
private:
	std::map<std::string, std::string> fields;

	
};

std::vector<Passport*> passports;

int main()
{
	ReadInputDay4("input.txt");
	int count = 0;
	for (auto passport : passports)
	{
		if (passport->isValidPuzzleTwo()) count++;
	}

	std::cout << count;
}

void ReadInputDay4(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}

	std::string line;
	Passport* passport = new Passport();

	
	while (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		std::string token;

		if (line.empty())
		{
			passports.push_back(passport);
			passport = new Passport();
			continue;
		}
		
		while (std::getline(iss, token, ' '))
		{
			
			std::string key = token.substr(0, token.find(':'));
			std::string value = token.substr(token.find(':') + 1, token.length() - key.length());
			passport->AddPair(key, value);
		}

		
		


		//if newline: create new passwort and push back and create new
		//

		//std::cout << minNumber << "-" << maxNumber << " " << policy << ": " << password << std::endl;





		


		
	}

	passports.push_back(passport);
	inFile.close();
}