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

#include "ScenarioObject.h"

#include "Ball.h"
#include "Lever.h"
#include "Hammer.h"
#include "Obstacle.h"
#include "AnimatedObstacle.h"
#include "Bounds.h"

#include "AnimatedMesh.h"
#include "GeneratedMesh.h"

#include "Gravity.h"
#include "Teleporter.h"
#include "Ramp.h"

#include "ofxBulletTriMeshShape.h"
#include "SimpleObject.h"
#include "ofxXmlSettings.h"

#include "SimpleMission.h"


#include "ofxUI.h"
#include "ofxUIDefines.h"


class Scenario {
    
public:
	Scenario();
    ~Scenario();
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
    
	//Multiball methods
	void addOneBallMore();

    ofVec3f ballLimitsBoxSize;

    //general Light ambient
    ofVec3f                 lightPos;
	
	//material for shadows
	ofMaterial material;
	
	void addCoverScenario(ofxBulletWorldRigid &world);
	void removeCoverScenario();
    
    void setDebugMode(bool &DebugMode);

    SimpleObject* FindScenarioObjectByName(string name);
    SimpleObject* FindScenarioObjectById(int id);
	SimpleObject* FindScenarioObjectByRigidBody(const btRigidBody* body);
	vector <Ball *> getBalls();
	
	
	//Basic Gui
	bool bEditorMode, lastbEditorMode;
	ofxUICanvas *guiBasicScenario;
	void createBasicGUIScenario();
	bool bVisibleBasicTerrain;
	ofVec2f posGui;
	void guiEventBasics(ofxUIEventArgs &e);
	
	float defaulDeltaZPos = 0;
	
	ofVec2f ScorePos;
	
    void ActivateTeleport(bool activateFlag);
    void ActivateGravityObjects(bool activateFlag);

private:
	///////////////////
	//Ball atributes
	int ballCounter; // from 0 to -X
	ofVec3f posBall;
	ofQuaternion rotationBall;
	float radiusBall;
	Ball *oBall;
	float massBall;
	float restitutionBall;
	float frictionBall;
	BallAttrib *ballAttrib;
	int colorBall;
	int invisibleBall;
						   

	//BASIC SCENARIO STATGE/////////////////////////////////////
	
    vector<SimpleMission *> *currentMissions;
	int idCurrentMission;
	
    bool DebugMode;

	
	
};