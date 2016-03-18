#pragma once

#include "cocos2d.h"
#include <stdio.h>
//#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace std;

enum type
{
	Start,
	UFOLeft,
	UFORight,
	BirdLeft,
	BirdRight
};

class FlyingEnemy
{
public:
	FlyingEnemy(cocos2d::Node * root, Sprite* _paperBoy);
	~FlyingEnemy();

	void SpawnEnemy();
	//maybe used later
	void AttackPlayer();
	void Reset();
	void Update();
	void Run();

	cocos2d::Rect getRect();

private:
	cocos2d::Sprite* birdSprite;
	cocos2d::Sprite* UFOSprite;

	Sprite* paperBoy;

	cocos2d::Node* mRoot;

	type enemyType = Start;

	float rand;
	float randTime;
	float timeCount;

	Size winSize;

	float scaleX;

	float birdMoveSpeed = 2.0f;
};

