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

string PinballChinoManager::projectName = "";

//-------------------------------------------------------------
PinballChinoManager::PinballChinoManager():
            statusDisplay(ofGetWidth() - 300,ofGetHeight() - 150)
{
//  currentMission = new SimpleMission(1);
	
    string message = "loading project name";
	if( XML.loadFile("projectSettings.xml") ){
		message = "projectSettings.xml loaded!";
	}else{
		message = "unable to load projectSettings.xml check folder data/" + projectName;
	}
	cout << "Loading projectSettings.xml" << message << endl;
	
	
	projectName = XML.getValue("PROJECT_NAME","", 0);
    bAddScenarioCover = XML.getValue("ADD_SCENARIO_COVER",0, 0);
    m_bLinkInitialBallPositionToHammer = XML.getValue("LINK_INITIAL_BALL_POS_TO_HAMMER",0, 0);

	SimpleMission* mission0 = new SimpleMission(0);
	idcurrentMission = 0;
	SimpleMission* mission1 = new SimpleMission(1);
	SimpleMission* mission2 = new SimpleMission(2);
	
	
	currentMissions.push_back(mission1);
	currentMissions.push_back(mission2);
}

PinballChinoManager::~PinballChinoManager(){
	
}
//--------------------------------------------------------------
void PinballChinoManager::setup(){
    
    

    // setup bullet world
	world.setup();
	world.setGravity( ofVec3f(0, 10, 17) );
    // setup camera
	camera.setPosition(ofVec3f(0, -2, -15.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    camera.setDistance(20);
	world.setCamera(&camera);
    
    
    // load camera position
    savedPose = loadCameraPosition(); 
    camera.setTransformMatrix(savedPose);
    
    // setup scenario
	myScenario.setupMissions(&currentMissions);
	myScenario.setCurrentMission(idcurrentMission);
    myScenario.setup(world, bAddScenarioCover);
    
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
    
    chinoLights.setup();
	
	
	//Shadows
	//simple_shadow.setup(&camera);
	

    webSock.setup(this);
    
}

//--------------------------------------------------------------
void PinballChinoManager::update(){
	
	// Shadows
	//updating shadow color using mouse position
	//ofColor shadow_color = ofFloatColor(0.1);
	//simple_shadow.setShadowColor( shadow_color );
	//simple_shadow.setLightPosition(myScenario.lightPos);

	
	world.update();
    chinoLights.update();
    
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

    (currentMissions)[idcurrentMission]->update();
    
    
}

//--------------------------------------------------------------
void PinballChinoManager::draw(){
    
	
	camera.begin();
	glEnable( GL_DEPTH_TEST );
    
   
    chinoLights.setMainLightPosition(myScenario.lightPos);
    
    
	ofEnableLighting();
    chinoLights.enable();
    

    // debug draw
    if(bDrawDebug){
        //myScenario.drawDebug();
        
        world.drawDebug();
        // draw the box that is used to detect if the ball is outside the scenario
        ofNoFill();
        ofDrawBox(0, 0, 0, myScenario.ballLimitsBoxSize);
		//cout << "PinballChinoManager ballLimitsBoxSize = " << myScenario.ballLimitsBoxSize << endl;
        ofDrawSphere(myScenario.lightPos, 2);
        ofFill();
         
    }
	
	//Draw Scenario
	myScenario.draw(ScenarioEditor::getInstance()->bEscenarioEditorMode);
	
	chinoLights.disable();
	ofDisableLighting();

 
	glDisable(GL_DEPTH_TEST);
	camera.end();

    statusDisplay.draw();
    missionDisplay.draw();
    
    ScenarioEditor::getInstance()->draw();
    
    if(bDrawDebug){

        (currentMissions)[idcurrentMission]->debugDraw();
    }
    
    chinoLights.draw();
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
                    if(m_bLinkInitialBallPositionToHammer){
                        pos.set(hammer->getPosition().x,hammer->getPosition().y-5,hammer->getPosition().z);
                    }
                    else{
                        pos.set(ball->getInitialPos());
                    }
                    ball->setPosition(pos);
                }
            }
            
            ball->reset();
        }
    }
    
    //do other stuff that should be done whe restaring game score stuff etc
    
	/* reset current mission */
    (currentMissions)[idcurrentMission]->resetMission();
	if(GameStatus::getInstance()->Death()){
		GameStatus::getInstance()->NewPlayer();
		statusDisplay.GameOver();
		
		//Send new envet
		SoundManager::getInstance()->PlaySound(7); // Pierde Sound
	}
	else{
		//Send Dramatic event sound
		SoundManager::getInstance()->PlaySound(7); // Pierde Sound
	}
	
	
	
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveLeftLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            Lever* lever = (Lever*) myScenario.ScenarioObjects[i];
            if (!lever->getLeverAttr()->direction) lever->onMoveEvent();
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
            if (!lever->getLeverAttr()->direction) lever->onReleaseEvent();
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
            if (lever->getLeverAttr()->direction) lever->onMoveEvent();
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
            if (lever->getLeverAttr()->direction) lever->onReleaseEvent();
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
	ofxXmlSettings *XML = new ofxXmlSettings(projectName+"/cameraSettings.xml");
    XML->setValue("_camPose_00", _camPose(0,0), 0); XML->setValue("_camPose_01", _camPose(0,1), 0); XML->setValue("_camPose_02", _camPose(0,2), 0); XML->setValue("_camPose_03", _camPose(0,3), 0);
    XML->setValue("_camPose_10", _camPose(1,0), 0); XML->setValue("_camPose_11", _camPose(1,1), 0); XML->setValue("_camPose_12", _camPose(1,2), 0); XML->setValue("_camPose_13", _camPose(1,3), 0);
    XML->setValue("_camPose_20", _camPose(2,0), 0); XML->setValue("_camPose_21", _camPose(2,1), 0); XML->setValue("_camPose_22", _camPose(2,2), 0); XML->setValue("_camPose_23", _camPose(2,3), 0);
    XML->setValue("_camPose_30", _camPose(3,0), 0); XML->setValue("_camPose_31", _camPose(3,1), 0); XML->setValue("_camPose_32", _camPose(3,2), 0); XML->setValue("_camPose_33", _camPose(3,3), 0);
	//XML->setValue("distance", cam.getDistance(), 0);
    //	XML->setValue("fov", cam.getFov(), 0);
	XML->saveFile(projectName+"/cameraSettings.xml");
    delete XML;
	
	cout << "end saveCameraPosition ?? " << endl;
}

//--------------------------------------------------------------
void PinballChinoManager::saveCameraFov(float fov)
{
	cout << "saveCameraFov " << endl;
	
	ofxXmlSettings *XML = new ofxXmlSettings(projectName+"/cameraSettings.xml");
    XML->setValue("fov", fov, 0); 	//XML->setValue("distance", cam.getDistance(), 0);
    //	XML->setValue("fov", cam.getFov(), 0);
	XML->saveFile(projectName+"/cameraSettings.xml");
    delete XML;
	
	cout << "end saveCameraFov " << endl;
}

//--------------------------------------------------------------
ofMatrix4x4 PinballChinoManager::loadCameraPosition()
{
	ofMatrix4x4 _camPose;
	
	string message = "loading cameraSettings.xml";
	if( XML.loadFile(projectName+"/cameraSettings.xml") ){
		message = projectName+"/cameraSettings.xml loaded!";
	}else{
		message = "unable to load cameraSettings.xml check folder data/" + projectName;
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
float PinballChinoManager::loadCameraFov()
{
	float fov;
	
	string message = "loading cameraSettings.xml";
	if( XML.loadFile(projectName+"/cameraSettings.xml") ){
		message = projectName+"/cameraSettings.xml loaded!";
	}else{
		message = "unable to load cameraSettings.xml check folder data/" + projectName;
	}
	cout << "Loading Camera position" << message << endl;
	
	
	fov = XML.getValue("fov",0.0, 0);
	printf("(%.4f)\n ", fov);
	
	//cam.getTarget().setTransformMatrix(_camPose);
	return fov;
}

//--------------------------------------------------------------
void PinballChinoManager::keyReleased(int key){
	
	int amountX = 1;
	
    switch(key)
    {
        case 'f':
            bFullScreen = !bFullScreen;
            ofSetFullscreen(bFullScreen);
            break;
            
        case 's':
            savedPose = camera.getGlobalTransformMatrix();
            saveCameraPosition(savedPose); // ideal to save on XML
            saveCameraFov(camera.getFov());
            cout << "saved camera Pose xml" << endl;
            break;
	
        case 'l':
            savedPose = loadCameraPosition(); // write over the savedCamPose var
            camera.setTransformMatrix(savedPose);
            camera.setFov(loadCameraFov());
            cout << "load camera Pose xml" << endl;
            break;
		case 'n':
			SoundManager::getInstance()->TogleMute();
            break;

		case 'o':
			cout << "camera.getPosition().x = " << camera.getPosition().x << endl;
				camera.move(+amountX, 0, 0);
			break;
			
		case 'p':
			cout << "camera.getPosition().x = " << camera.getPosition().x << endl;
				camera.move(-amountX, 0, 0);
			break;
		case 'i':
			cout << "camera.getPosition().z = " << camera.getPosition().z << endl;
			camera.move(0, 0, +amountX);
			break;
			
		case 'k':
			cout << "camera.getPosition().z = " << camera.getPosition().z << endl;
			camera.move(0, 0, -amountX);
			break;
		case 'u':
			cout << "camera.getPosition().y = " << camera.getPosition().y << endl;
			camera.move(0, +amountX, 0);
            
            
            //works no matter what is pressed first
            if(ofGetKeyPressed(OF_KEY_CONTROL) && ofGetKeyPressed(OF_KEY_SHIFT)){
                cout<<"shift "<<ofGetFrameNum()<<endl;
            }
            
			break;
			
		case 'j':
			cout << "camera.getPosition().y = " << camera.getPosition().y << endl;
			camera.move(0, -amountX, 0);
			break;
			
		case 'c':
			cout << "movement of the camera ";
			if (camera.getMouseInputEnabled())
            {
                camera.disableMouseInput();
                cout << "disabled" << endl;
            }
            else
            {
                camera.enableMouseInput();
                cout << "enabled" << endl;
            }
			break;
			
			//Hack a simple mission
			//myScenario.ScenarioObjects[11]->onCollision();
			//myScenario.ScenarioObjects[12]->onCollision();
			//myScenario.ScenarioObjects[13]->onCollision();
            
			
		case 'U':
            camera.setFov(camera.getFov() + 1);
            camera.dolly(-1);
			cout << "FOV: " << camera.getFov() << endl;
			break;
			
		case 'J':
            camera.setFov(camera.getFov() - 1);
            camera.dolly(1);
			cout << "FOV: " << camera.getFov() << endl;
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
			SimpleObject *object2 = myScenario.FindScenarioObjectByRigidBody(cdata.body2);
            myScenario.ScenarioObjects[i]->onCollision(object2);
            (currentMissions)[idcurrentMission]->OnCollision(myScenario.ScenarioObjects[i]->GetObjectId()); //call the mission OnCollision and pass the ID of the colisioned object
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

