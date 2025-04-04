// Иванов Максим ПС-21
// Среда разработки Clion C++20
// 3.6. Бальные танцы (5)
// В школу бальных танцев записались N учеников — мальчиков и девочек.
// Профессор построил их в один ряд,
// и хочет отобрать из них для первого занятия группу стоящих подряд учеников,
// в которой количество мальчиков и девочек одинаково.Сколько вариантов выбора есть у профессора?
// Решить задачу с помощью рекуррентных соотношений.Ввод
// .В первой строке входного файла задано число N(1 ≤ N ≤ 10 6)
// .Во второй строке задается описание построенного ряда из мальчиков и
// девочек — строка из N символов a и b(символ a соответствует девочке, а символ b — мальчику).
// Вывод .В единственной строке выходного файла должно содержаться
// количество вариантов выбора требуемой группы.
// Примеры
// Ввод 1     Ввод 2
// 3          8
// bab        abbababa
// Вывод 1    Вывод 2
// 2          13
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int main()
{
  std::ifstream inputFile("input.txt");
  std::ofstream outputFile("output.txt");
  if (!inputFile.is_open())
  {
    std::cout << "Error opening file" << std::endl;
    return 1;
  }


  /*int dsd = 1000000;
  std::ofstream temp("temp.txt");
  temp << dsd << "\n";
  for (size_t i = 0; i <= dsd; ++i)
  {
    temp << (std::rand() % 2 == 0 ? "a" : "b");
  }*/


  auto start = std::chrono::high_resolution_clock::now();

  int n;
  inputFile >> n;
  std::vector<int> wordCount(n * 2 + 1, 0);
  wordCount[n] = 1;

  int countEqualSegments = 0;
  int indexSum = 0;
  char ch;

  for (size_t i = 0; i < n; ++i)
  {
    inputFile >> ch;
    if (ch == 'a')
    {
      indexSum++;
    }
    else
    {
      indexSum--;
    }

    countEqualSegments += wordCount[indexSum + n];
    wordCount[n + indexSum]++;
  }


  std::cout << countEqualSegments << std::endl;
  outputFile << countEqualSegments << std::endl;
  outputFile.flush();

  auto end = std::chrono::high_resolution_clock::now();
  auto durationMic = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  auto durationMill = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << "Time spent: " << durationSec.count() << " secs" << std::endl;
  std::cout << "Time spent: " << durationMill.count() << " ms" << std::endl;
  std::cout << "Time spent: " << durationMic.count() << " mcs" << std::endl;
  return 0;
}
