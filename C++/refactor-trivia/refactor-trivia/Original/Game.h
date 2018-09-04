#include <iostream>
#include <list>
#include <vector>
#include "../Common/IGame.h"

using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game : public IGame{

		private:
			vector<string> players;

			int places[6];
			int purses[6];

			bool inPenaltyBox[6];

			list<string> popQuestions;
			list<string> scienceQuestions;
			list<string> sportsQuestions;
			list<string> rockQuestions;

			int currentPlayer;
			bool isGettingOutOfPenaltyBox;

public:
	Game(std::shared_ptr<std::ostream> os);
	string CreateRockQuestion(int index);
	bool IsPlayable();
	bool Add(string playerName);

	int HowManyPlayers();
	void Roll(int roll);

	private:
		void askQuestion();
		string currentCategory();

				public:
					bool WasCorrectlyAnswered();
					bool WrongAnswer();

private:
	shared_ptr<ostream> m_OutputStream;
	bool didPlayerWin();
};

#endif /* GAME_H_ */
