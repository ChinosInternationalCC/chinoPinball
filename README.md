chinoPinball
============

Pinball. ChinoPinball is an opensource tool for mapping pinball via projection.

The project is under development.

***
###Roadmap

- First step, build a pinball game ( forces , objects, textures, events, score, scenes, etc )
- Map the game projection to a physical space
- Create scenario editor for editing scenario directly at the place where it is projected 
- Build interfaces to shoot and play game

***
###Screenshot

![Screenshot](/doc/screenshot.png)

***
###GITHUB 
**fork** master branch

Dude, where's my fork? 
Each developer has to fork in his Github ( click on website fork ) 
Then clone it to you git client
```
	>> git clone http://GitHubProjectAdresss
```	
develop your code
upload your changes to your github branch
```
	>> git stage xxx file
	>> git commit -m 'message to the statge files'
	>> git push or git push -u origin master
```
When finally
u wanna merge it, to chinos  master branch 
push from origin to master 	
```
	>> git push -u origin masterChinos
```

***
###Dependencies

* OF008 http://www.openframeworks.cc 
* ofxBullet https://github.com/NickHardeman/ofxBullet
* ofxSyphon https://github.com/astellato/ofxSyphon

Currently developed on MAC (XCode < 4.4) and Windows (CodeBlocks) (not countinued)

We are using MadMapper for projection mapping http://www.madmapper.com

***
###ClassHierarchy

![ClassHierarchy](/doc/ClassHierarchy.png)

***
###Projection mapping

**Mappig the game on one surface with 3D elements**

*First step is to find or build a physical space for mapping (like a wall or ramp with some 3D elements)
*Second, setup projector and don't touch it later
*Next, in the game, adjust free camera position and FOV according to spectators' point of view (it is not the same as projector's point of view) and fix the camera
*In Madmapper grab video from Syphon and adjust it so that game's perspective fits to the physical space
*Edit scenario using scenario editor to fit the table and objects to physical elements  

**Mappig the game on multiple surfaces with 3D elements**

We don't know how to do this yet ...


***
###Scenario editor

The idea is to be able to create scenario directly on the place where the game will be projected, without proir preparation (only the objects could be prepared earlier).
Then, maybe we could also let the people create scenarios by themselves. 

Editor should have the following functionalities:
*saved/load scenario to a file
*change width and height of a table (with walls)
*add new objects
*select object to edit
*edit object's properties:
	*position XY (we can forget about Z for now), the best would be drag&drop
	*scale
	*rotation
	*color
*objects types: lever, hammer, obstacle ...