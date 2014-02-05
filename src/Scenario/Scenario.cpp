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
    

    m_Ball.setup(world,ofVec3f(2,-10,-0.5));
    m_Ball2.setup(world,ofVec3f(7,-6,-0.5));
    leverLeft.setup(world, ofVec3f(-3, 7, -0.3), 0);
    leverRight.setup(world, ofVec3f(3, 7, -0.3), 1);
    m_Hammer.setup(world,ofVec3f(7,5,-0.3));
    loadObstacles(world);
	
	ofVec3f initworldpos = ofVec3f(0,0,0);
	loadBasicScenario(world, initworldpos);
    
}

void Scenario::loadObstacles(ofxBulletWorldRigid &world){
    obstacles.resize(4);
    for(int i = 0; i < 4; i++) {
        obstacles[i].setup(world, ofVec3f(-5+3.3*i,-4,-0.5), "cylinder.stl");
    }
}

void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
	/////////////////////////////////////////////////////////////////////////////////////////
    
	// STATGE
	float scaleStage = 0.15;
	
	ofVec3f startLoc;
	ofPoint dimens;
	
	boundsWidth = 10.;
	float depthStage = 200;
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
			startLoc.set(0, 0, depthbasePlane*0.85);
			dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
		} else if (i == 1) { // back wall //
			startLoc.set(0, -widthbasePlane*1, -depthbasePlane*0.5);
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
		bounds[i]->setProperties(.90, .95); // .25 (more restituition means more energy) , .95 ( friction )
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
	leverLeft.update();
	leverRight.update();
    m_Hammer.update();
    for(int i = 0; i < obstacles.size(); i++) {
        obstacles[i].update();
    }
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    m_Ball.draw();
    m_Ball2.draw();
    leverLeft.draw();
    leverRight.draw();
    m_Hammer.draw();
	
	ofDrawAxis(1);

    for(int i = 0; i < obstacles.size(); i++) {
        obstacles[i].draw();
    }

    
}
