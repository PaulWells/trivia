#include "pch.h"
#include <string>
#include <memory>
#include "IGame.h"
#include "GameFactory.h"
#include "../Original/Game.h"
#include "../New/Game2.h"

using namespace std;

static vector<string> s_PlayerNames = {
	"Chet",
	"Pat",
	"Sue",
	"Paul",
	"Aileen",
	"Keara",
};

/*static*/ IGame* GameFactory::CreateGame(shared_ptr<ostream> os, const int numPlayers)
{
	Game* game = new Game(os);
	for (int i = 0; i < numPlayers; i++)
	{
		game->Add(s_PlayerNames[i]);
	}
	return game;
}

/*static*/ IGame* GameFactory::CreateGame2(shared_ptr<ostream> os, const int numPlayers)
{
	std::vector<string> playerNames;
	for (int i = 0; i < numPlayers; i++)
	{
		playerNames.push_back(s_PlayerNames[i]);
	}
	return new Game2(os, playerNames);
}