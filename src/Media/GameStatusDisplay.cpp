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
    
    str = "初音ミク";
    
    // The third parameter is depth, use it to extrude the shape.
    font.loadFont("mplus-1c-regular.ttf", 100, 20);
    
    light.setDiffuseColor(ofColor(200, 64, 64));
    light.setSpecularColor(ofColor(255, 255, 255));
    light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 200);
    
    material.setShininess(64);
    
    
}

//------------------------------
void GameStatusDisplay::draw(void){
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
    
    
    //ofBackground(255);
    
    ofEnableLighting();
    
    light.enable();
    material.begin();
    cam.begin();
	{
        ofScale(1, -1, 1);  // Flip back since we're in 3D.
        font.drawString(str, font.stringWidth(str) * -0.5f, font.stringHeight(str) * 0.5f);
    }
    cam.end();
    material.end();
}