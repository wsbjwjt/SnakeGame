//
//  HelpScene.h
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#ifndef __SnakeGame__HelpScene__
#define __SnakeGame__HelpScene__

#include "cocos2d.h"

USING_NS_CC;

class Help : public Layer {
    
public:
    static Scene* createScene();
    
    CREATE_FUNC(Help);
    
    virtual bool init();
    void menuCallBack(Ref* object);
};


#endif /* defined(__SnakeGame__HelpScene__) */
