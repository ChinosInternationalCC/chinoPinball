//
//  Score.cpp
//  chinoPinball
//
//  Created by Ovidiu on 05/02/14.
//
//

#include "Score.h"
Score::Score(){
    idPlayer = 0;
    lastMission = 0;
    points = 0;
}
Score::Score(int idPlayer, int numMissionsCompleted, int points){
    this->idPlayer = idPlayer;
    this->lastMission = numMissionsCompleted;
    this->points = points;
}