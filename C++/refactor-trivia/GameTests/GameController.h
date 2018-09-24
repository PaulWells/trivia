#pragma once
class GameController
{
public:
	GameController(IGame* game);

	

private:
	std::unique_ptr<IGame> m_Game;
};

