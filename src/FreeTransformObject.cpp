//
//  FreeTransformObject.cpp
//  chinoPinball
//
//  Created by Ovidiu on 7/6/15.
//
//

#include "FreeTransformObject.h"
#include "SimpleObject.h"

FreeTransformObject::FreeTransformObject(SimpleObject *pSimpleObj){
    m_poSimpleObj = pSimpleObj;
    
    last_angleValX = angleValX = 0;
	last_angleValY = angleValY = 0;
	last_angleValZ = angleValZ = 0;
	
	axis2RotateX = ofVec3f(1,0,0);
	axis2RotateY = ofVec3f(0,1,0);
	axis2RotateZ = ofVec3f(0,0,1);
}

void FreeTransformObject::update(){
    if(m_poSimpleObj->getPosition().x != last_positionX){
		m_poSimpleObj->setPhysicsPosition(m_poSimpleObj->getPosition());
		last_positionX = m_poSimpleObj->getPosition().x;
	}
	if(m_poSimpleObj->getPosition().y != last_positionY){
		m_poSimpleObj->setPhysicsPosition(m_poSimpleObj->getPosition());
		last_positionY = m_poSimpleObj->getPosition().y;
	}
	if(m_poSimpleObj->getPosition().z != last_positionZ){
		m_poSimpleObj->setPhysicsPosition(m_poSimpleObj->getPosition());
		last_positionZ = m_poSimpleObj->getPosition().z;
	}
	
	
	if(angleValX != last_angleValX){
		
		setAngle2Rotate(angleValX, axis2RotateX); //, angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValX = angleValX;
	}
	if(angleValY != last_angleValY){
		
		setAngle2Rotate(angleValY, axis2RotateY); // , angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValY = angleValY;
	}
	if(angleValZ != last_angleValZ){
		
		setAngle2Rotate(angleValZ, axis2RotateZ); //, angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValZ = angleValZ;
	}
    
}

//--------------------------------------------------------------
void FreeTransformObject::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
	btTransform transform;
	btRigidBody* a_rb = m_poSimpleObj->getSimpleBody()->getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
	btQuaternion currentRotation = transform.getRotation();
	btQuaternion rotate = btQuaternion(btVector3(axis2rot.x,axis2rot.y,axis2rot.z), ofDegToRad(angle2rot));
    
	//rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle2rot));
	//rotate.setEuler(ofDegToRad(0), ofDegToRad(90), ofDegToRad(0));
	transform.setRotation(rotate * currentRotation);
    
	a_rb->getMotionState()->setWorldTransform( transform );
	
	btQuaternion Rotation2Save = a_rb->getOrientation();
	//save this var for the XML
	m_poSimpleObj->rotation.set(Rotation2Save.x(), Rotation2Save.y(), Rotation2Save.z(), Rotation2Save.w());
	
	m_poSimpleObj->getSimpleBody()->activate();
	
	
}

//--------------------------------------------------------------
void FreeTransformObject::SetLastRotation(ofQuaternion rotation){
    last_rotation = rotation;
}