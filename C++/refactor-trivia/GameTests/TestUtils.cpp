#include "pch.h"
#include "TestUtils.h"


/*static*/ int TestUtils::GetNewBoardPosition(int startingPosition, int rollValue)
{
	return (startingPosition + rollValue) % BOARD_SIZE;
}