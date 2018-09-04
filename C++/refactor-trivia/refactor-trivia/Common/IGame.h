#pragma once
#include <string>

using namespace std;

class IGame
{
public:
	virtual string CreateRockQuestion(int index) = 0;
	virtual bool IsPlayable() = 0;
	virtual bool Add(string playerName) = 0;

	virtual int HowManyPlayers() = 0;
	virtual void Roll(int roll) = 0;
	virtual bool WasCorrectlyAnswered() = 0;
	virtual bool WrongAnswer() = 0;
};