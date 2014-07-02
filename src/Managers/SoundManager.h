//
//  SoundManager.h
//  chinoPinball
//
//  Created by Angel Mu–oz on 27/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "eventGame.h"
#include "eventMission.h"

#include "eventComunication.h"
#include "eventMission.h"

class SoundManager {
public:
	
	enum SoundsType { startGame = 1, launchBall = 2, ObjCol1
		= 3, ObjCol3 = 0, songGeneralGame = 4};
	
	SoundManager();
	static SoundManager* getInstance(void);
	void PlaySound(int idAudio);

	//Events
	void listenerOnHammerLaunch(eventGame & args);
	void listenerOnCollission(eventComunication & args);
	void listenerOnUpdateMission(eventMission & args);
	
private:
	// singleton stuff
	static bool    instanceFlag;
    static SoundManager *single;
    
    vector<string> soundFiles;
    vector<ofSoundPlayer*> soundObj;
	
};

/*

/ HOW TO USE THIS CLASS IN my code? ?


(.h)

#include "SoundManager.h"

(.cpp)
SoundManager::getInstance()->PlaySound(1);

*/
