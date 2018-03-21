/*
The game logic(no view code or direct user interaction).
The game is a simple guess the word game.

*/

#pragma once

#include <string>

// Header file works as a contract 
// never use using for namespace in header file

//this called substitution. Type Aliases. To make syntax UnrealEngine-friendly
using FString = std::string;
using int32 = int;


// 2 integers initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame 
{
// classes literally mean "types". 
// Think of a class as a template to create instances
// Also think of a instance as a console that contains functions that do things.
// And like a console, class needs to be initialized(power up/boot) before use. 
// To do so, it requires "constructor"
public:
	FBullCowGame();// Constructor. It becomes deconstructor when "~" at the front

	int32 GetMaxTries()const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString)const; 
	//When declare a function in .h file, arugument name is optional.
	//But it still needs to be there when defining(implementing) the function

	void Reset(); 
	// counts bulls & cows, and increments try #(number) assuming valid guess
	FBullCowCount SubmitValidGuess(FString);


// Please try and ignore this and focus on the interface above ^^
private:
	//see constructor for initialization of declared values below
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString)const;
	bool IsLowercase(FString)const;

};
