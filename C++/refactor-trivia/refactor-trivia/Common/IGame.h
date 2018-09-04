#pragma once
#include <string>

using namespace std;

class IGame
{
public:
	virtual string createRockQuestion(int index) = 0;
	virtual bool isPlayable() = 0;
	virtual bool add(string playerName) = 0;

	virtual int howManyPlayers() = 0;
	virtual void roll(int roll) = 0;
	virtual bool wasCorrectlyAnswered() = 0;
	virtual bool wrongAnswer() = 0;
};