//
//  arduComunicationManager.cpp
//  chinoPinball
//
//  Created by carles on 28/03/14.
//
//

#include "arduComunicationManager.h"


/*
ShapeTypeBall = 0,
ShapeTypeSimpleBox = 1,
ShapeTypeSpring = 2,
ShapeTypeLever = 3,
ShapeTypeContainer = 4,
ShapeTypeHammer = 5,
ShapeTypeObstacle = 6
*/

arduComunicationManager::arduComunicationManager(){
	
	//Serial vars --------------------------------------------------------
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
    bool SerialOk;
	SerialOk = serial.setup(0, baud); //open the first device
	//SerialOk = serial.setup("COM4", baud); // windows example
	//SerialOk = serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//SerialOk = serial.setup("/dev/ttyUSB0", baud); //linux example
	
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 1);
    if (SerialOk){
        breadingArduino = true;
        bFirstTimeReadingArduino = true;
    }
    else{
        breadingArduino = false;
        bFirstTimeReadingArduino = false;
    }
	//--------------------------------------------------------------------
	

}

//--------------------------------------------------------------------
void arduComunicationManager::setup(){
	
	///arduino
	//Listeners
	//TODO ARDUDAY
	if (breadingArduino){
        ofAddListener(eventComunication::onNewCom,this, &arduComunicationManager::listenerOnCollission);
    }


}

//--------------------------------------------------------------------
void arduComunicationManager::update(InputEventManager * inputs){
	
	if (breadingArduino){
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to
		// read as much as we can in groups of three...
		
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		bool bSomethingToRead;
		
		unsigned char bytesReturned[1];
		
		memset(bytesReadString, 0, 1);
		memset(bytesReturned, 0, 1);
		
		while( (nRead = serial.readBytes( bytesReturned, 1)) > 0){
			nTimesRead++;
			nBytesRead = nRead;
		};
		
		memcpy(bytesReadString, bytesReturned, 1);
		string sms = ofToString(bytesReadString);
		
		if(sms.length()>0){
			cout << "bytesReadString = " << sms << endl;
			bSomethingToRead = true;
		}
		
		readTime = ofGetElapsedTimef();
		
		// (1) check communication to read
		
		if(bSomethingToRead ){ //Free way to recognize Serial commads
			
			//LEFT
			if (sms.compare(charRUConfirm) == 0){ //loof for read RIGHT lever
				inputs->onMoveLeftLeverEvent();
				cout << "Right UP Confirm" << endl;
			}
			else if (sms.compare(charRDConfirm) == 0){
				inputs->onReleaseLeftLeverEvent();
				cout << "Right Down Confirm" << endl;
			}
			
			//RIGHT
			else if(sms.compare(charLUConfirm) == 0){
				inputs->onMoveRightLeverEvent();
				cout << "Left UP Confirm" << endl;
			}
			else if (sms.compare(charLDConfirm) == 0){
				inputs->onReleaseRightLeverEvent();
				cout << "Left DOWN Confirm" << endl;
			}
			
			//HAMMER
			else if(sms.compare(charHUConfirm) == 0){
				inputs->onMoveBallLauncherEvent();
				cout << "Hammer UP Confirm" << endl;
			}
			else if (sms.compare(charHDConfirm) == 0){
				inputs->onReleaseBallLauncherEvent();
				cout << "Hammer DOWN Confirm" << endl;
			}
		}
		
		
	}
}


//Listeners 

//--------------------------------------------------------------------
void arduComunicationManager::obstableCollision(SimpleObject* object){
	
	if(object->type == SimpleObject::ShapeTypeObstacle){
	
		
	}

}

//Listeners
//--------------------------------------------------------------------
void arduComunicationManager::listenerOnCollission(eventComunication & args){
	//int id = args.pObject->GetObjectId();
	//Send rele Envent to Arduino
	serial.writeByte('0');
	serial.writeByte('2');
	
}
