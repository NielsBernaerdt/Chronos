#pragma once
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

const std::string fileName{ "../Data/HighScores.txt" };
constexpr int maxNrScores{ 10 };

void WriteScoreToFile(int value)
{
	std::vector<int> highScores;
	std::ifstream readFile{ fileName };
//Firstly get all the scores currently in the file
	std::string str;
	/*discard first line :*/ std::getline(readFile, str);
	while (std::getline(readFile, str))
	{
		highScores.push_back(std::stoi(str));
	}
//Add the new value & sort the list
	highScores.push_back(value);
	std::sort(highScores.begin(), highScores.end());
//write 10 highest values back
	std::ofstream writeFile{ fileName, std::ofstream::out };
	if (writeFile.is_open())
	{
		writeFile << "HIGHSCORES:\n";
		for (size_t i{ 1 }; i < maxNrScores+1; ++i)
		{
			int temp = highScores[highScores.size() - i];
			writeFile << temp << std::endl;
		}
	}
	else
		std::cout << "cant open file\n";
}