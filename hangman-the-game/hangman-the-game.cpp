//add categories later

#include <iostream>
#include <vector>

void gameplayLoop(std::vector<std::string> words);
std::string randomWord(std::vector<std::string> words);

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
	bool correctGuess = false;
	int score = 0;

	do
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n";

		std::cout << wordBlank;

		std::cout << "\n\nTries left: " << health;
		std::cout << "\nEnter your guess: ";
		std::cin >> guess;

		for (int i = 0; i < length; i++)
		{
			if (word[i] == guess)
			{
				wordBlank[i] = guess;
				correctGuess = true;
				score++;
			}
		}
		if (correctGuess == false)
		{
			wrongGuesses.push_back(guess);
			health--;
		}
		else
		{
			correctGuess = false;
		}
	} while (score != length && health != 0);

	if (score == length)
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n\n";

		std::cout << wordBlank;

		std::cout << "\n\nYou win!";
	}
	else if (health == 0)
	{
		system("cls");
		std::cout << "HANGMAN - THE GAME\n";
		std::cout << "******************\n\n";

		std::cout << wordBlank;

		std::cout << "\n\nYou lose.";
	}
}