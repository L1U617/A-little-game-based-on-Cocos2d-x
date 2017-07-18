#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

class InfoNode : public cocos2d::Sprite//关卡信息类
{
public:
	int type;//关卡标号
	static InfoNode *create(int type);//创建节点
	virtual bool init(int type);//初始化节点
};

class MapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int type);//创建场景，调用create函数
	static MapScene*create(int type);//调用init函数
	virtual bool init(int type);//初始化

	void menuCloseCallback(cocos2d::Ref *pSender);//回调函数

	void showInfo(int x,int y,cocos2d::MenuItemImage* item, InfoNode *&showinfo);//显示关卡信息
	bool judge(int x, int y, cocos2d::MenuItemImage* item);//判断鼠标悬停位置
};
#endif
