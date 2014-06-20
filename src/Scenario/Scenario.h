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
#include "ofxJSONElement.h"


class Scenario {
    
public:
	void setup(ofxBulletWorldRigid &world);
	void update();
	void draw();
    void loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos);
    void loadFromXml(ofxBulletWorldRigid &world);
    void saveToXml(void);
    void loadFromJSON(ofxBulletWorldRigid &world);
    void saveToJSON(void);
    
    void popObject(SimpleObject* obj);
    void pushObject(ofxBulletWorldRigid &world, int typeObject, ofVec3f pos);
	
    //ofxXmlSettings ScenarioXml;
    
    ofxBulletWorldRigid *     world;
    
    Ball                    m_Ball,m_Ball2;
    Lever                   leverLeft;
    Lever                   leverRight;
    Hammer                   m_Hammer;
    
    Obstacle                m_obstable1;
    Obstacle                m_obstable2;
    Obstacle                m_obstable3;
    Obstacle                m_obstable4;
    
    vector<SimpleObject*> ScenarioObjects;
    
	//basic World
	vector <ofxBulletBox*>		bounds;
	float						boundsWidth;
	
};