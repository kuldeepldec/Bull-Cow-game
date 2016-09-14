// cowgame.cpp : Defines the entry point for the console application.

#pragma once
#include "stdafx.h"
#include<iostream>
#include<string>
#include "FbullcowGame.h"

using FText = std::string;
using int32 = int;

//functions in the game
void printIntro();
void playGame();
void printGameSummary();
FText getValidGuess();
bool AskPlayAgain();

FbullcowGame BCGame;   //instantite a game

//entry into the game
int main()
{
	
	bool bPlayAgain = false;
	do {
		printIntro();
		playGame();
		bPlayAgain = AskPlayAgain();
	} while (bPlayAgain);

	system("pause");
	return 0;
}
//Introduction of bull cow game
void printIntro() {
	std::cout << "***********************************************\n";
	std::cout << "Welcome to cows and Bulls game" << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter Isogram I am thinking of" << std::endl;
	std::cout << "************************************************\n";
	return;

}

// Output of your guess result
void playGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while(! BCGame.isgameWon() && BCGame.getcurrentTry()<=MaxTries){
    	FText Guess = getValidGuess(); 
		FBullCowCount BullCowCount= BCGame.submitValidGuess(Guess);

		std::cout << "Bulls is :" << BullCowCount.Bulls << std::endl;
		std::cout << "Cows is :" << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}
	printGameSummary();
	return;
	
}

// Try number of guess

FText getValidGuess() {
	FText Guess="";
	Ewordstatus status = Ewordstatus::Invalid_status;
	do {
		int32 CurrentTries = BCGame.getcurrentTry();
		//get a guess from user
		std::cout << "Try " << CurrentTries << " of " << BCGame.GetMaxTries() << ". Enter your guess with word starting " << BCGame.StartingChar() << " :" << std::endl;
		getline(std::cin, Guess);
		status = BCGame.checkguessValidity(Guess);
		switch (status) {
		case Ewordstatus::Not_Isogram:
			std::cout << "Please enter non repeating word " << std::endl;
			break;
		case Ewordstatus::Not_Lowercase:
			std::cout << "Please enter a lower case word" << std::endl;
			break;
		case Ewordstatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " word" << std::endl;
			break;

		default:
			break;
			
		}
		std::cout << std::endl;
	} while (status != Ewordstatus::OK);  //keep looping we do not get valid guess
	
	return Guess;

}

// Recursive program for playing the game again or not
bool AskPlayAgain() {

	std::cout << "Do you want to play again (y/n): ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');

}
// printing you have won or not
void printGameSummary()
{
	if (BCGame.isgameWon()) {
		std::cout << "Well done! You won\n";
	}
	else {
		std::cout << "Bad luck next time\n";
	}
	return;


}