// Иванов Максим ПС-21
// Среда выполнения Clion c++20
/*
7.2. Скобки (4)
Последовательность круглых скобок называют правильной, если можно добавить
в нее числа и знаки арифметических операций так, что полученное алгебраическое выражение станет корректным.
Например, скобочная последовательность (())() является правильной, а (())) и ())(() такими не являются.
Пустая последовательность также считается правильной. Задана правильная скобочная последовательность.
Назовем парой внешних скобок первую открывающую и последнюю закрывающую скобки.
После удаления пары внешних скобок правильность последовательности может как сохраниться,
так и нарушиться. Найти наибольшее число пар внешних скобок, которые можно удалять
до первого нарушения правильности последовательности.
Ввод из файла INPUT.TXT. В первой строке задано значение N (1 ≤ N ≤ 3×105).
Во второй строке находится правильная скобочная последовательность длины 2N.
Вывод в файл OUTPUT.TXT. Вывести единственное значение: указанное число пар внешних скобок.
Примеры
Ввод 1     Ввод 2     Ввод 3
3          3          5
()()()     ((()))     ((())(()))
Вывод 1    Вывод 2    Вывод 3
0          3          1
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>


int main() {
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");

	int N;
	inputFile >> N;
	std::string S;
	inputFile >> S;

	std::vector<int> B(2 * N + 1, 0);
	for (int i = 0; i < 2 * N; i++) {
		B[i + 1] = B[i] + (S[i] == '(' ? 1 : -1);
	}

	std::multiset<int> ms(B.begin(), B.end());

	int answer = 0;
	// 3) Сдвигаем k от 0 и дальше,
	//    каждый раз смотрим окно [k .. 2N-k] в B[]
	for (int k = 0; k < N; k++) {
		int left  = k;
		int right = 2 * N - k;

		if (B[right] - B[left] != 0)
			break;

		if (*ms.begin() < B[left])
			break;

		++answer;
		ms.erase(ms.find(B[left]));
		ms.erase(ms.find(B[right]));
	}

	if (answer != 0 && answer != N)
	{
		--answer;
	}

	std::cout << answer << "\n";
	return 0;
}


/*int main() {
	std::ifstream inputFile("input11.txt");
	std::ofstream outputFile("output.txt");

	int N;
	inputFile >> N;
	std::string S;
	inputFile >> S;

	std::vector<int> B(2 * N + 1);
	B[0] = 0;
	for (int i = 0; i < 2 * N; ++i)
	{
		B[i + 1] = B[i] + (S[i] == '(' ? 1 : -1);
	}

	int left = 0;
	int right = 2 * N;
	int count = 0;
	while (left < right)
	{
		int a = left + 1;
		int b = right - 1;
		if (a > b)
		{
			++count;
			++left;
			--right;
			continue;
		}
		bool valid = true;
		if (B[b] != B[a])
		{
			valid = false;
		}
		else
		{
			int min_balance = B[a];
			for (int i = a; i < b; ++i)
			{
				/*if (i != B.size() - 1)
				{#1#
					min_balance = std::min(min_balance, B[i]);
				/*}#1#
				if (min_balance < B[a])
				{
					valid = false;
					break;
				}
			}
		}
		if (valid)
		{
			++count;
			++left;
			--right;
		}
		else
		{
			break;
		}
	}

	std::cout << count << std::endl;
	outputFile << count << std::endl;

	return 0;
}*/