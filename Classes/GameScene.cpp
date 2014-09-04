//
//  GameScene.cpp
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#include "GameScene.h"
#include "MainMenu.h"

Scene* Game::createScene() {
    
    auto scene = Scene::create();
    auto layer = Game::create();
    
    scene->addChild(layer);
    
    return scene;
}

SnakeNode* SnakeNode::create(int type) {
    SnakeNode *pRet = new SnakeNode();
    if (pRet && pRet->init(type)) {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool SnakeNode::init(int type) {
    if (!Sprite::init()) {
        return false;
    }
    switch (type) {
        case 1:
        {
            auto sprite = Sprite::create("redstar.png");
            sprite->setAnchorPoint(Point::ZERO);
            this->addChild(sprite);
            m_dir = ENUM_DIR::DIR_RIGHT;
        }
            break;
        case 2:
        {
            auto sprite = Sprite::create("greenstar.png");
            sprite->setAnchorPoint(Point::ZERO);
            this->addChild(sprite);
            m_dir = ENUM_DIR::DIR_RIGHT;
        }
            break;
        case 3:
        {
            auto sprite = Sprite::create("yellowstar.png");
            sprite->setAnchorPoint(Point::ZERO);
            this->addChild(sprite);
            m_dir = ENUM_DIR::DIR_RIGHT;
        }
            break;
        default:
            break;
    }
    return true;
}
void SnakeNode::setPositionRC(int row, int col) {
    this->m_row = row;
    this->m_col = col;
    setPosition(Point(col *32, row * 32));
}

bool Game::init() {
    if (!Layer::init()) {
        return false;
    }
    //Add map
    auto draw = DrawNode::create();
    draw->setAnchorPoint(Point::ZERO);
    draw->setPosition(Point::ZERO);
    this->addChild(draw);
    
    for (int i=0; i < 21; i++) {
        draw->drawSegment(Point(0, 32 * i), Point(640, 32 * i), 1, Color4F(1, 1, 1, 1));
        draw->drawSegment(Point(32 *i, 0), Point(32 * i, 640), 1, Color4F(1, 1, 1, 1));
    }
    
    //Add Head
    spHead = SnakeNode::create(1);
    this->addChild(spHead);
    
    //Add Body
    
    //Add Food
    spFood = SnakeNode::create(3);
    
    int row = rand()%20;
    int col = rand()%20;
    spFood->setPositionRC(row, col);
    
    this->addChild(spFood);
    
    auto size = Director::getInstance()->getWinSize();
    
    auto spriteBK = Sprite::create("menuback.png");
    
    spriteBK->setPosition(Point(size.width/2, size.height/2));
    spriteBK->setOpacity(75);
    this->addChild(spriteBK);
    
    //Score
    auto labelScore = Label::create("分数: 0", "宋体", 25);
    
    labelScore->setPosition(Point(size.width-80, size.height-50));
    this->addChild(labelScore);
    
    auto menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(Game::menuCallBack, this));
    
    menuItemBack->setPosition(Point(size.width-menuItemBack->getContentSize().width-50, menuItemBack->getContentSize().height+10));
    
    auto menu = Menu::create(menuItemBack, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    this->schedule(schedule_selector(Game::gameLogic), 0.5);
    return true;
}

void Game::menuCallBack(Ref* object) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}
void Game::gameLogic(float dt) {
    
//    moveBody();
    switch (spHead->m_dir) {
        case ENUM_DIR::DIR_RIGHT:
            spHead->runAction(MoveBy::create(0.3, Point(32,0)));
            break;
        case ENUM_DIR::DIR_LEFT:
            spHead->runAction(MoveBy::create(0.3, Point(-32,0)));
            break;
        case ENUM_DIR::DIR_DOWN:
            spHead->runAction(MoveBy::create(0.3, Point(0,-32)));
            break;
        case ENUM_DIR::DIR_UP:
            spHead->runAction(MoveBy::create(0.3, Point(0,32)));
            break;
            
        default:
            break;
    }
    
}




















