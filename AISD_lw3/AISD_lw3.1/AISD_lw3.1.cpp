// Иванов Максим ПС-21
// Среда выполнения Visual Studio 2022, С++

// Лабораторная работа №3
// Задание №9
// Структура  некоторого института задана деревом. 
// Сыновьям корневой вершины соответствуют факультеты, факультеты в свою очередь 
// делятся  на  кафедры, которые  могут  иметь филиалы.
// Листьям дерева соответствуют преподаватели. 
// Выявить преподавателей, ведущих занятия на трех и более кафедрах(9).

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include <sstream>


struct Tree {
	std::string name;
	int level;
	Tree* father;
	std::vector<Tree*> sons;
};

struct Teacher {
	std::string name;
	std::vector<std::string> departments;
};

void AddSon(Tree* parent, Tree* son) {
	if (parent) {
		parent->sons.push_back(son);
		son->father = parent;
	}
}

Tree* CreateTreeFromFile(std::ifstream& file, Tree*& root, std::vector<Teacher>& teachers) {
	std::string line;
	Tree* currentParent = nullptr;
	std::vector<Tree*> parentsByLevel;
	std::vector<std::string> departmentTeachers;
	std::string department;

	while (std::getline(file, line)) {
		int level = 0;
		while (level < line.size() && line[level] == '.') {
			level++;
		}

		std::string nodeName = line.substr(level);
		Tree* newNode = new Tree;
		newNode->name = nodeName;
		newNode->level = level;
		newNode->father = nullptr;

		if (level == 0) {
			root = newNode;
			currentParent = root;
			parentsByLevel.push_back(root);
		} else {
			while (parentsByLevel.size() > level) {
				parentsByLevel.pop_back();
			}

			if (parentsByLevel.size() == 3) {
				if (department != parentsByLevel[2]->name) {
					departmentTeachers.clear();
				}
				department = parentsByLevel[2]->name;
			}

			if ((level == 3 || level == 4) && (nodeName != "Kazan branch" && nodeName != "Moscow branch")) {
				bool found = false;
				for (int i = 0; i < teachers.size(); ++i) {
					if (teachers[i].name == nodeName) {
						found = true;
						bool departmentFound = false;
						for (int j = 0; j < teachers[i].departments.size(); ++j) {
							if (teachers[i].departments[j] == department) {
								departmentFound = true;
								break;
							}
						}

						if (!departmentFound) {
							teachers[i].departments.push_back(department);
						}
						break;
					}
				}


				if (!found) {
					teachers.push_back({ nodeName, { department } });
				}

				departmentTeachers.push_back(nodeName);
			}


			Tree* currentParent = parentsByLevel.back();
			AddSon(currentParent, newNode);
		}

		parentsByLevel.push_back(newNode);
	}

	return root;
}

void SearchTeacher(std::ifstream& file) {
	std::cout << "Creating tree...\n";
	std::vector<Teacher> teachers;
	Tree* root = nullptr;
	root = CreateTreeFromFile(file, root, teachers);
	std::cout << "Creating complete\n";

	std::cout << "Searching teachers (working in >= 3 departments):\n";
	for (const Teacher& teacher : teachers) {
		if (teacher.departments.size() >= 3) {
			std::cout << teacher.name << "\n";
			for (const std::string& dept : teacher.departments) {
				std::cout << "- " << dept << "\n";
			}
		}
	}

	std::cout << "Search complete\n\n";
}

std::string PrintSpaces(int i) {
	std::string spaces;
	if (i == 1) {
		spaces = "     ";
	} else if (i == 2) {
		spaces = "          ";
	} else if (i == 3) {
		spaces = "               ";
	} else if (i == 4) {
		spaces = "                    ";
	}
	return spaces;
}

void PrintTree(std::ifstream& file) {
	std::cout << "Printing tree\n";

	std::string line;
	std::string spaces;
	while (std::getline(file, line)) {
		if (line[3] == '.') {
			spaces = PrintSpaces(4);
			std::cout << spaces << line.substr(4) << "\n";
		} else if (line[2] == '.') {
			spaces = PrintSpaces(3);
			std::cout << spaces << line.substr(3) << "\n";
		} else if (line[1] == '.') {
			spaces = PrintSpaces(2);
			std::cout << spaces << line.substr(2) << "\n";
		} else if (line[0] == '.') {
			spaces = PrintSpaces(1);
			std::cout << spaces << line.substr(1) << "\n";
		} else {
			std::cout << line << "\n";
		}
	}
}

void PrintUniversityMenu() {
	std::cout << "University tools:\n";
	std::cout << "[1] Search teacher\n";
	std::cout << "[2] Print tree\n";
}

void UniversityTools() {
	std::string fileName;
	do {
		std::cout << "Enter file name with tree: ";
		std::getline(std::cin, fileName);
	} while (fileName.empty());

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "File does not exist\n\n";
		return;
	}

	while (true) {
		PrintUniversityMenu();

		std::string userCommand;
		std::getline(std::cin, userCommand);
		int command = 0;
		if (userCommand == "1") {
			command = '1';
		} else if (userCommand == "2") {
			command = '2';
		}

		switch (command) {
			case '1':
				SearchTeacher(file);
				return;
			case '2':
				PrintTree(file);
				return;
			default:
				std::cout << "Invalid command\n";
				break;
		}
	}
}

// Главное меню программы
void PrintMainMenu() {
	std::cout << "University\n";
	std::cout << "[1] University tools\n";
	std::cout << "[2] Exit\n";
}

int main() {
	while (true) {
		PrintMainMenu();

		std::string userCommand;
		std::getline(std::cin, userCommand);
		int command = 0;
		if (userCommand == "1") {
			command = '1';
		} else if (userCommand == "2") {
			command = '2';
		}

		switch (command) {
			case '1':
				UniversityTools();
				break;
			case '2':
				return 0;
			default:
				std::cout << "Invalid command\n";
				break;
		}
	}

	return 0;
}