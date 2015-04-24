//
//  ScenarioEditor.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "ScenarioEditor.h"


//----------------------------------------------
// SINGLETON initalizations
bool ScenarioEditor::instanceFlag = false;
ScenarioEditor* ScenarioEditor::single = NULL;


ScenarioEditor* ScenarioEditor::getInstance(){
    if(! instanceFlag)
    {
        single = new ScenarioEditor();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}

//--------------------------------------------------------------
void ScenarioEditor::setup(chinoWorld &world, Scenario &scenario){
    
    this->world = &world;
    this->scenario = &scenario;
    
	// enables mouse Pick events //
	this->world->enableGrabbing(-1);
	ofAddListener(world.MOUSE_PICK_EVENT, this, &ScenarioEditor::onMousePick);
    
    ofRegisterMouseEvents(this);
    
    selectedObject = NULL;
	
	gui = NULL;
	//bGoForRemove = false;
	deleteObject = false;
	resetUIvalues();
    
}

//--------------------------------------------------------------
void ScenarioEditor::resetUIvalues(){
	/*GUI setup */
	//set some sketch parameters
	//Background Color
	//gred = 233;     gblue = 240;    ggreen = 52;    galpha = 200;
	//gradius = 150;    gnoiseScale = .1;
	//drawFill = true;
	backgroundColor = ofColor(233, 52, 27);
	//gresolution = 30;
	//gposition = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5);
	//ofSetCircleResolution(gresolution);
}

//--------------------------------------------------------------
bool ScenarioEditor::createGUI(SimpleObject * _obj){
	
	bool bcreated = false;
	
	if(bEscenarioEditorMode){
	
		//create speficic gui for each object selected
		
		//Link directly to the main properties of the object selected // (selectedObject != NULL))
		
		
		if(gui != NULL && bGuiPointer){
			
			cout << "Going to del Gui" << endl;
			delete gui;
			cout << "Del Gui" << endl;
			bGuiPointer = false;
			
		}else bcreated = false;
		
		resetUIvalues();
		
		
		if(selectedObject != NULL){
			
			//if (selectedObject->type == SimpleObject::ShapeTypeObstacle) {
				
				cout << "Going to create a new Gui" << endl;
				posGui = ofVec2f(ofGetWidth()-OFX_UI_GLOBAL_CANVAS_WIDTH, 0);
				gui = new ofxUICanvas(posGui.x, posGui.y, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);

				bGuiPointer = true;
				cout << "new ofxUICanvas()" << endl;
			
			gui->addLabel("Editor Object");
			gui->addSpacer();
			
			gui->addSlider("angleValX", 0, PI, &selectedObject->angleValX);
			gui->addSlider("angleValY", 0, PI, &selectedObject->angleValY);
			gui->addSlider("angleValZ", 0, PI, &selectedObject->angleValZ);
				

				//gui->addSlider("Resolution", 0.0, 100.0, &selectedObject->scale);
				//gui->addSpacer();
				//gui->addIntSlider("COLOR", 0.0, 255.0, &selectedObject->color);
	
				gui->addSpacer();
				gui->addSlider("Scale XYZ", 0, 1, &selectedObject->scaleXyz);
				gui->addSpacer();
				gui->addSlider("damping", 0.0, 1.0, &selectedObject->damping);
				gui->addSlider("friction", 0.0, 1.0, &selectedObject->friction);
			

			gui->addLabel("Object Type ["+ofToString(selectedObject->type)+"]");
			gui->addSpacer();
			gui->addLabel("ObjectId ["+ofToString(selectedObject->ObjectId)+"]");
			gui->addSpacer();
			
			gui->addSpacer();
			gui->addLabelToggle("PRESS & PICK TO DELETE IT", &deleteObject);
			
			gui->addLabel("Escenario BoundingBox");
			gui->addSpacer();
			
				gui->addSpacer();
                gui->addSlider("ballLimitBox", 0.0, 50.0, &scenario->ballLimitsBoxSize);
			
			gui->addLabel("Escenario Lighting");
			gui->addSpacer();
                gui->addSlider("LightX", -50.0, 50.0, &scenario->lightPos.x);
                gui->addSlider("LightY", -50.0, 50.0, &scenario->lightPos.y);
                gui->addSlider("LightZ", -50.0, 50.0, &scenario->lightPos.z);
            gui->addLabel("ObjectDefaultColor");
			gui->addSpacer();
            ofImage *img;
            img = new ofImage();
            img->loadImage("colorpicker.png");
            
            gui->addImageSampler("SAMPLER", img);

			/*
				gui->addSlider("RotX", -3.0, +3.0, &selectedObject->rotation.x());
				gui->addSlider("RotY", -3.0, +3.0, &selectedObject->rotation.y());
				gui->addSlider("RotZ", -3.0, +3.0, &selectedObject->rotation.z());
				gui->addSlider("RotW", -3.0, +3.0, &selectedObject->rotation.w());
			*/


			
			/*
				gui->addSlider("Angel2RotXx", -1, +1, &selectedObject->axis2RotateX.x);
				gui->addSlider("Angel2RotXy", -1, +1, &selectedObject->axis2RotateX.y);
				gui->addSlider("Angel2RotXz", -1, +1, &selectedObject->axis2RotateX.z);

				gui->addSlider("Angel2RotYx", -1, +1, &selectedObject->axis2RotateY.x);
				gui->addSlider("Angel2RotYy", -1, +1, &selectedObject->axis2RotateY.y);
				gui->addSlider("Angel2RotYz", -1, +1, &selectedObject->axis2RotateY.z);
			
				gui->addSlider("Angel2RotZx", -1, +1, &selectedObject->axis2RotateZ.x);
				gui->addSlider("Angel2RotZy", -1, +1, &selectedObject->axis2RotateZ.y);
				gui->addSlider("Angel2RotZz", -1, +1, &selectedObject->axis2RotateZ.z);
			*/

				//gui->addLabelToggle("DRAWFILL", &drawFill);
				gui->autoSizeToFitWidgets();
				ofAddListener(gui->newGUIEvent,this,&ScenarioEditor::guiEvent);
				gui->loadSettings("GUI/guiSettings.xml");
				
				//gui->setVisible(false);
				
					cout << "new Gui Done" << endl;
			//}
		}
		
	}
	
	
	return bcreated;

}


//--------------------------------------------------------------
void ScenarioEditor::update(){
}

//--------------------------------------------------------------
void ScenarioEditor::draw(){
    if(bEscenarioEditorMode){
        //ofSetColor(100, 100, 100);
        string fpsStr = "Scenario Editor Mode";
        ofDrawBitmapString(fpsStr, 50,ofGetHeight()-100);
    }
}

//--------------------------------------------------------------
void ScenarioEditor::keyReleased(int key){
    
    switch(key)
    {
		case 'e':
            bEscenarioEditorMode = !bEscenarioEditorMode;
			
			if(bEscenarioEditorMode){
				scenario->removeCoverScenario();
			if(gui != NULL && bGuiPointer)gui->setVisible(true);
			}else {
				//Need to be at least once time created to be removed
				scenario->addCoverScenario(*world); //
				if(gui != NULL && bGuiPointer)gui->setVisible(false);
			}
			cout << "bScenarioEditorActive= " << bEscenarioEditorMode << endl;
            break;
        case 'x':
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
	//delete gui;

    for(int i = 0; i < scenario->ScenarioObjects.size(); i++) {
		ofxBulletBaseShape *baseShape;
        baseShape = scenario->ScenarioObjects[i]->getBulletBaseShape();
      
		if( *baseShape == e ) {
            
            selectedObject = scenario->ScenarioObjects[i];
            
            //selectedObject
            ofLogVerbose("EditorVerbose") << "ScenarioEditor::onMousePick : selected a " << scenario->ScenarioObjects[i]->getObjectName() << endl;
            
			//mousePickPos = e.pickPosWorld;
			//Save current location and current mouse
			//objPressedLoc = ofVec2f(selectedObject->position.x, selectedObject->position.y);
			mousePickLoc = ofVec2f(ofGetMouseX(), ofGetMouseY());
			
			
			//Create Personal GUI of this type OR Remove Object Touched
			if(deleteObject){
				
				cout << "Going to del Gui and Object" << endl;
				delete gui;
				cout << "Del Gui" << endl;
				bGuiPointer = false;
				
				scenario->popObject(selectedObject);
				deleteObject = false;
			}
			else {
				bgui = createGUI(selectedObject);
			}
			
			
			break; //Stop looking for objects
		}
	}
	
}

//--------------------------------------------------------
void ScenarioEditor::mouseDragged(ofMouseEventArgs &args){
   
	bool bEscenarioEditorRotation = true;
	
	
	//btTransform transform;
    //btRigidBody* a_rb = body.getRigidBody();
    //a_rb->getMotionState()->getWorldTransform( transform );
	//Apply ROTs..
	//a_rb->getMotionState()->getWorldTransform( transform );
    
    if (bEscenarioEditorMode){

			if( (gui != NULL) && (selectedObject != NULL) && bGuiPointer ){
				if(gui->isHit(args.x, args.y) == false){ // BAD ACCES While moving Objects out of Shape Collision
					
						ofVec3f newPos = selectedObject->position;
						newPos.x = newPos.x + (args.x - mouseOldPosition.x)/50;
						newPos.y = newPos.y + (args.y - mouseOldPosition.y)/50;
						selectedObject -> position = newPos;
						selectedObject -> setPosition(newPos);
					
					mouseOldPosition = args;
				}
			}
    }

	
	/* TODO to ROT
	ofQuaternion objectRotation = selectedObject->rotation;
	
	float newRotX = objectRotation.x() + (args.x - mouseOldPosition.x)/50;
	float newRotY = objectRotation.y() + (args.y - mouseOldPosition.y)/50;
	float newRotZ = objectRotation.z();
	float newRotW = objectRotation.w();
	
	objectRotation.set(newRotX, newRotY, newRotZ, newRotW);
	
	selectedObject->setRotation(objectRotation);
	*/
	
    /*
	if(bEscenarioEditorMode){
		ofVec2f mousePos = ofVec2f(args.x, args.y);
		ofVec2f mouseDir = mousePickLoc - mousePos;
		mouseDir.normalize();
		
		ofVec3f newPos;
		if (selectedObject != NULL){
			
			newPos = selectedObject->position;
			//newPos.x = newPos.x + (args.x/1000);
			//newPos.y = newPos.y + (args.y/1000);
			newPos += 0.1* mouseDir;
			
			ofLogVerbose("EditorVerbose") << "mouseDragged, newpos = " << newPos << " mouseDir =" << mouseDir << endl;
			
			selectedObject -> position = newPos;
			selectedObject -> setPosition(newPos);
		}
	}
     */
}

//--------------------------------------------------------
void ScenarioEditor::mouseMoved(ofMouseEventArgs &args){
    
}

//--------------------------------------------------------
void ScenarioEditor::mousePressed(ofMouseEventArgs &args){
	
	if(bEscenarioEditorMode){
		///deactivate camera mouse events //can be added more params to do this action in eventMoveObjectScenario
		eventMoveObjectScenario newMoveObjectEvent;
        newMoveObjectEvent.bMovingObject = true;
        ofNotifyEvent(eventMoveObjectScenario::onMoveObject, newMoveObjectEvent);
	
		if(bgui){
			if(args.button == 2){
				gui->setPosition(args.x, args.y);
				gui->setVisible(true);
				return;
			}
			
			if(!gui->isHit(args.x, args.y)){
				gui->setVisible(false);
			}
		}
	}
    
    mouseOldPosition = args;
}



//--------------------------------------------------------
void ScenarioEditor::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    //	int kind = e.widget->getKind();
    if (name == "PRESS & PICK TO DELETE IT"){

    }else if(name == "SAMPLER"){
        ofxUIImageSampler *is = (ofxUIImageSampler *) e.widget;
        ofColor clr = is->getColor();
        //red = clr.r;
        //blue = clr.b;
        //green = clr.g;
        clr.getHex();
    }
}


//--------------------------------------------------------
void ScenarioEditor::mouseReleased(ofMouseEventArgs &args){
    
	if(bEscenarioEditorMode){
		///deactivate camera mouse events //can be added more params to do this action in eventMoveObjectScenario
		eventMoveObjectScenario newMoveObjectEvent;
        newMoveObjectEvent.bMovingObject = false;
        ofNotifyEvent(eventMoveObjectScenario::onMoveObject, newMoveObjectEvent);
		
		//free the selectedObject
		selectedObject = NULL;
	}
	
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