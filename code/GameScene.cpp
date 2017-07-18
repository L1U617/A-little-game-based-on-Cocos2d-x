#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BlockNode :public cocos2d::Sprite
{
public:
	static BlockNode *create(int type);
	virtual bool init(int type);
	bool valid;//方块是否可以被放置到此处
};

class GameStart:public cocos2d::Layer{
public:
	BlockNode *block;
	int score;
	int sceneType;

	static cocos2d::Scene *createScene(int type);
	static GameStart *create(int type);//自定义一个可以更据type的不同创建不同场景的函数
	virtual bool init(int type);
    
	void menuCloseCallBack(cocos2d::Ref* pSender);

	void createBlock(BlockNode *usableBlock[], int num, BlockNode *blockAreaOn[][6]);//产生可用的方块

	bool startDrag(int mouse_x, int mouse_y, BlockNode *&block);//判断鼠标是否拖动方块
	bool judgePlace(int mouse_x, int mouse_y, BlockNode *&block,BlockNode *blockAreaOn[][6]);//判断是否能放置方块,并调用placeBlock函数
	void placeBlock(int i, int j, BlockNode* block,BlockNode *blockAreaOn[][6]);//放置方块，并调用judgeClear函数判断是否消除

	void judgeClear(int i,int j,BlockNode *blockAreaOn[][6]);//判断消除并更新分数
	bool judgeOver(int type,BlockNode *blockAreaOn[][6]);//判断是否无法继续放置，此函数由createBlock函数调用
	
};

class Result :public cocos2d::Layer
{
public:
	static Result *create(int resultType, int gameSceneType);
	virtual bool init(int resultType, int gameSceneType);
	void menuCloseCallBack(cocos2d::Ref* pSender);
	int result;
};

#endif
