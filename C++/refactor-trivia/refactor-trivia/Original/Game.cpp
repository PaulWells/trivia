#include "pch.h"
#include "Game.h"
#include <iostream>
#include <sstream>

using namespace std;

Game::Game(shared_ptr<ostream> os) : currentPlayer(0), places(), purses(), m_OutputStream(os){
	for (int i = 0; i < 500; i++)
	{
		ostringstream oss (ostringstream::out);
		oss << "Pop Question " << i;
		
		popQuestions.push_back(oss.str());

		char str[255];
		sprintf_s(str, "Science Question %d", i);
		scienceQuestions.push_back(str);

		char str1[255];
		sprintf_s(str1, "Sports Question %d", i);
		sportsQuestions.push_back(str1);

		rockQuestions.push_back(CreateRockQuestion(i));
	}
}

string Game::CreateRockQuestion(int index)
{
	char indexStr[127];
	sprintf_s(indexStr, "Rock Question %d", index);
	return indexStr;
}

bool Game::IsPlayable()
{
	return (HowManyPlayers() >= 2);
}

bool Game::Add(string playerName){
	players.push_back(playerName);
	places[HowManyPlayers()] = 0;
	purses[HowManyPlayers()] = 0;
	inPenaltyBox[HowManyPlayers()] = false;

	*m_OutputStream << playerName << " was added" << endl;
	*m_OutputStream << "They are player number " << players.size() << endl;
	return true;
}

int Game::HowManyPlayers()
{
	return players.size();
}

void Game::Roll(int roll)
{
	*m_OutputStream << players[currentPlayer] << " is the current player" << endl;
	*m_OutputStream << "They have rolled a " << roll << endl;

	if (inPenaltyBox[currentPlayer])
	{
		if (roll % 2 != 0)
		{
			isGettingOutOfPenaltyBox = true;

			*m_OutputStream << players[currentPlayer] << " is getting out of the penalty box" << endl;
			places[currentPlayer] = places[currentPlayer] + roll;
			if (places[currentPlayer] > 11) places[currentPlayer] = places[currentPlayer] - 12;

			*m_OutputStream << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
			*m_OutputStream << "The category is " << currentCategory() << endl;
			askQuestion();
		}
		else
		{
			*m_OutputStream << players[currentPlayer] << " is not getting out of the penalty box" << endl;
			isGettingOutOfPenaltyBox = false;
		}

	}
	else
	{

		places[currentPlayer] = places[currentPlayer] + roll;
		if (places[currentPlayer] > 11) places[currentPlayer] = places[currentPlayer] - 12;

		*m_OutputStream << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
		*m_OutputStream << "The category is " << currentCategory() << endl;
		askQuestion();
	}

}

void Game::askQuestion()
{
	if (currentCategory() == "Pop")
	{
		*m_OutputStream << popQuestions.front() << endl;
		popQuestions.pop_front();
	}
	if (currentCategory() == "Science")
	{
		*m_OutputStream << scienceQuestions.front() << endl;
		scienceQuestions.pop_front();
	}
	if (currentCategory() == "Sports")
	{
		*m_OutputStream << sportsQuestions.front() << endl;
		sportsQuestions.pop_front();
	}
	if (currentCategory() == "Rock")
	{
		*m_OutputStream << rockQuestions.front() << endl;
		rockQuestions.pop_front();
	}
}


string Game::currentCategory()
{
	if (places[currentPlayer] == 0) return "Pop";
	if (places[currentPlayer] == 4) return "Pop";
	if (places[currentPlayer] == 8) return "Pop";
	if (places[currentPlayer] == 1) return "Science";
	if (places[currentPlayer] == 5) return "Science";
	if (places[currentPlayer] == 9) return "Science";
	if (places[currentPlayer] == 2) return "Sports";
	if (places[currentPlayer] == 6) return "Sports";
	if (places[currentPlayer] == 10) return "Sports";
	return "Rock";
}

bool Game::CorrectAnswer()
{
	if (inPenaltyBox[currentPlayer])
	{
		if (isGettingOutOfPenaltyBox)
		{
			*m_OutputStream << "Answer was correct!!!!" << endl;
			purses[currentPlayer]++;
			*m_OutputStream << players[currentPlayer]
			     << " now has "
			     << purses[currentPlayer]
				<<  " Gold Coins." << endl;

			bool winner = didPlayerWin();
			currentPlayer++;
			if (currentPlayer == players.size()) currentPlayer = 0;

			return winner;
		}
		else
		{
			currentPlayer++;
			if (currentPlayer == players.size()) currentPlayer = 0;
			return true;
		}



	}
	else
	{

		*m_OutputStream << "Answer was corrent!!!!" << endl;
		purses[currentPlayer]++;
		*m_OutputStream << players[currentPlayer]
				<< " now has "
				<< purses[currentPlayer]
			<< " Gold Coins." << endl;

		bool winner = didPlayerWin();
		currentPlayer++;
		if (currentPlayer == players.size()) currentPlayer = 0;

		return winner;
	}
}

bool Game::WrongAnswer()
{
	*m_OutputStream << "Question was incorrectly answered" << endl;
	*m_OutputStream << players[currentPlayer] + " was sent to the penalty box" << endl;
	inPenaltyBox[currentPlayer] = true;

	currentPlayer++;
	if (currentPlayer == players.size()) currentPlayer = 0;
	return true;
}


bool Game::didPlayerWin()
{
	return !(purses[currentPlayer] == 6);
}
