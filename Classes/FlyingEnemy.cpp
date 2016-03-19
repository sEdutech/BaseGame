#include "FlyingEnemy.h"


FlyingEnemy::FlyingEnemy(cocos2d::Node * root, Sprite* _paperBoy)
{
	birdSprite = (Sprite*)root->getChildByName("BirdSprite");
	UFOSprite = (Sprite*)root->getChildByName("BirdSprite");

	scaleX = birdSprite->getScaleX();
	Reset();

	mRoot = root;

	winSize = Director::getInstance()->getWinSize();

	paperBoy = _paperBoy;
}


FlyingEnemy::~FlyingEnemy()
{

}

void FlyingEnemy::SpawnEnemy()
{
	rand = cocos2d::RandomHelper::random_int(1, 50);

	auto callAct = CallFunc::create(CC_CALLBACK_0(FlyingEnemy::Reset, this));

	if (rand == 13)
	{
		enemyType = UFOLeft;
		UFOSprite->setPosition(-30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
		UFOSprite->setVisible(true);
	}
	else if (rand == 38)
	{
		enemyType = UFORight;
		UFOSprite->setPosition(Director::getInstance()->getVisibleSize().width + 30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
		UFOSprite->setVisible(true);
	}
	else if (rand >= 25)
	{
		enemyType = BirdLeft;
		birdSprite->setScaleX(birdSprite->getScaleX() * -1);
		birdSprite->setPosition(-30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
		birdSprite->setVisible(true);

		auto moveRightFirst = MoveTo::create(3, Vec2(winSize.width / 4, birdSprite->getPositionY()));
		auto moveDown = MoveTo::create(2, Vec2(paperBoy->getPosition()));
		auto moveUp = MoveTo::create(3, Vec2(winSize.width / 4 * 3, (Director::getInstance()->getVisibleSize().height / 4) * 3));
		auto moveRightSecond = MoveTo::create(2, Vec2(winSize.width, birdSprite->getPositionY()));
		birdSprite->runAction(Sequence::create(moveRightFirst, moveDown, moveUp, moveRightSecond, callAct, nullptr));

	}
	else if (rand < 25)
	{
		enemyType = BirdRight;
		birdSprite->setPosition(Director::getInstance()->getVisibleSize().width + 30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
		birdSprite->setVisible(true);

		auto moveLeftFirst = MoveTo::create(3, Vec2(winSize.width / 4 * 3, birdSprite->getPositionY()));
		auto moveDown = MoveTo::create(2, Vec2(paperBoy->getPosition()));
		auto moveUp = MoveTo::create(3, Vec2(winSize.width / 4, (Director::getInstance()->getVisibleSize().height / 4) * 3));
		auto moveLeftSecond = MoveTo::create(2, Vec2(-30, birdSprite->getPositionY()));
		birdSprite->runAction(Sequence::create(moveLeftFirst, moveDown, moveUp, moveLeftSecond, callAct, nullptr));
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
		
	}
}

void FlyingEnemy::Reset()
{
	UFOSprite->setVisible(false);
	birdSprite->setVisible(false);
	birdSprite->setScaleX(scaleX);
	birdSprite->setPosition(-30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
	UFOSprite->setPosition(-30, (Director::getInstance()->getVisibleSize().height / 4) * 3);
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

void FlyingEnemy::Run()
{		
	birdSprite->stopAllActions();
	auto callAct = CallFunc::create(CC_CALLBACK_0(FlyingEnemy::Reset, this));
	switch (enemyType)
	{

	case BirdLeft:
	{
		auto moveToRight = MoveTo::create(3, Vec2(Director::getInstance()->getVisibleSize().width, birdSprite->getPositionY()));
		birdSprite->runAction(Sequence::create(moveToRight, callAct, nullptr));
		break;
	}
	case BirdRight:
	{
		auto moveToLeft = MoveTo::create(3, Vec2(-20, birdSprite->getPositionY()));
		birdSprite->runAction(Sequence::create(moveToLeft, callAct, nullptr));
		break;
	}

	}
}