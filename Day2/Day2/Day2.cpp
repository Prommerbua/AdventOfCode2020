#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

void ReadInputFileDay2(const std::string path);

class InputFileLine
{
public:
	InputFileLine(int minNumber, int maxNumber, char policy, std::string password) : m_minNumber(minNumber), m_maxNumber(maxNumber), m_policy(policy), m_password(std::move(password))
	{

	}

	bool isValidPuzzleOne()
	{
		int count = 0;
		for (int i = 0; i < m_password.size(); ++i)
		{
			if(m_password[i] == m_policy)
			{
				count++;
			}
		}

		if(count >= m_minNumber && count <= m_maxNumber)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isValidPuzzleTwo()
	{
		int count = 0;
		if (m_password[m_minNumber - 1] == m_policy && m_password[m_maxNumber - 1] == m_policy) return false;
		if (m_password[m_minNumber - 1] == m_policy || m_password[m_maxNumber - 1] == m_policy) return true;
		else return false;
	}

	int m_minNumber;
	int m_maxNumber;
	char m_policy;
	std::string m_password;
};


std::vector<InputFileLine> fileContent;



int main()
{
	ReadInputFileDay2("input.txt");

	int count = 0;
	for (auto line : fileContent)
	{
		if (line.isValidPuzzleOne()) count++;
	}

	count = 0;
	for (auto line : fileContent)
	{
		if (line.isValidPuzzleTwo()) count++;
	}


	

	std::cout << count;
}

void ReadInputFileDay2(const std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file " << path;
		exit(1);
	}

	std::string line;
	std::string delimiter1 = "-";
	char delimiter2 = ' ';
	std::string delimiter3 = ":";

	while (std::getline(inFile, line))
	{
		size_t pos1 = 0;
		size_t pos2 = 0;
		size_t pos3 = 0;
		int minNumber;
		int maxNumber;
		char policy;
		std::string password;
		


		pos1 = line.find_first_of(delimiter1);
		minNumber = std::stoi( line.substr(0, pos1));

		pos2 = line.find_first_of(delimiter2);
		maxNumber = std::stoi(line.substr(pos1 + 1, pos2-pos1 - 1));

		pos3 = line.find_first_of(delimiter3);
		policy = line.substr(pos2 + 1, 1)[0];

		
		password = line.substr(pos3 + 2, line.length() - pos3 - 2);
		
		//std::cout << minNumber << "-" << maxNumber << " " << policy << ": " << password << std::endl;

		
		InputFileLine inputLine(minNumber, maxNumber, policy, password);
		fileContent.push_back(inputLine);
		

		
		/*pos2 = line.find_first_of(delimiter2);
		token = line.substr(0, pos2);
		std::cout << token << std::endl;*/


		//Read Number
		//Read Char
		//Read Passwort
	}

	inFile.close();
}

