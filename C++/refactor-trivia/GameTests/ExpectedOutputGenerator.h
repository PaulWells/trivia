#pragma once
class ExpectedOutputGenerator
{
public:
	static std::vector<std::string> GenerateConstructorOutput(std::vector<std::string> playerNames);
	static std::vector<std::string> GenerateRollWhenNotInPenaltyBox(std::string playerName, int startingLocation, int rollValue, int instanceOfQuestion);

private:
	static std::string GetCategory(int boardPosition);
};

