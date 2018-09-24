#include "pch.h"
#include <memory>
#include "..\refactor-trivia\Common\IGame.h"
#include "GameController.h"


GameController::GameController(IGame* game)
{
	m_Game = game;
}

void GameController::SkipTurns(int numTurns)
{
	for (int i = 0; i < numTurns; i++)
	{
		// By rolling an odd number and answering the question wrong
		// The current player will be put in the penalty box and stay there.
		// This way they have no effect on the other players' games besides answering
		// one question wrong.
		m_Game->Roll(1);
		m_Game->WrongAnswer();
	}
}

void GameController::MovePlayerForward(int numSpaces)
{
	m_Game->Roll(numSpaces);
	m_Game->CorrectAnswer();
}