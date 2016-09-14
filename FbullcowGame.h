/* This is game header file and this game is about guessing a word if answer is correct it is
bull and id it is not correct it is cow
*/

#pragma once

#include<string>
// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//structure for counting bulls and cows
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

// condition for guess is invalid,lowercase or wrong word length
enum Ewordstatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// class for bull cow game
class FbullcowGame {

public:
	
	FbullcowGame();    //constructor

	int32 GetMaxTries()const;
	int32 getcurrentTry()const;
	bool isgameWon()const;
	Ewordstatus checkguessValidity(FString)const;
	int32 GetHiddenWordLength()const;
	char StartingChar()const;
	

	void Reset();
	FBullCowCount submitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bplayWon;
	bool IsIsogram(FString)const;
	bool IsLowerCase(FString)const;

};
