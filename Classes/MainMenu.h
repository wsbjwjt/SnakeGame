//
//  MainMenu.h
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#ifndef __SnakeGame__MainMenu__
#define __SnakeGame__MainMenu__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public Layer {
    
public:
    static Scene* createScene();
    
    CREATE_FUNC(MainMenu);
    
    virtual bool init();
    void menuCallBack(Ref* object);
};


#endif /* defined(__SnakeGame__MainMenu__) */
