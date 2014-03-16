//
//  ScenarioEditor.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "ScenarioEditor.h"

//--------------------------------------------------------------
void ScenarioEditor::setup(chinoWorld &world, Scenario &scenario){
    
    this->world = &world;
    this->scenario = &scenario;
    
	// enables mouse Pick events //
	this->world->enableGrabbing(-1);
	ofAddListener(world.MOUSE_PICK_EVENT, this, &ScenarioEditor::onMousePick);
    
    ofRegisterMouseEvents(this);
    
    selectedObject = NULL;
}

//--------------------------------------------------------------
void ScenarioEditor::update(){
}

//--------------------------------------------------------------
void ScenarioEditor::draw(){
}

//--------------------------------------------------------------
void ScenarioEditor::keyReleased(int key){
    
    switch(key)
    {
		case 'm':
            bEscenarioEditorMode = !bEscenarioEditorMode;
			cout << "bScenarioEditorActive= " << bEscenarioEditorMode << endl;   
            break;
            
        case 'e':
            scenario->saveToXml();
            cout << "saving scenario to Xml" << endl;
            break;
            
        case '0':
            addObject(SimpleObject::ShapeTypeBall);
            break;
        case '3':
            addObject(SimpleObject::ShapeTypeLever);
            break;
        case '5':
            addObject(SimpleObject::ShapeTypeHammer);
            break;
        case '6':
            addObject(SimpleObject::ShapeTypeObstacle);
            break;
            
    }
    
}

//--------------------------------------------------------------
void ScenarioEditor::onMousePick( ofxBulletMousePickEvent &e ) {
    
    selectedObject = NULL;
	
    //    cout << "ScenarioEditor::onMousePick : selected a body!!!" << endl;
    for(int i = 0; i < scenario->ScenarioObjects.size(); i++) {
		ofxBulletBaseShape *baseShape;
        baseShape = scenario->ScenarioObjects[i]->getBulletBaseShape();
        if(*baseShape == e) {
            
            selectedObject = scenario->ScenarioObjects[i];
            
            //selectedObject
            ofLogVerbose("EditorVerbose") << "ScenarioEditor::onMousePick : selected a " << scenario->ScenarioObjects[i]->getObjectName() << endl;
            
			//mousePickPos = e.pickPosWorld;
			break;
		}
	}
    
}

//--------------------------------------------------------
void ScenarioEditor::mouseDragged(ofMouseEventArgs &args){
    ofVec3f newPos;
    if (selectedObject != NULL){
        
        newPos = selectedObject->position;
        newPos.x = newPos.x + (args.x/1000);
        newPos.y = newPos.y + (args.y/1000);
        selectedObject -> position = newPos;
        selectedObject -> setPosition(newPos);
    }
}

//--------------------------------------------------------
void ScenarioEditor::mouseMoved(ofMouseEventArgs &args){
    
}

//--------------------------------------------------------
void ScenarioEditor::mousePressed(ofMouseEventArgs &args){
    
}

//--------------------------------------------------------
void ScenarioEditor::mouseReleased(ofMouseEventArgs &args){
    
}

//--------------------------------------------------------------
void ScenarioEditor::addObject(SimpleObject::shapeType type) {
	
    //Set new objects if Editor mode is active and Selected Obstacle
    if(bEscenarioEditorMode){
        
        //Create class to save type of objec and Notifie the Event to escenario
        eventObjectScenario newObjectEvent;
        newObjectEvent.posObject = ofVec3f(world->getWorldPos());
        newObjectEvent.type = type;
        ofNotifyEvent(eventObjectScenario::onNewObject, newObjectEvent);
        
    };
    
}