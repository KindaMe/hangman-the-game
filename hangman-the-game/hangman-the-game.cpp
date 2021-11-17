#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem::v1;

void gameplayLoop(std::vector<std::string> words, std::string categoryName);
std::string randomWord(std::vector<std::string> words);
void difficulty(int* health);
bool validGuess(char guess, std::string wrongGuesses, std::string correctGuesses);
std::string spacer(std::string word);
void readFile(std::vector<std::string>* words, std::string fileName);
bool restart();
std::string chooseCategory(std::vector<std::string>* words);
std::string convertPath(std::string path);

int main()
{
	std::vector<std::string> words;
	std::string categoryName;

	srand((unsigned)time(0));

	do
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n";
		std::cout << "\nPRESS ENTER TO START...\n";
		std::cin.get();

		categoryName = chooseCategory(&words);
		gameplayLoop(words, categoryName);
	} while (restart() == true);

	system("cls");
	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n";

	std::cout << "\nThanks for playing!\ngithub.com/KindaMe\n";

	system("pause>0");
}

void gameplayLoop(std::vector<std::string> words, std::string categoryName)
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
			std::cout << "******************\n";
			std::cout << "CATEGORY: " << categoryName << "\n\n";

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
				std::cout << "******************\n";
				std::cout << "CATEGORY: " << categoryName << "\n\n";

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
				std::cout << "******************\n";
				std::cout << "CATEGORY: " << categoryName << "\n\n";

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
	std::cout << "******************\n";
	std::cout << "CATEGORY: " << categoryName << "\n\n";

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

void readFile(std::vector<std::string>* words, std::string fileName)
{
	std::ifstream file;
	std::string line;

	words->clear();

	file.open(fileName);
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

std::string chooseCategory(std::vector<std::string>* words)
{
	std::string categoryName;
	int choice;
	std::vector<std::string> categories;

	system("cls");
	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n\n";

	std::cout << "CHOOSE CATEGORY: \n\n";

	for (const auto& name : fs::directory_iterator("Categories/"))//gets file paths in folder
	{
		fs::path path = name;
		std::string path_string{ path.u8string() };

		categories.push_back(path_string);
	}

	for (int i = 0; i < categories.size(); i++)
	{
		std::cout << i + 1 << " - " << convertPath(categories[i]) << "\n";
	}

	std::cout << "\n";
	std::cin >> choice;
	readFile(words, categories[choice - 1]);

	return convertPath(categories[choice - 1]);
}

std::string convertPath(std::string path)
{
	std::string newName;

	for (int i = 11; i <= (path.size() - 5); i++)//skips "category/" and ends before ".txt"
	{
		newName.push_back(toupper(path[i]));
	}

	return newName;
}