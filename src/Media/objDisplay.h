//
//  objDisplay.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#ifndef __ofxBulletEventsExample__objDisplay__
#define __ofxBulletEventsExample__objDisplay__

#include "ofMain.h"

class objDisplay {
    
public:
	void setup();
	void update();
	void draw();
    
	ofTexture texture;
	
	/*
	State ( normal / collision / animation )
	textureFilename (string);
	videoFilename (string);
	bAnimated (bool);
	 */
	
private:
	/*
	worldposition ( ofmatrix4x4)
	shapeType ( enum )
	
	setup(worldposition, shape )
	update(gameStatus, objectStatus)
	eventCollision( )
	 */
	
};

#endif /* defined(__ofxBulletEventsExample__objDisplay__) */
