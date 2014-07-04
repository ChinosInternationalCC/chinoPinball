//
//  LightsManager.cpp
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#include "LightsManager.h"

void LightsManager::setup(void){
    // radius of the sphere //
	radius		= 200.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    //pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    
    // specular color, the highlight/shininess color //
	//pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	//pointLight.setPointLight();
    
}
void LightsManager::update(void){
    center = mainLightPosition;
    
    /*pointLight.setPosition(cos(ofGetElapsedTimef()*.06f) * radius * 2 + center.x,
						   sin(ofGetElapsedTimef()*.08f) * radius * 2 + center.y,
						   -cos(ofGetElapsedTimef()*.08f) * radius * 2 + center.z);*/
    
}

void LightsManager::enable(void){
    //pointLight.enable();
    mainLight.enable();
}
void LightsManager::disable(void){
   // pointLight.disable();
    mainLight.disable();
}
void LightsManager::draw(void){
    //pointLight.draw();
}

void LightsManager::setMainLightPosition(ofVec3f lightPos){
    mainLightPosition = lightPos;
    mainLight.setPosition(lightPos);
}