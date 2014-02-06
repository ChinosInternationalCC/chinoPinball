#pragma once
#include "Score.h"
#include "ofxXmlSettings.h"

class Ranking: public ofxXmlSettings
{
public:
	Ranking(void);
	void saveXmlScore(Score score);
	void loadXmlRanking();
    Score getMaxScore(void);
private:
    int numberOfSavedPoints;
    vector<Score> rank;
                   
                   
};