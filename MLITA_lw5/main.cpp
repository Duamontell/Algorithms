/*
Иванов Максим ПС-21
Задание 5.1 Размещение(4)
В массив A 1 , A 2 ,…, A N (1 ≤ N ≤ 10 5 ) помещены числа 2, 3,..., N+1
так, что каждое значение A i делится на i. Сколько способов такого размещения?
Ввод из файла INPUT.TXT. В единственной строке вводится значение N.
Вывод в файл OUTPUT.TXT. В единственной строке выводится количество вариантов
размещения.
Примеры
Ввод 1	Ввод 2	Ввод 3
6		3		11
Вывод 1	Вывод 2	Вывод 3
1		2		8
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*std::string add(const std::string &a, const std::string &b) {
	int i = static_cast<int>(a.size()) - 1;
	int j = static_cast<int>(b.size()) - 1;
	int carry = 0;
	std::string res;
	res.reserve(std::max(a.size(), b.size()) + 1);

	while (i >= 0 || j >= 0 || carry) {
		int da = (i >= 0 ? a[i--] - '0' : 0);
		int db = (j >= 0 ? b[j--] - '0' : 0);
		int sum = da + db + carry;
		res.push_back(char('0' + (sum % 10)));
		carry = sum / 10;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

int main() {

	int N;
	if (!(std::cin >> N)) {
		return 0;
	}

	// 1) Строим делители для 1..N+1
	std::vector<std::vector<int>> divs(N + 2);
	for (int d = 1; d <= N + 1; ++d) {
		for (int m = d; m <= N + 1; m += d) {
			divs[m].push_back(d);
		}
	}

	// 2) DP-массив f[i] — число способов для длины i (строки)
	std::vector<std::string> f(N + 1);
	f[0] = "1";

	// 3) Основной цикл DP
	for (int i = 1; i <= N; ++i) {
		std::string sum = "0";
		int limit = (i + 1) / 2;
		for (int d : divs[i + 1]) {
			if (d <= limit) {
				sum = add(sum, f[d - 1]);
			}
		}
		f[i] = std::move(sum);
	}

	// 4) Вывод ответа
	std::cout << f[N] << "\n";
	return 0;
}*/


int main()
{
	std::ifstream inputFile("input2.txt");
	if (!inputFile.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return 1;
	}
	std::ofstream outputFile("output.txt");

	int n;
	inputFile >> n;

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::pair<int, int>> delimeters(n);

	for (int i = 2; i < n; ++i) {
		delimeters[i] = {i + 1, 1};
	}
	delimeters[0] = {1, n};
	delimeters[1] = {2, (n + 1) / 2};

	for (int i = 2; i < n / 2 + 1; ++i)
	{
		int d = i + 1;
		for (int j = 2 * d; j <= n + 1; j += d)
		{
			delimeters[i].second++;
		}
	}

	std::vector<std::pair<int, int>> copyDelimiters(n);
	copyDelimiters = delimeters;
	int result = 0;
	while (delimeters.size() > 1)
	{
		std::vector<int> removedElements;
		int count = 0;
		for (int i = delimeters.size() - 1; i >= 0; --i)
		{
			if (delimeters[i].second == 1)
			{
				removedElements.push_back(delimeters[i].first);
				for (int j = 1; j <= (i + 1) / 2 ; ++j)
				{
					if ( ( i + 1)  % j == 0 )
					{
						--copyDelimiters[j - 1].second;
					}
				}
			}
		}

		if (removedElements.empty())
		{
			if (delimeters.size() > 1)
			{
				count += delimeters[delimeters.size() - 1].second;
				removedElements.push_back(delimeters[delimeters.size() - 1].first);
				for (int i = 1; i < delimeters.size() - 1; ++i)
				{
					if ( ( delimeters.size() - 1 + 1)  % i == 0 )
					{
						--copyDelimiters[i - 1].second;
					}
				}
			}
		}

		for ( auto element : removedElements)
		{
			copyDelimiters.erase(copyDelimiters.begin() + element - 1);

		}

		delimeters = copyDelimiters;
		result += count;
	}

	if (result == 0)
	{
		result = 1;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto durationS = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Time spent: " << durationS << std::endl;
	std::cout << "Time spent: " << durationMs << std::endl;
	std::cout << result << std::endl;
	outputFile << result << std::endl;

	return 0;
}