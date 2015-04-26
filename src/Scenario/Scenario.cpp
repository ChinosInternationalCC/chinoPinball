//
//  Scenario.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "Scenario.h"
#include "PinballChinoManager.h"

 Scenario::Scenario(){
	scaleStage = 0.25;
	boundsWidth = 7.;;
	depthStage = 160;
	frontbackwallHeigh = 40;
	heightwalls = 20;
	
	//Ground
	widthbasePlane = 100;
	heightbasePlane = depthStage;
	depthbasePlane = boundsWidth;
	
	//BackWall
	widthbkPlane = 100;
	heightbkPlane = boundsWidth*1.5;
	depthbkPlane = frontbackwallHeigh;
	
	//RightLeftWall
	widthrlPlane = boundsWidth;
	heightrlPlane = depthStage;
	depthrlPlane = heightwalls;
}

//---------------------------------------------------
void Scenario::setCurrentMission(int _idcurrentMission){
    this->idCurrentMission = _idcurrentMission;
}

//---------------------------------------------------
void Scenario::setupMissions(vector<SimpleMission*> *vectorMission){
    this->currentMissions = vectorMission;
}

//--------------------------------------------------------------
void Scenario::setup(ofxBulletWorldRigid &_world, bool bAddScenarioCover){
    
    loadFromXml(_world);
    //loadFromJSON(world);
    //saveToJSON();
	loadBasicScenario(_world, ofVec3f(0,0,0));
    if (bAddScenarioCover)
        addCoverScenario(_world);
	
    ballLimitsBoxSize = 25; // the size of the box that is used to detect is the ball is outside the scenario
    
    /* set light position */
    lightPos = ofVec3f(0, 10, -15.f);
	
	//copy a reference
	//world = _world;
    DebugMode = false;

}

void Scenario::setDebugMode(bool &DebugMode){
    this->DebugMode = DebugMode;
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->setDebugMode(DebugMode);
    }
    
}

//--------------------------------------------------------------
void Scenario::addCoverScenario(ofxBulletWorldRigid &world){
	
	bounds.push_back( new ofxBulletBox() );
	startLoc.set(0, 0, -2*heightbkPlane);
	dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
	
	bounds[lastPosIdCoverScenario]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
	bounds[lastPosIdCoverScenario]->setProperties(.95, .5);
	bounds[lastPosIdCoverScenario]->add();
	
}

//--------------------------------------------------------------
void Scenario::removeCoverScenario(){
	bounds[lastPosIdCoverScenario]->removeRigidBody();
	bounds.erase(bounds.begin()+lastPosIdCoverScenario);
}


//--------------------------------------------------------------
void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
    
	// STATGE
	for(int i = 0; i < 5; i++) {
		bounds.push_back( new ofxBulletBox() );
		if(i == 0) { // ground //
			//startLoc.set(-widthPlane*0.5, -heightPlane*0.5, 0);
			startLoc.set(0, 0, depthbasePlane*0.5);
			dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
		} else if (i == 1) { // back wall //
			startLoc.set(0, -depthStage*0.5, -depthbasePlane*0.5);
			dimens.set(widthbkPlane, heightbkPlane, depthbkPlane);
		} else if (i == 2) { // right wall //
			startLoc.set(-widthbasePlane*0.5 , 0, -depthbasePlane*0.5);
			dimens.set(widthrlPlane, heightrlPlane, depthrlPlane);
		} else if (i == 3) { // left wall //
			startLoc.set(+widthbasePlane*0.5 , 0, -depthbasePlane*0.5);
			dimens.set(widthrlPlane, heightrlPlane, depthrlPlane);
		}
		
		bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
		bounds[i]->setProperties(.95, .3); // .25 (more restituition means more energy) , .95 ( friction )
		bounds[i]->add();
		
		lastPosIdCoverScenario = i;


	}
	
	
	
	

}

//--------------------------------------------------------------
void Scenario::update(bool bEditorMode){
    
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->update(bEditorMode);
    }
    
}

//--------------------------------------------------------------
void Scenario::draw(bool bEditorMode){
    
	ofSetColor(ofColor::white);
	
	material.begin();
	
    for(int i = 0; i < ScenarioObjects.size(); i++) {
		//CHECK if OBJECT is Visible in object properties. LOAD First from XMl that parameter
		if(ScenarioObjects[i]->bVisible){
			ScenarioObjects[i]->draw(bEditorMode);
		}

    }
	material.end();
	
	ofSetColor(ofColor::gray);
	
	//Draw the basic scneario ground
	if(bounds.size()>0){
		material.begin();
		bounds[0]->draw();
		material.end();
	}
    
	//ofDrawAxis(1);
    
}

void Scenario::drawDebug(void){
	
		material.begin();
	
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->drawDebug();
    }
		material.end();
    
}


//--------------------------------------------------------------
void Scenario::pushObject(ofxBulletWorldRigid &world, int typeObject, ofVec3f pos){
    
 //   ScenarioObjects.push_back(&m_obstable1);

/*
    ofVec3f pos;
    pos.x = ScenarioXml.getValue("positionX",0.0, 0);
    pos.y = ScenarioXml.getValue("positionY",0.0, 0);
    pos.z = ScenarioXml.getValue("positionZ",0.0, 0);
*/

    switch(typeObject){

        case SimpleObject::ShapeTypeBall:{
            Ball *oBall = new Ball(currentMissions);
            oBall->setup(world, pos);
            oBall->setDefaultZ();
            ScenarioObjects.push_back(oBall);
        }
        break;
            
        case SimpleObject::ShapeTypeHammer:{
            Hammer *oHammer = new Hammer(currentMissions);
            oHammer->setup(world, pos);
            oHammer->setDefaultZ();
            ScenarioObjects.push_back(oHammer);
        }
        break;
            
        case SimpleObject::ShapeTypeLever:{
            Lever *oLever = new Lever(currentMissions);
            int dir = 0;
            oLever->setup(world, pos, "cylinder.stl", ofVec3f(0.05, 0.05, 0.05), dir);
            oLever->setDefaultZ();
            ScenarioObjects.push_back(oLever);
        }
        break;
            
        case SimpleObject::ShapeTypeObstacle:{
            Obstacle *oObstable = new Obstacle(currentMissions);
            oObstable->setup(world, pos, "cylinder.stl", ofVec3f(0.05, 0.05, 0.05));
            oObstable->setDefaultZ();
            ScenarioObjects.push_back(oObstable);
        }
        break;
            
    }
}

//--------------------------------------------------------------
void Scenario::popAllObjects(void){
    
    while(ScenarioObjects.size()){
        SimpleObject *obj = ScenarioObjects.front();
        ScenarioObjects.erase(ScenarioObjects.begin());
        delete obj;
    }
    
}

//--------------------------------------------------------------
void Scenario::popObject(SimpleObject* obj){
    //vector<SimpleObject*>::iterator it;
    //TODO
	//SEarch the object and pop it
	for(int i = 0; i < ScenarioObjects.size(); i++) {
		if(ScenarioObjects[i] == obj){
			cout << "goig to remove i = " << i << endl;
			//ScenarioObjects.pop_back();
			ScenarioObjects.erase(ScenarioObjects.begin()+i);
            delete obj;
			break;
		}
	}
}



//--------------------------------------------------------------

void Scenario::loadFromXml(ofxBulletWorldRigid &world){
    ofxXmlSettings ScenarioXml;
    
    if(ScenarioXml.loadFile(PinballChinoManager::projectName+"/scenario.xml")){
        
        ScenarioXml.pushTag("scenario");
        
        int numberOfSavedObjects = ScenarioXml.getNumTags("object");
        
        for(int i = 0; i < numberOfSavedObjects; i++){
            
            ScenarioXml.pushTag("object", i);
            SimpleObject::shapeType Type = (SimpleObject::shapeType)ScenarioXml.getValue("type", 0);
            int objId = ScenarioXml.getValue("id", 0);
            
            
            ofVec3f pos, scale;
			
            pos.x = ScenarioXml.getValue("positionX",0.0, 0);
            pos.y = ScenarioXml.getValue("positionY",0.0, 0);
            pos.z = ScenarioXml.getValue("positionZ",0.0, 0);
            
            scale.x = ScenarioXml.getValue("scaleX",0.0, 0);
            scale.y = ScenarioXml.getValue("scaleY",0.0, 0);
            scale.z = ScenarioXml.getValue("scaleZ",0.0, 0);
			
			ofQuaternion rotation;
            ofVec4f rot;
			
			rot.x = ScenarioXml.getValue("rotationX",0.0,0);
			rot.y = ScenarioXml.getValue("rotationY",0.0,0);
			rot.z = ScenarioXml.getValue("rotationZ",0.0,0);
            rot.w = ScenarioXml.getValue("rotationW",0.0,0);
			rotation.set(rot);
			
            string path;
            path = ScenarioXml.getValue("path","", 0);
            
            //TODO uncomment the line below when the xml is properly configured
            //string strcolor = ScenarioXml.getValue("color", "0xFFFFFF", 0);
			int color = ScenarioXml.getValue("color", 0xFFFFFF, 0);
			
			int pointsCollision = ScenarioXml.getValue("pointsCollision", 0, 0);

			int invisible = 0; // Visible by default event if this value is not implemented in the Xml editor
			invisible = ScenarioXml.getValue("invisible", 0, 0);
			
            switch(Type){
                case SimpleObject::ShapeTypeBall:{
                    Ball *oBall = new Ball(currentMissions);
                    float mass = ScenarioXml.getValue("mass", 0.0);
                    float radius = ScenarioXml.getValue("radius", 0.0);
                    float restitution = ScenarioXml.getValue("restitution", 0.0);
                    float friction = ScenarioXml.getValue("friction", 0.0);
                    oBall->setup(world, pos, mass, radius, restitution, friction);
                    oBall->SetObjectId(objId);
					oBall->setRotation(rotation);
                    oBall->color = color;
					oBall->setVisibility(invisible);
					
                    ScenarioObjects.push_back(oBall);
                }
                break;
                    
                case SimpleObject::ShapeTypeHammer:{
                    Hammer *oHammer = new Hammer(currentMissions);
                    oHammer->setup(world, pos);
                    oHammer->SetObjectId(objId);
					oHammer->setRotation(rotation);
                    oHammer->color = color;
					oHammer->setVisibility(invisible);
                    ScenarioObjects.push_back(oHammer);
					
					oHammer->setupRot();
                }
                break;
                    
                case SimpleObject::ShapeTypeLever:{
                    Lever *oLever = new Lever(currentMissions);
                    int dir = ScenarioXml.getValue("LeverType", 0);
                    oLever->setup(world, pos, path, scale, dir);
                    oLever->SetObjectId(objId);
					oLever->setRotation(rotation);
                    oLever->color = color;
					oLever->setVisibility(invisible);
                    ScenarioObjects.push_back(oLever);

                }
                break;
                    
                case SimpleObject::ShapeTypeObstacle:{
                    Obstacle *oObstable = new Obstacle(currentMissions);
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oObstable->setup(world, pos, path, scale);
                    oObstable->SetObjectId(objId);
					oObstable->setRotation(rotation);
                    oObstable->color = color;
					oObstable->setVisibility(invisible);
                    ScenarioObjects.push_back(oObstable);
					oObstable->setPointsCollision(pointsCollision);
					oObstable->setupRot();

                }
                break;
                    
                case SimpleObject::ShapeTypeAnimatedObject:{
                    AnimatedObject *oAnimatedObject = new AnimatedObject(currentMissions);
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oAnimatedObject->setup(world, pos, path, scale);
                    oAnimatedObject->SetObjectId(objId);
					oAnimatedObject->setRotation(rotation);
                    oAnimatedObject->color = color;
					oAnimatedObject->setVisibility(invisible);
                    ScenarioObjects.push_back(oAnimatedObject);
					oAnimatedObject->setPointsCollision(pointsCollision);
					oAnimatedObject->setupRot();
                    
                }
                break;
                
                case SimpleObject::ShapeTypeAnimatedMotionPath:{
                    string pathMotionModel;
                    pathMotionModel = ScenarioXml.getValue("pathMotionModel","", 0);
                    AnimatedMotionPath *oAnimatedMotionPath = new AnimatedMotionPath(currentMissions);
                    oAnimatedMotionPath->setup(world, pos, path, pathMotionModel, scale);
                    oAnimatedMotionPath->SetObjectId(objId);
					oAnimatedMotionPath->setRotation(rotation);
                    oAnimatedMotionPath->color = color;
					oAnimatedMotionPath->setVisibility(invisible);
                    ScenarioObjects.push_back(oAnimatedMotionPath);
					oAnimatedMotionPath->setPointsCollision(pointsCollision);
					oAnimatedMotionPath->setupRot();
                    
                }
                break;
                    
                case SimpleObject::ShapeTypeAnimatedMesh:{
                    AnimatedMesh *oAnimatedMesh = new AnimatedMesh(currentMissions);
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oAnimatedMesh->setup(world, pos, path, scale);
                    oAnimatedMesh->SetObjectId(objId);
					oAnimatedMesh->setRotation(rotation);
                    oAnimatedMesh->color = color;
					oAnimatedMesh->setVisibility(invisible);
                    ScenarioObjects.push_back(oAnimatedMesh);
					oAnimatedMesh->setPointsCollision(pointsCollision);
					oAnimatedMesh->setupRot();
                    
                }
                break;
                case SimpleObject::ShapeTypeGeneratedMesh:{
                    GeneratedMesh *oGeneratedMesh = new GeneratedMesh(currentMissions);
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oGeneratedMesh->setup(world, pos, path, scale);
                    oGeneratedMesh->SetObjectId(objId);
					oGeneratedMesh->setRotation(rotation);
                    oGeneratedMesh->color = color;
					oGeneratedMesh->setVisibility(invisible);
                    ScenarioObjects.push_back(oGeneratedMesh);
					oGeneratedMesh->setPointsCollision(pointsCollision);
					oGeneratedMesh->setupRot();
                    
                }
                break;
                    
                case SimpleObject::ShapeTypeBounds:{
                    Bounds *oBounds = new Bounds(currentMissions);
                    oBounds->setup(world, pos, path, scale);
                    oBounds->SetObjectId(objId);
					oBounds->setRotation(rotation);
                    oBounds->color = color;
					oBounds->setVisibility(invisible);
                    ScenarioObjects.push_back(oBounds);
					
					oBounds->setupRot();
                }
                break;

            }
            ScenarioXml.popTag();
        }
        
        ScenarioXml.popTag(); //pop position
    }
    
    else{
        
        ofLogError("Scenario file did not load!");
        
    }
    
}


//------------------------------

void Scenario::saveToXml(){
    ofxXmlSettings ScenarioXml;
    ScenarioXml.addTag("scenario");
    ScenarioXml.pushTag("scenario");
    
    for(int i = 0; i < ScenarioObjects.size(); i++){
        
        ScenarioXml.addTag("object");
        ScenarioXml.pushTag("object",i);
    
        ScenarioXml.addValue("type", ScenarioObjects[i]->type);
        ScenarioXml.addValue("id", ScenarioObjects[i]->GetObjectId());
		
		//string auxColor = ofToHex(ofColor(ScenarioObjects[i]->color);
		//string resColor = auxColor.substr(2,auxColor.length());
		//resColor = ofToUpper(resColor);
        //ScenarioXml.addValue("color", "0x"+resColor);
		
		ScenarioXml.addValue("color", ScenarioObjects[i]->color);
		ScenarioXml.addValue("invisible", !ScenarioObjects[i]->bVisible);
		ScenarioXml.addValue("pointsCollision", ScenarioObjects[i]->collisionPoints);
        ScenarioXml.addValue("positionX", ScenarioObjects[i]->position.x);
        ScenarioXml.addValue("positionY", ScenarioObjects[i]->position.y);
        ScenarioXml.addValue("positionZ", ScenarioObjects[i]->position.z);
        ScenarioXml.addValue("scaleX", ScenarioObjects[i]->scale.x);
        ScenarioXml.addValue("scaleY", ScenarioObjects[i]->scale.y);
        ScenarioXml.addValue("scaleZ", ScenarioObjects[i]->scale.z);
		ScenarioXml.addValue("rotationX", ScenarioObjects[i]->rotation.x());
		ScenarioXml.addValue("rotationY", ScenarioObjects[i]->rotation.y());
		ScenarioXml.addValue("rotationZ", ScenarioObjects[i]->rotation.z());
		ScenarioXml.addValue("rotationW", ScenarioObjects[i]->rotation.w());
        ScenarioXml.addValue("path", ScenarioObjects[i]->ModelPath);
		
		if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeBounds){
			
			cout << "rotation.x()= " << ScenarioObjects[i]->rotation.x() << endl;
			cout << "rotation.y()= " << ScenarioObjects[i]->rotation.y() << endl;
			cout << "rotation.z()= " << ScenarioObjects[i]->rotation.z() << endl;
		}
		
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeLever){
            Lever *pLever;
            pLever = (Lever*)ScenarioObjects[i];
            ScenarioXml.addValue("LeverType", pLever->direction);
        }
        
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeAnimatedMotionPath){
            AnimatedMotionPath *pAnimatedMotionPath;
            pAnimatedMotionPath = (AnimatedMotionPath*)ScenarioObjects[i];
            ScenarioXml.addValue("pathMotionModel", pAnimatedMotionPath->getMotionModelPath());
        }
        
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeBall){
            Ball *pBall;
            pBall = (Ball*)ScenarioObjects[i];
            ScenarioXml.addValue("mass", pBall->mass);
            ScenarioXml.addValue("radius", pBall->radius);
            ScenarioXml.addValue("restitution", pBall->restitution);
            ScenarioXml.addValue("friction", pBall->friction);
        }
        
        ScenarioXml.popTag();
    }
    
    ScenarioXml.popTag();
    ScenarioXml.saveFile(PinballChinoManager::projectName+"/scenario.xml");
    
}

SimpleObject* Scenario::FindScenarioObjectByName(string name){
    for(int i = 0; i < ScenarioObjects.size(); i++){
        if (ScenarioObjects[i]->getObjectName().compare(name) == 0){
            return ScenarioObjects[i];
        }
    }
    return NULL;
    
}
SimpleObject* Scenario::FindScenarioObjectById(int id){
    for(int i = 0; i < ScenarioObjects.size(); i++){
        if (ScenarioObjects[i]->GetObjectId() == id){
            return ScenarioObjects[i];
        }
    }
    return NULL;
    
}
