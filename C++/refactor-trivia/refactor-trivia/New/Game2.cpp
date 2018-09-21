#include "pch.h"
#include "Game2.h"
#include <iostream>
#include <sstream>

using namespace std;

Game2::Game2(shared_ptr<ostream> os, const vector<string>& playerNames) 
	: m_CurrentPlayer(0)
	, m_Places()
	, m_Purses()
	, m_OutputStream(os)
{
	for (string playerName : playerNames)
	{
		Add(playerName);
	}

	for (int i = 0; i < 500; i++)
	{

		ostringstream oss (ostringstream::out);
		oss << "Pop Question " << i;

		m_PopQuestions.push_back(oss.str());

		char str[255];
		sprintf_s(str, "Science Question %d", i);
		m_ScienceQuestions.push_back(str);

		char str1[255];
		sprintf_s(str1, "Sports Question %d", i);
		m_SportsQuestions.push_back(str1);

		m_RockQuestions.push_back(CreateRockQuestion(i));
	}
}

string Game2::CreateRockQuestion(int index)
{
	char indexStr[127];
	sprintf_s(indexStr, "Rock Question %d", index);
	return indexStr;
}

bool Game2::IsPlayable()
{
	return (HowManyPlayers() >= 2);
}

bool Game2::Add(string playerName)
{
	m_Players.push_back(playerName);
	m_Places[HowManyPlayers()] = 0;
	m_Purses[HowManyPlayers()] = 0;
	m_InPenaltyBox[HowManyPlayers()] = false;

	*m_OutputStream << playerName << " was added" << endl;
	*m_OutputStream << "They are player number " << m_Players.size() << endl;
	return true;
}

int Game2::HowManyPlayers()
{
	return m_Players.size();
}

void Game2::Roll(int roll)
{
	*m_OutputStream << m_Players[m_CurrentPlayer] << " is the current player" << endl;
	*m_OutputStream << "They have rolled a " << roll << endl;

	if (m_InPenaltyBox[m_CurrentPlayer])
	{
		if (roll % 2 != 0)
		{
			m_IsGettingOutOfPenaltyBox = true;

			*m_OutputStream << m_Players[m_CurrentPlayer] << " is getting out of the penalty box" << endl;
			m_Places[m_CurrentPlayer] = m_Places[m_CurrentPlayer] + roll;
			if (m_Places[m_CurrentPlayer] > 11)
			{
				m_Places[m_CurrentPlayer] = m_Places[m_CurrentPlayer] - 12;
			}

			*m_OutputStream << m_Players[m_CurrentPlayer] << "'s new location is " << m_Places[m_CurrentPlayer] << endl;
			*m_OutputStream << "The category is " << CurrentCategory() << endl;
			AskQuestion();
		}
		else
		{
			*m_OutputStream << m_Players[m_CurrentPlayer] << " is not getting out of the penalty box" << endl;
			m_IsGettingOutOfPenaltyBox = false;
		}

	}
	else
	{

		m_Places[m_CurrentPlayer] = m_Places[m_CurrentPlayer] + roll;
		if (m_Places[m_CurrentPlayer] > 11)
		{
			m_Places[m_CurrentPlayer] = m_Places[m_CurrentPlayer] - 12;
		}

		*m_OutputStream << m_Players[m_CurrentPlayer] << "'s new location is " << m_Places[m_CurrentPlayer] << endl;
		*m_OutputStream << "The category is " << CurrentCategory() << endl;
		AskQuestion();
	}

}

void Game2::AskQuestion()
{
	if (CurrentCategory() == "Pop")
	{
		*m_OutputStream << m_PopQuestions.front() << endl;
		m_PopQuestions.pop_front();
	}
	if (CurrentCategory() == "Science")
	{
		*m_OutputStream << m_ScienceQuestions.front() << endl;
		m_ScienceQuestions.pop_front();
	}
	if (CurrentCategory() == "Sports")
	{
		*m_OutputStream << m_SportsQuestions.front() << endl;
		m_SportsQuestions.pop_front();
	}
	if (CurrentCategory() == "Rock")
	{
		*m_OutputStream << m_RockQuestions.front() << endl;
		m_RockQuestions.pop_front();
	}
}


string Game2::CurrentCategory()
{
	if (m_Places[m_CurrentPlayer] == 0) return "Pop";
	if (m_Places[m_CurrentPlayer] == 4) return "Pop";
	if (m_Places[m_CurrentPlayer] == 8) return "Pop";
	if (m_Places[m_CurrentPlayer] == 1) return "Science";
	if (m_Places[m_CurrentPlayer] == 5) return "Science";
	if (m_Places[m_CurrentPlayer] == 9) return "Science";
	if (m_Places[m_CurrentPlayer] == 2) return "Sports";
	if (m_Places[m_CurrentPlayer] == 6) return "Sports";
	if (m_Places[m_CurrentPlayer] == 10) return "Sports";
	return "Rock";
}

bool Game2::CorrectAnswer()
{
	if (m_InPenaltyBox[m_CurrentPlayer])
	{
		if (m_IsGettingOutOfPenaltyBox)
		{
			*m_OutputStream << "Answer was correct!!!!" << endl;
			m_Purses[m_CurrentPlayer]++;
			*m_OutputStream << m_Players[m_CurrentPlayer]
				<< " now has "
			    << m_Purses[m_CurrentPlayer]
				<<  " Gold Coins." << endl;

			bool winner = DidPlayerWin();
			m_CurrentPlayer++;
			if (m_CurrentPlayer == m_Players.size()) m_CurrentPlayer = 0;

			return winner;
		}
		else
		{
			m_CurrentPlayer++;
			if (m_CurrentPlayer == m_Players.size()) m_CurrentPlayer = 0;
			return true;
		}
	}
	else
	{

		*m_OutputStream << "Answer was corrent!!!!" << endl;
		m_Purses[m_CurrentPlayer]++;
		*m_OutputStream << m_Players[m_CurrentPlayer]
			<< " now has "
			<< m_Purses[m_CurrentPlayer]
			<< " Gold Coins." << endl;

		bool winner = DidPlayerWin();
		m_CurrentPlayer++;
		if (m_CurrentPlayer == m_Players.size())
		{
			m_CurrentPlayer = 0;
		}

		return winner;
	}
}

bool Game2::WrongAnswer()
{
	*m_OutputStream << "Question was incorrectly answered" << endl;
	*m_OutputStream << m_Players[m_CurrentPlayer] + " was sent to the penalty box" << endl;
	m_InPenaltyBox[m_CurrentPlayer] = true;

	m_CurrentPlayer++;
	if (m_CurrentPlayer == m_Players.size())
	{
		m_CurrentPlayer = 0;
	}
	return true;
}


bool Game2::DidPlayerWin()
{
	return !(m_Purses[m_CurrentPlayer] == 6);
}
