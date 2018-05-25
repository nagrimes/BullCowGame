/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;



void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText Guess);
bool AskToPlayAgain();

FBullCowGame BCGame;


int main() {
	do {
		PrintIntro();
		PlayGame();
		
	} while (AskToPlayAgain());
	return 0;
}

void PlayGame(){
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess(); // TODO make loop checking valid

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO add a game summary.
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

// loop contuinually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << ". Please enter your guess. ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintBack(FText Guess){
	std::cout << "Your guess was: " << Guess << "\n";
}

bool AskToPlayAgain(){
	std::cout << "Would you like to play again?";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}
