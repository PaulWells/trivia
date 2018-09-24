#pragma once
class ExpectedOutputGenerator
{
public:
	static std::vector<std::string> GenerateCreationOutput(std::vector<std::string> playerNames);
	static std::vector<std::string> GenerateRollWhenNotInPenaltyBox(std::string playerName, int startingLocation, int rollValue);

private:
	static int GetNewBoardPosition(int startingPosition, int rollValue);
	static std::string GetCategory(int boardPosition);
};

