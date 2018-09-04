#include "pch.h"
#include "CppUnitTest.h"
#include "Original/GameRunner.h"
#include "Original/Game.h"
#include "New/GameRunner2.h"
#include "New/Game2.h"
#include "Common/IGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AcceptanceTests
{		
	static std::vector<string> s_PlayerNames = {
		"Chet",
		"Pat",
		"Sue",
		"Paul",
		"Aileen",
		"Keara",
	};

	TEST_CLASS(GameRunnerAcceptanceTests)
	{
	public:

		static const int MAX_NUMBER_OF_PLAYERS = 6;
		static const int MIN_NUMBER_OF_PLAYERS = 2;

		TEST_METHOD(OutputOfOriginalAndRefactoredGamesAreEqual)
		{
			for (int i = 0; i < 1000; i++)
			{
				int seed = i;
				CompareOutputForOneRandomGame(seed);
			}
		}

		static void CompareOutputForOneRandomGame(int seed)
		{
			int numPlayers = GenerateNumberOfPlayers(seed);

			// Initialize the random number generator which is used to simulate
			// die rolls in the game so that that it will generate the same 
			// sequence of numbers each test run.
			srand(seed);

			string originalConsoleOutput = RunOneGame<Game>(numPlayers);

			// Reinitialize the random number generator so that the second test run
			// uses the same sequence as the first as the first.
			srand(seed);

			string newConsoleOutput = RunOneGame<Game2>(numPlayers);

			Assert::AreEqual(originalConsoleOutput, newConsoleOutput);
		}

		static int GenerateNumberOfPlayers(int seed)
		{
			// The number of players is deterministically calculated from the seed
			// so that we get good coverage with each possible number of players
			// but every time the test is run the output will be the same. e.g. When
			// the seed is 10 there will always be 4 players.
			return (seed % (MAX_NUMBER_OF_PLAYERS - MIN_NUMBER_OF_PLAYERS)) + MIN_NUMBER_OF_PLAYERS;
		}

		template<typename T>
		static string RunOneGame(int numPlayers)
		{
			std::shared_ptr<std::stringstream> gameOutput = make_shared<std::stringstream>();
			std::unique_ptr<IGame> game = std::make_unique<T>(gameOutput);
			AddPlayers(game.get(), numPlayers);

			GameRunner gameRunner(game.release());
			gameRunner.Run();

			return gameOutput->str();
		}

		static void AddPlayers(IGame* game, int numPlayers)
		{
			for (int i = 0; i < numPlayers; i++)
			{
				game->Add(s_PlayerNames[i]);
			}
		}
	};
}