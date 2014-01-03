//
//  Scenario.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//  Description: Responsable por inicializar y controlar los elementos de un escenario del juego.
//

#include "ofxBullet.h"
#include "SimpleObject.h"
#include "Ball.h"
#include "Lever.h"

class Scenario {
    
public:
	void setup(ofxBulletWorldRigid &world);
	void update();
	void draw();
    
    ofxBulletWorldRigid *     world;
    
    //SimpleObject              m_sphere;
    Ball                      m_Ball;
    Lever                     leverLeft;
    
    
};