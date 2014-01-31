//
//  GameStatusDisplay.h
//  chinoPinball
//
//  Created by Ovidiu on 31/01/14.
//
//

#ifndef __chinoPinball__GameStatusDisplay__
#define __chinoPinball__GameStatusDisplay__



class GameStatusDisplay{
public:
    GameStatusDisplay(int posX, int posY);
    void draw(void);
private:
    int startPositionX, startPositionY;
};

#endif /* defined(__chinoPinball__GameStatusDisplay__) */
