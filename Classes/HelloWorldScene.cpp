#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//test commit

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

	this->scheduleUpdate();

	return true;
}

void HelloWorld::initHouse()
{
	auto rootNode = this->getChildByName("Scene");

	for (int i = 0; i < numHouses; i++)
	{
		houses[i] = new House();
		//Will need to change when have different sprites
		houses[i]->houseSprite = (Sprite*)rootNode->getChildByName("house_" + to_string(i));
		//Doors
		houses[i]->doorSprite = (Sprite*)rootNode->getChildByName("house_" + to_string(i) + "_door");
		//houses[i]->houseSprite->addChild(houses[i]->doorSprite);
		//houses[i]->doorSprite->setScale(1);
		//Also need to add init for windows and doors when available - make them children of house
		houses[i]->speed = 1;
	}
}

void HelloWorld::update(float t)
{
	updateHouseMovement();
	updateHouseCollision();
}

void HelloWorld::updateHouseMovement()
{
	//Movement
	for (int i = 0; i < numHouses; i++)
	{
		//Move Left
		houses[i]->houseSprite->setPositionX(houses[i]->houseSprite->getPositionX() - houses[i]->speed);
		houses[i]->doorSprite->setPositionX(houses[i]->doorSprite->getPositionX() - houses[i]->speed);

		//Bob up and down
		houses[i]->houseSprite->setPositionY((sin(houses[i]->houseSprite->getPositionX() / 10) * 8 + 125)); //Divide by 10 slows it down, multiply by 8 to increase how much it bobs by and add 125 to increase overall height.
		houses[i]->doorSprite->setPositionY((sin(houses[i]->houseSprite->getPositionX() / 10) * 8 + (2.464 * 125) /*Equals 308 - makes it relative*/));

		//Wrap around
		if (houses[i]->houseSprite->getPositionX() < (0 - houses[i]->houseSprite->getBoundingBox().size.width))
		{
			int distance = 550;
			if (i == 0)
			{
				houses[i]->houseSprite->setPositionX(houses[2]->houseSprite->getPositionX() + distance);
				houses[i]->doorSprite->setPositionX(houses[2]->doorSprite->getPositionX() + distance);
			}
			else
			{
				houses[i]->houseSprite->setPositionX(houses[i - 1]->houseSprite->getPositionX() + distance);
				houses[i]->doorSprite->setPositionX(houses[i - 1]->doorSprite->getPositionX() + distance);
			}
		}
	}
}

void HelloWorld::updateHouseCollision()
{
	//If newspaper collides with door...

	//Else If newspaper collides with window 1...

	//Else If newspaper collides with window 2...

	//Else If newspaper collides with window 3...

	//Else player missed
}