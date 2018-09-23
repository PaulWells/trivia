#pragma once
#include <string>

using namespace std;

enum class GameVersion
{
	One,
	Two
};

class IGame
{
public:
	virtual void Roll(int roll) = 0;
	virtual bool CorrectAnswer() = 0;
	virtual bool WrongAnswer() = 0;
};