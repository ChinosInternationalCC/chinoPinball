//GameStatus (singletoon class)
// reference about singleton design pattern “Chapter 6. Implementing Singletons” from Modern C++ Design by Andrei Alexanrescu

//Description:
//Manages the game score, players, levels, todo

//Vars:
#pragma once

#include "ofMain.h"
#include "Ranking.h"
#include "Score.h"



class GameStatus: public Score{
public:
	GameStatus();
	static GameStatus* getInstance(void);
	void saveRanking(void);
	bool StartMission();
	void EndMission();
	void AddPoints(int points);
	void NewPlayer(void);
    bool Play(void);
	bool Death();//the player looses one life

	int GetRemainingLifes(void);
	int GetRemainingMissions(void);
	int GetPlayerId(void);
    int GetCurrentPlayerScore(void);
    
    Score getBestScore(void);
    
    
    
    enum enGameStatus{
        WAITING_NEW_PLAYER = 0,
        SETTING_UP_THE_GAME,
        WAITING_START_PLAY,
        PLAYING,
        DEAD
    };
    
    enGameStatus GetGameStatus(void);

private:
	// singleton stuff
	static bool    instanceFlag;
    static GameStatus *single;  

	int lives;
	enum gamestatus {waintingStart, playing, gameOver};
	Ranking myRanking;
	bool missionsCompleted;

	enum enScoreConstants{
		NO_OF_LIVES = 3,
		NO_OF_MISSIONS =1
	};
    

    
    enGameStatus status;

};

/*

/ HOW TO USE THIS CLASS IN my code? ?


(.h)

#include "GameStatus.h"

(.cpp)
GameStatus::getInstance()->AddPoints(1);

*/
