#include "pch.h"
#include "Original/GameRunner.h"
#include <iostream>
#include <sstream>
#include "Common/GameFactory.h"

int main()
{
	std::shared_ptr<std::stringstream> gameOutput = std::make_shared<std::stringstream>();
	std::unique_ptr<IGame> game(GameFactory::CreateGame(gameOutput, 3));
	GameRunner gameRunner(game.release());
	gameRunner.Run();
}