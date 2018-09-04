#pragma once

class GameRunner2
{
public:
	GameRunner2(IGame* game);
	void Run();
private:
	std::unique_ptr<IGame> m_Game;
};