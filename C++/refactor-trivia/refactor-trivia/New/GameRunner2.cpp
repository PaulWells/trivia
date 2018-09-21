#include "pch.h"
#include <string>
#include "Game2.h"
#include "GameRunner2.h"

static bool notAWinner;

GameRunner2::GameRunner2(IGame* game)
{
	m_Game = std::unique_ptr<IGame>(game);
}

void GameRunner2::Run()
{
	do
	{
		m_Game->Roll(rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			notAWinner = m_Game->WrongAnswer();
		}
		else
		{
			notAWinner = m_Game->CorrectAnswer();
		}
	} while (notAWinner);

}
