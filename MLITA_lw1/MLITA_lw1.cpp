// Иванов Максим ПС-21 
// Лабораторная работа №1, задача 14.15

// Пульт дистанционного управления имеет 13 клавиш
// 1  2  3  ↑
// 4  5  6  ↓
// 7  8  9
// --  0
//  Имеется 100 каналов с номерами от 0 до 99. Можно переключаться, либо уменьшая номер 
// канала кнопкой ↓ (после 0 следует 99), либо увеличивая номер кнопкой ↑ (после 99 следует 0), 
// либо набирая нужный номер.Для набора двузначного номера нажимается кнопка '--', 
// а затем цифры номера.Некоторые кнопки неисправны. Требуется от некоторого начального канала 
// переключиться на заданный канал минимальным количеством нажатий.
// 
//  Ввод из файла INPUT.TXT.В первых 4 строках через пробел задается состояние клавиш.
// Исправным клавишам соответствуют 1, а неисправным 0. В строке 5 через пробел 
// задаются 2 номера каналов : начального и конечного.
//  Вывод в файл OUTPUT.TXT.В единственной строке выдать минимальное количество нажатий.
// Если переключение невозможно, вывести - 1.


#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>


void PrintMenu() {
	std::cout << "Пульт дистанционного управления\n";
	std::cout << "[1] Включить пульт\n";
	std::cout << "[2] Выход\n";
}

std::ifstream GetFile() {
	std::string fileName;
	do {
		std::cout << "Введите имя ВХОДНОГО файла: ";
		std::getline(std::cin, fileName);
	} while (fileName.empty());

	std::ifstream inputFile(fileName);

	return inputFile;
}
std::ofstream CreateOutput() {
	std::string fileName;
	do {
		std::cout << "Введите имя ВЫХОДНОГО файла: ";
		std::getline(std::cin, fileName);
	} while (fileName.empty());

	std::ofstream outputFile(fileName, std::ios::out);

	return outputFile;
}

bool IsCheckedFile(std::ifstream& file, std::vector<std::vector<short>>& controller) {
	std::string line;
	short level = 1;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		short num1, num2, num3, num4;
		switch (level) {
			case 1: case 2:
				if (iss >> num1 >> num2 >> num3 >> num4) {
					std::vector<short> numbers = { num1, num2, num3, num4 };
					controller.push_back(numbers);
				} else return false;
				break;
			case 3:
				if (iss >> num1 >> num2 >> num3) {
					std::vector<short> numbers = { num1, num2, num3 };
					controller.push_back(numbers);
				} else return false;
				break;
			case 4:
				if (iss >> num1 >> num2) {
					std::vector<short> numbers = { num1, num2 };
					controller.push_back(numbers);
				} else return false;
				break;
			case 5:
				if (iss >> num1 >> num2 && 99 >= num1 >= 0 && 99 >= num2 >= 0) {
					std::vector<short> numbers = { num1, num2 };
					controller.push_back(numbers);
				} else return false;
				break;
		}

		level++;
	}

	return true;
}

//void PrintController(std::vector<std::vector<short>>& controller, short& num) {
//	std::cout << controller[4][0] << "\n";
//	std::cout << (controller[0][0] == 1 ? 1 : 0) << (controller[0][1] == 1 ? 2 : 0) <<
//		(controller[0][0] == 1 ? 3 : 0) << (controller[0][0] == 1 ? "+" : 0) << "\n";
//	std::cout << (controller[1][0] == 1 ? 4 : 0) << (controller[1][1] == 1 ? 5 : 0) <<
//		(controller[1][2] == 1 ? 6 : 0) << (controller[1][3] == 1 ? "-" : 0) << "\n";
//	std::cout << (controller[2][0] == 1 ? 7 : 0) << (controller[2][1] == 1 ? 8 : 0) <<
//		(controller[2][2] == 1 ? 9 : 0) << "\n";
//}

short GetDiv(std::vector<std::vector<short>>& controller) {
	if (controller[4][0] > controller[4][1]) {
		return controller[4][0] - controller[4][1];
	} else {
		return controller[4][1] - controller[4][0];
	}
}

short RemoteControl(std::vector<std::vector<short>>& controller) {
	short div = GetDiv(controller); // НЕ ЗАБЫТЬ ПРО ДИВ
	if (controller[4][0] == controller[4][1]) { // Каналы равны
		return 0;
	} else if (controller[3][0] == 0 && controller[0][3] == 1 && controller[1][3] == 1) { // Только + -
		if (div <= 50) {
			return div;
		} else return 100 - div;
	} else if (controller[3][0] == 0 && controller[0][3] == 1 && controller[1][3] == 0) { // Только +
		return div;
	} else if (controller[3][0] == 0 && controller[0][3] == 0 && controller[1][3] == 1) { // Только -
		return 100 - div;
	} else if (controller[3][0] == 1) { // Есть --
		short buttons[10] = { controller[0][0], controller[0][0], controller[0][0],controller[0][0],
							  controller[0][0],controller[0][0],controller[0][0],controller[0][0],
							  controller[0][0], controller[0][0] };
		short touchNumbers = 0;
		short num1 = controller[4][1] / 10;
		short num2 = controller[4][1] % 10;
		for (short i = 0; i <= 9; i++) {
			if ()
		}
		if (controller[0][3] == 1 && controller[1][3] == 1) {

		}
	}







	//} else if (controller[3][0] == 1) { // Есть --
	//	short touchNumbers = 0;
	//	short num1 = controller[4][1] / 10;
	//	short num2 = controller[4][1] % 10;
	//	for (short i = 0; i <= 9; i++) {
	//		if (controller[4][1])
	//	}
	//	if (controller[0][3] == 1 && controller[1][3] == 1) {
	//	}
	//}

	return -1;
}

int main() {
	setlocale(LC_ALL, "Ru");

	while (true) {
		PrintMenu();

		std::string userCommand;
		std::getline(std::cin, userCommand);
		if (userCommand == "1") {
			std::ifstream inputFile = GetFile();
			if (!inputFile.is_open()) {
				std::cout << "Файл не существует!\n\n";
				break;
			}

			std::ofstream outputFile = CreateOutput();

			std::vector<std::vector<short>> controller;
			if (!IsCheckedFile(inputFile, controller)) {
				std::cout << "Файл заполнен неверно!\n\n";
				break;
			}

			short touchNumbers = RemoteControl(controller);
			if (touchNumbers == -1) {
				std::cout << "Переключение невозможно\n" << touchNumbers << "\n\n";
				outputFile << touchNumbers;
			} else {
				std::cout << touchNumbers << "\n\n";
				outputFile << touchNumbers;
			}
		} else if (userCommand == "2") {
			return 0;
		} else {
			std::cout << "Неизвестная комманда\n\n";
		}
	}
}