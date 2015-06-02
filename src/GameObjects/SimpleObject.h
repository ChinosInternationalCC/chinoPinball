//
//  SimpleObject.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxAssimpModelLoader.h"
#include "SimpleMission.h"

class SimpleObjectAttrib{
public:
    inline SimpleObjectAttrib(string modelPath,
							  ofVec3f _position,
                              float _damping,
                              float _friction,
                              float _mass,
                              float _restitution,
							  ofVec3f _ModelScale);
    //positions
	string modelPath;
	ofVec3f ModelScale;
    ofVec3f position;
    
    float damping;
	float friction;
    float mass;
    float restitution;
    
private:
};

inline SimpleObjectAttrib::SimpleObjectAttrib(string _modelPath,
											  ofVec3f _position,
                                              float _damping,
                                              float _friction,
                                              float _mass,
                                              float _restitution,
											  ofVec3f _ModelScale){
	
	modelPath = _modelPath;
    position = _position;
    damping = _damping;
    friction = _friction;
    mass = _mass;
    restitution = _restitution;
	ModelScale = _ModelScale;
}

class SimpleObject {
    
public:

    enum shapeType{
        ShapeTypeBall = 0,
        ShapeTypeSimpleBox = 1,
        ShapeTypeSpring = 2,
        ShapeTypeLever = 3,
        ShapeTypeContainer = 4,
        ShapeTypeHammer = 5,
        ShapeTypeObstacle = 6,
        ShapeTypeAnimatedMesh = 9,
        ShapeTypeGeneratedMesh = 10,
        ShapeTypeGravity = 11,
        ShapeTypeTeleporter = 12,
		ShapeTypeRamp = 13
    };
	
    shapeType type;
    
	virtual void update(bool bEditorMode);
    virtual void updateSpecific(bool bEditorMode) = 0;
	virtual void draw(bool bEditorMode)=0;
    
    void setDebugMode(bool &DebugMode);
    void drawDebug(void);
	
	//--------------------------------------------------------------

    
    
	//general vars
	int idobject;
	
    
	void setVisibility(int invisible);
    
	bool bVisible;
    int color;
	int highlightColor;
    int highlightTime;
	
    //////////////////////////////////////////////
    //Physics
    ofxBulletWorldRigid* world;
    
    void SetObjectId(int objId);
    int GetObjectId(void);
	//graphic vars
	//objDisplay mygraphicobject;
	virtual ofxBulletBaseShape* getBulletBaseShape() = 0;
    virtual string getObjectName() = 0;
    virtual void onCollision() = 0;
    
	//physics vars
	//enum {Static/dynamic/Kinematic}

	
	//var status
	bool bAnimation;
	
	//var events
	//ofEvent bColision;
	bool bColision;
	int  collisionTime;
	int colisionCounter;
    
    //ofVec3f scale //TODO use now ModelScale
	ofVec3f getScale();
	ofVec3f* getScaleRef();
	ofVec3f last_scale;  // if we load a 3D model this variable should store the scale factors
	float scaleXyz, last_scaleXyz;
                    // with the correct values so that our model nicely fits inside the Scenario

    int ObjectId; //this should be a unique identificator for each object that we have on the scenario

    
    void setDefaultPostion();
    ofVec3f getPosition();
    void setPosition(ofVec3f _position);
    void setDefaultZ();
    void setPhysicsPosition(ofVec3f position);
	void setPhysicsRotation(ofQuaternion rotation);
    

    float last_positionX, last_positionY, last_positionZ;
    
	void setupRot();
    //Rotations
	ofQuaternion    rotation, last_rotation;
	ofVec3f		axis2RotateX;
	ofVec3f		axis2RotateY;
	ofVec3f		axis2RotateZ;
	float		angleValX, last_angleValX;
	float		angleValY, last_angleValY;
	float		angleValZ, last_angleValZ;

    
    //Scaling
    ofVec3f         initScale;
    void autoScalingXYZ();
    void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
    
	
	//3d models, Texteres and Colors
	ofMesh                  assimpModelMesh;
	ofxAssimpModelLoader	assimpModel;
	ofMaterial				material;
	
	
	//Missions
	void setCurrentMissionId(int _idCurrentMission);
	
	
	//Game vars
	void setPointsCollision(int points);
	int collisionPoints;
	   
    bool bDebugMode;
    
    void genericSetup(ofxBulletWorldRigid &myWorld, SimpleObjectAttrib &Attributes);
    SimpleObjectAttrib * getSimpleAttrib();
    
protected:
	int						idCurrtentMission;
    vector <SimpleMission *> *currentMissions;
    
    /**
	 *  Simple Object Constructor declared as protected so only child classes can create SimpleObjects
	 */
	SimpleObject(ofxBulletBaseShape *poBulletBaseShape, // [<in] pointer to the ofxBulletBaseShape of the derived class
                 vector <SimpleMission *> * _currentMissions, // [<in] pointer to the current mission
                float _DefaultPositionZ
    );
    
    virtual void setupBody(SimpleObjectAttrib &Attributes) = 0;
    virtual void setupLookStyle(SimpleObjectAttrib &Attributes) = 0;
    virtual void setupAnimations(SimpleObjectAttrib &Attributes) = 0;
    virtual void setupType() = 0;
    


private:
    ofxBulletBaseShape	*poSimpleBody;
    float fDefaultPositionZ;
    
    ofMatrix4x4 worldposition;
    SimpleObjectAttrib *pAttrib;
    
	
    
   
};



