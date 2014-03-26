//
//  InputEventManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#include "InputEventManager.h"


InputEventManager::InputEventManager(){
	
	//Serial vars --------------------------------------------------------
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	serial.setup(0, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 1);
	breadingArduino = true;
	bFirstTimeReadingArduino = true;
	//--------------------------------------------------------------------
	
}

//--------------------------------------------------------------
void InputEventManager::update()
{
	
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
				onMoveLeftLeverEvent();
				cout << "Right UP Confirm" << endl;
			}
			else if (sms.compare(charRDConfirm) == 0){
				onReleaseLeftLeverEvent();
				cout << "Right Down Confirm" << endl;
			}
			
			//RIGHT
			else if(sms.compare(charLUConfirm) == 0){
				onMoveRightLeverEvent();
				cout << "Left UP Confirm" << endl;
			}
			else if (sms.compare(charLDConfirm) == 0){
				onReleaseRightLeverEvent();
				cout << "Left DOWN Confirm" << endl;
			}
			
			//HAMMER
			else if(sms.compare(charHUConfirm) == 0){
				onMoveBallLauncherEvent();
				cout << "Hammer UP Confirm" << endl;
			}
			else if (sms.compare(charHDConfirm) == 0){
				onReleaseBallLauncherEvent();
				cout << "Hammer DOWN Confirm" << endl;
			}
		}

		
	}


		
		

}


//--------------------------------------------------------------
void InputEventManager::keyPressed(int key)
{
    
    switch(key)
    {
        case OF_KEY_RETURN:
            onRestartGameEvent();
            break;
            
        case OF_KEY_DOWN:
            onMoveBallLauncherEvent();
            break;
        case 'z':
        case 'Z':
            onMoveLeftLeverEvent();
			break;
        case 'm':
        case 'M':
            onMoveRightLeverEvent();
	       break;
		case 'A':
			breadingArduino = !breadingArduino;
			cout << "breadingArduino = " << breadingArduino << endl;
		   break;
    }
    
}

//--------------------------------------------------------------
void InputEventManager::keyReleased(int key)
{
    
    switch(key)
    {
            
        case OF_KEY_DOWN:
            onReleaseBallLauncherEvent();
            break;
            
        case 'z':
		case 'Z':
            onReleaseLeftLeverEvent();
            break;
            
        case 'm':
        case 'M':
            onReleaseRightLeverEvent();
            break;
            
    }
    
}
