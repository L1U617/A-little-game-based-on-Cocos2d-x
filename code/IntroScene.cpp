#include "HelloWorldScene.h"
#include "IntroScene.h"
USING_NS_CC;
Scene* Intro::createScene()//创建场景
{
	auto scene = Scene::create();
	auto layer = Intro::create();//函数中调用了初始化
	scene->addChild(layer);
	return scene;
}

bool Intro::init()//初始化
{

	if (!Layer::init())
	{
		return false;//初始化失败则返回false
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设置背景
	auto spriteBK = Sprite::create("Bk\\introscene.png");
	spriteBK->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spriteBK);
	//设置返回按钮并添加回调函数
	auto backItem = MenuItemImage::create("button\\back.png", "button\\backSelected.png",
		CC_CALLBACK_1(Intro::menuCloseCallback, this));
	backItem->setPosition(Point(788, 56));
	backItem->setTag(1);

	
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Intro::menuCloseCallback(Ref* object)//回调函数
{
	auto target = (Node*)object;

	Scene *scene;
	switch (target->getTag()){
    case 1://返回开始菜单
	{
		scene =HelloWorld::createScene();
		Director::getInstance()->replaceScene(scene);

	}
		break;
	
	default:break;
	}
}
