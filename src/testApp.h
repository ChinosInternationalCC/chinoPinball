#pragma once


#include "ExternalsConfig.h"
#include "ofMain.h"
#include "PinballChinoManager.h"


#ifdef USE_SYPHON  /* configured in ExternalsConfig.h */
#include "ofxSyphon.h"
#endif

#ifdef USE_MTL_MAPPING
#include "ofxMtlMapping2D.h"
#endif

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
private:
    
    PinballChinoManager    chinopinball;
    
#ifdef USE_SYPHON
    ofxSyphonServer mainOutputSyphonServer;
#endif

#ifdef USE_MTL_MAPPING
    ofxMtlMapping2D* _mapping;
#endif
	
};
