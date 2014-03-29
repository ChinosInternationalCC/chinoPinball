//
//  arduOutputManager.h
//  chinoPinball
//
//  Created by carles on 28/03/14.
//
//

#pragma once

#define charRUConfirm "R"
#define charRDConfirm "r"
#define charLUConfirm "L"
#define charLDConfirm "l"
#define charHUConfirm "H"
#define charHDConfirm "h"


#include "ofMain.h"
#include "SimpleObject.h"
#include "InputEventManager.h"

#include "arduComunicationManager.h"
#include "eventComunication.h"


class arduComunicationManager{
	
public:
    arduComunicationManager();

	void setup();
	void update(InputEventManager * inputs);
	
	void obstableCollision(SimpleObject* object);
	
	ofSerial	serial;
    
	//Events
	void listenerOnCollission(eventComunication & args);

private:
	
	//Serial vars
	bool		bFirstTimeReadingArduino;
	bool		breadingArduino;
	

	bool		bSendSerialMessage;			// a flag for sending serial
	char		bytesRead[1];				// data from serial, we will be trying to read 3
	char		bytesReadString[2];			// a string needs a null terminator, so we need 3 + 1 bytes
	int			nBytesRead;					// how much did we read?
	int			nTimesRead;					// how many times did we read?
	float		readTime;					// when did we last read?
	
};
