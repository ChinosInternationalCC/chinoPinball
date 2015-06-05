//
//  GameStatusDisplay.cpp
//  chinoPinball
//
//  Created by Ovidiu on 31/01/14.
//
//

#include "GameStatusDisplay.h"
#include "GameStatus.h"
#include "ofGraphics.h"

//------------------------------
GameStatusDisplay::GameStatusDisplay(int posX, int posY){
    startPositionX = posX;
    startPositionY = posY;
    show3dfont = true;
    setup3dFont();
	SplashScreenDuration = 1000;
    SplashScreenTimer = SplashScreenDuration;
	displayGameOver= false;
    
}

//--------------------------------
void GameStatusDisplay::setup3dFont(void){
    //str = "初音ミク";
    str = "score";
    // The third parameter is depth, use it to extrude the shape.
    font.loadFont("ARCADE.TTF", 25);
    
    //light.setDiffuseColor(ofColor(200, 64, 64));
    //light.setSpecularColor(ofColor(255, 255, 255));
    //light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 200);
    //light.setPosition(startPositionX, startPositionY, 200);
    //material.setShininess(64);
	fontMedium.loadFont("ARCADE.TTF", 30);
    GOstartPositionX = 0;
    GOstartPositionY = -ofGetHeight()*0.4;
    
}

/*void GameStatusDisplay::setCamera(ofEasyCam *cam){
    this->cam = cam;
}*/
//--------------------------------
void GameStatusDisplay::draw3dFont(void){
    GameStatus *status;
    status = GameStatus::getInstance();
    
    //ofEnableLighting();
    
    //light.enable();
    //material.begin();
    cam.begin();
    MediaUtils::billboardBegin();//always facing the camera
	{
        ofScale(1, -1, 1);  // Flip back since we're in 3D.
        //font.drawString(str, font.stringWidth(str) * -0.5f, font.stringHeight(str) * 0.5f);
        ofSetColor(5, 200, 220);
        font.drawString(str+"  "+ofToString(status->GetCurrentPlayerScore(), 2), -450, -300);
        //font.drawString("FPS  "+ofToString(ofGetFrameRate(), 0), -450, -200);
        font.drawString("balls  "+ofToString(status->GetRemainingLifes(), 0), -450, -200);
    }
    MediaUtils::billboardEnd();
    cam.end();
    //material.end();
    
}

void GameStatusDisplay::draw2dFont(void){
    GameStatus *status;
    
    int posX = startPositionX;
    int posY = startPositionY;
    
    int lineSpacing = 15;
    status = GameStatus::getInstance();
    
    ofSetColor(255, 255, 255);
    
    string fpsStr = "Remaining lives: "+ofToString(status->GetRemainingLifes(), 2);
    ofDrawBitmapString(fpsStr, posX,posY);
    posY += lineSpacing;
    fpsStr = "Remaining missions: "+ofToString(status->GetRemainingMissions(), 2);
    ofDrawBitmapString(fpsStr, posX,posY);
    posY += lineSpacing;
    fpsStr = "Player id: "+ofToString(status->GetPlayerId(), 2);
    ofDrawBitmapString(fpsStr, posX,posY);
    posY += lineSpacing;
    fpsStr = "Player score: "+ofToString(status->GetCurrentPlayerScore(), 2);
    ofDrawBitmapString(fpsStr, posX,posY);
    posY += lineSpacing;
    fpsStr = "FPS: "+ofToString(ofGetFrameRate(), 0);
    ofDrawBitmapString(fpsStr, posX,posY);
    posY += lineSpacing;
    
    switch(status->GetGameStatus()){
        case GameStatus::WAITING_NEW_PLAYER:
            fpsStr = "GameStatus: WAITING_NEW_PLAYER";
            ofDrawBitmapString(fpsStr, posX,posY);
            posY += lineSpacing;
            break;
        case GameStatus::SETTING_UP_THE_GAME:
            fpsStr = "GameStatus: SETTING_UP_THE_GAME";
            ofDrawBitmapString(fpsStr, posX,posY);
            posY += lineSpacing;
            break;
        case GameStatus::WAITING_START_PLAY:
            fpsStr = "GameStatus: WAITING_START_PLAY";
            ofDrawBitmapString(fpsStr, posX,posY);
            posY += lineSpacing;
            break;
        case GameStatus::PLAYING:
            fpsStr = "GameStatus: PLAYING";
            ofDrawBitmapString(fpsStr, posX,posY);
            posY += lineSpacing;
            break;
        case GameStatus::DEAD:
            fpsStr = "GameStatus: DEAD";
            ofDrawBitmapString(fpsStr, posX,posY);
            posY += lineSpacing;
            break;
        default:
            break;
    }

    
}

void GameStatusDisplay::GameOver(void){
	
	SplashScreenTimer = ofGetElapsedTimeMillis();
	displayGameOver = true;

		
}
//------------------------------
void GameStatusDisplay::draw(void){
    
    if (show3dfont)
        draw3dFont();
    else
        draw2dFont();
	
	if (displayGameOver)
	//game over
		if ((ofGetElapsedTimeMillis() - SplashScreenTimer) < SplashScreenDuration){
			cam.begin();
			MediaUtils::billboardBegin();//always facing the camera
			{
				ofScale(1, -1, 1);  // Flip back since we're in 3D.
				//font.drawString(str, font.stringWidth(str) * -0.5f, font.stringHeight(str) * 0.5f);
				ofSetColor(5, 200, 220);
				string GOstr = "GAME OVER";
				fontMedium.drawString(GOstr, GOstartPositionX, GOstartPositionY);
			
			
			}
			MediaUtils::billboardEnd();
			cam.end();
		}
		else{
			displayGameOver = false;
		}
    
}

