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

static IGame* CreateGameVersionOne(shared_ptr<ostream> os, const int numPlayers)
{
	Game* game = new Game(os);
	for (int i = 0; i < numPlayers; i++)
	{
		game->Add(s_PlayerNames[i]);
	}
	return game;
}

static IGame* CreateGameVersionTwo(shared_ptr<ostream> os, const int numPlayers)
{
	std::vector<string> playerNames;
	for (int i = 0; i < numPlayers; i++)
	{
		playerNames.push_back(s_PlayerNames[i]);
	}
	return new Game2(os, playerNames);
}

/*static*/ IGame* GameFactory::CreateGame(GameVersion version, shared_ptr<ostream> os, const int numPlayers)
{
	switch (version)
	{
		case GameVersion::One:
		{
			return CreateGameVersionOne(os, numPlayers);
		}
		case GameVersion::Two:
		{
			return CreateGameVersionTwo(os, numPlayers);
		}
		default:
			throw std::invalid_argument("Invalid GameVersion");
	}
}