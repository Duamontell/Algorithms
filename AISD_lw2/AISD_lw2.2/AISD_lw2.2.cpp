// Иванов Максим ПС-21
// Среда выполнения Visual Studio 2022, C++

// Лабораторная работа №2
// Задание №12
// В файле заданы N упорядоченных по возрастанию списков целых чисел.
// Организовать в оперативной памяти с помощью указателей N линейных списков 
// и слить их в общий список(8).

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>

struct Node {
	int value;
	Node* next;
};

struct LinkedList {
	Node* head;
	LinkedList* nextList;
};

Node* MergeSortedLists(LinkedList* lists) {
	Node* mergedList = nullptr;
	Node** lastPtr = &mergedList;

	while (true) {
		int minValue = std::numeric_limits<int>::max();
		LinkedList* minList = nullptr;

		for (LinkedList* currentList = lists; currentList != nullptr; currentList = currentList->nextList) {
			if (currentList->head != nullptr && currentList->head->value < minValue) {
				minValue = currentList->head->value;
				minList = currentList;
			}
		}

		if (minList == nullptr) {
			break;
		}

		*lastPtr = new Node{ minValue, nullptr };
		lastPtr = &((*lastPtr)->next);

		minList->head = minList->head->next;
	}

	return mergedList;
}

LinkedList* ReadListsFromFile(const std::string& fileName) {
	std::ifstream file(fileName);

	LinkedList* firstList = nullptr;
	LinkedList* lastList = nullptr;

	std::string line;
	while (std::getline(file, line)) {
		LinkedList* newList = new LinkedList{ nullptr, nullptr };

		std::istringstream iss(line);
		Node** lastPtr = &newList->head;
		int value;

		while (iss >> value) {
			*lastPtr = new Node{ value, nullptr };
			lastPtr = &((*lastPtr)->next);
		}

		if (lastList == nullptr) {
			firstList = newList;
		} else {
			lastList->nextList = newList;
		}

		lastList = newList;
	}

	return firstList;
}

void PrintList(Node* list) {
	while (list != nullptr) {
		std::cout << list->value << " ";
		list = list->next;
	}
	std::cout << std::endl;
}

void FreeList(Node* list) {
	while (list != nullptr) {
		Node* temp = list;
		list = list->next;
		delete temp;
	}
}

void FreeLists(LinkedList* list) {
	while (list != nullptr) {
		FreeList(list->head);
		LinkedList* temp = list;
		list = list->nextList;
		delete temp;
	}
}

void Menu() {
	std::cout << "Menu\n";
	std::cout << "[1] Merge lists\n";
	std::cout << "[2] Exit\n";
}

void MergeList() {
	std::cout << "Enter file name: ";
	std::string fileName;
	getline(std::cin, fileName);
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "File does not exist\n\n";
		return;
	}

	LinkedList* lists = ReadListsFromFile(fileName);
	if (lists == nullptr) {
		std::cout << "File is empty\n";
		return;
	}

	Node* mergedList = MergeSortedLists(lists);

	std::cout << "Merged list: ";
	PrintList(mergedList);

	FreeList(mergedList);
	FreeLists(lists);
}

int main() {
	setlocale(LC_ALL, "Russian");

	while (true) {
		Menu();

		std::string userCommand;
		getline(std::cin, userCommand);
		int i = 0;
		if (userCommand == "1") i = 1;
		if (userCommand == "2") i = 2;

		switch (i) {
			case 1:
				MergeList();
				break;
			case 2:
				return 0;
			default:
				std::cout << "Unknown command\n";
				break;
		}
	}

	return 0;
}
