#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem::v1;

void gameplayLoop();
std::string randomWord(std::vector<std::string> words);
int difficulty();
bool validGuess(char guess, std::string wrongGuesses, std::string correctGuesses);
std::string spacer(std::string word);
std::string readFile(std::string filePath, int* spaceCounter);
bool restart();
std::string chooseCategory();
std::string convertPath(std::string filePath);
void hangman(int health);

int main()
{
	srand((unsigned)time(0));

	do
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n";
		std::cout << "\nPRESS ENTER TO START...\n";
		std::cin.get();

		gameplayLoop();
	} while (restart() == true);

	system("cls");
	std::cout << "HANGMAN - THE GAME\n";
	std::cout << "******************\n";

	std::cout << "\nThanks for playing!\ngithub.com/KindaMe\n";

	std::cin.clear();
	std::cin.ignore();
	std::cin.get();
	return 0;
}

void gameplayLoop()
{
	std::string categoryPath = chooseCategory();
	std::string categoryName = convertPath(categoryPath);

	int spaceCounter = 0;
	std::string word = readFile(categoryPath, &spaceCounter);
	int length = word.length();
	std::string wordBlank;
	for (int i = 0; i < length; i++)
	{
		(isalpha(word[i])) ? wordBlank.push_back('_') : wordBlank.push_back(word[i]);
	}

	int health = difficulty();
	int score = 0 + spaceCounter;

	char guess;
	std::string wrongGuesses;
	std::string correctGuesses;
	bool correctGuess = false;

	do
	{
		do
		{
			system("cls");
			std::cout << "HANGMAN - THE GAME\n";
			std::cout << "******************\n";
			std::cout << "CATEGORY: " << categoryName << "\n\n";

			std::cout << spacer(wordBlank);

			hangman(health);

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
		std::cout << "\n\n";
		std::cout << " \\O/\n";
		std::cout << "  I\n";
		std::cout << "  I\n";
		std::cout << " / \\";

		std::cout << "\n\nYOU WIN!";
	}
	else if (health == 0)
	{
		hangman(health);

		std::cout << "\n\nYOU LOSE.";
	}
}

std::string chooseCategory()
{
	int choice, categoryIndex;
	std::vector<std::string> categories;

	do
	{
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

		if (categories.size() != 0)
		{
			for (int i = 0; i < categories.size(); i++)
			{
				std::cout << i + 1 << " - " << convertPath(categories[i]) << "\n";
			}
		}
		else
		{
			std::cout << "NO CATEGORIES FOUND - CHECK YOUR GAME FILES...\n\nVisit\ngithub.com/KindaMe\nfor more info.";

			std::cin.get();
			exit(1);
		}

		std::cout << "\n";
		std::cout << "CHOICE: ";
		if (std::cin >> choice && (choice != 0 && choice <= categories.size()))
		{
			categoryIndex = choice - 1;

			std::ifstream peekFile(categories[categoryIndex]);
			if (peekFile.peek() == EOF)
			{
				std::cout << "\nCATEGORY IS EMPTY - CHOOSE A DIFFERENT ONE...";
			}
			else
			{
				return categories[categoryIndex];
			}
		}
		else
		{
			std::cout << "\nWRONG INPUT - TRY AGAIN...";
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin.get();

		categories.clear();
	} while (true);
}

std::string convertPath(std::string filePath)
{
	std::string newName;

	for (int i = 11; i <= (filePath.size() - 5); i++)//skips "category/" and ends before ".txt"
	{
		newName.push_back(toupper(filePath[i]));
	}

	return newName;
}

std::string readFile(std::string filePath, int* spaceCounter)
{
	std::vector<std::string> words;

	std::ifstream file;
	std::string line;

	file.open(filePath);
	while (getline(file, line))
	{
		words.push_back(line);
	}

	file.close();

	std::string word = randomWord(words);

	for (int i = 0; i < word.size(); i++)
	{
		if (!(isalpha(word[i])))
		{
			*spaceCounter = *spaceCounter + 1;
		}
	}

	return word;
}

std::string randomWord(std::vector<std::string> words)
{
	int randomNumber = rand() % words.size();
	return words[randomNumber];
}

int difficulty()
{
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
		std::cout << "CHOICE: ";
		std::cin >> mode;

		switch (mode)
		{
		case '1':
			return 8;

		case '2':
			return 6;

		case '3':
			return 4;

		default:
			std::cout << "\nWRONG INPUT - TRY AGAIN...";
			std::cin.clear();
			std::cin.ignore();
			std::cin.get();
			break;
		}
	} while (true);
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

	for (int i = 0; i < length; i++)
	{
		output += word.substr(i, 1) + " ";
	}
	return output;
}

bool restart()
{
	char yn;

	std::cout << "\n\nRestart? (y/n)\n";
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

void hangman(int health)
{
	switch (health)
	{
	case 0:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |   /I\\ \n";
		std::cout << "  |    I\n";
		std::cout << "  |   / \\ \n";
		std::cout << "__|__";
		break;
	case 1:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |   /I\\ \n";
		std::cout << "  |    I\n";
		std::cout << "  |   / \n";
		std::cout << "__|__";
		break;
	case 2:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |   /I\\ \n";
		std::cout << "  |    I\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 3:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |   /I\\ \n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 4:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |   /I\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 5:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |    I\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 6:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |    O\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 7:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |    |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	case 8:
		std::cout << "\n\n";
		std::cout << "  ______\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "  |\n";
		std::cout << "__|__";
		break;
	}
}