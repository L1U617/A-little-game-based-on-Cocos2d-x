#include "HelloWorldScene.h"
#include "IntroScene.h"
#include"MapScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()//初始化场景
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设置背景
	auto spriteBK = Sprite::create("Bk\\helloscene.png");
	spriteBK->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spriteBK);
	//添加菜单元素，并添加了回调函数
	auto startItem=MenuItemImage::create("button\\start.png","button\\startSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//开始新游戏
	startItem->setPosition(Point(141,466));
	startItem->setTag(1);//设置标记

	auto loadItem = MenuItemImage::create("button\\load.png","button\\loadSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//继续游戏，暂时没用……
	loadItem->setPosition(Point(129, 416));
	loadItem->setTag(2);

	auto introItem=MenuItemImage::create("button\\intro.png","button\\introSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//玩法介绍
	introItem->setPosition(Point(129, 366));
	introItem->setTag(3);

	auto closeItem = MenuItemImage::create("button\\quit.png","button\\quitSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//退出
	closeItem->setPosition(Point(104, 316));
	closeItem->setTag(4);

	auto menu = Menu::create(closeItem,startItem,introItem,loadItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);//添加子节点
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* object)//回调函数
{
	auto target = (Node*)object;

	Scene *scene;
	switch (target->getTag()){
	case 1://点击开始新游戏，进入关卡图界面
	{
		scene = MapScene::createScene(1);
		Director::getInstance()->replaceScene(scene);
	}
	break;
	case 3://点击玩法介绍，进入玩法介绍界面
	{
		scene = Intro::createScene();
		Director::getInstance()->replaceScene(scene);

	}
	break;
	case 4://点击退出，结束游戏
		Director::getInstance()->end();
		break;
	default:break;
	}
}
