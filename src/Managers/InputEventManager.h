//
//  InputEventManager.h
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#ifndef __chinoPinball__InputEventManager__
#define __chinoPinball__InputEventManager__


#include "ExternalsConfig.h"
#include "ofMain.h"


#ifdef USE_OSC /* configured in ExternalsConfig.h */
#include "ofxOsc.h"
#endif

#define MAXKEYS 10


#define charRUConfirm "R"
#define charRDConfirm "r"
#define charLUConfirm "L"
#define charLDConfirm "l"
#define charHUConfirm "H"
#define charHDConfirm "h"

//string charRConfirm = "R";
//string charLConfirm = "L";

/* this class is the entry point from all the interfaces suported
 * eg: keyboard, OSC TBD
 * should be extended by the PinballChino manager
 * PinbalChinoManager should implement the pure virtual methods
 */

class InputEventManager
{
public:
    InputEventManager();
    
    virtual void onMoveLeftLeverEvent(void) = 0;
    virtual void onReleaseLeftLeverEvent(void) = 0;
    virtual void onMoveRightLeverEvent(void) = 0;
    virtual void onReleaseRightLeverEvent(void) = 0;
    virtual void onMoveBallLauncherEvent(void) = 0;
    virtual void onReleaseBallLauncherEvent(void) = 0;
    virtual void onRestartGameEvent(void) = 0;
    
#ifdef USE_OSC
    ofxOscReceiver oscReceiver;
#endif
    
    void keyPressed(int key);
    void keyReleased(int key);
	
	void update();
    
	
	//Serial vars
	bool		bFirstTimeReadingArduino;
	bool		breadingArduino;

	ofSerial	serial;
	bool		bSendSerialMessage;			// a flag for sending serial
	char		bytesRead[1];				// data from serial, we will be trying to read 3
	char		bytesReadString[2];			// a string needs a null terminator, so we need 3 + 1 bytes
	int			nBytesRead;					// how much did we read?
	int			nTimesRead;					// how many times did we read?
	float		readTime;					// when did we last read?

};


#endif /* defined(__chinoPinball__InputEventManager__) */
