//
//  SoundManager.cpp
//  chinoPinball
//
//  Created by Angel Muñoz on 27/02/14.
//
//

#include "SoundManager.h"

// SINGLETON initalizations
bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::single = NULL;


//--------------------------------------
SoundManager* SoundManager::getInstance(void){
	if(! instanceFlag)
	{
		single = new SoundManager();
		instanceFlag = true;
		return single;
	}else{
		return single;
	}
}

//--------------------------------------
SoundManager::SoundManager(void){
	//loadSounds
    
    soundFiles.push_back("sounds/campanaraval.wav");
    ofSoundPlayer *audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[0]->loadSound(soundFiles[0]);
    soundObj[0]->setVolume(0.5f);
    soundObj[0]->setMultiPlay(false);
    
    soundFiles.push_back("sounds/ball.mp3");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[1]->loadSound(soundFiles[1]);
    soundObj[1]->setVolume(0.5f);
    soundObj[1]->setMultiPlay(false);


	soundFiles.push_back("sounds/bengalalanzabola.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[2]->loadSound(soundFiles[2]);
    soundObj[2]->setVolume(0.5f);
    soundObj[2]->setMultiPlay(false);
 
	soundFiles.push_back("sounds/bumper02.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[3]->loadSound(soundFiles[3]);
    soundObj[3]->setVolume(0.5f);
    soundObj[3]->setMultiPlay(false);

	soundFiles.push_back("sounds/chinospinballsong02.mp3");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[4]->loadSound(soundFiles[4]);
    soundObj[4]->setVolume(0.5f);
    soundObj[4]->setMultiPlay(false);
	

	soundFiles.push_back("sounds/bumper01.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[5]->loadSound(soundFiles[5]);
    soundObj[5]->setVolume(0.5f);
    soundObj[5]->setMultiPlay(false);
	
	soundFiles.push_back("sounds/paletas.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[6]->loadSound(soundFiles[6]);
    soundObj[6]->setVolume(0.5f);
    soundObj[6]->setMultiPlay(false);

	soundFiles.push_back("sounds/pierde.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[7]->loadSound(soundFiles[7]);
    soundObj[7]->setVolume(0.5f);
    soundObj[7]->setMultiPlay(false);

	/*
	soundFiles.push_back("sounds/vocesraval01.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[8]->loadSound(soundFiles[8]);
    soundObj[8]->setVolume(0.5f);
    soundObj[8]->setMultiPlay(false);
	
	soundFiles.push_back("sounds/vocesraval02.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[9]->loadSound(soundFiles[9]);
    soundObj[9]->setVolume(0.5f);
    soundObj[9]->setMultiPlay(false);
	
	soundFiles.push_back("sounds/vocesraval03.wav");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[10]->loadSound(soundFiles[10]);
    soundObj[10]->setVolume(0.5f);
    soundObj[10]->setMultiPlay(false);

	soundFiles.push_back("sounds/chinospinballsong03.mp3");
	audio  = new ofSoundPlayer();
	soundObj.push_back(audio);
	soundObj[11]->loadSound(soundFiles[11]);
	soundObj[11]->setVolume(0.5f);
	soundObj[11]->setMultiPlay(false);
	 */
	
			 //EVENTS
	ofAddListener(eventGame::onGameEvent,this, &SoundManager::listenerOnHammerLaunch);
	
	ofAddListener(eventComunication::onNewCom,this, &SoundManager::listenerOnCollission);
    ofAddListener(eventMission::onMissionUpdate,this, &SoundManager::listenerOnUpdateMission);
	
	bMute = false;
	
}

//--------------------------------------
/*void SoundManager::AddPoints(int idAudio){
    //this->points += points;
}*/
//------------------------------------
void SoundManager::PlaySound(int idAudio){
	if (!bMute)
		this->soundObj[idAudio]->play();
}


//Listeners
//--------------------------------------------------------------------
void SoundManager::listenerOnHammerLaunch(eventGame & args){

	if(args.gameEvent == eventGame::GAME_EVENT_HAMMER_LAUNCH){
		if (!bMute)
			soundObj[launchBall]->play();
	}
	
}

//--------------------------------------------------------------------
void SoundManager::listenerOnCollission(eventComunication & args){
	
	if (!bMute){
		if(args.collision){
			
			if(args.pObject->idobject == 5){//DHUB HACK SOUND OBJECTS ID MANUALLLLL
				soundObj[ObjCol1]->play();
			}
			
	/*		else if(args.pObject->idobject == 8){//DHUB HACK SOUND OBJECTS ID MANUALLLLL
				soundObj[ObjCol1]->play();
			}
			else if(args.pObject->idobject == 9){//DHUB HACK SOUND OBJECTS ID MANUALLLLL
				soundObj[ObjCol1]->play();
			}
			else if(args.pObject->idobject == 10){//DHUB HACK SOUND OBJECTS ID MANUALLLLL
				soundObj[ObjCol1]->play();
			}
	*/
			
			soundObj[ObjCol1]->play();
		}

	}
}

void SoundManager::Mute(bool flag){
	bMute = flag;
}

void SoundManager::TogleMute(){
	bMute = !bMute;
	
}

//--------------------------------------------------------------------
void SoundManager::listenerOnUpdateMission(eventMission & args){
    
	switch(args.eventType){
        case eventMission::MISSION_EVENT_START_MISSION:
            
            if (NULL != args.pMission){
			}
			if (!bMute)
				soundObj[songGeneralGame]->play();
            
            break;
        case eventMission::MISSION_EVENT_END_MISSION:
 
            if (NULL != args.pMission){
            }
            break;
        case eventMission::MISSION_EVENT_MISSION_COMPLETED:
            
			
			
            break;
        case eventMission::MISSION_EVENT_START_CALIFICATION:
            
            break;
        case eventMission::MISSION_EVENT_RESTART_MISSION:
            soundObj[songGeneralGame]->stop();
            break;
        case eventMission::MISSION_EVENT_NEW_MISSION:

            break;
    }
	
}

