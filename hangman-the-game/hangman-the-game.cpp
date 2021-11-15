#include <iostream>
#include <random>
#include <vector>

std::string randomWord(std::vector<std::string> words);

int main()
{
	std::vector<std::string> words;
	srand((unsigned)time(0));

	words.push_back("1111");
	words.push_back("2222");
	words.push_back("3333");

	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
	std::cout << randomWord(words) << "\n";
}

std::string randomWord(std::vector<std::string> words)
{
	int randomNumber = rand() % words.size();
	return words[randomNumber];
}