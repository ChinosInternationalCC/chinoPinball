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
	
	 
	 guiBasicScenario = NULL;
	 createBasicGUIScenario();
	 bVisibleBasicTerrain = true;
	 
	 bEditorMode = false;
	 lastbEditorMode = true;
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
    if (bAddScenarioCover){
        loadBasicScenario(_world, ofVec3f(0,0,0));
        addCoverScenario(_world);
	}
	
	
	//Load XML values
	
	
    //ballLimitsBoxSize = 25; // the size of the box that is used to detect is the ball is outside the scenario
    
    /* set light position */
    lightPos = ofVec3f(0, 10, -15.f);
	
	//copy a reference
	//world = _world;
    DebugMode = false;

}

//--------------------------------------------------------------
void Scenario::setDebugMode(bool &DebugMode){
    this->DebugMode = DebugMode;
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->setDebugMode(DebugMode);
    }
    
}

//--------------------------------------------------------------
void Scenario::addCoverScenario(ofxBulletWorldRigid &world){
	/*
	bounds.push_back( new ofxBulletBox() );
	startLoc.set(0, 0, -2*heightbkPlane);
	dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
	
	bounds[lastPosIdCoverScenario]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
	bounds[lastPosIdCoverScenario]->setProperties(.95, .5);
	bounds[lastPosIdCoverScenario]->add();
	 */
	
}

//--------------------------------------------------------------
void Scenario::removeCoverScenario(){
   /* if (bounds.size() > 0){
        bounds[lastPosIdCoverScenario]->removeRigidBody();
        bounds.erase(bounds.begin()+lastPosIdCoverScenario);
    }
	*/
}


//--------------------------------------------------------------
void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
   /*
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
	*/

	
	

}

//--------------------------------------------------------------
void Scenario::update(bool _bEditorMode){
	
	bEditorMode = _bEditorMode;
	
    //TODO Check this if its not being usefull pass all time that boolean , also that for and try to Optimiza
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->update(bEditorMode);
    }
	
	
	
	///Crappy Toogle Gui Visibility
	if(bEditorMode == true){
		if (lastbEditorMode == false) {
			guiBasicScenario->toggleVisible();
		}
	}else{
		if (lastbEditorMode == true) {
			guiBasicScenario->toggleVisible();
		}
	}
	
	lastbEditorMode = bEditorMode;
    
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
	
	/*
	//Draw the basic scneario ground
	if(bVisibleBasicTerrain){
		
		if(bounds.size()>0){
			material.begin();
			bounds[0]->draw();
			material.end();
		}
	}
	 */
	
    
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
    switch(typeObject){

        case SimpleObject::ShapeTypeBall:{
            Ball *oBall = new Ball(currentMissions, 0.5);
            BallAttrib *poBallAttrib = new BallAttrib(pos,0, 1, 0.25, 0.44, 0.25); // damping not used  so we use 0...
            oBall->setup(world, (SimpleObjectAttrib*) poBallAttrib);
            oBall->setDefaultZ();
            ScenarioObjects.push_back(oBall);
        }
        break;
            
        case SimpleObject::ShapeTypeHammer:{
            Hammer *oHammer = new Hammer(currentMissions);
            SimpleObjectAttrib *poAttrib = new SimpleObjectAttrib();
            oHammer->setup(world, poAttrib);
            oHammer->setDefaultZ();
            ScenarioObjects.push_back(oHammer);
        }
        break;
            
        case SimpleObject::ShapeTypeLever:{
            Lever *oLever = new Lever(currentMissions);
            int dir = 0;
            LeverAttrib *poAttr = new LeverAttrib();
            oLever->setup(world, (SimpleObjectAttrib*) poAttr);
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

*/

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

		//ScenarioXml.pushTag("ScenarioBoxArea");PT:X
		ballLimitsBoxSize = ScenarioXml.getValue("ScenarioBoxArea",0.0, 0);
		cout << " ballLimitsBoxSize loaded = " << ballLimitsBoxSize << endl;
		ScenarioXml.popTag();
        
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
                    float radius = ScenarioXml.getValue("radius", 0.0);
                    Ball *oBall = new Ball(currentMissions, radius);
					
					float mass = ScenarioXml.getValue("mass", 0.0);
                    float restitution = ScenarioXml.getValue("restitution", 0.0);
                    float friction = ScenarioXml.getValue("friction", 0.0);

					
					BallAttrib *ballAttrib = new BallAttrib("",		//string 3dmodelPath
															pos,	//position
															0,		//damping
															friction,//friction
															mass,	//mass
															restitution,
															radius,
															ofVec3f(0,0,0));

					
                    oBall->setup(world, ballAttrib);
                    oBall->SetObjectId(objId);
					oBall->setPhysicsRotation(rotation);
                    oBall->color = color;
					oBall->setVisibility(invisible);
					
                    ScenarioObjects.push_back(oBall);
                }
                break;
                    
                case SimpleObject::ShapeTypeHammer:{
                    Hammer *oHammer = new Hammer(currentMissions);
					
					SimpleObjectAttrib *Attrib = new SimpleObjectAttrib("", pos, 0, 0, 0, 0, ofVec3f(0,0,0));
                    oHammer->setup(world, Attrib);
                    oHammer->SetObjectId(objId);
					oHammer->setPhysicsRotation(rotation);
                    oHammer->color = color;
					oHammer->setVisibility(invisible);
                    ScenarioObjects.push_back(oHammer);
					
					oHammer->setupRot();
                }
                break;
                    
                case SimpleObject::ShapeTypeLever:{
                    Lever *oLever = new Lever(currentMissions);

                    int dir = ScenarioXml.getValue("LeverType", 0);
					//pos, path, scale, dir
					LeverAttrib *Attrib = new LeverAttrib(path, //string _modelData,
														  pos,	//ofVec3f _position,
														  0,	//float _damping,
														  0,	//float _friction,
														  0,	//float _mass,
														  0,	//float _restitution,
														  scale,	//ofVec3f _ModelScale,
														  dir);	//int _direction);

					
                    
                    oLever->setup(world, Attrib);
                    oLever->SetObjectId(objId);
					oLever->setPhysicsRotation(rotation);
                    oLever->color = color;
					oLever->setVisibility(invisible);
                    ScenarioObjects.push_back(oLever);

                }
                break;
                    
                case SimpleObject::ShapeTypeObstacle:{
                    Obstacle *oObstable = new Obstacle(currentMissions);
					
					ObstacleAttrib *Attrib = new ObstacleAttrib(path,
																pos,
																0,
																0,
																0,
																0,
																scale);
					
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oObstable->setup(world, Attrib);
                    oObstable->SetObjectId(objId);
					oObstable->setPhysicsRotation(rotation);
                    oObstable->color = color;
					oObstable->setVisibility(invisible);
                    ScenarioObjects.push_back(oObstable);
					oObstable->setPointsCollision(pointsCollision);
					oObstable->setupRot();

                }
                break;
                
                case SimpleObject::ShapeTypeGravity:{
                    Gravity *oGravity = new Gravity(currentMissions);
					
					ObstacleAttrib *Attrib = new ObstacleAttrib(path,
																pos,
																0,
																0,
																0,
																0,
																scale);
					
                    oGravity->setup(world, Attrib);
                    oGravity->SetObjectId(objId);
					oGravity->setPhysicsRotation(rotation);
                    oGravity->color = color;
					oGravity->setVisibility(invisible);
                    ScenarioObjects.push_back(oGravity);
					oGravity->setPointsCollision(pointsCollision);
					oGravity->setupRot();
                    
                }
                break;
                   
                case SimpleObject::ShapeTypeTeleporter:{
                    Teleporter *oTeleporter = new Teleporter(currentMissions);
					
					ObstacleAttrib *Attrib = new ObstacleAttrib(path,
																pos,
																0,
																0,
																0,
																0,
																scale);
					
                    oTeleporter->setup(world, Attrib);
                    oTeleporter->SetObjectId(objId);
					oTeleporter->setPhysicsRotation(rotation);
                    oTeleporter->color = color;
					oTeleporter->setVisibility(invisible);
					oTeleporter->RegisterScenarioRef(this);
					oTeleporter->SetDetinationObjectId(8);//TODO read this from xml
					oTeleporter->SetMultiBallStickyFlag(false); //TODO read this from xml
                    ScenarioObjects.push_back(oTeleporter);
					oTeleporter->setPointsCollision(pointsCollision);
					oTeleporter->setupRot();
                    
                }
                break;
					
				case SimpleObject::ShapeTypeRamp:{
					Ramp *oRamp = new Ramp(currentMissions);
					
					ObstacleAttrib *Attrib = new ObstacleAttrib(path,
																pos,
																0,
																0,
																0,
																0,
																scale);
					
					oRamp->setup(world, Attrib);
					oRamp->SetObjectId(objId);
					oRamp->setPhysicsRotation(rotation);
					oRamp->color = color;
					oRamp->setVisibility(invisible);
					ScenarioObjects.push_back(oRamp);
					oRamp->setPointsCollision(pointsCollision);
					oRamp->setupRot();
				}
					break;
					
                case SimpleObject::ShapeTypeAnimatedMesh:{
                    AnimatedMesh *oAnimatedMesh = new AnimatedMesh(currentMissions);
					
					AnimatedMeshAttrib *Attrib = new AnimatedMeshAttrib(path,
																pos,
																0,
																0,
																0,
																0,
																scale);
					
					
                    oAnimatedMesh->setup(world, Attrib);
                    oAnimatedMesh->SetObjectId(objId);
					oAnimatedMesh->setPhysicsRotation(rotation);
                    oAnimatedMesh->color = color;
					oAnimatedMesh->setVisibility(invisible);
                    ScenarioObjects.push_back(oAnimatedMesh);
					oAnimatedMesh->setPointsCollision(pointsCollision);
					oAnimatedMesh->setupRot();
                    
                }
                break;
					
				case SimpleObject::ShapeTypeScenario:{
					
					ScenarioObject * oScenarioObject = new ScenarioObject(currentMissions);
					
					//string _modelData,
					//ofVec3f _position,
					//float _damping,
					//float _friction,
					//float _mass,
					//float _restitution,
					//ofVec3f _ModelScale,
					//int _direction);
					
					ScenarioObjectAttrib *Attrib = new ScenarioObjectAttrib(path,
																		pos,
																		0,
																		0,
																		0,
																		0, //restitution by default to walls?
																		scale);
					
					oScenarioObject->setup(world, Attrib);
					oScenarioObject->SetObjectId(objId);
					oScenarioObject->setPhysicsRotation(rotation);
					oScenarioObject->color = color;
					oScenarioObject->setVisibility(invisible);
					ScenarioObjects.push_back(oScenarioObject);
					oScenarioObject->setPointsCollision(pointsCollision);
					oScenarioObject->setupRot();
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
	
	ScenarioXml.pushTag("scenarioBoxArea");
	ScenarioXml.addValue("ScenarioBoxArea", ballLimitsBoxSize);

	
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
        ScenarioXml.addValue("positionX", ScenarioObjects[i]->getPosition().x);
        ScenarioXml.addValue("positionY", ScenarioObjects[i]->getPosition().y);
        ScenarioXml.addValue("positionZ", ScenarioObjects[i]->getPosition().z);
        ScenarioXml.addValue("scaleX", ScenarioObjects[i]->getScale().x);
        ScenarioXml.addValue("scaleY", ScenarioObjects[i]->getScale().y);
        ScenarioXml.addValue("scaleZ", ScenarioObjects[i]->getScale().z);
		ScenarioXml.addValue("rotationX", ScenarioObjects[i]->rotation.x());
		ScenarioXml.addValue("rotationY", ScenarioObjects[i]->rotation.y());
		ScenarioXml.addValue("rotationZ", ScenarioObjects[i]->rotation.z());
		ScenarioXml.addValue("rotationW", ScenarioObjects[i]->rotation.w());
        ScenarioXml.addValue("path", ScenarioObjects[i]->getSimpleAttrib()->modelPath);
    
		
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeLever){
            Lever *pLever;
            pLever = (Lever*)ScenarioObjects[i];
            ScenarioXml.addValue("LeverType", pLever->getLeverAttr()->direction);
        }
        
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeBall){
            Ball *pBall;
            pBall = (Ball*)ScenarioObjects[i];
            ScenarioXml.addValue("mass", pBall->getBallAttr()->mass);
            ScenarioXml.addValue("radius", pBall->getBallAttr()->radius);
            ScenarioXml.addValue("restitution", pBall->getBallAttr()->restitution);
            ScenarioXml.addValue("friction", pBall->getBallAttr()->friction);
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


//--------------------------------------------------------------
void Scenario::createBasicGUIScenario(){
	
	posGui = ofVec2f(0, 0);
	guiBasicScenario = new ofxUICanvas(posGui.x, posGui.y, OFX_UI_GLOBAL_CANVAS_WIDTH, OFX_UI_GLOBAL_CANVAS_WIDTH);
	guiBasicScenario->addLabelToggle("Toggle Floor Visibility", &bVisibleBasicTerrain); // PRESS & PICK TO Toogle Visibility
	
	guiBasicScenario->addSlider("ballLimitBox", 0.0, 50.0, &ballLimitsBoxSize);
	
	guiBasicScenario->autoSizeToFitWidgets();
	ofAddListener(guiBasicScenario->newGUIEvent,this,&Scenario::guiEventBasics);
	guiBasicScenario->loadSettings("GUI/guiSettings.xml");
	
}
//--------------------------------------------------------
void Scenario::guiEventBasics(ofxUIEventArgs &e){
	string name = e.widget->getName();
	//	int kind = e.widget->getKind();
	if (name == "Toggle Floor Visibility"){
		//bVisibleBasicTerrain = !bVisibleBasicTerrain;
		cout << "bVisibleBasicTerrain invert = "  << bVisibleBasicTerrain << endl;
	}

}
//--------------------------------------------------------
vector <Ball *> Scenario::getBalls(){
	vector <Ball *> Balls;
	for(int i = 0; i < ScenarioObjects.size(); i++){
		if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeBall){
			Ball *pBall = (Ball*)ScenarioObjects[i];
			Balls.push_back(pBall);
		}
	}

	return Balls;
}
//---------------------------------------------------------
SimpleObject* Scenario::FindScenarioObjectByRigidBody(const btRigidBody* body){
	for(int i = 0; i < ScenarioObjects.size(); i++){
		if (ScenarioObjects[i]->getBulletBaseShape()->getRigidBody() == body)
			return ScenarioObjects[i];
	}
}
