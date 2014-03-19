//
//  Score.h
//  chinoPinball
//
//  Created by Ovidiu on 05/02/14.
//
//

#ifndef __chinoPinball__Score__
#define __chinoPinball__Score__

class Score{
public:
    Score();
    Score(int idPlayer, int lastMission, int points);
    int idPlayer, lastMission, points;
};

#endif /* defined(__chinoPinball__Score__) */
