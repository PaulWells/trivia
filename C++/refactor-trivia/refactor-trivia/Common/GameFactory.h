#pragma once

class GameFactory
{
public:
	static IGame* CreateGame(
		GameVersion version,
		std::shared_ptr<std::ostream> os,
		int numPlayers);

	static IGame* CreateGame(
		GameVersion version,
		std::shared_ptr<std::ostream> os,
		const std::vector<std::string>& playerNames);
};