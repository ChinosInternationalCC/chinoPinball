//
//  SoundManager.cpp
//  chinoPinball
//
//  Created by Angel Muñoz on 27/02/14.
//
//

#include "SoundManager.h"
#include "DMXManager.h"

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
    
    soundFiles.push_back("sounds/obstacle.wav");
    ofSoundPlayer *audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[0]->loadSound(soundFiles[0]);
    soundObj[0]->setVolume(0.5f);
    soundObj[0]->setMultiPlay(true);
    
    soundFiles.push_back("sounds/ball.mp3");
    audio  = new ofSoundPlayer();
    soundObj.push_back(audio);
    soundObj[1]->loadSound(soundFiles[1]);
    soundObj[1]->setVolume(0.5f);
    soundObj[1]->setMultiPlay(true);
}

//--------------------------------------
/*void SoundManager::AddPoints(int idAudio){
    //this->points += points;
}*/
//------------------------------------
void SoundManager::PlaySound(int idAudio){
    this->soundObj[idAudio]->play();
    DMXManager::getInstance()->flashChannel();
}
