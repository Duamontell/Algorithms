// Иванов Максим ПС-21
// Среда выполнения - Visual Studio 2022, C++

// Лабораторная №1 
// Задание №3
// Дан текстовый файл и ключевое слово для  поиска.  
// Выдать на  экран 5 строк файла, начиная с первой строки, включающей заданное слово.
// Результат не должен зависеть от регистра букв в файле и заданном слове

#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <string>
#include <cctype>
#include <locale.h>

const char delimiters[] = { ' ', '\t', '(', ')', '[', ']', '{', '}', '"', '\'', ',' };
const int numDelimiters = sizeof(delimiters) / sizeof(delimiters[0]);

bool fileExists(const std::string& fileName) {
	std::ifstream file(fileName);

	return file.good();
}

bool isStart(const std::string& word, const std::string& line, const int i) {
	if (i + 1 - word.length() == 0) {
		return true;
	} else if (i != 0) {
		for (int k = 0; k <= numDelimiters; ++k) {
			if (line[i - word.length()] == delimiters[k]) {
				return true;
			}
		}

	}

	return false;
}

bool isEnd(const std::string& word, const std::string& line, const int i) {
	if (i + 1 == line.length()) {
		return true;
	} else {
		for (int k = 0; k <= numDelimiters; ++k) {
			if (line[i + 1] == delimiters[k]) {
				return true;
			}
		}
	}

	return false;
}

bool containsWord(const std::string& line, std::string& word) {
	for (int i = 0; i <= line.length(); ++i) {
		for (int j = 0; j <= word.length(); ++j) {
			char big = word[j];
			big = std::toupper(big);
			if (word[j] == line[i] || big == line[i]) {
				if (j + 1 == word.length()) {
					if (isStart(word, line, i) && isEnd(word, line, i)) {
						return true;
					}
				}
				++i;
			} else {
				break;
			}
		}
	};

	return false;
}

std::string toLowerString(const std::string& input) {
	std::string result = input;
	for (int i = 0; i < result.length(); ++i) {
		result[i] = std::tolower(result[i]);
	}

	return result;
}

int main() {
	std::setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
	std::cout << "Enter file name: ";
	std::cin >> fileName;

	if (!fileExists(fileName)) {
		std::cout << "File \"" << fileName << "\" not exist.\n";

		exit(0);
	}

	std::string word;
	std::cout << "Enter your word for search: ";
	std::cin >> word;
	word = toLowerString(word);
	/*std::transform(word.begin(), word.end(), word.begin(), tolower);*/

	std::ifstream file(fileName);
	std::string line;
	int count = 0;

	while (std::getline(file, line) && count < 5) {
		if (containsWord(line, word)) {
			std::cout << line << std::endl;
			++count;
		}
	}

	if (count == 0) {
		std::cout << "Strings not found\n";
	}

	file.close();

	return 0;
}