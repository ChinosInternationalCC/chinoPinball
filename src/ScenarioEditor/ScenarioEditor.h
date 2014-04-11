//
//  ScenarioEditor.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#pragma once


#include "ofxBullet.h"
#include "Scenario.h"
#include "eventObjectScenario.h"
#include "eventMoveObjectScenario.h"
#include "SimpleObject.h"
#include "chinoWorld.h"
#include "ofxUI.h"

class ScenarioEditor {
    
public:
	void setup(chinoWorld &world, Scenario &scenario);
	void update();
	void draw();
    
    void keyReleased(int key);
    void onMousePick( ofxBulletMousePickEvent &e );
	//ofVec3f objPressedLoc;
	ofVec2f mousePickLoc;
    
    chinoWorld *	world;
    Scenario *		scenario;
	
	bool bEscenarioEditorMode;
    
    SimpleObject *	selectedObject; /* current selected object, NULL if no object selected */
   
	void mouseDragged(ofMouseEventArgs &args);
    void mouseMoved(ofMouseEventArgs &args);
    void mousePressed(ofMouseEventArgs &args);
    void mouseReleased(ofMouseEventArgs &args);
    
    void addObject(SimpleObject::shapeType type);
    
    ofMouseEventArgs mouseOldPosition;
    
    
    /* GUI stuff */
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    bool drawFill;
	float red, green, blue, alpha;
	ofColor backgroundColor;
    float radius;
    int resolution;
    ofPoint position;
    
    float noiseScale;
    float *buffer;
    vector<float> xPos;
    vector<float> yPos;
    
    ofxUIMovingGraph *xGraph;
    ofxUIMovingGraph *yGraph;
    
    int bufferSize;
    
    ofImage *image;
	
};