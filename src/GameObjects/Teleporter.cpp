//
//  Teleporter.cpp
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#include "Teleporter.h"
#include "Ball.h"
#include "Scenario.h"

Teleporter::Teleporter(vector <SimpleMission *> * _currentMissions)
: Obstacle(_currentMissions){
    m_poDestinationObject = NULL;
	m_iBallStuckCount = 0;
}

void Teleporter::setupSpecific(){
    type = ShapeTypeTeleporter;
}

void Teleporter::updateSpecific(bool bEditorMode){
    //TODO
}

string Teleporter::getObjectName(){
    return "Teleporter";
}

void Teleporter::onCollisionSpecific(int ObjId){
    //TODO move the ball to the destination point m_poDestinationObject
	//if the sticky flag is active the ball should remain stuck
	vector <Ball *> balls;
	balls = m_poScenario->getBalls();
	
	//TODO find the ball that collisioned, for the moment stuck the first ball
	Ball *pMyBall = balls[0];
	
	cout << ObjId << endl;
	
    if (bSticky){
		pMyBall->stop(true);
		m_iBallStuckCount ++;
    }
	else{
		SetDestinationObject(m_poScenario->FindScenarioObjectById(m_iDestinationObjectId));
	
		pMyBall->setPosition(m_poDestinationObject->getPosition());
		pMyBall->reset();
	}
}

void Teleporter::ReleaseBall(){
    if (m_iBallStuckCount > 0){
		m_iBallStuckCount = 0;
        //TODO release the Ball
		
		vector <Ball *> balls;
		balls = m_poScenario->getBalls();
		
		//TODO find the ball that collisioned, for the moment stuck the first ball
		Ball *pMyBall = balls[0];
		pMyBall->stop(false);

    }
}

void Teleporter::SetDestinationObject(SimpleObject *object){
    m_poDestinationObject = object;
}

void Teleporter::SetMultiBallStickyFlag(bool bFlag){
    bSticky = bFlag;
    if (bFlag){
        m_poDestinationObject = this;
    }
}

bool Teleporter::GetMultiBallStickyFlag(void){
    return bSticky;
}

bool Teleporter::IsBallStuck(){
	return (m_iBallStuckCount > 0)? true : false;
}

void Teleporter::RegisterScenarioRef(Scenario *pScenario){
	m_poScenario = pScenario;
}

void Teleporter::SetDetinationObjectId(int id){
	m_iDestinationObjectId = id;
}
