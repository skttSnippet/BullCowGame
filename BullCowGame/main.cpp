/*
This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern deisgn and is responsible for all user
interaction. For game logic see the FBullCowGame class

This main.cpp is basically the view controller for this whole game

User-Controller-Model-View-User 
MVC patter
*/

// #include <iostream> for standard stuff
// #include "MyCode.h" for personal code
// #include literally means copy and paste content in the library/file
// every starts with "#" in the code called preprocessor directive. It happens before compilation happens
// iostream here is a library
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// this line can allow code to remove "std::".
// But when multiple "using" are used in same file, then there will be good chance causing namcespace clash
//using namespace std;

//this called substitution. Type Aliases. To make syntax UnrealEngine-friendly
using Ftext = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrinGameSummary();
// header file content in the future
// funcion(){} would be implementation of the function 
// here we only need prototype of the func, curly brackets {} not needed 

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays


// in cpp function starts with return_type
// it can be int32, string, void, etc. Void stands for 'nothing returned'



// the entry point for our application
int main()
{
	// Don't substitute int main() with int32 main() cuz this is called by operating system. 
	// We don't want confuse things. It would still work with int32 but I don't wanna mess around

	std::cout << BCGame.GetCurrentTry();
	bool  bPlayAgain = false;

	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;//exit the application
}


void PrintIntro()
{
	// When a var is only available inside a func,
	// If this var being used outside this func, it would be "out of scope"

	// std here is a namespace in iostream library
	// the way to access members of namespace is colon colon "::"
	// cout for character output. Wrapped up in(tagged with) namespace "std"(like a folder)

	// std::cout << "Welcome to Bulls and Cows\n";
	//    ||
	// std::cout << "Welcome to Bulls and Cows" ;
	// std::cout << "\n" ;
	//    ||
	// std::cout << "Welcome to Bulls and Cows" ;
	// std::cout << std::endl; // endl means end line

	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl; // endl means end line
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;


	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess();
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}

	PrinGameSummary();
	return;
}

// loop continueally till the use gives valid guess
Ftext GetValidGuess()
{	
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";
	do 
	{	// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of ";
		std::cout << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check the validity
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
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
			//assuming the guess is valid
			break;
			
		}

	} while (Status != EGuessStatus::OK);//keep do while looping till we get a valid guess
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) \n";
	Ftext Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrinGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}




