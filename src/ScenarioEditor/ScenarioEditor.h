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
#include "ofxUIDefines.h"

class ScenarioEditor {
	
	// variables & methods for singleton
private:
    static bool	instanceFlag;
    static ScenarioEditor *single;
	
public:
	static ScenarioEditor* getInstance();
	// end singleton
	
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
	bool bgui;
	bool createGUI(SimpleObject *);
	void resetUIvalues();
    
	ofxUICanvas *gui;
	//bool bGoForRemove;
	ofVec2f posGui;
	
	bool bGuiPointer;//var to protect from gui * bad accsss
	
    bool deleteObject;
    
    void guiEvent(ofxUIEventArgs &e);
    //bool drawFill;
	//float gred, ggreen, gblue, galpha;
	ofColor backgroundColor;
    //float gradius;
    //float gresolution;
    ofPoint gposition;
    
    float gnoiseScale;
    float *buffer;
    //vector<float> xPos;
    //vector<float> yPos;
    
    ofxUIMovingGraph *xGraph;
    ofxUIMovingGraph *yGraph;
    
    int bufferSize;
    
    ofImage *image;
	
	
	//&_obj->angleRotX
	ofVec3f angleRotations;
	
};