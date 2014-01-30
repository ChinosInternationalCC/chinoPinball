#include "GameStatus.h"

// SINGLETON initalizations
bool GameStatus::instanceFlag = false;
GameStatus* GameStatus::single = NULL;


GameStatus::GameStatus(void){
}


GameStatus* GameStatus::getInstance(void){
	if(! instanceFlag)
		{
			single = new GameStatus();
			instanceFlag = true;
			return single;
		}else{
			return single;
		}
}

void GameStatus::saveRanking(void){
}

void GameStatus::StartMission(){
}

void GameStatus::EndMission(){
}

void GameStatus::AddPoints(int points){
    score += points;
}

void GameStatus::GetLife(){
    lives -= 1;
}
