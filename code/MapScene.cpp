#include "HelloWorldScene.h"
#include "MapScene.h"
#include"GameScene.h"
#include"cocos2d.h"
USING_NS_CC;

static MenuItemImage *bks, *bank, *square, *spc;//定义地图上的各关卡点位全局变量

Scene* MapScene::createScene(int type)//创建场景
{
	auto scene = Scene::create();
	auto layer = MapScene::create(type);//create函数调用初始化程序
	scene->addChild(layer);
	return scene;
}

MapScene *MapScene::create(int type){//create函数
	MapScene* mapS = new MapScene();
	if (mapS&&mapS->init(type)){//调用init并判断是否初始化成功
		mapS->autorelease();
		return mapS;
	}
	else
	{
		delete mapS;
		mapS = NULL;
		return nullptr;
	}
}

bool MapScene::init(int type)//初始化函数
{

	if (!Layer::init())//初始化不成功，返回false
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建背景
	auto spriteBK = Sprite::create("map\\map.png");
	spriteBK->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spriteBK);
    //创建返回按钮
	auto backItem = MenuItemImage::create("button\\back_2.png", "button\\backSelected.png",
		CC_CALLBACK_1(MapScene::menuCloseCallback, this));
	backItem->setPosition(Point(788, 56));
	backItem->setTag(0);
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	/*设置各节点信息：
	 *“贝克街“、”银行“、”广场“、”教堂区”
	 */
	
	//创建“贝克街”处图标并设置tag
	bks= MenuItemImage::create("node\\bks.png", "node\\bks.png",
			CC_CALLBACK_1(MapScene::menuCloseCallback, this));
	bks->setTag(1);
	//同理，创建”教堂区“处图标
	if (type >= 2)
	{
		spc = MenuItemImage::create("node\\spcAvailable.png", "node\\spcAvailable.png",
			CC_CALLBACK_1(MapScene::menuCloseCallback, this));
		spc->setTag(2);
	}
	else
		spc = MenuItemImage::create("node\\spc.png", "node\\spc.png",
		CC_CALLBACK_1(MapScene::menuCloseCallback, this));
	//同理，创建”广场“处图标,有可选和不可选两种
	if ( type>= 3)
	{
		square = MenuItemImage::create("node\\squareAvailable.png", "node\\squareAvailable.png",
			CC_CALLBACK_1(MapScene::menuCloseCallback, this));
		square->setTag(3);
	}	    
	else
		square = MenuItemImage::create("node\\square.png", "node\\square.png",
		CC_CALLBACK_1(MapScene::menuCloseCallback, this));
	//同理，创建”银行“处图标
	if (type >= 4)
	{
		bank = MenuItemImage::create("node\\bankAvailable.png", "node\\bankAvailable.png",
			CC_CALLBACK_1(MapScene::menuCloseCallback, this));
		bank->setTag(4);
	}
	else
		bank = MenuItemImage::create("node\\bank.png", "node\\bank.png",
		CC_CALLBACK_1(MapScene::menuCloseCallback, this));
	
	//下面将各点放置在相应位置
	bks->setPosition(Point(266, 454));
	square->setPosition(Point(708, 206));
	bank->setPosition(Point(802, 229));
	spc->setPosition(Point(919, 303));
	//将以上创建好的图标存入可选择菜单中
	auto mapnode = Menu::create(bks,bank,square,spc, NULL);
	mapnode->setPosition(Vec2::ZERO);
	this->addChild(mapnode,1);
	static InfoNode *bksInfo;
	static InfoNode *spcInfo; 
	static InfoNode *squareInfo; 
	static InfoNode *bankInfo;
    //创建鼠标监听器
	auto Listener_1 = EventListenerMouse::create();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener_1, this);
	Listener_1->onMouseMove = [=](Event* event){//鼠标移动信号
		EventMouse *e = (EventMouse*)event;
		int x = e->getCursorX();
		int y = e->getCursorY();//获得鼠标指针坐标
		showInfo(x, y, bks,bksInfo);//判断指针是否悬停在图标上并显示信息
		showInfo(x, y, spc,spcInfo); 
		showInfo(x, y, square,squareInfo);
		showInfo(x, y, bank,bankInfo);
	};
	
	return true;
}

void MapScene::menuCloseCallback(Ref* object)//回调函数
{
	auto target = (Node*)object;

	Scene *scene;
	switch (target->getTag()){
	case 0://返回按钮返回开始菜单
	{
		scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(scene);

	}
	break;
	case 1://进入第一关
	{
		scene = GameStart::createScene(1);
		Director::getInstance()->replaceScene(scene);

	}break;
	case 2://进入第二关
	{
		scene = GameStart::createScene(2);
		Director::getInstance()->replaceScene(scene);
	}break;
	case 3://进入第三关
	{
		scene = GameStart::createScene(3);
		Director::getInstance()->replaceScene(scene);
	}break;
	case 4://进入第四关
	{
		scene = GameStart::createScene(4);
		Director::getInstance()->replaceScene(scene);
	}break;
	default:break;
	}
}

bool MapScene::judge(int x, int y, MenuItemImage* item){//判断鼠标指针是否悬停在图标上
	/*通过坐标的计算进行判断，
	 鼠标指针在图标锚点周围20像素处为有效悬停范围*/
	if (x<(item->getPositionX() + 20)
		&& x>(item->getPositionX() - 20)
		&& y < (item->getPositionY() + 20)
		&& y >(item->getPositionY() - 20))
		return true;
	else
		return false;
}

InfoNode *InfoNode::create(int type){//创建信息节点
	InfoNode *pRet = new InfoNode();
	if (pRet&&pRet->init(type)){
		pRet->autorelease();
		return pRet;
	}
	else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool InfoNode::init(int type){//信息页面的初始化
	if (!Sprite::init()){
		return false;
	}
	switch (type){//根据不同的标记显示不同的信息
	case 1:
	{
		auto sprite = Sprite::create("info\\bks.png");
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(sprite);
	}
	break;
	case 2:
	{
		auto sprite = Sprite::create("info\\spc.png");
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(sprite);
	}
	break;
	case 3:
	{
		auto sprite = Sprite::create("info\\square.png");
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(sprite);
	}
	break;
	case 4:
	{
		auto sprite = Sprite::create("info\\bank.png");
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(sprite);
	}
	break;
	default: break;
	}
	return true;
}

void MapScene::showInfo(int x,int y,cocos2d::MenuItemImage* item,InfoNode* &showinfo){
	if (judge(x, y, item)){//如果鼠标悬停在图标上就显示信息
		if (!showinfo){
			showinfo = InfoNode::create(item->getTag());
			this->addChild(showinfo);
			showinfo->setPosition(Point(480, 320));
		}
	}
	else if (!judge(x, y, item)){//鼠标没有在图标上就不显示信息
		this->removeChild(showinfo);
		showinfo = false;
	}
}
