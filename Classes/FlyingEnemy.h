#pragma once

#include "cocos2d.h"
#include <stdio.h>
//#include "HelloWorldScene.h"

using namespace cocos2d;

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
	FlyingEnemy(cocos2d::Node * root);
	~FlyingEnemy();

	void SpawnEnemy();
	//maybe used later
	void AttackPlayer();
	void Reset();
	void Update();

	cocos2d::Rect getRect();

private:
	cocos2d::Sprite* birdSprite;
	cocos2d::Sprite* UFOSprite;

	cocos2d::Node* mRoot;

	type enemyType = Start;

	float rand;
	float randTime;
	float timeCount;

	float scaleX;
};

