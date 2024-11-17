// Иванов Максим ПС-21
// Среда выполнения Microsoft Visual Studio 2022, C++

// Лабораторная работа №4
// Задание №17
// Реализовать алгоритм нахождения остовного дерева Прима
// и проиллюстрировать в таблице по шагам этапы его выполнения(9).

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <locale.h>


struct Edge {
	int x;
	int y;
	int weight;
};

void CreateGraph(std::ifstream& file, std::vector<std::vector<Edge>>& graph) {
	std::string line;
	int swap = 0;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		int startVertex, endVertex, weight;

		if (iss >> startVertex >> endVertex >> weight) {
			/*if (startVertex > endVertex) {
				swap = endVertex;
				endVertex = startVertex;
				startVertex = swap;
			}*/
			Edge edge{ startVertex, endVertex, weight };

			if (startVertex >= graph.size()) {
				graph.resize(startVertex + 1);
			}

			graph[startVertex].push_back(edge);
		}
	}

	/*int levelUp = graph.size();
	graph.resize(levelUp + 1);
	graph[levelUp].push_back({ levelUp, 0, 0 });*/
}

void ReadFile(std::vector<std::vector<Edge>>& graph) {
	std::string fileName;
	do {
		std::cout << "Enter file name: ";
		std::getline(std::cin, fileName);
	} while (fileName.empty());

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "File does not exist\n\n";
		return;
	}

	CreateGraph(file, graph);
	file.close();
}

void PrintTableTop(std::vector<std::vector<Edge>>& graph) {
	std::cout << "  N  |";

	int countVertex = graph.size() - 1;
	for (int i = 1; i <= countVertex; ++i) {
		std::cout << "   " << i << "   |";
	}

	std::cout << "  Edge  |  Sum  \n";
}

// 3
void PrintNextTurn(std::vector<std::vector<Edge>>& graph, std::vector<bool>& inPrimTree, int& num, int& sum, int& x, int& y, int& firstVertex, std::vector<Edge> minEdgeWeight) {
	if (num > 9) {
		std::cout << " " << num << "  |";
	} else {
		std::cout << "  " << num << "  |";
	}

	for (int i = 1; i < graph.size(); ++i) {
		if (minEdgeWeight[i].weight == std::numeric_limits<int>::max()) {
			std::cout << "  INF  |";
		} else if (minEdgeWeight[i].weight == 0) {
			std::cout << "   0   |";
		} else  if (inPrimTree[i] == true) {
			std::cout << " !" << minEdgeWeight[i].weight << "(" << minEdgeWeight[i].x << ")" << " |";
		} else {
			std::cout << "  " << minEdgeWeight[i].weight << "(" << minEdgeWeight[i].x << ")" << " |";
		}
	}

	if (x == 0 && y == 0) {
		std::cout << "    " << "    |";
	} else {
		std::cout << "   " << x << "-" << y << "  |";
	}

	if (sum == 0) {
		std::cout << "\n";
	} else {
		std::cout << "   " << sum << "   \n";
	}
}

void CreatePrimTree() {
	std::vector<std::vector<Edge>> graph;

	ReadFile(graph);
	if (graph.empty()) {
		return;
	}

	int noEdge = 0;
	int x = 0;
	int y = 0;
	int num = 1;
	int sum = 0;
	int check = 0;
	bool isFirst = true;
	int firstVertex = 1;
	std::vector<Edge > primTree;
	std::vector<Edge> minEdgeWeight(graph.size(), { 0, 0, std::numeric_limits<int>::max() }); // Дуги до вершин с минимальным весом
	std::vector<bool> inPrimTree(graph.size(), false); // Флаги для отслеживания вершин

	inPrimTree[firstVertex] = true;
	minEdgeWeight[firstVertex] = { firstVertex, firstVertex, 0 }; // Стартовая вершина


	PrintTableTop(graph);
	PrintNextTurn(graph, inPrimTree, num, sum, x, y, firstVertex, minEdgeWeight);
	num++;

	while (noEdge < graph.size() - 2) {
		x = 0;
		y = 0;
		int min = std::numeric_limits<int>::max();

		/*for (int i = 1; i < graph.size() - 1; ++i) {
			if (inPrimTree[i]) {
				for (int j = 0; j < graph[i].size(); ++j) {
					if (!inPrimTree[graph[i][j].y]) {
						if (min > graph[i][j].weight) {
							min = graph[i][j].weight;
							x = graph[i][j].x;
							y = graph[i][j].y;
						}

						if (minEdgeWeight[graph[i][j].y].weight > graph[i][j].weight) {
							minEdgeWeight[graph[i][j].y] = { i, graph[i][j].y, graph[i][j].weight };
						}
					}
				}
			}

		}*/

		for (int i = 1; i < graph.size(); ++i) {
			if (inPrimTree[i]) {
				for (int j = 0; j < graph[i].size(); ++j) {
					if (!inPrimTree[graph[i][j].y]) {
						if (min > graph[i][j].weight) {
							min = graph[i][j].weight;
							x = i;
							y = graph[i][j].y;
						}

						if (minEdgeWeight[graph[i][j].y].weight > graph[i][j].weight) {
							minEdgeWeight[graph[i][j].y] = { i, graph[i][j].y, graph[i][j].weight };
						}
					}
				}

				for (int j = 1; j < graph.size(); ++j) {
					for (const auto& edge : graph[j]) {
						if (edge.y == i && !inPrimTree[j]) {
							if (min > edge.weight) {
								min = edge.weight;
								x = j;
								y = i;
							}

							if (minEdgeWeight[j].weight > edge.weight) {
								minEdgeWeight[j] = { i, j, edge.weight };
							}
						}
					}
				}
			}
		}

		PrintNextTurn(graph, inPrimTree, num, check, check, check, firstVertex, minEdgeWeight);
		num++;
		primTree.push_back({ x, y, min });
		sum += min;
		inPrimTree[x] = true;
		inPrimTree[y] = true;
		PrintNextTurn(graph, inPrimTree, num, sum, x, y, firstVertex, minEdgeWeight);
		num++;
		noEdge++;
	}

	for (int i = 0; i < minEdgeWeight.size(); ++i) {
		std::cout << " " << i << ": " << minEdgeWeight[i].x << " " << minEdgeWeight[i].y << " " << minEdgeWeight[i].weight << "\n";
	}
	std::cout << "\n";
}

// Check graph for debug
void PrintGraph(std::vector<std::vector<Edge>>& graph) {
	for (int i = 0; i < graph.size(); ++i) {
		std::vector<Edge> edges = graph[i];
		if (!edges.empty()) {
			for (int j = 0; j < edges.size(); ++j) {

				std::cout << edges[j].x << " " << edges[j].y << " " << edges[j].weight << "\n";
			}
		}
	}

}

void PrintMainMenu() {
	std::cout << "[1] Start create Prim tree\n";
	std::cout << "[2] Exit\n";
}

int main() {
	setlocale(LC_ALL, "Ru");
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
				CreatePrimTree();
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