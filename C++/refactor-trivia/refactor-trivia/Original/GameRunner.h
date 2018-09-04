#pragma once
#include "Game.h"

class GameRunner
{
public:
	explicit GameRunner(IGame* game);
	void Run();
private:
	std::unique_ptr<IGame> m_Game;
};