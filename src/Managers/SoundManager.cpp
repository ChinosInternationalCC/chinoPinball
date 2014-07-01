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
 
	
	
	//EVENTS
	ofAddListener(eventGame::onGameEvent,this, &SoundManager::listenerOnHammerLaunch);

	
}

//--------------------------------------
/*void SoundManager::AddPoints(int idAudio){
    //this->points += points;
}*/
//------------------------------------
void SoundManager::PlaySound(int idAudio){
    this->soundObj[idAudio]->play();
}


//Listeners
//--------------------------------------------------------------------
void SoundManager::listenerOnHammerLaunch(eventGame & args){

	if(args.gameEvent == eventGame::GAME_EVENT_HAMMER_LAUNCH){
		soundObj[2]->play();
	}
	
}

