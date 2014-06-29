//
//  GameStatusDisplay.h
//  chinoPinball
//
//  Created by Ovidiu on 31/01/14.
//
//

#ifndef __chinoPinball__GameStatusDisplay__
#define __chinoPinball__GameStatusDisplay__

#include "ofxFTGL.h"
#include "MediaUtils.h"


class GameStatusDisplay{
public:
    GameStatusDisplay(int posX, int posY);
    void draw(void);
    
    ofxFTGLFont font;
    string str;
    
    
    ofLight light;
    ofMaterial material;
    
    bool show3dfont;

    //void setCamera(ofEasyCam *cam);
    
private:
    ofEasyCam cam;
    int startPositionX, startPositionY;
    void setup3dFont(void);
    void draw3dFont(void);
    void draw2dFont(void);

};

#endif /* defined(__chinoPinball__GameStatusDisplay__) */
