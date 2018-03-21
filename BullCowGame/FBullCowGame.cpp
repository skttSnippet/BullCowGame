#pragma once

#include "FBullCowGame.h"

#include <map>
#define TMap std::map // making syntax UnrealEngine-Friendly
//#define is a textual replacement.a alternative for "using"

using int32 = int;


FBullCowGame::FBullCowGame(){Reset();}// Constructor. Set game back to default.
// variables overwriting values that are in class called runtime value
// variables inside class would be compile time values

// all the getter methods
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}
//const ONLY allowed on member functions/methods. not allowed for normal func.

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,10},{6,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;// constant expression
	const FString HIDDEN_WORD = "planet";//constexpr only allowed for literal type like int or a reference type.So only use const here.
							//MUST BE A Isogram
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{

	// if the guess isn't an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	// if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength())// <calling method inside the class doesn't need namespace::
	{
		return EGuessStatus::Wrong_Length;
	}
	// if the guess isn't all lowercase 
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	// increment the turn number
	MyCurrentTry++;// var = var+1
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all the letters in hidden word  
	for (int32 MHWIndex = 0; MHWIndex< WordLength; MHWIndex++)
	{	// compare letters against the the guess
		for (int32 GIndex = 0; GIndex < WordLength; GIndex++)
		{	// if they match then
			if (MHWIndex == GIndex)
			{	// if they're in the same place
				if (Guess[GIndex] == MyHiddenWord[MHWIndex])
				{	// increment bulls 
					BullCowCount.Bulls++;
				}
				else
				{	// increment cows. If not a bull, must be a cow.
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter strings words as isograms
	if (Word.length() <= 1) { return true; }

	
	TMap<char, bool> LetterSeen;// setup our map
	for (auto Letter : Word)		//for all letters of the word
	{
		Letter = tolower(Letter);//handel mixed case(lower/upper)
		if (LetterSeen[Letter]) //if the letter is in the map
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
			

			

	}
	return true; // for example in cases where /0 is entered
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lower case letter
		{
			return false;
		}
	}
	return true;
}

