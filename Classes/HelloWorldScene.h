#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <sstream>
#include "Policeman.h"
#include "PaperBoy.h"

using namespace cocos2d;
using namespace std;

struct House
{
	Sprite* houseSprite;

	Sprite* windowBLSprite;
	bool windowBLHit;

	Sprite* windowTLSprite;
	bool windowTLHit;

	Sprite* windowTRSprite;
	bool windowTRHit;

	Sprite* doorSprite;
	bool doorHit;

	int speed;
};

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//Init Methods
	void initHouse();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	//Update Methods
	void update(float t);

	void updateHouseMovement();

	void updateHouseCollision();

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

private:
	//House
	int numHouses = 3;
	House* houses[3];
	Size winSize;
	Policeman* policeman;
	Vec2 touchStart;
	Vec2 touchEnd;
};

#endif // __HELLOWORLD_SCENE_H__