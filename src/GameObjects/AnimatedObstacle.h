//
//  AnimatedObstacle.h
//  chinoPinball
//
//  Created by Ovidiu on 20/7/15.
//
//

#pragma once
#include "Obstacle.h"

class AnimatedObstacle : public Obstacle{
public:
    AnimatedObstacle(vector <SimpleMission *> * _currentMissions);
    void setupSpecific();
    void updateSpecific(bool bEditorMode);
    string getObjectName();
    void onCollisionSpecific(SimpleObject* Obj);
	bool drawAssimpModelSpecific();

private:
    float m_animPos;
};
