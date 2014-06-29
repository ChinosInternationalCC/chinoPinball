//
//  MediaUtils.cpp
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#include "MediaUtils.h"

void MediaUtils::billboardBegin() {
    
    float modelview[16];
	int i,j;
    
	// save the current modelview matrix
	glPushMatrix();
    
	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
    
	// undo all rotations
	// beware all scaling is lost as well
	for( i=0; i<3; i++ )
	    for( j=0; j<3; j++ ) {
            if ( i==j )
                modelview[i*4+j] = 1.0;
            else
                modelview[i*4+j] = 0.0;
	    }
    
	// set the modelview with no rotations
	glLoadMatrixf(modelview);
}



void MediaUtils::billboardEnd() {
    
	// restore the previously
	// stored modelview matrix
	glPopMatrix();
}