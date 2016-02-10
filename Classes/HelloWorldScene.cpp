#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

PaperBoy* paperBoy;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");

	addChild(rootNode);

	winSize = Director::getInstance()->getWinSize();

	initHouse();
	policeman = new Policeman();
	policeman->init(rootNode);


	paperBoy = new PaperBoy();
	paperBoy->init();
	
	addChild(paperBoy);

	this->scheduleUpdate();

	auto touchListener = EventListenerTouchOneByOne::create();	
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);	
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);	
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);	
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void HelloWorld::initHouse()
{
	auto rootNode = this->getChildByName("Scene");

	for (int i = 0; i < numHouses; i++)
	{
		houses[i] = new House();
		//Will need to change when have different sprites
		stringstream house; //Cant use to_string
		house << "house_" << i;
		houses[i]->houseSprite = (Sprite*)rootNode->getChildByName(house.str());

		//Doors
		stringstream door; 
		door << "house_" << i << "_door";
		houses[i]->doorSprite = (Sprite*)rootNode->getChildByName(door.str());

		//BL windows
		stringstream BLWindow;
		BLWindow << "house_" << i << "_windowBL";
		houses[i]->windowBLSprite = (Sprite*)rootNode->getChildByName(BLWindow.str());
		houses[i]->windowBLHit = false;

		//TL windows
		stringstream TLWindow;
		TLWindow << "house_" << i << "_windowTL";
		houses[i]->windowTLSprite = (Sprite*)rootNode->getChildByName(TLWindow.str());
		houses[i]->windowTLHit = false;

		//TR windows
		stringstream TRWindow;
		TRWindow << "house_" << i << "_windowTR";
		houses[i]->windowTRSprite = (Sprite*)rootNode->getChildByName(TRWindow.str());
		houses[i]->windowTRHit = false;

		houses[i]->speed = 1;
	}
}

void HelloWorld::update(float t)
{
	updateHouseMovement();
	updateHouseCollision();
	policeman->update(t);
	paperBoy->update(t);
}

void HelloWorld::updateHouseMovement()
{
	//Movement
	for (int i = 0; i < numHouses; i++)
	{
		//Move Left
		houses[i]->houseSprite->setPositionX(houses[i]->houseSprite->getPositionX() - houses[i]->speed);

		//Bob up and down
		houses[i]->houseSprite->setPositionY((sin(houses[i]->houseSprite->getPositionX() / 10) * 8 + 125)); //Divide by 10 slows it down, multiply by 8 to increase how much it bobs by and add 125 to increase overall height.

		//Wrap around
		if (houses[i]->houseSprite->getPositionX() < (0 - houses[i]->houseSprite->getBoundingBox().size.width))
		{
			int distance = 550;
			if (i == 0)
			{
				houses[i]->houseSprite->setPositionX(houses[2]->houseSprite->getPositionX() + distance);
			}
			else
			{
				houses[i]->houseSprite->setPositionX(houses[i - 1]->houseSprite->getPositionX() + distance);
			}
		}

		if (!houses[i]->doorHit)
		{
			//Move doors with house
			houses[i]->doorSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 172.83);
			houses[i]->doorSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 138.17);
		}

		if (!houses[i]->windowBLHit)
		{
			//Move BL window with house
			houses[i]->windowBLSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 57.08);
			houses[i]->windowBLSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 151.62);
		}
		if (!houses[i]->windowTLHit)
		{
			//Move TL window with house
			houses[i]->windowTLSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 58);
			houses[i]->windowTLSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 250);
		}
		if (!houses[i]->windowTRHit)
		{
			//Move TR window with house
			houses[i]->windowTRSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 203.66);
			houses[i]->windowTRSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 249.18);
		}
	}
}

void HelloWorld::updateHouseCollision()
{
	//If newspaper collides with door...

	//Else If newspaper collides with window BL...

	//Else If newspaper collides with window TL...

	//Else If newspaper collides with window TR...

	//Else player missed
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchStart = touch->getLocation();
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchEnd = touch->getLocation();
	paperBoy->throwPaper(touchStart, touchEnd);
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}