#include "pch.h"
#include <vector>
#include "CppUnitTest.h"
#include "../refactor-trivia/Common/IGame.h"
#include "../refactor-trivia/Common/GameFactory.h"
#include "GameOutputParser.h"
#include "ExpectedOutputGenerator.h"
#include "OutputComparer.h"
#include "GameController.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{		
	vector<string> s_DefaultPlayerNames{ "Aileen", "Paul" };

	TEST_CLASS(GameVersionCompatibilityTests)
	{
	public:

		static void ClearGameOutput(shared_ptr<stringstream> gameOutput)
		{
			gameOutput->str("");
		}
		
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
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateConstructorOutput(s_DefaultPlayerNames);

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
			ClearGameOutput(gameOutput);

			int rollValue = 1;
			int startingLocation = 0;
			string currentPlayerName = s_DefaultPlayerNames[0];

			game->Roll(rollValue);
			vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(currentPlayerName, startingLocation, rollValue, 0);

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

			GameController gameController(game.get());
			gameController.MovePlayerForward(rollValue);
			gameController.SkipTurns(s_DefaultPlayerNames.size() - 1);

			ClearGameOutput(gameOutput);

			// Move Player 1 back to the starting square.
			game->Roll(rollValue);
			vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());

			int startingLocation = rollValue;
			string currentPlayerName = s_DefaultPlayerNames[0];
			vector<string> expectedOutput = ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(currentPlayerName, startingLocation, rollValue, 0);

			OutputComparer::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(Game1_Roll_VerifyPopSquarePositions)
		{
			Roll_VerifyPopSquarePositions(GameVersion::One);
		}

		TEST_METHOD(Game2_Roll_VerifyPopSquarePositions)
		{
			Roll_VerifyPopSquarePositions(GameVersion::Two);
		}

		static void Roll_VerifyPopSquarePositions(GameVersion version)
		{
			shared_ptr<stringstream> gameOutput = make_shared<stringstream>();
			unique_ptr<IGame> game(GameFactory::CreateGame(version, gameOutput, s_DefaultPlayerNames));

			GameController gameController(game.get());
			ClearGameOutput(gameOutput);

			Assert::IsTrue(TestUtils::BOARD_SIZE % TestUtils::NUM_CATEGORIES == 0, L"This test was written under the assumption that there is an equal number of spaces for each category");

			int rollValue = TestUtils::NUM_CATEGORIES;
			int startingPosition = 0;
			for (int i = 0; i < TestUtils::BOARD_SIZE / TestUtils::NUM_CATEGORIES; i++)
			{
				gameController.MovePlayerForward(rollValue);

				string currentPlayerName = s_DefaultPlayerNames[0];
				int instanceOfQuestion = i;
				vector<string> actualOutput = GameOutputParser::ParseLines(gameOutput->str());
				vector<string> expectedOutput = ExpectedOutputGenerator::GenerateRollWhenNotInPenaltyBox(currentPlayerName, startingPosition, rollValue, instanceOfQuestion);
				OutputComparer::ActualStartsWith(expectedOutput, actualOutput);
				startingPosition = TestUtils::GetNewBoardPosition(startingPosition, rollValue);

				gameController.SkipTurns(1);
				ClearGameOutput(gameOutput);
			}
		}
	};
}