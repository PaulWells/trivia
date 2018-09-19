#pragma once

class GameFactory
{
public:
	static IGame* CreateGame(
		std::shared_ptr<std::ostream> os,
		int numPlayers);

	static IGame* CreateGame2(
		std::shared_ptr<std::ostream> os,
		int numPlayers);
};