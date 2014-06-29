//
//  PinballChinoManager.cpp
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//

#include "PinballChinoManager.h"
#include "Ball.h"
#include "eventComunication.h"

PinballChinoManager::PinballChinoManager():statusDisplay(ofGetWidth() - 300,ofGetHeight() - 150){
  currentMission = new SimpleMission(1);  
}

//--------------------------------------------------------------
void PinballChinoManager::setup(){
    
    

    // setup bullet world
	world.setup();
	world.setGravity( ofVec3f(0, 4, 7) );

    // setup camera
	camera.setPosition(ofVec3f(0, -2, -15.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    camera.setDistance(20);
	world.setCamera(&camera);
    
    
    // load camera position
    savedPose = loadCameraPosition(); 
    camera.setTransformMatrix(savedPose);
    
    // setup scenario
    myScenario.setCurrentMission(currentMission);
    myScenario.setup(world);
    
    // setup scenario editor
    ScenarioEditor::getInstance()->setup(world, myScenario);
    
    // collision detection
    world.enableCollisionEvents();

	// Arduino Comunication
	arduCom.setup();
	
	// Listeners
	ofAddListener(world.COLLISION_EVENT, this, &PinballChinoManager::onCollision);
	
	ofAddListener(eventObjectScenario::onNewObject ,this, &PinballChinoManager::listenerAddObject2Scenario);
	
	ofAddListener(eventMoveObjectScenario::onMoveObject ,this, &PinballChinoManager::listenerMovingObjectScenario);
    
   
    
    bDrawDebug = false;
    
    
    
    
}

//--------------------------------------------------------------
void PinballChinoManager::update(){
	
	world.update();
    
    myScenario.update(ScenarioEditor::getInstance()->bEscenarioEditorMode);
	
	InputEventManager::update(); // Key Events
    
    dmx.update();
	
	//Arduino
	arduCom.update(this);
    
    //check if ball inside box
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 0)
        {
            Ball* ball = (Ball*) myScenario.ScenarioObjects[i];
            if (!ball->isInsideBox(myScenario.ballLimitsBoxSize))
                onRestartGameEvent();
        }
    }

    currentMission->update();
    
}

//--------------------------------------------------------------
void PinballChinoManager::draw(){
    
	glEnable( GL_DEPTH_TEST );
	camera.begin();
    
    /* set light position 
     Tip: we could move it in setup if we will not change the position of the light at runtime
     */
    light.setPosition(myScenario.lightPos);

    
	ofEnableLighting();
	light.enable();
    

    // debug draw
    if(bDrawDebug){
        //myScenario.drawDebug();
        
        world.drawDebug();
        // draw the box that is used to detect if the ball is outside the scenario
        ofNoFill();
        ofDrawBox(0, 0, 0, myScenario.ballLimitsBoxSize);
        ofDrawSphere(myScenario.lightPos, 2);
        ofFill();
         
    }
	
    myScenario.draw(ScenarioEditor::getInstance()->bEscenarioEditorMode);
    
	
	light.disable();
	ofDisableLighting();
    
	camera.end();
    glDisable(GL_DEPTH_TEST);
    
    statusDisplay.draw();
    missionDisplay.draw();
    
    ScenarioEditor::getInstance()->draw();
    
    if(bDrawDebug){

        currentMission->debugDraw();
    }
}

void PinballChinoManager::ToggleDrawDebug(void){
    bDrawDebug = !bDrawDebug;
    statusDisplay.show3dfont = !statusDisplay.show3dfont;
    //myScenario.setDebugMode(bDrawDebug);
}

//--------------------------------------------------------------
void PinballChinoManager::onRestartGameEvent(void){
    
    //reset ball
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 0)
        {
            Ball* ball = (Ball*) myScenario.ScenarioObjects[i];
            
            for(int j = 0; j < myScenario.ScenarioObjects.size(); j++)
            {
                if (myScenario.ScenarioObjects[j]->type == 5)
                {
                    Hammer* hammer = (Hammer*) myScenario.ScenarioObjects[j];
                    ofVec3f pos;
                    pos.set(hammer->position.x,hammer->position.y-5,hammer->position.z);
                    ball->setPosition(pos);
                }
            }
            
            ball->reset();
        }
    }
    
    //do other stuff that should be done whe restaring game score stuff etc
    
    currentMission->resetMission();
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveLeftLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            Lever* lever = (Lever*) myScenario.ScenarioObjects[i];
            if (!lever->direction) lever->onMoveEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseLeftLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            Lever* lever = (Lever*) myScenario.ScenarioObjects[i];
            if (!lever->direction) lever->onReleaseEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveRightLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            Lever* lever = (Lever*) myScenario.ScenarioObjects[i];
            if (lever->direction) lever->onMoveEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseRightLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            Lever* lever = (Lever*) myScenario.ScenarioObjects[i];
            if (lever->direction) lever->onReleaseEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveBallLauncherEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 5)
        {
            Hammer* hammer = (Hammer*) myScenario.ScenarioObjects[i];
            hammer->onMoveEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseBallLauncherEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 5)
        {
            Hammer* hammer = (Hammer*) myScenario.ScenarioObjects[i];
            hammer->onReleaseEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::saveCameraPosition(ofMatrix4x4 _camPose)
{
	cout << "saveCameraPosition ?? " << endl;
	
	//_camPose = cam.getTarget().getGlobalTransformMatrix();
	ofxXmlSettings *XML = new ofxXmlSettings("cameraSettings.xml");
    XML->setValue("_camPose_00", _camPose(0,0), 0); XML->setValue("_camPose_01", _camPose(0,1), 0); XML->setValue("_camPose_02", _camPose(0,2), 0); XML->setValue("_camPose_03", _camPose(0,3), 0);
    XML->setValue("_camPose_10", _camPose(1,0), 0); XML->setValue("_camPose_11", _camPose(1,1), 0); XML->setValue("_camPose_12", _camPose(1,2), 0); XML->setValue("_camPose_13", _camPose(1,3), 0);
    XML->setValue("_camPose_20", _camPose(2,0), 0); XML->setValue("_camPose_21", _camPose(2,1), 0); XML->setValue("_camPose_22", _camPose(2,2), 0); XML->setValue("_camPose_23", _camPose(2,3), 0);
    XML->setValue("_camPose_30", _camPose(3,0), 0); XML->setValue("_camPose_31", _camPose(3,1), 0); XML->setValue("_camPose_32", _camPose(3,2), 0); XML->setValue("_camPose_33", _camPose(3,3), 0);
	//XML->setValue("distance", cam.getDistance(), 0);
	XML->saveFile("cameraSettings.xml");
    delete XML;
	
	cout << "end saveCameraPosition ?? " << endl;
}

//--------------------------------------------------------------
ofMatrix4x4 PinballChinoManager::loadCameraPosition()
{
	ofMatrix4x4 _camPose;
	
	string message = "loading cameraSettings.xml";
	if( XML.loadFile("cameraSettings.xml") ){
		message = "cameraSettings.xml loaded!";
	}else{
		message = "unable to load cameraSettings.xml check data/ folder";
	}
	cout << "Loading Camera position" << message << endl;
	
	
	_camPose(0,0)= XML.getValue("_camPose_00",0.0, 0); _camPose(0,1)= XML.getValue("_camPose_01",0.0, 0); _camPose(0,2)= XML.getValue("_camPose_02",0.0, 0); _camPose(0,3)= XML.getValue("_camPose_03",0.0, 0);
	_camPose(1,0)= XML.getValue("_camPose_10",0.0, 0); _camPose(1,1)= XML.getValue("_camPose_11",0.0, 0); _camPose(1,2)= XML.getValue("_camPose_12",0.0, 0); _camPose(1,3)= XML.getValue("_camPose_13",0.0, 0);
	_camPose(2,0)= XML.getValue("_camPose_20",0.0, 0); _camPose(2,1)= XML.getValue("_camPose_21",0.0, 0); _camPose(2,2)= XML.getValue("_camPose_22",0.0, 0); _camPose(2,3)= XML.getValue("_camPose_23",0.0, 0);
	_camPose(3,0)= XML.getValue("_camPose_30",0.0, 0); _camPose(3,1)= XML.getValue("_camPose_31",0.0, 0); _camPose(3,2)= XML.getValue("_camPose_32",0.0, 0); _camPose(3,3)= XML.getValue("_camPose_33",0.0, 0);
	//cam.setDistance(XML.getValue("distance",0.0, 0));
	printf("(%.4f,%.4f,%.4f,%.4f)\n ", _camPose(0,0), _camPose(0,1), _camPose(0,2), _camPose(0,3));
	printf("(%.4f,%.4f,%.4f,%.4f)\n ", _camPose(1,0), _camPose(1,1), _camPose(1,2), _camPose(1,3));
	printf("(%.4f,%.4f,%.4f,%.4f)\n ", _camPose(2,0), _camPose(2,1), _camPose(2,2), _camPose(2,3));
	printf("(%.4f,%.4f,%.4f,%.4f)\n ", _camPose(3,0), _camPose(3,1), _camPose(3,2), _camPose(3,3));
	
	//cam.getTarget().setTransformMatrix(_camPose);
	return _camPose;
}

//--------------------------------------------------------------
void PinballChinoManager::keyReleased(int key){
	
    switch(key)
    {
        case 'f':
            bFullScreen = !bFullScreen;
            ofSetFullscreen(bFullScreen);
            break;
            
        case 's':
            savedPose = camera.getGlobalTransformMatrix();
            saveCameraPosition(savedPose); // ideal to save on XML
            cout << "saved camera Pose xml" << endl;
            break;
	
        case 'l':
            savedPose = loadCameraPosition(); // write over the savedCamPose var
            camera.setTransformMatrix(savedPose);
            cout << "load camera Pose xml" << endl;
            break;
    }
    
    InputEventManager::keyReleased(key);
   
	ScenarioEditor::getInstance()->keyReleased(key);
    
}


//--------------------------------------------------------------
void PinballChinoManager::onCollision(ofxBulletCollisionData& cdata)
{
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if(*myScenario.ScenarioObjects[i]->getBulletBaseShape() == cdata)
        {
            ofLogVerbose("CollisionVerbose") << "PinballChinoManager::onCollision : " << myScenario.ScenarioObjects[i]->getObjectName() << endl;
            myScenario.ScenarioObjects[i]->onCollision();
            currentMission->OnCollision(myScenario.ScenarioObjects[i]->GetObjectId()); //call the mission OnCollision and pass the ID of the colisioned object
		}
	}
}

////////////////////////////////////////////////////////////////////////
//listener events

//------------------------------
//Add Object
void PinballChinoManager::listenerAddObject2Scenario(eventObjectScenario & args){
	myScenario.pushObject(world, args.type, args.posObject);
}

//------------------------------
//Activat / Deactivate Camera mouse events
void PinballChinoManager::listenerMovingObjectScenario(eventMoveObjectScenario & args){

	if(args.bMovingObject){
		camera.disableMouseInput();
	}
	else{
		camera.enableMouseInput();
	}
	
}

