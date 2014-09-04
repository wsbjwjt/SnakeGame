//
//  MainMenu.cpp
//  SnakeGame
//
//  Created by Eric Wang on 14-9-3.
//
//

#include "MainMenu.h"
#include "GameScene.h"
#include "HelpScene.h"


Scene* MainMenu::createScene() {
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    
    scene->addChild(layer);
    return scene;
}


bool MainMenu::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    auto spriteBK = Sprite::create("menuback.png");
    
    spriteBK->setPosition(Point(size.width/2, size.height/2));
    this->addChild(spriteBK);
    
    auto menuItemStart = MenuItemFont::create("Start", CC_CALLBACK_1(MainMenu::menuCallBack, this));
    menuItemStart->setTag(1);
    menuItemStart->setPosition(Point(size.width-menuItemStart->getContentSize().width-100, menuItemStart->getContentSize().height+10));
    
    auto menuItemHelp = MenuItemFont::create("Help", CC_CALLBACK_1(MainMenu::menuCallBack, this));
    menuItemHelp->setTag(2);
    menuItemHelp->setPosition(Point(size.width-menuItemHelp->getContentSize().width-10, menuItemHelp->getContentSize().height+10));
    
    auto menu = Menu::create(menuItemStart, menuItemHelp, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    
    return true;
}

void MainMenu::menuCallBack(Ref* object) {
    auto target = (Node* )object;
    
    Scene* scene;
    
    switch (target->getTag()) {
        case 1:
            scene = Game::createScene();
            break;
        case 2:
            scene = Help::createScene();
            break;

        default:
            break;
    }
    Director::getInstance()->replaceScene(scene);
    
}
