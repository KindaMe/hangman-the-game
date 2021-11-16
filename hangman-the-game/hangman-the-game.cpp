#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>

void gameplayLoop(std::vector<std::string> words);
std::string randomWord(std::vector<std::string> words);
void difficulty(int* health);
bool validGuess(char guess, std::string wrongGuesses, std::string correctGuesses);
std::string spacer(std::string word);
void readFile(std::vector<std::string>* words);
bool restart();

int main()
{
	std::vector<std::string> words;
	readFile(&words);

	srand((unsigned)time(0));

	do
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n";
		std::cout << "\nPRESS ENTER TO START...\n";
		std::cin.get();

		gameplayLoop(words);
	} while (restart() == true);

	system("cls");
	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n";

	std::cout << "\nThanks for playing!\ngithub.com/KindaMe\n";

	system("pause>0");
}

void gameplayLoop(std::vector<std::string> words)
{
	std::string word = randomWord(words);
	int length = word.length();
	std::string wordBlank = std::string(length, '_');

	int health = 6;
	int score = 0;

	char guess;
	std::string wrongGuesses;
	std::string correctGuesses;
	bool correctGuess = false;

	difficulty(&health);

	do
	{
		do
		{
			system("cls");
			std::cout << "HANGMAN - THE GAME\n";
			std::cout << "******************\n\n";

			std::cout << spacer(wordBlank);

			std::cout << "\n\n\nATTEMPTS LEFT: " << health;
			(wrongGuesses.length() == 0) ? std::cout << "\nUSED LETTERS: NONE" : std::cout << "\nUSED LETTERS: " << spacer(wrongGuesses);
			std::cout << "\n\nENTER YOUR GUESS: ";
			std::cin >> guess;
			guess = toupper(guess);

			if (validGuess(guess, correctGuesses, wrongGuesses) == false)
			{
				system("cls");
				std::cout << "HANGMAN - THE GAME\n";
				std::cout << "******************\n\n";

				std::cout << spacer(wordBlank);

				std::cout << "\n\n\nYOU TRIED THAT ONE ALREADY!";
				std::cin.clear();
				std::cin.ignore();
				std::cin.get();
			}
			else if (isalpha(guess) == false)
			{
				system("cls");
				std::cout << "HANGMAN - THE GAME\n";
				std::cout << "******************\n\n";

				std::cout << spacer(wordBlank);

				std::cout << "\n\n\nWRONG LETTER!";
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
		std::cout << "\n\n\nYOU WIN!";
	}
	else if (health == 0)
	{
		std::cout << "\n\n\nYOU LOSE.";
	}
}

std::string randomWord(std::vector<std::string> words)
{
	int randomNumber = rand() % words.size();
	return words[randomNumber];
}

void difficulty(int* health)
{
	bool valid = false;

	do
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n\n";

		std::cout << "SET DIFFICULTY:\n";
		std::cout << "\n1 - EASY";
		std::cout << "\n2 - NORMAL";
		std::cout << "\n3 - HARD\n\n";

		char mode;

		std::cin >> mode;

		switch (mode)
		{
		case '1':
			*health = 8;
			valid = true;
			break;
		case '2':
			*health = 6;
			valid = true;
			break;
		case '3':
			*health = 4;
			valid = true;
			break;
		default:
			valid = false;
			std::cout << "WRONG INPUT - TRY AGAIN...";
			std::cin.clear();
			std::cin.ignore();
			std::cin.get();
			break;
		}
	} while (valid == false);
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

bool restart()
{
	char yn;

	std::cout << "\n\nRestart? (y/n)";
	std::cin >> yn;
	yn = toupper(yn);

	switch (yn)
	{
	case 'Y':
		return true;
	default:
		return false;
	}
}