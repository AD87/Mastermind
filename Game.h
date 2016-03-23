#pragma once

#include <vector>
#include <string>
#include <list>
#include "GenericPlayer.h"
#include "WrongPlaceStruct.h"

class Game{
public:
	Game();
	void startGame();
	void guess(GenericPlayer* activePlayer);// the guessing state
	void populateContainers(const std::string& strOutput);// place all numbers to the respective container
	std::string printCharacters(const std::string& strInput);// print on the screen where the numbers are in the correct place or not
	void placeKnownNumbers();// try a different position for all digits on the wrongPlaceList
	char randomDigit();// returns a valid digit as char
private:
	std::string m_numberString;//the 4 digit's number to guess, as a string
	std::string m_guessString;//the number the computer has generated as its guess, as a string
	std::vector<int> m_numberToGuess;
	std::vector<GenericPlayer*> m_players;
	char m_rightPlace[4];//we will place the numbers guessed in the correct place here
	std::vector<char> m_wrongNumbers;//container to store all wrong numbers
	std::list<WrongPlaceStruct> m_wrongPlaceList;//list of structs, here we will place numbers in the wrong place
	int m_playerAttempts;
	int m_computerAttempts;
};