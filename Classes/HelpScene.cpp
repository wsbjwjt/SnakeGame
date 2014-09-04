//
//  HelpScene.cpp
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#include "HelpScene.h"
#include "MainMenu.h"

Scene* Help::createScene() {
    
    auto scene = Scene::create();
    auto layer = Help::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool Help::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    auto spriteBK = Sprite::create("menuback.png");
    
    spriteBK->setPosition(Point(size.width/2, size.height/2));
    spriteBK->setOpacity(75);
    this->addChild(spriteBK);
    
    //help infomation
    auto labelScore = Label::create("帮助信息", "宋体", 25);
    
    labelScore->setPosition(Point(size.width-80, size.height-50));
    this->addChild(labelScore);
    
    auto menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(Help::menuCallBack, this));
    
    menuItemBack->setPosition(Point(size.width-menuItemBack->getContentSize().width-100, menuItemBack->getContentSize().height+10));
    
    auto menu = Menu::create(menuItemBack, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    return true;
}

void Help::menuCallBack(Ref* object) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}