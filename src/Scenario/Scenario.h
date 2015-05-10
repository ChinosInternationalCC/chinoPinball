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
#include "AnimatedObject.h"
#include "AnimatedMesh.h"
#include "GeneratedMesh.h"
#include "AnimatedMotionPath.h"
#include "Gravity.h"
#include "Teleporter.h"
#include "Ramp.h"
#include "ObstacleTriShapeMesh.h"
#include "ofxBulletTriMeshShape.h"
#include "SimpleObject.h"
#include "ofxXmlSettings.h"

#include "SimpleMission.h"


#include "ofxUI.h"
#include "ofxUIDefines.h"


class Scenario {
    
public:
	Scenario();
	//Missions
    void setCurrentMission(int idMission);
    void setupMissions(vector <SimpleMission *> *missions);
	
	///
	void setup(ofxBulletWorldRigid &world, bool bAddScenarioCover);
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

    SimpleObject* FindScenarioObjectByName(string name);
    SimpleObject* FindScenarioObjectById(int id);
	
	
	//Basic Gui
	bool bEditorMode, lastbEditorMode;
	ofxUICanvas *guiBasicScenario;
	void createBasicGUIScenario();
	bool bVisibleBasicTerrain;
	ofVec2f posGui;
	void guiEventBasics(ofxUIEventArgs &e);
	
private:
	
	//BASIC SCENARIO STATGE/////////////////////////////////////
	ofVec3f startLoc;
	ofPoint dimens;
	
	float scaleStage;
	float	boundsWidth;
	float depthStage;
	float frontbackwallHeigh;
	float heightwalls;
	
	//Ground
	float widthbasePlane;
	float heightbasePlane;
	float depthbasePlane;
	
	//BackWall
	float widthbkPlane;
	float heightbkPlane;
	float depthbkPlane;
	
	//RightLeftWall
	float widthrlPlane;
	float heightrlPlane;
	float depthrlPlane;
	
	int	 lastPosIdCoverScenario;
	//BASIC SCENARIO STATGE/////////////////////////////////////
	
    vector<SimpleMission *> *currentMissions;
	int idCurrentMission;
	
    bool DebugMode;

	
	
};