#include "pch.h"
#include <string>
#include <vector>
#include "GameOutputParser.h"

using namespace std;

const string LineDelimeter = "\n";

vector<string> GameOutputParser::ParseLines(std::string gameOutput)
{
	std::vector<string> lines;
	int previousPosition = 0;
	int currentPosition = gameOutput.find(LineDelimeter);
	while (currentPosition != string::npos)
	{
		lines.push_back(gameOutput.substr(previousPosition, currentPosition - previousPosition));

		// Skip past delimeter.
		previousPosition = currentPosition + 1;

		currentPosition = gameOutput.find(LineDelimeter, previousPosition);
	}
	return lines;
}
