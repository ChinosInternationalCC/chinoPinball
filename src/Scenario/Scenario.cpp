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
    
    m_Ball.setup(world,ofVec3f(5,-10,0));
    m_Ball2.setup(world,ofVec3f(6,-3,0));
    leverLeft.setup(world,ofVec3f(4.5, 7, 0));
    m_Hammer.setup(world,ofVec3f(6,9,0));
	
	ofVec3f initworldpos = ofVec3f(0,0,0);
	loadBasicScenario(world, initworldpos);
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

}

//--------------------------------------------------------------
void Scenario::update(){
	leverLeft.update();
    m_Hammer.update();
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    m_Ball.draw();
    m_Ball2.draw();
    leverLeft.draw();
    m_Hammer.draw();
	
	ofDrawAxis(1);
    
}