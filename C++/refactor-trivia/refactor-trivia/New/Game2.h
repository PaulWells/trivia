#include <iostream>
#include <list>
#include <vector>
#include "../Common/IGame.h"

class Game2 : public IGame {

public:
	Game2(std::shared_ptr<ostream> os, const std::vector<std::string>& playerNames);

	bool Add(std::string playerName);

	void Roll(int roll) override;
	bool CorrectAnswer() override;
	bool WrongAnswer() override;

private:
	void AskQuestion();
	std::string CurrentCategory();
	bool DidPlayerWin();
	int HowManyPlayers();
	bool IsPlayable();
	std::string CreateRockQuestion(int index);

	vector<std::string> m_Players;

	int m_Places[6];
	int m_Purses[6];
	bool m_InPenaltyBox[6];

	list<std::string> m_PopQuestions;
	list<std::string> m_ScienceQuestions;
	list<std::string> m_SportsQuestions;
	list<std::string> m_RockQuestions;

	int m_CurrentPlayer;
	bool m_IsGettingOutOfPenaltyBox;

	std::shared_ptr<std::ostream> m_OutputStream;
};
