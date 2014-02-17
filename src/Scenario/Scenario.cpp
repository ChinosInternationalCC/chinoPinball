//
//  Scenario.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "Scenario.h"

//--------------------------------------------------------------
void Scenario::setup(ofxBulletWorldRigid &world){
    

//    m_Ball.setup		(world,	ofVec3f(0,0,	-0.5));
    m_Ball2.setup		(world,	ofVec3f(5,	0,	-0.5));
    leverLeft.setup		(world, ofVec3f(-3,	8,	-0.2),0);
    leverRight.setup	(world, ofVec3f(3,	8,	-0.2),1);
    m_Hammer.setup		(world,	ofVec3f(5,	5,	-0.4));
    loadObstacles		(world);
	
    ScenarioObjects.push_back(&m_Ball2);
    ScenarioObjects.push_back(&leverLeft);
    ScenarioObjects.push_back(&leverRight);
    ScenarioObjects.push_back(&m_Hammer);
    
	ofVec3f initworldpos = ofVec3f(0,0,0);
	loadBasicScenario(world, initworldpos);
    //saveToXml();
}

//------------------------------
void Scenario::loadFromXml(ofxBulletWorldRigid &world){
    if(ScenarioXml.loadFile("scenario.xml")){
        ScenarioXml.pushTag("scenario");
        int numberOfSavedObjects = ScenarioXml.getNumTags("object");
        for(int i = 0; i < numberOfSavedObjects; i++){
            ScenarioXml.pushTag("object", i);
            
            SimpleObject::shapeType Type = (SimpleObject::shapeType)ScenarioXml.getValue("type", 0);
            ofVec3f pos;
            pos.x = ScenarioXml.getValue("positionX", 0);
            pos.y = ScenarioXml.getValue("positionY", 0);
            pos.z = ScenarioXml.getValue("positionZ", 0);
            
            switch(Type){
                case SimpleObject::ShapeTypeBall:{
                    Ball *oBall = new Ball();
                    oBall->setup(world, pos);
                    ScenarioObjects.push_back(oBall);
                }
                    break;

                case SimpleObject::ShapeTypeHammer:{
                    Hammer *oHammer = new Hammer();
                    oHammer->setup(world, pos);
                    ScenarioObjects.push_back(oHammer);
                }
                    break;
                case SimpleObject::ShapeTypeLever:{
                    Lever *oLever = new Lever();
                    oLever->setup(world, pos, 0);
                }
                    break;
                default:
                    break;

                
            }
            
           
            ScenarioXml.popTag();
        }
        
        ScenarioXml.popTag(); //pop position
    }
    else{
        ofLogError("Scenario file did not load!");
    }
}

//------------------------------
void Scenario::saveToXml(){
    ScenarioXml.addTag("scenario");
    ScenarioXml.pushTag("scenario");
    
    for(int i = 0; i < ScenarioObjects.size(); i++){
        
        ScenarioXml.addTag("object");
        ScenarioXml.pushTag("object",i);
        
        ScenarioXml.addValue("type", ScenarioObjects[i]->type);
        ScenarioXml.addValue("positionX", ScenarioObjects[i]->position.x);
        ScenarioXml.addValue("positionY", ScenarioObjects[i]->position.y);
        ScenarioXml.addValue("positionZ", ScenarioObjects[i]->position.z);
        ScenarioXml.popTag();
    }
    ScenarioXml.popTag();
    ScenarioXml.saveFile("scenario.xml");
    
}



void Scenario::loadObstacles(ofxBulletWorldRigid &world){
    obstacles.resize(4);
    for(int i = 0; i < 4; i++) {
        obstacles[i].setup(world, ofVec3f(-3.5+3*i,-4,-.7), "cylinder.stl");
    }
}

void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
	/////////////////////////////////////////////////////////////////////////////////////////
    
	// STATGE
	float scaleStage = 0.12;
	
	ofVec3f startLoc;
	ofPoint dimens;
	
	boundsWidth = 7.;
	float depthStage = 160;
	float frontbackwallHeigh = 40;
	float heightwalls = 20;
	
	//Ground
	float widthbasePlane = 100;
	float heightbasePlane = depthStage;
	float depthbasePlane = boundsWidth;
	
	//BackWall
	float widthbkPlane = 100;
	float heightbkPlane = boundsWidth;
	float depthbkPlane = frontbackwallHeigh;
	
	//RightLeftWall
	float widthrlPlane = boundsWidth;
	float heightrlPlane = depthStage;
	float depthrlPlane = heightwalls;

	
	
	for(int i = 0; i < 4; i++) {
		bounds.push_back( new ofxBulletBox() );
		if(i == 0) { // ground //
			//startLoc.set(-widthPlane*0.5, -heightPlane*0.5, 0);
			startLoc.set(0, 0, depthbasePlane*0.5);
			dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
		} else if (i == 1) { // back wall //
			startLoc.set(0, -depthStage*0.5, -depthbasePlane*0.5);
			dimens.set(widthbkPlane, heightbkPlane, depthbkPlane);
		} else if (i == 2) { // right wall //
			startLoc.set(-widthbasePlane*0.5 , 0, -depthbasePlane*0.5);
			dimens.set(widthrlPlane, heightrlPlane, depthrlPlane);
		} else if (i == 3) { // left wall //
			startLoc.set(+widthbasePlane*0.5 , 0, -depthbasePlane*0.5);
			dimens.set(widthrlPlane, heightrlPlane, depthrlPlane);
		}
		
		bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
		//bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.z*scaleStage, dimens.y*scaleStage );
		bounds[i]->setProperties(.99, .05); // .25 (more restituition means more energy) , .95 ( friction )
		bounds[i]->add();
	}

	/*
	
    //up right box
    bounds.push_back( new ofxBulletBox() );

    //ofQuaternion(float angle, const ofVec3f& axis);
    //ofxBulletBox::create( btDiscreteDynamicsWorld* a_world, ofVec3f a_loc, ofQuaternion a_rot, float a_mass, float a_sizeX, float a_sizeY, float a_sizeZ )
    bounds[4]->create( world.world, startLoc*scaleStage, ofQuaternion(290,ofVec3f(0,0,1)), 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
    bounds[4]->setProperties(.95, .05); // .25 (more restituition means more energy) , .95 ( friction )
    bounds[4]->add();
	 */
}

//--------------------------------------------------------------
void Scenario::update(){
    
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->update();
    }
    
    for(int i = 0; i < obstacles.size(); i++) {
        obstacles[i].update();
    }
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->draw();
    }
    
	ofDrawAxis(1);

    for(int i = 0; i < obstacles.size(); i++) {
        obstacles[i].draw();
    }

    
}
