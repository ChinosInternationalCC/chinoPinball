//
//  Scenario.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "Scenario.h"

//--------------------------------------------------------------
void Scenario::setup(ofxBulletWorldRigid &world){
    
    loadFromXml(world);
    //loadFromJSON(world);
    //saveToJSON();
    loadBasicScenario(world, ofVec3f(0,0,0));

}


//--------------------------------------------------------------
void Scenario::loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos){
	/////////////////////////////////////////////////////////////////////////////////////////
    
	// STATGE
	float scaleStage = 0.15;
	
	ofVec3f startLoc;
	ofPoint dimens;
	
	boundsWidth = 7.;
	float depthStage = 160;
	float frontbackwallHeigh = 40;
	float heightwalls = 20;
	
	//Ground
	float widthbasePlane = 100;
	float heightbasePlane = depthStage;
	float depthbasePlane = boundsWidth;
	
	//BackWall
	float widthbkPlane = 100;
	float heightbkPlane = boundsWidth*1.5;
	float depthbkPlane = frontbackwallHeigh;
	
	//RightLeftWall
	float widthrlPlane = boundsWidth;
	float heightrlPlane = depthStage;
	float depthrlPlane = heightwalls;

	
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
		//TODO Better to set a dynamic ceiling. That can be added and removed easyly to let scenario to be free for Editor.
		/*else if(i == 4) { // ground //
			startLoc.set(0, 0, -2*heightbkPlane);
			dimens.set(widthbasePlane, heightbasePlane, depthbasePlane);
		}*/
		
		bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
		//bounds[i]->create( world.world, startLoc*scaleStage, 0., dimens.x*scaleStage, dimens.z*scaleStage, dimens.y*scaleStage );
		bounds[i]->setProperties(.95, .5); // .25 (more restituition means more energy) , .95 ( friction )
		bounds[i]->add();
	}
    
	/*
    //up right box
    bounds.push_back( new ofxBulletBox() );

    //ofQuaternion(float angle, const ofVec3f& axis);
    //ofxBulletBox::create( btDiscreteDynamicsWorld* a_world, ofVec3f a_loc, ofQuaternion a_rot, float a_mass, float a_sizeX, float a_sizeY, float a_sizeZ )
    bounds[4]->create( world.world, startLoc*scaleStage, ofQuaternion(290,ofVec3f(0,0,1)), 0., dimens.x*scaleStage, dimens.y*scaleStage, dimens.z*scaleStage );
    bounds[4]->setProperties(.95, .05); // .25 (more restituition means more energy) , .95 ( friction )
    bounds[4]->add();
	 */
}

//--------------------------------------------------------------
void Scenario::update(){
    
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->update();
    }
    
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    for(int i = 0; i < ScenarioObjects.size(); i++) {
        ScenarioObjects[i]->draw();
    }
    
	ofDrawAxis(1);
    
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
            Ball *oBall = new Ball();
            oBall->setup(world, pos);
            oBall->setDefaultZ();
            ScenarioObjects.push_back(oBall);
        }
        break;
            
        case SimpleObject::ShapeTypeHammer:{
            Hammer *oHammer = new Hammer();
            oHammer->setup(world, pos);
            oHammer->setDefaultZ();
            ScenarioObjects.push_back(oHammer);
        }
        break;
            
        case SimpleObject::ShapeTypeLever:{
            Lever *oLever = new Lever();
            int dir = 0;
            oLever->setup(world, pos, dir);
            oLever->setDefaultZ();
            ScenarioObjects.push_back(oLever);
        }
        break;
            
        case SimpleObject::ShapeTypeObstacle:{
            Obstacle *oObstable = new Obstacle();
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
#if 0 //the function is not mentained, update it first if you want to use it
void Scenario::loadFromJSON(ofxBulletWorldRigid &world){
    ofxJSONElement ScenarioJSON;
    
    std::string file = "scenario.json";
	
	// Now parse the JSON
	bool parsingSuccessful = ScenarioJSON.open(file);
    if (parsingSuccessful) {
        /* the root JSON value si a list so go through each element */
        for(unsigned int i=0; i<ScenarioJSON.size(); ++i){
            Json::Value Object = ScenarioJSON[i];
            SimpleObject::shapeType Type = (SimpleObject::shapeType)Object["SimpleObject"]["type"].asInt();
            
            ofVec3f pos;
            
            pos.x = Object["SimpleObject"]["position"]["X"].asFloat();
            pos.y = Object["SimpleObject"]["position"]["Y"].asFloat();
            pos.z = Object["SimpleObject"]["position"]["Z"].asFloat();

            switch(Type){
                    
                case SimpleObject::ShapeTypeBall:{
                    Ball *oBall = new Ball();
                    oBall->setup(world, pos);
                    ScenarioObjects.push_back(oBall);
                }
                break;
                    
                case SimpleObject::ShapeTypeHammer:{
                    Hammer *oHammer = new Hammer();
                    oHammer->setup(world, pos);
                    ScenarioObjects.push_back(oHammer);
                }
                break;
                    
                case SimpleObject::ShapeTypeLever:{
                    Lever *oLever = new Lever();
                    int dir = Object["SimpleObject"]["SubType"].asInt();
                    oLever->setup(world, pos, dir);
                    ScenarioObjects.push_back(oLever);
                }
                break;
                    
                case SimpleObject::ShapeTypeObstacle:{
                    Obstacle *oObstable = new Obstacle();
                    oObstable->setup(world, pos, "cylinder.stl", ofVec3f(0.05, 0.05, 0.05));
                    ScenarioObjects.push_back(oObstable);
                }
                break;
                    
            }
            
        }
		
	} else {
		cout  << "Failed to parse JSON" << endl;
	}

    
}
#endif

//--------------------------------------------------------------

void Scenario::loadFromXml(ofxBulletWorldRigid &world){
    ofxXmlSettings ScenarioXml;
    
    if(ScenarioXml.loadFile("scenario.xml")){
        
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
            
            string path;
            path = ScenarioXml.getValue("path","", 0);
            
            switch(Type){
                case SimpleObject::ShapeTypeBall:{
                    Ball *oBall = new Ball();
                    oBall->setup(world, pos);
                    oBall->SetObjectId(objId);
                    ScenarioObjects.push_back(oBall);
                }
                break;
                    
                case SimpleObject::ShapeTypeHammer:{
                    Hammer *oHammer = new Hammer();
                    oHammer->setup(world, pos);
                    oHammer->SetObjectId(objId);
                    ScenarioObjects.push_back(oHammer);
                }
                break;
                    
                case SimpleObject::ShapeTypeLever:{
                    Lever *oLever = new Lever();
                    int dir = ScenarioXml.getValue("LeverType", 0);
                    oLever->setup(world, pos, dir);
                    oLever->SetObjectId(objId);
                    ScenarioObjects.push_back(oLever);
                }
                break;
                    
                case SimpleObject::ShapeTypeObstacle:{
                    Obstacle *oObstable = new Obstacle();
                    //oObstable->setup(world, pos, "3DModels/chino_6.dae");
                    oObstable->setup(world, pos, path, scale);
                    oObstable->SetObjectId(objId);
                    ScenarioObjects.push_back(oObstable);
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
        
        ScenarioXml.addValue("positionX", ScenarioObjects[i]->position.x);
        ScenarioXml.addValue("positionY", ScenarioObjects[i]->position.y);
        ScenarioXml.addValue("positionZ", ScenarioObjects[i]->position.z);
        ScenarioXml.addValue("scaleX", ScenarioObjects[i]->scale.x);
        ScenarioXml.addValue("scaleY", ScenarioObjects[i]->scale.y);
        ScenarioXml.addValue("scaleZ", ScenarioObjects[i]->scale.z);
        ScenarioXml.addValue("path", ScenarioObjects[i]->ModelPath);
        
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeLever){
            Lever *pLever;
            pLever = (Lever*)ScenarioObjects[i];
            ScenarioXml.addValue("LeverType", pLever->direction);
        }
        
        ScenarioXml.popTag();
    }
    
    ScenarioXml.popTag();
    ScenarioXml.saveFile("scenario.xml");
    
}

//------------------------------
#if 0 //the function is not mentained, update it firs if you want to use it
void Scenario::saveToJSON(){
   
    ofxJSONElement ScenarioJSON;
    Json::Value Object;
    
    for(int i = 0; i < ScenarioObjects.size(); i++){

        Object["SimpleObject"]["type"] = ScenarioObjects[i]->type;
        if (ScenarioObjects[i]->type == SimpleObject::ShapeTypeLever){
            /* for the moment only LEVER has subtypes left and right */
            Lever *pLever;
            pLever = (Lever*)ScenarioObjects[i];
            Object["SimpleObject"]["SubType"] = pLever->direction;
        }
        else{
            /* The other objects don«t have this field so we put it to 0*/
            Object["SimpleObject"]["SubType"] = 0;
        }
        Object["SimpleObject"]["position"]["X"] = ScenarioObjects[i]->position.x;
        Object["SimpleObject"]["position"]["Y"] = ScenarioObjects[i]->position.y;
        Object["SimpleObject"]["position"]["Z"] = ScenarioObjects[i]->position.z;

    
        ScenarioJSON.append(Object);
    }

    // now write
    if(!ScenarioJSON.save("scenario.json",true)) {
        cout << "scenario.json written unsuccessfully." << endl;
    } else {
        cout << "scenario.json written successfully." << endl;
    }
    
    
    
}
#endif
