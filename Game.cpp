#include <time.h>
#include <algorithm>
#include <iostream>
#include "Game.h"
#include "Computer.h"
#include "Player.h"




Game::Game(){
	time_t t;
	srand((unsigned int)time(&t));

	m_players.push_back(new Computer);
	m_players.push_back(new Player);

	m_numberString = "";

	m_rightPlace[0] = 'w';//initialize to wrong (w)
	m_rightPlace[1] = 'w';
	m_rightPlace[2] = 'w';
	m_rightPlace[3] = 'w';

	m_playerAttempts = 0;
	m_computerAttempts = 0;
}

void Game::startGame(){
	std::cout << "Welcome to MasterMind." << std::endl << std::endl;
	std::cout << "A player try to guess the other player's 4 digits number,"<< std::endl;
	std::cout << "where no two digits are the same." << std::endl;
	std::cout << "- If a digit is correct and in the correct place, it will get marked with a *" << std::endl;
	std::cout << "- If it is correct but not in the correct place, it will get marked with a !" << std::endl;
	std::cout << "- If a digit is not in the number, nothing will be shown" << std::endl;
	std::cout << "The goal is to figure the number out in the least number of guesses." << std::endl << std::endl;
	std::cout << "Let's start!" << std::endl;

	std::random_shuffle(m_players.begin(), m_players.end());//shuffle the vector to give random order of turns
	for (size_t i = 0; i < m_players.size(); i++){
		m_numberString = m_players[i]->generateNumber();
		for (int j = 0; j < 4; j++){
			m_numberToGuess.push_back(static_cast<int> (m_numberString[j] - 48));
		}
		if (i==0) guess(m_players[1]);
		else if (i == 1) guess(m_players[0]);//a player think of a number, the other tries to guess
	}

	if (m_computerAttempts < m_playerAttempts) std::cout << "Computer won!!" << std::endl;
	else if (m_playerAttempts < m_computerAttempts) std::cout << "Congratulations, you have beaten the computer!!" << std::endl;
	else std::cout << "Thats a tie!!" << std::endl;
	std::cout << "Do you want to play again? y/n" << std::endl;
	char c;
	std::cin >> c;
	if (c == 'y') {
		//initialize variables for next game
		m_numberString = "";
		m_rightPlace[0] = 'w';
		m_rightPlace[1] = 'w';
		m_rightPlace[2] = 'w';
		m_rightPlace[3] = 'w';
		m_playerAttempts = 0;
		m_computerAttempts = 0;
		m_wrongNumbers.clear();
		m_wrongPlaceList.clear();

		startGame();//start again
	}
}

void Game::guess(GenericPlayer* activePlayer){
	//player guessing
	if (dynamic_cast<Player*>(activePlayer)){
		std::cout << "The computer has thought of a number, try to guess it, type a 4 digits number." << std::endl;
		while (true){
			std::string strInput;
			std::cin >> strInput;
			std::string strOutput = printCharacters(strInput);
			m_playerAttempts++;
			if (strOutput == "****") break;//if all characters are correct exit loop
		}
		std::cout << "Correct! You have guessed it in " << m_playerAttempts << " attempts" << std::endl << std::endl;
		m_numberToGuess.clear();
	}
	//computer guessing
	else {
		std::cout << "The computer will try to guess your number:" << std::endl;
		//first guess
		m_guessString = activePlayer->generateNumber();
		while (true){
			std::cout << m_guessString << std::endl;
			std::string strOutput = printCharacters(m_guessString);
			m_computerAttempts++;
			if (strOutput == "****") break;
			populateContainers(strOutput);

			m_guessString = "    ";//empty the string for next guess
			for (int i = 0; i < 4; i++){
				if (m_rightPlace[i] != 'w')m_guessString[i] = m_rightPlace[i];//place correctNumbers on their place for next guess
			}
			placeKnownNumbers();//put any numbers in the wrongPlaceList in a different place for next guess

			for (int i = 0; i < 4; i++){
				if (m_guessString[i] == ' '){
					m_guessString[i] = randomDigit();//generate a random digit for all the remaining empty places
				}
			}
			system("pause");
			//next guesses
		}
		std::cout << "The computer have guessed it in " << m_computerAttempts << " attempts" << std::endl << std::endl;
		m_numberToGuess.clear();
	}
}

void Game::populateContainers(const std::string& strOutput){
	for (int i = 0; i < 4; i++){//add numbers to the rightPlace,wrongNumbers and wrongPlace containers
		if (strOutput[i] == '*') {
			m_rightPlace[i] = m_guessString[i];
			for (std::list<WrongPlaceStruct>::iterator it = m_wrongPlaceList.begin(); it != m_wrongPlaceList.end(); it++){
				if (it->num == m_rightPlace[i]){
					it = m_wrongPlaceList.erase(it);//if the correct number was in the wrongPlaceList, remove it from there
					if (it == m_wrongPlaceList.end()) break;
				}
			}
		}

		else if (strOutput[i] == ' ') m_wrongNumbers.push_back(m_guessString[i]);

		else if (strOutput[i] == '!'){
			bool allowNewInstance = true;
			for (std::list<WrongPlaceStruct>::iterator it = m_wrongPlaceList.begin(); it != m_wrongPlaceList.end(); it++){
				if (m_guessString[i] == it->num){
					it->place[i] = true;
					allowNewInstance = false;
				}
			}
			if (allowNewInstance == true){ //add it to the list only if its not already there
				WrongPlaceStruct wps;
				wps.num = m_guessString[i];
				wps.place[i] = true;
				m_wrongPlaceList.push_back(wps);
			}
		}
	}
}

std::string Game::printCharacters(const std::string& strInput){
	std::string strOutput;
	for (int i = 0; i < 4; i++){
		int n[4];
		n[i] = static_cast<int> (strInput[i] - 48);
		if (n[i] == m_numberToGuess[i]){//if guess digit is correct and same position
			strOutput.push_back('*');
		}
		else {
			bool charAlreadyPrinted = false;
			for (int j = 0; j < 4; j++){
				if (n[i] == m_numberToGuess[j] && i != j){//check if digit is correct but in different position
					strOutput.push_back('!');
					charAlreadyPrinted = true;//if yes print it and skip space
				}
			}
			if (!charAlreadyPrinted) strOutput.push_back(' ');//if not found print space
		}
	}
	std::cout << strOutput << std::endl;
	return strOutput;
}

void Game::placeKnownNumbers(){
	for (std::list<WrongPlaceStruct>::iterator it = m_wrongPlaceList.begin(); it != m_wrongPlaceList.end(); it++){
		bool exitFor = false;
		for (int i = 0; i < 4; i++){
			if (exitFor == false){
				if (m_guessString[i] == ' ' && it->place[i] == false){
					//starting from left, try to put all numbers on the wrongPlace container on a place that is not false
					m_guessString[i] = it->num;
					exitFor = true;
				}
			}
		}
	}
}

char Game::randomDigit(){//generate a random number between 0 and 9 for each empty char in the guess,
	//if the number is already in the wrongNumber vector, rightPlace vector or the current guess(to avoid repeating any number)
	//then tries again until a number is valid
	char c;
	bool exit = false;
	while (!exit)
	{
		bool cont = true;//cont for continue
		int r = rand();
		int num = r % 10;
		c = (char)num + 48;//conversion to char

		for (size_t i = 0; i < m_wrongNumbers.size(); i++){
			if (m_wrongNumbers[i] == c) cont = false;
		}
		if (!cont){
			continue;
		}

		for (int j = 0; j < 4; j++){
			if (m_guessString[j] == c) cont = false;
		}
		if (!cont){
			continue;
		}

		for (int k = 0; k < 4; k++){
			if (m_rightPlace[k] == c) cont = false;
		}
		if (!cont){
			continue;
		}
		exit = true;
	}
	return c;
}