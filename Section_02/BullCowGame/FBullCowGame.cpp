#include "FBullCowGame.h"

int32 FBullCowGame::GetMaxTries() const { return  MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
	int32 constexpr MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;

	MyCurrentTry = 1;
}

FBullCowGame::FBullCowGame() { Reset(); }



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (false) { //If the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (false) { //if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		//compare letters against the guess
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (Guess[i] == MyHiddenWord[j]) {
				// if they're in the same place
				if (i == j)
					BullCowCount.Bulls++; // increment bulls
				// else
				else
					BullCowCount.Cows++; // increment cows
			}
		}
	}
	return BullCowCount;
}
