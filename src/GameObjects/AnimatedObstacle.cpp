//
//  AnimatedObstacle.cpp
//  chinoPinball
//
//  Created by Ovidiu on 20/7/15.
//
//

#include "AnimatedObstacle.h"

AnimatedObstacle::AnimatedObstacle(vector <SimpleMission *> * _currentMissions)
: Obstacle(_currentMissions){
    m_animPos = 0;
}

void AnimatedObstacle::setupSpecific(){
    type = ShapeTypeAnimatedObstacle;
    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
}

void AnimatedObstacle::updateSpecific(bool bEditorMode){

    
   
    m_animPos++;
    if (m_animPos > 100)
        m_animPos = 0;
}

//-------------------------------------------------------------
bool AnimatedObstacle::drawAssimpModelSpecific(){
    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
     //assimpModel.setPositionForAllAnimations(m_animPos);
    cout << m_animPos <<endl;
    for (int i=0; i<assimpModel.getNumMeshes();i++){
        assimpModel.getCurrentAnimatedMesh(i).drawFaces();
    }
#if 0
    for(unsigned int i=0; i<assimpModel.getNumMeshes(); i++) {
        ofxAssimpMeshHelper & mesh = assimpModel.getMeshHelper(i);

        

        
        if(mesh.twoSided) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        
        ofEnableBlendMode(mesh.blendMode);
#ifndef TARGET_OPENGLES
        mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
#else
        switch(renderType){
		    case OF_MESH_FILL:
		    	mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
		    	break;
		    case OF_MESH_WIREFRAME:
		    	mesh.vbo.drawElements(GL_LINES,mesh.indices.size());
		    	break;
		    case OF_MESH_POINTS:
		    	mesh.vbo.drawElements(GL_POINTS,mesh.indices.size());
		    	break;
        }
#endif
        

        

    }
#endif
    return true;
}

string AnimatedObstacle::getObjectName(){
    return "AnimatedObstacle";
}

void AnimatedObstacle::onCollisionSpecific(SimpleObject* Obj){

	

}