#include <iostream>
#include <list>
#include <vector>
#include "../Common/IGame.h"

using namespace std;

#ifndef GAME2_H_
#define GAME2_H_

class Game2 : public IGame{

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
	Game2(shared_ptr<ostream> os);
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
	bool didPlayerWin();
	shared_ptr<ostream> m_OutputStream;
};

#endif /* GAME2_H_ */
