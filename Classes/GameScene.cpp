//
//  GameScene.cpp
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#include "GameScene.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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
        }
            m_dir = ENUM_DIR::DIR_STOP;
            break;
        case 3:
        {
            auto sprite = Sprite::create("yellowstar.png");
            sprite->setAnchorPoint(Point::ZERO);
            this->addChild(sprite);
        }
            m_dir = ENUM_DIR::DIR_STOP;
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
    m_score = 0;
    //Score
    auto labelScore = Label::create("分数: 0", "宋体", 25);
    
    labelScore->setTag(110);
    
    labelScore->setPosition(Point(size.width-80, size.height-50));
    this->addChild(labelScore);
    
    auto menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(Game::menuCallBack, this));
    
    menuItemBack->setPosition(Point(size.width-menuItemBack->getContentSize().width-50, menuItemBack->getContentSize().height+10));
    
    auto menu = Menu::create(menuItemBack, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    this->schedule(schedule_selector(Game::gameLogic), 0.4);
    
    //Add user touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch *touch, Event *event){
        
        //通过触摸改变贪食蛇移动方向
        int colum = touch->getLocation().x/32;
        int row = touch->getLocation().y/32;
        
        int spHeadCol = spHead->getPositionX()/32;
        int spHeadRow = spHead->getPositionY()/32;
        
        if (abs(spHeadCol-colum) > abs(spHeadRow-row)) {
            
            if (spHeadCol < colum) {
                spHead->m_dir = ENUM_DIR::DIR_RIGHT;
            } else {
                spHead->m_dir = ENUM_DIR::DIR_LEFT;
            }
        } else {
            if (spHeadRow < row) {
                spHead->m_dir = ENUM_DIR::DIR_UP;
            } else {
                spHead->m_dir = ENUM_DIR::DIR_DOWN;
            }
        }
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void Game::menuCallBack(Ref* object) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}
void Game::gameLogic(float dt) {
    
    moveBody();
    switch (spHead->m_dir) {
        case ENUM_DIR::DIR_RIGHT:
            spHead->runAction(MoveBy::create(0.3, Point(32,0)));
            spHead->m_col++;
            break;
        case ENUM_DIR::DIR_LEFT:
            spHead->runAction(MoveBy::create(0.3, Point(-32,0)));
            spHead->m_col--;
            break;
        case ENUM_DIR::DIR_DOWN:
            spHead->runAction(MoveBy::create(0.3, Point(0,-32)));
            spHead->m_row--;
            break;
        case ENUM_DIR::DIR_UP:
            spHead->runAction(MoveBy::create(0.3, Point(0,32)));
            spHead->m_row++;
            break;
            
        default:
            break;
    }
    //碰撞检测
    if (spHead->m_row == spFood->m_row && spHead->m_col == spFood->m_col) {
        
        SimpleAudioEngine::getInstance()->playEffect("eat.wav");
        this->m_score +=100;
        Label *label = (Label *)this->getChildByTag(110);
        char strScore[20];
        sprintf(strScore, "分数: %d",m_score);
        label->setString(strScore);
        
        int row = rand()%10;
        int col = rand()%10;
        spFood->setPositionRC(row, col);
        
        newBody();
    }
    
    
}

void Game::newBody() {
    
    auto bodynode = SnakeNode::create(2);
    
    if (allBody.size() > 0) {
        
        auto lastBody = allBody.at(allBody.size() - 1);
        bodynode->m_dir = lastBody->m_dir;
        
        switch (bodynode->m_dir) {
            case ENUM_DIR::DIR_UP:
                bodynode->setPositionRC(lastBody->m_row - 1, lastBody->m_col);
                break;
            case ENUM_DIR::DIR_DOWN:
                bodynode->setPositionRC(lastBody->m_row + 1, lastBody->m_col);
                break;
            case ENUM_DIR::DIR_LEFT:
                bodynode->setPositionRC(lastBody->m_row, lastBody->m_col + 1);
                break;
            case ENUM_DIR::DIR_RIGHT:
                bodynode->setPositionRC(lastBody->m_row, lastBody->m_col - 1);
                break;
                
            default:
                break;
        }
    } else {
        
        bodynode->m_dir = spHead->m_dir;
        
        switch (bodynode->m_dir) {
            case ENUM_DIR::DIR_UP:
                bodynode->setPositionRC(spHead->m_row - 1, spHead->m_col);
                break;
            case ENUM_DIR::DIR_DOWN:
                bodynode->setPositionRC(spHead->m_row + 1, spHead->m_col);
                break;
            case ENUM_DIR::DIR_LEFT:
                bodynode->setPositionRC(spHead->m_row, spHead->m_col + 1);
                break;
            case ENUM_DIR::DIR_RIGHT:
                bodynode->setPositionRC(spHead->m_row, spHead->m_col - 1);
                break;
                
            default:
                break;
        }
    }
    this->addChild(bodynode);
    allBody.pushBack(bodynode);
}

void Game::moveBody() {
    
    if (allBody.size()==0) {
        return;
    }
    for (auto bodynode:allBody) {
        
        switch (bodynode->m_dir) {
            case ENUM_DIR::DIR_RIGHT:
                bodynode->runAction(MoveBy::create(0.3, Point(32,0)));
                bodynode->m_col++;
                break;
            case ENUM_DIR::DIR_LEFT:
                bodynode->runAction(MoveBy::create(0.3, Point(-32,0)));
                bodynode->m_col--;
                break;
            case ENUM_DIR::DIR_DOWN:
                bodynode->runAction(MoveBy::create(0.3, Point(0,-32)));
                bodynode->m_row--;
                break;
            case ENUM_DIR::DIR_UP:
                bodynode->runAction(MoveBy::create(0.3, Point(0,32)));
                bodynode->m_row++;
                break;
                
            default:
                break;
        }
    }
    
    //移动完成，改变每个body的方向
    for (int i = allBody.size()-1; i > 0; i--) {
        allBody.at(i)->m_dir = allBody.at(i-1)->m_dir;
    }
    allBody.at(0)->m_dir = spHead->m_dir;
}



















