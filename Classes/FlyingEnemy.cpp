#include "FlyingEnemy.h"


FlyingEnemy::FlyingEnemy(cocos2d::Node * root)
{
	birdSprite = (Sprite*)root->getChildByName("BirdSprite");
	UFOSprite = (Sprite*)root->getChildByName("BirdSprite");

	Reset();

	mRoot = root;
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::SpawnEnemy()
{
	rand = cocos2d::RandomHelper::random_int(1, 50);

	if (rand == 13)
	{
		enemyType = UFOLeft;
		UFOSprite->setPosition(-30, Director::getInstance()->getVisibleSize().height / 2);
		UFOSprite->setVisible(true);
	}
	else if (rand == 38)
	{
		enemyType = UFORight;
		UFOSprite->setPosition(Director::getInstance()->getVisibleSize().width + 30, Director::getInstance()->getVisibleSize().height / 2);
		UFOSprite->setVisible(true);
	}
	else if (rand >= 25)
	{
		enemyType = BirdLeft;
		birdSprite->setPosition(-30, Director::getInstance()->getVisibleSize().height / 2);
		birdSprite->setVisible(true);
	}
	else if (rand < 25)
	{
		enemyType = BirdRight;
		birdSprite->setPosition(Director::getInstance()->getVisibleSize().width + 30, Director::getInstance()->getVisibleSize().height / 2);
		birdSprite->setVisible(true);
	}
}

void FlyingEnemy::Update()
{
	switch (enemyType){
	case Start:
		timeCount++;
		if (timeCount >= randTime)
		{
			SpawnEnemy();
		}
		break;

	case UFOLeft:
		UFOSprite->setPosition(UFOSprite->getPosition().x + 1, UFOSprite->getPosition().y);
		if (UFOSprite->getPosition().x >= Director::getInstance()->getVisibleSize().width + 30)
		{
			Reset();
		}
		break;

	case UFORight:
		UFOSprite->setPosition(UFOSprite->getPosition().x - 1, UFOSprite->getPosition().y);
		if (UFOSprite->getPosition().x <= -30)
		{
			Reset();
		}
		break;

	case BirdLeft:
		birdSprite->setPosition(birdSprite->getPosition().x + 1, birdSprite->getPosition().y);
		if (birdSprite->getPosition().x >= Director::getInstance()->getVisibleSize().width + 30)
		{
			Reset();
		}
		break;

	case BirdRight:
		birdSprite->setPosition(birdSprite->getPosition().x - 1, birdSprite->getPosition().y);
		if (UFOSprite->getPosition().x <= -30)
		{
			Reset();
		}
		break;
	}
}

void FlyingEnemy::Reset()
{
	UFOSprite->setVisible(false);
	birdSprite->setVisible(false);
	birdSprite->setPosition(-30, Director::getInstance()->getVisibleSize().height/2);
	UFOSprite->setPosition(-30, Director::getInstance()->getVisibleSize().height / 2);
	timeCount = 0;
	randTime = cocos2d::RandomHelper::random_int(180, 200);
	enemyType = Start;
}

cocos2d::Rect FlyingEnemy::getRect()
{
	switch (enemyType)
	{
	case Start:
		return birdSprite->getBoundingBox();
		break;
	case UFOLeft:
		return UFOSprite->getBoundingBox();
		break;
	case UFORight:
		return UFOSprite->getBoundingBox();
		break;
	case BirdLeft:
		return birdSprite->getBoundingBox();
		break;
	case BirdRight:
		return birdSprite->getBoundingBox();
	}
}