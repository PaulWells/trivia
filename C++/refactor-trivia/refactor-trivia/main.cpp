#include "pch.h"
#include "Original/GameRunner.h"
#include <iostream>
#include <sstream>

static std::vector<string> PlayerNames = {
	"Chet",
	"Pat",
	"Sue",
	"Paul",
	"Aileen",
	"Keara",
};

static void AddPlayers(IGame* game, int numPlayers)
{
	for (int i = 0; i < numPlayers; i++)
	{
		game->Add(PlayerNames[i]);
	}
}

int main()
{
	std::shared_ptr<std::stringstream> gameOutput = std::make_shared<std::stringstream>();
	std::unique_ptr<IGame> game = make_unique<Game>(gameOutput);
	AddPlayers(game.get(), 3);
	GameRunner gameRunner(game.release());
	gameRunner.Run();
}