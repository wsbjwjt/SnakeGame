//
//  GameScene.h
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#ifndef __SnakeGame__GameScene__
#define __SnakeGame__GameScene__

#include "cocos2d.h"

USING_NS_CC;
enum class ENUM_DIR {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_STOP
};

class SnakeNode : public Sprite {
public:
    enum ENUM_DIR m_dir;
    int nodeType; // 1. Head, 2.body, 3. Food
    int m_row, m_col;
    
    static SnakeNode* create(int type);
    virtual bool init(int type);
    void setPositionRC(int row, int col);
};

class Game : public Layer {
    
public:
    SnakeNode* spFood;
    SnakeNode* spHead;
    int m_score;
    Vector<SnakeNode *> allBody; //save body node.
    
    static Scene* createScene();
    
    CREATE_FUNC(Game);
    
    virtual bool init();
    void menuCallBack(Ref* object);
    void gameLogic(float dt);
    
    void newBody(); //add one dody node.
    void moveBody(); //move all body node.
    
    
};


#endif /* defined(__SnakeGame__GameScene__) */
