#pragma once
#include "Score.h"

class Ranking: public Score{
public:
	Ranking(void);
	void saveXmlScore(Score score);
	void loadXmlRanking();

};