#pragma once

#include "stdafx.h"
#include "FbullcowGame.h"
#include<map>
#define Tmap std::map //using map unreal friendly

using FString = std::string;
using int32 = int;

FbullcowGame::FbullcowGame(){ Reset();}
int32 FbullcowGame::getcurrentTry()const {return MyCurrentTry;} //return current try of guesses
int32 FbullcowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
char FbullcowGame::StartingChar() const{return MyHiddenWord[0];}


// return hidden word length
bool FbullcowGame::isgameWon()const {return bplayWon;} // return if game is worn or better luck next time

int32 FbullcowGame::GetMaxTries()const { 
	Tmap<int32, int32>WordLengthMaxTries{{3,4},{4,7},{5,10},{6,15} };// maximum word length for different letter words
	return WordLengthMaxTries[MyHiddenWord.length()];
}

void FbullcowGame::Reset()// reset the game to initial level
{
	
	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;
	bool bplayWon=false;
	MyCurrentTry = 1;
	return;
}



// return status that guess is isogram, lowercase or word length not appropriate
Ewordstatus FbullcowGame::checkguessValidity(FString Guess)const
{
	if (!IsIsogram(Guess)) {
		return Ewordstatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return Ewordstatus::Not_Lowercase;
	}
	else if (Guess.length()!=GetHiddenWordLength()) {
		return Ewordstatus::Wrong_Length;
	}
	else {
		return Ewordstatus::OK;
	}
}

//providing bull and cows count assuming a valid guess
FBullCowCount FbullcowGame::submitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordlength = MyHiddenWord.length();
	
	for (int32 i = 0; i < HiddenWordlength; i++) {
		for (int32 j = 0; j < HiddenWordlength; j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordlength) {
		bplayWon = true;
	}
	else {
		bplayWon = false;

	}

	return BullCowCount;
}

bool FbullcowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 word as isogram
	if (Word.length() <= 1) { return true; }
	Tmap<char, bool>LetterSeen;
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter]=true; }
	}
	
	//check the string character 1 by 1
	//if any character found 2 times return false
	return true;
}
// check that guess word is lower letter or not
bool FbullcowGame::IsLowerCase(FString Word) const
{
	
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
		
	}

	return true;
			
}
