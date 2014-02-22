//
//  ScenarioEditor.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "ScenarioEditor.h"

//--------------------------------------------------------------
void ScenarioEditor::setup(ofxBulletWorldRigid &world, Scenario &scenario){
    
    this->world = &world;
    this->scenario = &scenario;
    
	// enables mouse Pick events //
	this->world->enableGrabbing(-1);
	ofAddListener(world.MOUSE_PICK_EVENT, this, &ScenarioEditor::onMousePick);

}

//--------------------------------------------------------------
void ScenarioEditor::update(){
}

//--------------------------------------------------------------
void ScenarioEditor::draw(){
}

//--------------------------------------------------------------
void ScenarioEditor::onMousePick( ofxBulletMousePickEvent &e ) {
	
    cout << "ScenarioEditor::onMousePick : selected a body!!!" << endl;
    //mousePickIndex = -1;
    for(int i = 0; i < scenario->ScenarioObjects.size(); i++) {
		/*
        if(scenario->ScenarioObjects[i]->body == e) {
            cout << "ScenarioEditor::onMousePick : selected a SimpleObject!!!" << endl;
            //mousePickIndex = i;
			//mousePickPos = e.pickPosWorld;
			break;
		}
         */
	}
}