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
	Newspaper* getNewspaper(int i) { return newspapers[i]; };
	int getNumOfNewspapers() { return totalNumNewspapers; };
	void throwPaper(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);
	bool getReloadActive() { return reloadActive; };
	Sprite* getReloadButton() { return reloadSprite; };
	int getActiveNewspaper();
	void reloadNewspapers();
	void moveOffscreen(int i);
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

