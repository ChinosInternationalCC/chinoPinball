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
	float scaleStage = 1;
	
	ofVec3f startLoc;
	ofPoint dimens;
	
	boundsWidth = 1;
	float depthStage = 20;
	float widthPlane = 15;
	float frontbackwallHeigh = 2;
	
	
	for(int i = 0; i < 4; i++) {
		bounds.push_back( new ofxBulletBox() );
		if(i == 0) { // ground //
			startLoc.set(0, 0, 0.5);
			dimens.set(widthPlane, depthStage, 1);
		} else if (i == 1) { // back wall //
			startLoc.set(0, -depthStage*0.5 - 0.5, - 0);
			dimens.set(widthPlane, boundsWidth, 2);
		} else if (i == 2) { // right wall //
			startLoc.set(widthPlane*0.5 + 0.5, -0.5*boundsWidth, 0);
			dimens.set(1, depthStage + boundsWidth, 2);
		} else if (i == 3) { // left wall //
			startLoc.set(-widthPlane*0.5 - 0.5, -0.5*boundsWidth, 0);
			dimens.set(1, depthStage + boundsWidth, 2);
		}
		/*else if (i == 4) { // no ceiling //
		 //startLoc.set(0, -hwidth-hdepth, 0.);
		 //dimens.set(widthPlane, boundsWidth, depthStage);
		 } else if (i == 5) { // front wall //
		 //startLoc.set(0, 0, -hwidth-hdepth);
		 //dimens.set(widthPlane, frontbackwallHeigh, boundsWidth);
		 }*/
        bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
		bounds[i]->setProperties(.95, .05); // .25 (more restituition means more energy) , .95 ( friction )
		bounds[i]->add();
	}
    
    bounds.push_back( new ofxBulletBox() );

    startLoc.set(widthPlane*0.5 - 1.2, -8.5, 0);
    dimens.set(0.8, 4, 2);
    
    //ofQuaternion(float angle, const ofVec3f& axis);
    //ofxBulletBox::create( btDiscreteDynamicsWorld* a_world, ofVec3f a_loc, ofQuaternion a_rot, float a_mass, float a_sizeX, float a_sizeY, float a_sizeZ )
    bounds[4]->create( world.world, startLoc*scaleStage, ofQuaternion(290,ofVec3f(0,0,1)), 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
    bounds[4]->setProperties(.95, .05); // .25 (more restituition means more energy) , .95 ( friction )
    bounds[4]->add();
    

    
    
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
    for(int i = 0; i < obstacles.size(); i++) {
        obstacles[i].draw();
    }
    
}