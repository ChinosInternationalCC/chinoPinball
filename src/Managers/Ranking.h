#pragma once

class Ranking{
public:
	Ranking(void);
	void saveXmlScore(int gameNumber, int numMissionsCompleted, int score);
	void loadXmlRanking();
	int bestPlayer;
	int bestScore;
	int bestNumMissionsCompleted;
};