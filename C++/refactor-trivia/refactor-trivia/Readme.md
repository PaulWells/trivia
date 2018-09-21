[] write tests
	Rewrite Option
	[x] Create Game2 folder
	[x] Make console printing interface injectable (and testable)
	[x] Make rand interface injectable (and testable)
	[x] Write test suit which uses specific seeds to make repeatable output from rand which can be compared to new implementation.
	   These tests cannot be relied upon to prove correctness because there is no guarantee that they cover every scenario. Instead,
	   they will be used as a sanity check and supplementary testing.
	[] Write test suite which tests specific scenarios. It will be painful to enumerate all of the possibilities
	   so we'll have to develop a reasonably sophisticated library with methods at the level of abstraction equal
	   to "CreateGameWithThreePlayers(); PutCurrentPlayerInPenaltyBox()" etc.




	   Other possibilities we ruled out:
	   - Specific scenario testing at GameRunner level. The GameRunner API takes no arguments so it would be difficult to test
	   - Injecting game state. This would make it easier to create game state but it would rely on 
	     implementation details of Game so that.

[] refactor
  [] both wrong answer and correct answer return whether a player has won. Wrong answer does not need to
  [] WrongAnswer and CorrectAnswer are called even if the player was not asked a question and is in the penalty box
     This is a poor API design. In reality the class should be rewritten but I will assume that I must stick with this interface.