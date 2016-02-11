#pragma once
#include "cocos2d.h"
#include <stdio.h>
#include "HelloWorldScene.h"

using namespace cocos2d;

class PaperBoy : public cocos2d::Node
{
public:
	PaperBoy();
	~PaperBoy();

	virtual bool init() override;
	PaperBoy* create();
	Sprite* getNewspaper() { return mPaperMoving; };
	void throwPaper(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);
	void resetNewspaper();
	void update(float delta);

private:
	cocos2d::Sprite* mPaperBoySprite;
	cocos2d::Sprite* mPaperMoving;

	cocos2d::Size mWinSize;

	Rect window;

	float projectileSpeed;

	Vec2 trajectory;

	bool mPaperThrown;
};

