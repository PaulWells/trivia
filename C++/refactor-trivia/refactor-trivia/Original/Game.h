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
	string createRockQuestion(int index);
	bool isPlayable();
	bool add(string playerName);

	int howManyPlayers();
	void roll(int roll);

	private:
		void askQuestion();
		string currentCategory();

				public:
					bool wasCorrectlyAnswered();
					bool wrongAnswer();

private:
	shared_ptr<ostream> m_OutputStream;
	bool didPlayerWin();
};

#endif /* GAME_H_ */
