#pragma once

class GameFactory
{
public:
	static IGame* CreateGame(
		GameVersion version,
		std::shared_ptr<std::ostream> os,
		int numPlayers);
};