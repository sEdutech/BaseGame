#pragma once
#include "cocos2d.h"
#include <stdio.h>
#include <sstream>

using namespace cocos2d;
using namespace std;

struct Newspaper
{
	Sprite* sprite;
	bool thrown;
	bool active;
	Vec2 trajectory;
};
class PaperBoy : public cocos2d::Node
{
public:
	PaperBoy();
	~PaperBoy();
	virtual bool init() override;

	PaperBoy* create();	
	Sprite* getPaperboySprite() { return mPaperBoySprite; };

	Newspaper* getNewspaper(int i) { return newspapers[i]; };
	int getNumOfNewspapers() { return totalNumNewspapers; };
	int getActiveNewspaper();
	void throwPaper(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);
	void moveOffscreen(int i);

	bool getReloadActive() { return reloadActive; };
	Sprite* getReloadButton() { return reloadSprite; };
	void reloadNewspapers();

	void update(float delta);

private:
	Sprite* mPaperBoySprite;
	
	Sprite* reloadSprite;
	bool reloadActive;

	static const int totalNumNewspapers = 3;
	int currentNumNewspapers = totalNumNewspapers;
	
	Newspaper* newspapers[totalNumNewspapers];

	Size mWinSize;

	Rect window;

	float projectileSpeed;
};

