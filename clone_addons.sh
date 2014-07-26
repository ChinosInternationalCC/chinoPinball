#!/bin/bash
# Dependencies for chinoPinball

cd ../../../addons

if [ -z $1 ]; then
PREFIX="git clone https://github.com/"
else
PREFIX="git clone git@github.com:"
fi

${PREFIX}NickHardeman/ofxBullet.git
${PREFIX}astellato/ofxSyphon.git
${PREFIX}rezaali/ofxUI.git
${PREFIX}jefftimesten/ofxJSON.git
${PREFIX}kylemcdonald/ofxDmx.git
${PREFIX}Flightphase/ofxFTGL.git
${PREFIX}memo/ofxMSAInteractiveObject
${PREFIX}morethanlogic/ofxMtlMapping2D