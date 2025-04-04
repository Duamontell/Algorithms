// Иванов Максим ПС-21
// Лабораторная работа №2, задача 2.10(6)
// Среда выполнения Visual Studio 22 C++

// 2.10 Шестеренки (6)
//	Имеется система сцепленных шестеренок, пронумерованных от 1 до N.
// Заданы пары номеров сцепленных шестеренок.Первая должна двигаться по  часовой стрелке.
// Определить характер движения всех шестеренок.
//	Варианты движения :
// clockwise - по часовой;
// unclockwise - против;
// immovable - шестеренка неподвижна;
// block - заклинивание.
// 
//	Ввод из файла INPUT.TXT.В первой строке записаны через пробел 
// число N - количество шестеренок(2 ≤ N ≤ 10000) и M - количество пар(1 ≤ M ≤ 100000).
// Во следующих M строках указаны пары шестеренок в виде двух номеров через пробел.
// 
//	Вывод в файл OUTPUT.TXT.В i - й строке должна быть информация о 
// движении i - й шестеренки : clockwise - по часовой, against - против, 
// immovable – шестеренка неподвижна.Если система заклинивается, то выдать block.


#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>


const int MAX_GEARS = 10000;
const int MAX_PAIRS = 100000;

void WriteInFile(std::ofstream& outputFile, std::vector<std::string> gearMovement)
{
		for (size_t i = 1; i < gearMovement.size(); ++i)
		{
				outputFile << gearMovement[i] << "\n";
		}
}

std::vector<std::string> BlockingGears(std::vector<std::string>& gears)
{
		std::vector<std::string> result(2);
		result[1] = "blocked";
		return result;
}

std::vector<std::string> CheckImmovableGears(std::vector<std::string>& result, int lastMarkedGear)
{
		for (size_t i = 0; i < result.size(); ++i)
		{
				if (result[i].empty())
				{
						result[i] = "immovable";
				}
		}

		return result;
}

std::string GetMovement(std::string prevGearMovement, bool& isBlocked)
{
		if (prevGearMovement == "clockwise")
		{
				return "unclockwise";
		}
		else if (prevGearMovement == "unclockwise")
		{
				return "clockwise";
		}
		else
		{
				isBlocked = true;
				return "blocked";
		}
}

std::vector<std::string> GetGearsMovement(std::vector<std::vector<int>>& edges)
{
		std::vector<std::string> result(edges.size());
		std::vector<bool> markedGears(edges.size());
		std::queue<int> gearsInQueue;
		int lastMarkedGear = 0;
		bool isBlocked = false;

		std::string startMovement = "clockwise";
		int startGear = 1;
		result[startGear] = startMovement;
		gearsInQueue.push(startGear);
		markedGears[startGear] = true;

		while (!gearsInQueue.empty())
		{
				int gear = gearsInQueue.front();
				gearsInQueue.pop();
				for (size_t i = 0; i < edges[gear].size(); ++i)
				{
						if (markedGears[edges[gear][i]] == false)
						{
								result[edges[gear][i]] = GetMovement(result[gear], isBlocked);
								markedGears[edges[gear][i]] = true;
								gearsInQueue.push(edges[gear][i]);
						}
						else if (result[gear] == result[edges[gear][i]])
						{
								isBlocked = true;
						}
				}

				if (gear == lastMarkedGear + 1)
				{
						lastMarkedGear++;
				}
		}

		if (isBlocked)
		{
				result = BlockingGears(result);
		}
		else
		{
				result = CheckImmovableGears(result, lastMarkedGear);
		}

		return result;
}

std::vector<std::vector<int>> GetEdgesFromFile(std::ifstream& inputFile)
{
		std::vector<std::vector<int>> result;
		std::string line;
		int num1, num2;
		int countGears = 0;
		int countPair = -1;
		while (std::getline(inputFile, line))
		{
				std::istringstream iss(line);
				if (countPair == -1)
				{
						if (iss >> countGears >> countPair)
						{
								result.resize(countGears + 1);
								continue;
						}
						else
						{
								throw std::runtime_error("Invalid input data!");
						}
				}
				else if (iss >> num1 >> num2)
				{

						result[std::min(num1, num2)].push_back(std::max(num1, num2));
						result[std::max(num1, num2)].push_back(std::min(num1, num2));

				}
				else if (!line.empty())
				{
						throw std::runtime_error("Invalid input file data!");
				}
		}

		if (countPair != -1 && countPair <= MAX_PAIRS)
		{
				return result;
		}
		else
		{
				throw std::runtime_error("Wrong data input file!");
		}
}

std::ifstream GetInputFile(std::string fileName)
{
		std::ifstream inputFile(fileName);
		if (!inputFile.is_open())
		{
				throw std::runtime_error("Invalid input data!");
		}

		return inputFile;
}

std::ofstream GetOutputFile(std::string fileName)
{
		std::ofstream outputFile(fileName);
		if (!outputFile.is_open())
		{
				throw std::runtime_error("Invalid input data!");
		}

		return outputFile;
}

std::string GetFileName(std::string str)
{
		std::string fileName;
		std::cout << "Enter " << str << " file name: ";
		std::getline(std::cin, fileName);

		return fileName;
}

int main()
{
		try
		{
				std::string fileName = GetFileName("input");
				std::ifstream inputFile = GetInputFile(fileName);
				fileName = GetFileName("output");
				std::ofstream outputFile = GetOutputFile(fileName);

				std::vector<std::vector<int>> edges = GetEdgesFromFile(inputFile);

				std::vector<std::string> gearMovement = GetGearsMovement(edges);
				WriteInFile(outputFile, gearMovement);
		}
		catch (const std::exception& e)
		{
				std::cout << e.what() << std::endl;
				return 1;
		}

		return 0;
}