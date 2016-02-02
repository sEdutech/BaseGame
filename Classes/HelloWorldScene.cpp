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

	winSize = Director::sharedDirector()->getWinSize();

	initHouse();

	this->scheduleUpdate();

	return true;
}

void HelloWorld::initHouse()
{
	auto rootNode = this->getChildByName("Scene");

	for (int i = 0; i < 2; i++)
	{
		houses[i] = new House();
		//Will need to change when have different sprites
		houses[i]->houseSprite = (Sprite*)rootNode->getChildByName("house_" + to_string(i));
		//Also need to add init for windows and doors when available - make them children of house
		houses[i]->speed = 1;
	}
}

void HelloWorld::update(float t)
{
	updateHouse(t);
}

void HelloWorld::updateHouse(float t)
{
	for (int i = 0; i < 2; i++)
	{
		//Move Left
		houses[i]->houseSprite->setPositionX(houses[i]->houseSprite->getPositionX() + houses[i]->speed);

		//Wrap around
		if (houses[i]->houseSprite->getPositionX() > winSize.width)
		{
			houses[i]->houseSprite->setPositionX(0 - houses[i]->houseSprite->getBoundingBox().size.width);
		}

		//Bob up and down
		houses[i]->houseSprite->setPositionY((sin(houses[i]->houseSprite->getPositionX() / 10) * 4 + 125)); //Divide by 10 slows it down, multiply by 4 to increase how much it bobs by and add 125 to increase overall height.
	}
}
