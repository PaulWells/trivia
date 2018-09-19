#pragma once
#include <string>

using namespace std;

class IGame
{
public:
	virtual void Roll(int roll) = 0;
	virtual bool WasCorrectlyAnswered() = 0;
	virtual bool WrongAnswer() = 0;
};