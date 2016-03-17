#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <sstream>
#include "Policeman.h"
#include "PaperBoy.h"
#include "FlyingEnemy.h"
#include "SuperPaperCollectable.h"

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

	bool onScreen;
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

	void initForegroundObjects(Node* root);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	//Update Methods
	void update(float t);

	void updateHouseMovement();

	void updateCloudMovement();

	void updateHouseCollision();

	void updateStage(float);

	void handleCollectableCollisions();

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

private:
	//House
	int numHouses = 3;
	House* houses[3];

	Sprite* clouds[5];
	float cloudSpeed;
	int numClouds = 5;

	Size winSize;
	
	Policeman* policeman;
	
	Vec2 touchStart;
	Vec2 touchEnd;

	FlyingEnemy* birdEnemy;

	float worldSpeed;

	//Score
	Label* _scoreLabel;
	int _scoreCounter;

	//sprites that need to be infront of characters
	cocos2d::Sprite* curtain1;
	cocos2d::Sprite* curtain2;
	cocos2d::Sprite* beltWheel1;
	cocos2d::Sprite* beltWheel2;
	cocos2d::Sprite* beltWheel3;
	cocos2d::Sprite* beltWheel4;
	cocos2d::Sprite* beltWheel5;
	cocos2d::Sprite* beltWheel6;
	cocos2d::Sprite* beltWheel7;
	cocos2d::Sprite* beltWheel8;
	cocos2d::Sprite* beltWheel9;

	cocos2d::Sprite* beltTopForeground;
	cocos2d::Sprite* beltTopBackground;
	cocos2d::Sprite* beltbottom;
	cocos2d::Sprite* beltBackground;

	//Collectible
	vector<Collectable *> collectables;
};

#endif // __HELLOWORLD_SCENE_H__