//
//  InputEventManager.h
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#ifndef __chinoPinball__InputEventManager__
#define __chinoPinball__InputEventManager__

#include "ofMain.h"
#include "ofxOsc.h"

/* this class is the entry point from all the interfaces suported
 * eg: keyboard, OSC TBD
 * should be extended by the PinballChino manager
 * PinbalChinoManager should implement the pure virtual methods
 */
class InputEventManager: public ofBaseApp,
                         public ofxOscReceiver
{
public:
    InputEventManager();
    
    virtual void moveLeftLever(void) = 0;
    virtual void moveRightLever(void) = 0;
    virtual void moveBallLauncher(void) = 0;
    
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
    
};


#endif /* defined(__chinoPinball__InputEventManager__) */
