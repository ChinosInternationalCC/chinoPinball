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
    
    m_Ball.setup(world,ofVec3f(2,-10,0));
    m_Ball2.setup(world,ofVec3f(7,-6,0));
    leverLeft.setup(world);
    m_Hammer.setup(world,ofVec3f(7,4,0));
	
	ofVec3f initworldpos = ofVec3f(0,0,0);
	loadBasicScenario(world, initworldpos);
    
}

void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
	/////////////////////////////////////////////////////////////////////////////////////////
	// STATGE
	float scaleStage = 1;
	
	ofVec3f startLoc;
	ofPoint dimens;
	
	boundsWidth = 10.;
	float depthStage = 300;
	float widthPlane = 100;
	float frontbackwallHeigh = 40;
	
	
	for(int i = 0; i < 4; i++) {
		bounds.push_back( new ofxBulletBox() );
		if(i == 0) { // ground //
			startLoc.set(0, 0, 0);
			dimens.set(widthPlane, boundsWidth, depthStage);
		} else if (i == 1) { // back wall //
			startLoc.set(0, -boundsWidth, depthStage*0.5);
			dimens.set(widthPlane+(2*boundsWidth), frontbackwallHeigh, boundsWidth);
		} else if (i == 2) { // right wall //
			startLoc.set(widthPlane*0.5 , -boundsWidth, 0.);
			dimens.set(boundsWidth, boundsWidth, depthStage);
		} else if (i == 3) { // left wall //
			startLoc.set(-widthPlane*0.5 /* or 0*/, -boundsWidth, 0.);
			dimens.set(boundsWidth, boundsWidth, depthStage);
		}
		/*else if (i == 4) { // no ceiling //
		 //startLoc.set(0, -hwidth-hdepth, 0.);
		 //dimens.set(widthPlane, boundsWidth, depthStage);
		 } else if (i == 5) { // front wall //
		 //startLoc.set(0, 0, -hwidth-hdepth);
		 //dimens.set(widthPlane, frontbackwallHeigh, boundsWidth);
		 }*/
		
		bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
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
    
}