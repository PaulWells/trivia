#include "pch.h"
#include <string>
#include <memory>
#include "Game.h"
#include "GameRunner.h"

using namespace std;

static bool notAWinner;

GameRunner::GameRunner(IGame* game)
{
	m_Game = std::unique_ptr<IGame>(game);
}

void GameRunner::Run()
{
	do
	{

		m_Game->roll(rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			notAWinner = m_Game->wrongAnswer();
		}
		else
		{
			notAWinner = m_Game->wasCorrectlyAnswered();
		}
	} while (notAWinner);

}
