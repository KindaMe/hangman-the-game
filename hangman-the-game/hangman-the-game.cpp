//add categories later

#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>

void gameplayLoop(std::vector<std::string> words);
std::string randomWord(std::vector<std::string> words);
bool validGuess(char guess, std::string wrongGuesses, std::string correctGuesses);
std::string spacer(std::string word);
void readFile(std::vector<std::string>* words);

int main()
{
	std::vector<std::string> words;
	readFile(&words);

	srand((unsigned)time(0));

	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n";
	std::cout << "PRESS ENTER TO START...\n";
	std::cin.get();

	gameplayLoop(words);

	system("pause>0");
}

std::string randomWord(std::vector<std::string> words)
{
	int randomNumber = rand() % words.size();
	return words[randomNumber];
}

void gameplayLoop(std::vector<std::string> words)
{
	std::string word = randomWord(words);
	int length = word.length();
	std::string wordBlank = std::string(length, '_');
	int health = 6;
	char guess;
	std::string wrongGuesses;
	std::string correctGuesses;
	bool correctGuess = false;
	int score = 0;

	do
	{
		do
		{
			system("cls");
			std::cout << "HANGMAN - THE GAME\n";
			std::cout << "******************\n";

			std::cout << spacer(wordBlank);

			std::cout << "\n\nATTEMPTS LEFT: " << health;
			std::cout << "\nUSED LETTERS: " << spacer(wrongGuesses);
			std::cout << "\n\nENTER YOUR GUESS: ";
			std::cin >> guess;
			guess = toupper(guess);

			if (validGuess(guess, correctGuesses, wrongGuesses) == false)
			{
				system("cls");
				std::cout << "HANGMAN - THE GAME\n";
				std::cout << "******************\n";

				std::cout << spacer(wordBlank);

				std::cout << "\n\nYOU TRIED THAT ONE ALREADY!";
				std::cin.clear();
				std::cin.ignore();
				std::cin.get();
			}
			else if (isalpha(guess) == false)
			{
				system("cls");
				std::cout << "HANGMAN - THE GAME\n";
				std::cout << "******************\n";

				std::cout << spacer(wordBlank);

				std::cout << "\n\nWRONG LETTER!";
				std::cin.clear();
				std::cin.ignore();
				std::cin.get();
			}
		} while (validGuess(guess, correctGuesses, wrongGuesses) == false || isalpha(guess) == false);

		for (int i = 0; i < length; i++)
		{
			if (word[i] == guess)
			{
				wordBlank[i] = guess;
				correctGuess = true;
				score++;
			}
		}
		switch (correctGuess)
		{
		case false:
			wrongGuesses.push_back(guess);
			health--;
			break;
		case true:
			correctGuesses.push_back(guess);
			correctGuess = false;
			break;
		}
	} while (score != length && health != 0);

	system("cls");
	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n\n";

	std::cout << word;

	if (score == length)
	{
		std::cout << "\n\nYOU WIN!";
	}
	else if (health == 0)
	{
		std::cout << "\n\nYOU LOSE.";
	}
}

bool validGuess(char guess, std::string wrongGuesses, std::string correctGuesses)
{
	for (int i = 0; i < correctGuesses.size(); i++)
	{
		if (correctGuesses[i] == guess)
		{
			return false;
		}
	}
	for (int i = 0; i < wrongGuesses.size(); i++)
	{
		if (wrongGuesses[i] == guess)
		{
			return false;
		}
	}

	return true;
}

std::string spacer(std::string word)
{
	int length = word.size();
	std::string output;

	for (int i = 0; i < length; i = i++)
	{
		output += word.substr(i, 1) + " ";
	}
	return output;
}

void readFile(std::vector<std::string>* words)
{
	std::ifstream file;
	std::string line;

	file.open("words.txt");
	while (getline(file, line))
	{
		words->push_back(line);
	}

	file.close();
}