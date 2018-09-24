#pragma once
class GameController
{
public:
	GameController(IGame* game);
	void SkipTurns(int numTurns);
	void MovePlayerForward(int numSpaces);
private:
	// Game object is owned by the test
	IGame* m_Game;
};

