#include "FBullCowGame.h"
#include <map>
#define TMap std::map

int32 FBullCowGame::GetMaxTries() const { return  MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
	int32 constexpr MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;

	MyCurrentTry = 1;
}

FBullCowGame::FBullCowGame() { Reset(); }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong 
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowercase(Guess)) { //if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsIsogram(Guess)) { //If the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
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
	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// create TMap with keys a - z
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) { // for all letters in the word
		Letter = tolower(Letter); // handle mixed case
		
		if (LetterSeen[Letter]) //if the letter is in the map
			return false;// we do Not have an isogram
		else//otherwise
			LetterSeen[Letter] = true;// add the letter to the map as seen
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) { // for all letters in the word
		if (islower(Letter)) { // if the letter is lower
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}