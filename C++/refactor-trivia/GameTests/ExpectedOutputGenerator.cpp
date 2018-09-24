#include "pch.h"
#include <string>
#include <vector>
#include "ExpectedOutputGenerator.h"

using namespace std;

static const int BOARD_SIZE = 12;

static const std::vector<string> s_Categories = {
	"Pop", "Science", "Sports", "Rock"
};

/*static*/ vector<string> ExpectedOutputGenerator::GenerateCreationOutput(vector<string> playerNames)
{
	vector<string> lines;
	for (unsigned int i = 0; i < playerNames.size(); i++)
	{
		lines.emplace_back(playerNames[i] + " was added");
		lines.emplace_back("They are player number " + std::to_string(i + 1));
	}
	return lines;
}

/*static*/ vector<string> ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(string playerName, int startingPosition, int rollValue)
{
	int newBoardPosition = GetNewBoardPosition(startingPosition, rollValue);
	string category = GetCategory(newBoardPosition);

	vector<string> lines;
	lines.emplace_back(playerName + " is the current player");
	lines.emplace_back("They have rolled a " + std::to_string(rollValue));
	lines.emplace_back(playerName + "'s new location is " + std::to_string(newBoardPosition));
	lines.emplace_back("The category is " + category);
	lines.emplace_back(category + " Question 0");
	return lines;
}

/*static*/ int ExpectedOutputGenerator::GetNewBoardPosition(int startingPosition, int rollValue)
{
	return (startingPosition + rollValue) % BOARD_SIZE;
}

/*static*/ string ExpectedOutputGenerator::GetCategory(int boardPosition)
{
	// Categories are placed on the board in a sequential, repeating pattern.
	// e.g. [Pop][Science][Sports][Rock][Pop][Science][Sports][Rock]
	int categoryNumber = boardPosition % s_Categories.size();
	return s_Categories[categoryNumber];
}