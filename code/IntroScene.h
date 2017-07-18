#ifndef __INTROSCENE_SCENE_H__
#define __INTROSCENE_SCENE_H__

#include "cocos2d.h"

class Intro : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();//创建场景
	virtual bool init();//初始化场景

	void menuCloseCallback(cocos2d::Ref *pSender);//回调函数
	CREATE_FUNC(Intro);//创建函数，调用初始化函数
};

#endif
