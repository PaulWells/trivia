#include "pch.h"
#include <vector>
#include "CppUnitTest.h"
#include "../refactor-trivia/Common/IGame.h"
#include "../refactor-trivia/Common/GameFactory.h"
#include "GameOutputParser.h"
#include "ExpectedOutputGenerator.h"
#include "OutputComparer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{		
	vector<string> s_DefaultPlayerNames{ "Aileen", "Paul" };

	TEST_CLASS(GameVersionCompatibilityTests)
	{
	public:
		
		TEST_METHOD(Game1_Constructor_DisplaysPlayerNamesAndPositions)
		{
			Constructor_DisplaysPlayerNamesAndPositions(GameVersion::One);
		}

		TEST_METHOD(Game2_Constructor_DisplaysPlayerNamesAndPositions)
		{
			Constructor_DisplaysPlayerNamesAndPositions(GameVersion::Two);
		}

		static void Constructor_DisplaysPlayerNamesAndPositions(GameVersion version)
		{
			shared_ptr<stringstream> gameOutput = make_shared<stringstream>();
			unique_ptr<IGame> game(GameFactory::CreateGame(version, gameOutput, s_DefaultPlayerNames));

			vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateCreationOutput(s_DefaultPlayerNames);

			OutputComparer::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(Game1_Roll_WhenNotInPenaltyBox)
		{
			Roll_WhenNotInPenaltyBox(GameVersion::One);
		}

		TEST_METHOD(Game2_Roll_WhenNotInPenaltyBox)
		{
			Roll_WhenNotInPenaltyBox(GameVersion::Two);
		}

		static void Roll_WhenNotInPenaltyBox(GameVersion version)
		{
			shared_ptr<stringstream> gameOutput = make_shared<stringstream>();
			unique_ptr<IGame> game(GameFactory::CreateGame(version, gameOutput, s_DefaultPlayerNames));

			gameOutput->str("");

			int rollValue = 1;
			int startingLocation = 0;
			string currentPlayerName = s_DefaultPlayerNames[0];

			game->Roll(rollValue);
			vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(currentPlayerName, startingLocation, rollValue);

			OutputComparer::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(Game1_Roll_WhenNotInPenaltyBox_WrapAroundBoard)
		{
			Roll_WhenNotInPenaltyBox_WrapAroundBoard(GameVersion::One);
		}

		TEST_METHOD(Game2_Roll_WhenNotInPenaltyBox_WrapAroundBoard)
		{
			Roll_WhenNotInPenaltyBox_WrapAroundBoard(GameVersion::Two);
		}

		static void Roll_WhenNotInPenaltyBox_WrapAroundBoard(GameVersion version)
		{
			shared_ptr<stringstream> gameOutput = make_shared<stringstream>();
			unique_ptr<IGame> game(GameFactory::CreateGame(version, gameOutput, s_DefaultPlayerNames));

			int rollValue = 6;

			// Move Player 1 forward 6 spaces.
			game->Roll(rollValue);
			game->CorrectAnswer();

			// Do Player 2's turn.
			game->Roll(rollValue);
			game->CorrectAnswer();
			gameOutput->str("");

			// Move Player 1 back to the starting square.
			game->Roll(rollValue);

			int startingLocation = 6;
			string currentPlayerName = s_DefaultPlayerNames[0];
			vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(currentPlayerName, startingLocation, rollValue);

			OutputComparer::AreEqual(expectedOutput, actualOutput);
		}

	};
}