//
//  PinballChinoManager.cpp
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//

#include "PinballChinoManager.h"
#include "Ball.h"

PinballChinoManager::PinballChinoManager():statusDisplay(20,60){
    
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
    cout << "load camera Pose xml" << endl;
    
    // setup scenario
    myScenario.setup(world);
    
    // setup scenario editor
    scenarioEditor.setup(world, myScenario);
    
    // collision detection
    world.enableCollisionEvents();
	ofAddListener(world.COLLISION_EVENT, this, &PinballChinoManager::onCollision);
    
}

//--------------------------------------------------------------
void PinballChinoManager::update(){
	
	world.update();
    
    myScenario.update();
    
}

//--------------------------------------------------------------
void PinballChinoManager::draw(){
    
	glEnable( GL_DEPTH_TEST );
	camera.begin();
    
//	ofEnableLighting();
//	light.enable();
    
    
    // debug draw
	world.drawDebug();
	
    myScenario.draw();
    
	
//	light.disable();
//	ofDisableLighting();
    
	camera.end();
    glDisable(GL_DEPTH_TEST);
    
    statusDisplay.draw();
    
}


//--------------------------------------------------------------
void PinballChinoManager::onRestartGameEvent(void){
    
    //reset ball & objects
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
        myScenario.ScenarioObjects[i]->reset();
    
    //do other stuff that should be done whe restaring game score stuff etc
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveLeftLeverEvent(void){
    
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if (myScenario.ScenarioObjects[i]->type == 3)
        {
            //            Lever lever = myScenario.ScenarioObjects[i];
            //            lever.onMoveEvent();
        }
    }
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseLeftLeverEvent(void){
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveRightLeverEvent(void){
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseRightLeverEvent(void){
    
}

//--------------------------------------------------------------
void PinballChinoManager::onMoveBallLauncherEvent(void){
    
}

//--------------------------------------------------------------
void PinballChinoManager::onReleaseBallLauncherEvent(void){
    
}

//--------------------------------------------------------------
void PinballChinoManager::saveCameraPosition(ofMatrix4x4 _camPose)
{
	//_camPose = cam.getTarget().getGlobalTransformMatrix();
	ofxXmlSettings *XML = new ofxXmlSettings("cameraSettings.xml");
    XML->setValue("_camPose_00", _camPose(0,0), 0); XML->setValue("_camPose_01", _camPose(0,1), 0); XML->setValue("_camPose_02", _camPose(0,2), 0); XML->setValue("_camPose_03", _camPose(0,3), 0);
    XML->setValue("_camPose_10", _camPose(1,0), 0); XML->setValue("_camPose_11", _camPose(1,1), 0); XML->setValue("_camPose_12", _camPose(1,2), 0); XML->setValue("_camPose_13", _camPose(1,3), 0);
    XML->setValue("_camPose_20", _camPose(2,0), 0); XML->setValue("_camPose_21", _camPose(2,1), 0); XML->setValue("_camPose_22", _camPose(2,2), 0); XML->setValue("_camPose_23", _camPose(2,3), 0);
    XML->setValue("_camPose_30", _camPose(3,0), 0); XML->setValue("_camPose_31", _camPose(3,1), 0); XML->setValue("_camPose_32", _camPose(3,2), 0); XML->setValue("_camPose_33", _camPose(3,3), 0);
	//XML->setValue("distance", cam.getDistance(), 0);
	XML->saveFile("cameraSettings.xml");
    delete XML;
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
    
    InputEventManager::keyReleased(key);
    
//	if (key=='c')
//		camera.toggleCursorDraw();
	
//	if (key=='u')
//		camera.toggleFixUpwards();
	
    switch(key)
    {
        case 'b': // Adding Obstacle to the world
            //        myScenario.pushObject(world, 6, camera.getCursorWorld());
            myScenario.pushObject(world, 6, ofVec3f(0, 0, 0));
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
	
        case 'e':
            myScenario.saveToXml();
            cout << "saving scenario to Xml" << endl;
            break;
            
        case 'f':
            bFullScreen = !bFullScreen;
            ofSetFullscreen(bFullScreen);
            break;
            
    }
    
}


//--------------------------------------------------------------
void PinballChinoManager::onCollision(ofxBulletCollisionData& cdata)
{
    for(int i = 0; i < myScenario.ScenarioObjects.size(); i++)
    {
        if(*myScenario.ScenarioObjects[i]->getBulletBaseShape() == cdata)
        {
//            if (myScenario.ScenarioObjects[i]->type == 0) continue; // ball
//            ofLogVerbose("CollisionVerbose") << "PinballChinoManager::onCollision : " << myScenario.ScenarioObjects[i]->getObjectName() << endl;
            myScenario.ScenarioObjects[i]->onCollision();
		}
	}
}