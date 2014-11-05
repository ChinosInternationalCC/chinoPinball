//
//  Scenario.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//  Description: Responsable por inicializar y controlar los elementos de un escenario del juego.
//

#pragma once

#include "ofxBullet.h"

#include "Ball.h"
#include "Lever.h"
#include "Hammer.h"
#include "Obstacle.h"
#include "Bounds.h"
#include "SimpleObject.h"
#include "ofxXmlSettings.h"

#include "SimpleMission.h"


class Scenario {
    
public:
	
	//Missions
    void setCurrentMission(int idMission);
    void setupMissions(vector <SimpleMission *> *missions);
	
	///
	void setup(ofxBulletWorldRigid &world);
	void update(bool bEditorMode);
	void draw(bool bEditorMode);
    void drawDebug(void);

    void loadFromXml(ofxBulletWorldRigid &world);
    void saveToXml(void);
    void loadFromJSON(ofxBulletWorldRigid &world);
    void saveToJSON(void);
    
    void popAllObjects(void); /* Can be usefull if we want to reload the scenario 
                                 call popAllObjects() and after load from Xml */
    
    void popObject(SimpleObject* obj);
    void pushObject(ofxBulletWorldRigid &world, int typeObject, ofVec3f pos);
	
    //ofxXmlSettings ScenarioXml;
    
    ofxBulletWorldRigid *     world;
   /*
    Ball                    m_Ball,m_Ball2;
    Lever                   leverLeft;
    Lever                   leverRight;
    Hammer                   m_Hammer;
    
    Obstacle                m_obstable1;
    Obstacle                m_obstable2;
    Obstacle                m_obstable3;
    Obstacle                m_obstable4;
    */
    vector<SimpleObject*> ScenarioObjects;
    
	//basic World
	vector <ofxBulletBox*>		bounds;

    float                       ballLimitsBoxSize;

    //general Light ambient
    ofVec3f                 lightPos;
	
	//material for shadows
	ofMaterial material;
	
	void loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos);
	void addCoverScenario(ofxBulletWorldRigid &world);
	void removeCoverScenario();
    
    void setDebugMode(bool &DebugMode);

	
private:
	
	//BASIC SCENARIO STATGE/////////////////////////////////////
	ofVec3f startLoc;
	ofPoint dimens;
	
	float scaleStage = 0.25;
	float	boundsWidth = 7.;;
	float depthStage = 160;
	float frontbackwallHeigh = 40;
	float heightwalls = 20;
	
	//Ground
	float widthbasePlane = 100;
	float heightbasePlane = depthStage;
	float depthbasePlane = boundsWidth;
	
	//BackWall
	float widthbkPlane = 100;
	float heightbkPlane = boundsWidth*1.5;
	float depthbkPlane = frontbackwallHeigh;
	
	//RightLeftWall
	float widthrlPlane = boundsWidth;
	float heightrlPlane = depthStage;
	float depthrlPlane = heightwalls;
	
	int	 lastPosIdCoverScenario;
	//BASIC SCENARIO STATGE/////////////////////////////////////
	
    vector<SimpleMission *> *currentMissions;
	int idCurrentMission;
	
    bool DebugMode;
	
};