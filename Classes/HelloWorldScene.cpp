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
	initForegroundObjects(rootNode);
	policeman = new Policeman();
	policeman->init(rootNode);


	paperBoy = new PaperBoy();
	paperBoy->init();

	policeman->setDistance((paperBoy->getPaperBoySprite()->getPosition().x - policeman->getSprite()->getPosition().x) / 4);
	
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

void HelloWorld::initForegroundObjects(Node* root)
{
	curtain1 = (Sprite*)root->getChildByName("curtainleft_3");
	curtain2 = (Sprite*)root->getChildByName("curtainleft_2");
	beltWheel1 = (Sprite*)root->getChildByName("beltwheel_11");
	beltWheel2 = (Sprite*)root->getChildByName("beltwheel_11_0");
	beltWheel3 = (Sprite*)root->getChildByName("beltwheel_11_1");
	beltWheel4 = (Sprite*)root->getChildByName("beltwheel_11_2");
	beltWheel5 = (Sprite*)root->getChildByName("beltwheel_11_3");
	beltWheel6 = (Sprite*)root->getChildByName("beltwheel_11_4");
	beltWheel7 = (Sprite*)root->getChildByName("beltwheel_11_5");
	beltWheel8 = (Sprite*)root->getChildByName("beltwheel_11_6");
	beltWheel9 = (Sprite*)root->getChildByName("beltwheel_11_7");
	beltTopForeground = (Sprite*)root->getChildByName("Sprite_8");
	beltbottom = (Sprite*)root->getChildByName("beltbottom_9");
	beltBackground = (Sprite*)root->getChildByName("beltbackground_10");


	root->addChild(curtain1);
	root->addChild(curtain2);

	root->addChild(beltWheel1);
	root->addChild(beltWheel2);
	root->addChild(beltWheel3);
	root->addChild(beltWheel4);
	root->addChild(beltWheel5);
	root->addChild(beltWheel6);
	root->addChild(beltWheel7);
	root->addChild(beltWheel8);
	root->addChild(beltWheel9);

	root->addChild(beltTopForeground);
	root->addChild(beltbottom);
	root->addChild(beltBackground);

	curtain1->setGlobalZOrder(4);
	curtain2->setGlobalZOrder(4);
	beltWheel1->setGlobalZOrder(3);
	beltWheel2->setGlobalZOrder(3);
	beltWheel3->setGlobalZOrder(3);
	beltWheel4->setGlobalZOrder(3);
	beltWheel5->setGlobalZOrder(3);
	beltWheel6->setGlobalZOrder(3);
	beltWheel7->setGlobalZOrder(3);
	beltWheel8->setGlobalZOrder(3);
	beltWheel9->setGlobalZOrder(3);

	beltTopForeground->setGlobalZOrder(2);
	beltbottom->setGlobalZOrder(2);
	beltBackground->setGlobalZOrder(1);

	
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
		houses[i]->doorHit = false;

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
	updateHouseCollision(t);
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

		if (houses[i]->onScreen == false)
		{
			//Bob up and down
			houses[i]->houseSprite->setPositionY((sin(houses[i]->houseSprite->getPositionX() / 10) * 8 + 125)); //Divide by 10 slows it down, multiply by 8 to increase how much it bobs by and add 125 to increase overall height.

			//Wrap around
			if (houses[i]->houseSprite->getPositionX() < (0 - houses[i]->houseSprite->getBoundingBox().size.width))
			{
				houses[i]->onScreen = false;
				int distance = 550;
				if (i == 0)
				{
					houses[i]->houseSprite->setPositionX(houses[2]->houseSprite->getPositionX() + distance);
				}
				else
				{
					houses[i]->houseSprite->setPositionX(houses[i - 1]->houseSprite->getPositionX() + distance);
				}
				//reset
				houses[i]->windowBLSprite->setVisible(true);
				houses[i]->windowTLSprite->setVisible(true);
				houses[i]->windowTRSprite->setVisible(true);
			
				houses[i]->windowBLHit = false;
				houses[i]->windowTLHit = false;
				houses[i]->windowTRHit = false;
				houses[i]->doorHit = false;
			}
		}
		else
		{
			houses[i]->onScreen = true;
		}

		//Move doors with house
		houses[i]->doorSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 172.83);
		houses[i]->doorSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 138.17);

		//Move BL window with house
		houses[i]->windowBLSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 57.08);
		houses[i]->windowBLSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 151.62);

		//Move TL window with house
		houses[i]->windowTLSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 58);
		houses[i]->windowTLSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 250);

		//Move TR window with house
		houses[i]->windowTRSprite->setPositionX(houses[i]->houseSprite->getPositionX() + 203.66);
		houses[i]->windowTRSprite->setPositionY(houses[i]->houseSprite->getPositionY() + 249.18);
	}
}

void HelloWorld::updateHouseCollision(float deltaTime)
{
	for (int i = 0; i < numHouses; i++)
	{
		if (!houses[i]->windowBLHit)
		{
			if (paperBoy->getNewspaper()->getBoundingBox().intersectsRect(houses[i]->windowBLSprite->getBoundingBox()))
			{
				houses[i]->windowBLSprite->setVisible(false);
				paperBoy->resetNewspaper();
				houses[i]->windowBLHit = true;
				policeman->moveCloser(deltaTime);
			}
		}
		if (!houses[i]->windowTLHit)
		{
			if (paperBoy->getNewspaper()->getBoundingBox().intersectsRect(houses[i]->windowTLSprite->getBoundingBox()))
			{
				houses[i]->windowTLSprite->setVisible(false);
				paperBoy->resetNewspaper();
				houses[i]->windowTLHit = true;
				policeman->moveCloser(deltaTime);
			}
		}
		if (!houses[i]->windowTRHit)
		{
			if (paperBoy->getNewspaper()->getBoundingBox().intersectsRect(houses[i]->windowTRSprite->getBoundingBox()))
			{
				houses[i]->windowTRSprite->setVisible(false);
				paperBoy->resetNewspaper();
				houses[i]->windowTRHit = true;
				policeman->moveCloser(deltaTime);
			}
		}
		if (!houses[i]->doorHit)
		{
			if (paperBoy->getNewspaper()->getBoundingBox().intersectsRect(houses[i]->doorSprite->getBoundingBox()))
			{
				paperBoy->resetNewspaper();
				houses[i]->doorHit = true;
				policeman->fallBack(deltaTime);
			}
		}

	}
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