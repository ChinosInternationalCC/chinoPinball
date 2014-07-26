chinoPinball
============

ChinoPinball is an opensource tool for mapping pinball via projection.


***
###Videos with the ChinoPinball in action

**ChinoPinball@FAB10 2014** DHUB Barcelona https://vimeo.com/100059297


***
###Screenshot

![Screenshot](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/screenshot.png)
![Screenshot](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/pinball.jpg)

***
###Contributing to ChinoPinball

In order to contribute to ChinoPinball the first step is to fork the project. Bellow you can find a small github tutorial on how to do it.
When you have updates that you want to merge in the main repository, make a pull request.

**fork** master branch

Dude, where's my fork? 
Each developer has to fork in his Github ( click on website fork ) 
Then clone it to you git client
```
	>> git clone http://GitHubProjectAdresss
```	
develop your code
add changes to the local repo
```
	>> git add <filename>
	or
	>> git add *
```
upload your changes to your github branch
```
	>> git stage xxx file
	>> git commit -m 'message to the statge files'
	>> git push or git push -u origin master
```
if the local repo is not connected to the remote one
```
	>> git remote add origin <server>
```
update local repository with remote changes
```
	git pull
```
branches
```
	>> git checkout -b <branch> #create new branch
	>> git checkout master #switch to master branch
	>> git branch -d <branch> #delete branch
	>> git push origin <branch> #push branch to remote repository
	
```
merge
```
	git merge <branch>
```
restore file with the last working copy from HEAD
```
	>> git checkout -- <filename>
```
When finally
u wanna merge it, to chinos  master branch 
push from origin to master 	
```
	>> git push -u origin masterChinos
```

***
###Examples of similar projects

* http://www.youtube.com/watch?v=eyUKAFCaHzo
* http://www.youtube.com/watch?v=MljNwzBp1y8
* http://www.youtube.com/watch?v=YvyRM175uQ0



***
###Dependencies

* OF008 http://www.openframeworks.cc 
* ofxBullet https://github.com/NickHardeman/ofxBullet
* ofxSyphon https://github.com/astellato/ofxSyphon
* ofxJSON https://github.com/jefftimesten/ofxJSON.git
* ofxDmx https://github.com/kylemcdonald/ofxDmx.git
* ofxFTGL https://github.com/Flightphase/ofxFTGL
* ofxMSAInteractiveObject https://github.com/memo/ofxMSAInteractiveObject
* ofxMtlMapping2D https://github.com/morethanlogic/ofxMtlMapping2D
 

To clone all the addons requested by the project you can also execute the ./clone_addons.sh script

Currently developed on MAC (XCode 5.0.2, MAC OS SDK 10.9, LLVM compiler) and Windows (CodeBlocks) (not countinued)

The project should also compile in Windows or Linux if ofxSyphone is not used. Just don't add ofxSyphon files to the compilation and comment in *ExternalsConfig.h*  the line *#define USE_SYPHON*:

```

//
// ExternalsConfig.h
// chinoPinball
//
// Created by Ovidiu on 14/02/14.
//
//

#ifndef chinoPinball_ExternalsConfig_h
#define chinoPinball_ExternalsConfig_h

/* comment define if don't want to use feature */
//#define USE_SYPHON
```
We are using MadMapper for projection mapping http://www.madmapper.com

***
###ClassHierarchy

![ClassHierarchy](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/ClassHierarchy.png)

The main class is **PinballChinoManager**. In this class are defines all the main object: a scenario and a scenario editor, objects that handles inputs and outputs like handling of the keyboard, OSC communication, DMX communication, Arduino communication, objects that handles the sound playback.

***
###SystemOverview
![SystemOverview](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/ChinoPinballDeploymentDiagram.jpg)

***
###Projection mapping

**Mapping the game on one surface with 3D elements**

* First step is to find or build a physical space for mapping (like a wall or ramp with some 3D elements)
* Second, setup projector and don't touch it later
* Next, in the game, adjust free camera position and FOV according to spectators' point of view (it is not the same as projector's point of view) and fix the camera
* In Madmapper grab video from Syphon and adjust it so that game's perspective fits to the physical space
* Edit scenario using scenario editor to fit the table and objects to physical elements  

**Mappig the game on multiple surfaces with 3D elements**

We don't know how to do this yet ...


***
###Scenario editor

The idea is to be able to create scenario directly on the place where the game will be projected, without prior preparation (only the objects could be prepared earlier).
Then, maybe we could also let the people create scenarios by themselves. 

Editor has the following functionalities:
* saved/load scenario to a file
* change width and height of a table (with walls)
* add new objects
* select object to edit
* edit object's properties:
	* position XY (we can forget about Z for now), the best would be drag&drop
	* scale
	* rotation
	* color
* objects types: lever, hammer, obstacle ...

To enter in the scenario editor mode press the key 'e'

![ScenarioEditor](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/EditorMode.png)

***
###Key bindings

* F1 - OF_LOG_SILENT
* F2 - OF_LOG_VERBOSE
* F3 - CollisionVerbose
* F4 - EditorVerbose
PinballChinoManager
* f - fullscreen
* s - save camera position to file
* l - load camera postion
* m - mute sounds
InputEventManager
* enter - restart game
* down - move hammer
* q/Q - move right lever
* w/W - move left lever
* d/D - draw debug
* m/M - open Mapping Editor if using MtlMapping
ScenarioEditor
* e - toggle editor mode
* x - saving scenario to file
* 0 - add a ball
* 3 - add a lever
* 5 - add a hammer
* 6 - add an obstacle

***
###3DModels

We support almos all the major 3D model file formats by using the AssimpModel Loader. In order to load a model designed in Cinema4D for example you have to copy them in the */bin/data* path and to add a new entry in te *scenario.xml* file.

```
    <object>
        <type>6</type>
        <id>5</id>
        <color>14423100</color>
        <pointsCollision>0</pointsCollision>
        <positionX>0.474898070</positionX>
        <positionY>12.638760567</positionY>
        <positionZ>-0.899999976</positionZ>
        <scaleX>0.100000009</scaleX>
        <scaleY>0.100000009</scaleY>
        <scaleZ>0.100000009</scaleZ>
        <rotationX>-0.541731715</rotationX>
        <rotationY>-0.442292124</rotationY>
        <rotationZ>0.587128937</rotationZ>
        <rotationW>0.407656848</rotationW>
        <path>3DMODELS/new/totem1.obj</path>
    </object>
```
The tag *<type>* should hold the object type; one of the values defined in the *enum shapeType*
```
    enum shapeType{
        ShapeTypeBall = 0,
        ShapeTypeSimpleBox = 1,
        ShapeTypeSpring = 2,
        ShapeTypeLever = 3,
        ShapeTypeContainer = 4,
        ShapeTypeHammer = 5,
        ShapeTypeObstacle = 6,
        ShapeTypeBounds = 7
    };
```

The tag *<id>* should hold a unique id for each object.

***
###OSC

All the collision events and other information regarding the game like the curent mission, score etc are sent via OSC in order to be available to other external application like MadMapper, Module8, PureData, MaxMsp, SuperCollider etc

The following OSC addresses are currently implemented

```
/Collision/Object/Id
/Collision/Object/Name
/Collision/Object/Position
/Mission/Event
/Mission/ID
```

Example PureData/collision.pd
![PureData](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PureData.png)

The OSC implementation can be found in the OSCManager class

***
###Sound


https://soundcloud.com/alexgeell/chinos-internacional-pinball-raval-song

Chinos Internacional Pinball Song utiliza una base de Rumba en la guitarra como símbolo los gitanos catalanes, una percusión afro india que aporta un ambiente oriental para que las melodías del baglama griego se combinen con el paisaje sonoro del barrio, que da cuenta de personas y actividades que se desarrollan cotidianamente en sus espacios públicos.

***
###License

ChinoPinball is released under a GPL license. You can read it here: https://github.com/ChinosInternationalCC/chinoPinball/blob/master/LICENSE

If you have any doubts on what you can do and what you can not do with the code just drop us an email at chinopinball@gmail.com

***
###Colaborators
 * Kuba Markiewicz  - Openframeworks
 * Carles Gutiérrez - Openframeworks
 * Ovidiu Cincheza - Openframeworks
 * Angel Muñoz - Openframeworks / Arduino
 * Augusto Zuniga - 3D Art
 * Mery Glez - DigitalFabrication
 * Alex Geell - SoundArt
 * Alex Reche - MadMapper

Thanks to FABLab Barcelona for letting us use their CNC machines

***
###Contact

chinopinball@gmail.com
