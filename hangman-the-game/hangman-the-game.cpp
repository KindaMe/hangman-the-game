//add categories later

#include <iostream>
#include <vector>

void gameplayLoop(std::vector<std::string> words);
std::string randomWord(std::vector<std::string> words);
bool validGuess(char guess, std::vector<char>wrongGuesses, std::vector<char>correctGuesses);

int main()
{
	std::vector<std::string> words;
	srand((unsigned)time(0));

	words.push_back("poggers");
	words.push_back("omegalul");
	words.push_back("pogchamp");

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
	std::vector<char>wrongGuesses;
	std::vector<char>correctGuesses;
	bool correctGuess = false;
	int score = 0;

	do
	{
		do
		{
			system("cls");
			std::cout << "HANGMAN - THE GAME\n";
			std::cout << "******************\n";

			std::cout << wordBlank;

			std::cout << "\n\nTries left: " << health;
			std::cout << "\nEnter your guess: ";
			std::cin >> guess;

			if (validGuess(guess, correctGuesses, wrongGuesses) == false)
			{
				system("cls");
				std::cout << "HANGMAN - THE GAME\n";
				std::cout << "******************\n";

				std::cout << wordBlank;

				std::cout << "\n\nTries left: " << health;

				std::cout << "\nYou tried that one already!";
				std::cin.clear();
				std::cin.ignore();
				std::cin.get();
			}
		} while (validGuess(guess, correctGuesses, wrongGuesses) == false);

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
		std::cout << "\n\nYou win!";
	}
	else if (health == 0)
	{
		std::cout << "\n\nYou lose.";
	}
}

bool validGuess(char guess, std::vector<char> wrongGuesses, std::vector<char> correctGuesses)
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