#include "pch.h"
#include <string>
#include <memory>
#include "IGame.h"
#include <vector>
#include "GameFactory.h"
#include "../Original/Game.h"
#include "../New/Game2.h"

using namespace std;

static const vector<string> s_DefaultPlayerNames = {
	"Chet",
	"Pat",
	"Sue",
	"Paul",
	"Aileen",
	"Keara",
};

static IGame* CreateGameVersionOne(shared_ptr<ostream> os, const vector<string>& playerNames, const int numPlayers)
{
	Game* game = new Game(os);
	for (int i = 0; i < numPlayers; i++)
	{
		game->Add(playerNames[i]);
	}
	return game;
}

static IGame* CreateGameVersionTwo(shared_ptr<ostream> os, const vector<string>& playerNamesList, const int numPlayers)
{
	std::vector<string> playerNames;
	for (int i = 0; i < numPlayers; i++)
	{
		playerNames.push_back(playerNamesList[i]);
	}
	return new Game2(os, playerNames);
}

static IGame* CreateGameInternal(GameVersion version, shared_ptr<ostream> os, const vector<string>& playerNamesList, const int numPlayers)
{
	switch (version)
	{
	case GameVersion::One:
	{
		return CreateGameVersionOne(os, playerNamesList, numPlayers);
	}
	case GameVersion::Two:
	{
		return CreateGameVersionTwo(os, playerNamesList, numPlayers);
	}
	default:
		throw std::invalid_argument("Invalid GameVersion");
	}
}

/*static*/ IGame* GameFactory::CreateGame(GameVersion version, shared_ptr<ostream> os, const int numPlayers)
{
	return CreateGameInternal(version, os, s_DefaultPlayerNames, numPlayers);
}

/*static*/ IGame* GameFactory::CreateGame(GameVersion version, shared_ptr<ostream> os, const vector<string>& playerNames)
{
	return CreateGameInternal(version, os, playerNames, playerNames.size());
}