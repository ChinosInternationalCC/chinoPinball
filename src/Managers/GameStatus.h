//GameStatus (singletoon class)
// reference about singleton design pattern “Chapter 6. Implementing Singletons” from Modern C++ Design by Andrei Alexanrescu

//Description:
//Manages the game score, players, levels, todo

//Vars:
#pragma once

#include "ofMain.h"
#include "Ranking.h"

class GameStatus{
public:
	GameStatus();
	static GameStatus* getInstance(void);
	void saveRanking(void);
	void StartMission();
	void EndMission();
	void AddPoints(int points);
	void GetLife();//the player looses one life

	

private:
	// singleton stuff
	static bool    instanceFlag;
    static GameStatus *single;  

	int idPlayer;
	int score;
	int lives;
	int currentMission;
	enum gamestatus {waintingStart, playing, gameOver};
	Ranking myRanking;
	bool missionsCompleted;

	enum enScoreConstants{
		NO_OF_LIVES = 3,
		NO_OF_MISSIONS =1
	};


};

/*

/ HOW TO USE THIS CLASS IN my code? ?


(,h)

#include "GameStatus.h"

(.cpp)
GameStatus::getInstance()->AddPoints(1);

*/