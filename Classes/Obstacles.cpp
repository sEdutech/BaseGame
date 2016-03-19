#include "Obstacles.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d;


Obstacles::Obstacles()
{

}


Obstacles::~Obstacles()
{

}

void Obstacles::init(cocos2d::Node * root)
{	
	winSize = Director::getInstance()->getWinSize();

	fireHydrant = (Sprite *) root->getChildByName("FireHydrant");
	root->addChild(fireHydrant);

	fireHydrant->setPosition(winSize.width + 20, winSize.height / 4);

	trashCan = (Sprite *) root->getChildByName("TrashCan");
	root->addChild(trashCan);

	trashCan->setPosition(fireHydrant->getPositionX() + winSize.width, winSize.height / 4);

	float timer = 0.0f;

	fireHydrantDropping = false;

	trashCanDropping = false;

	fireHydrantOnScreen = false;

	trashCanOnScreen = false;
}

void Obstacles::update(float delta)
{
	//timer += delta

	if (trashCanDropping)
	{
		auto moveByTC = MoveBy::create(0, Vec2(0, -2));
		trashCan->runAction(moveByTC);
	}
	else
	{	
		auto moveByTC = MoveBy::create(0, Vec2(-3, 0));
		trashCan->runAction(moveByTC);	
	}

	if (fireHydrantDropping)
	{
		auto moveByFH = MoveBy::create(0, Vec2(0, -2));
		fireHydrant->runAction(moveByFH);
	}
	else
	{	
		auto moveByFH = MoveBy::create(0, Vec2(-3, 0));
		fireHydrant->runAction(moveByFH);
	}
	

	//if (timer > 13.0f)
	//{

	//}

	//if (timer > 24.0f)
	//{
	//	timer = 0.0f;
	//	fireHydrant->setPosition(winSize.width + 20, winSize.height / 4);
	//	trashCan->setPosition(winSize.width + 20, winSize.height / 4);
	//}

	//The obstacles need to be into an array, it would make everything much easier

	if (fireHydrant->getPositionX() < 0 || fireHydrant->getPositionY() + fireHydrant->getBoundingBox().size.height < 0)
	{
		fireHydrantOnScreen = false;
		fireHydrantDropping = false;
		if (trashCanOnScreen)
		{
			fireHydrant->setPosition(trashCan->getPositionX() + winSize.width , winSize.height / 4);
		}
		else
		{
			fireHydrant->setPosition(winSize.width + 20, winSize.height / 4);
		}
	}
	else
	{
		fireHydrantOnScreen = true;
	}

	if (trashCan->getPositionX() < 0 || trashCan->getPositionY() + trashCan->getBoundingBox().size.height < 0)
	{
		trashCanOnScreen = false;
		trashCanDropping = false;
		if (fireHydrantOnScreen)
		{
			trashCan->setPosition(fireHydrant->getPositionX() + winSize.width, winSize.height / 4);
		}
		else
		{
			trashCan->setPosition(winSize.width + 20, winSize.height / 4);
		}
	}
	else
	{
		trashCanOnScreen = true;
	}
}

