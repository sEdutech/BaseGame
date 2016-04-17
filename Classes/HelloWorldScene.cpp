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

	worldSpeed = 2.0f;

	//PaperBoy
	paperBoy = new PaperBoy();
	//sets reload sprite
	paperBoy->setReloadSprite((Sprite*)rootNode->getChildByName("Reload"));
	paperBoy->init();
	paperBoy->setWorldSpeed(worldSpeed);
	
	//Policeman
	policeman = new Policeman;
	policeman->init(rootNode);
	policeman->setDistance((paperBoy->getPaperboySprite()->getPosition().x - policeman->getSprite()->getPosition().x) / 4);



	//init clouds
	for (int i = 0; i < numClouds; i++)
	{
		stringstream ss;
		ss << "cloudwrope" << i;
		clouds[i] = (Sprite*)rootNode->getChildByName(ss.str());
	}

	cloudSpeed = 0.5f;

	//Bird
	birdEnemy = new FlyingEnemy(rootNode, paperBoy->getPaperboySprite());

	//Obstacles
	obstacles = new Obstacles();
	obstacles->init(rootNode);

	//Score
	_scoreLabel = (ui::Text*)rootNode->getChildByName("Score");
	this->addChild(_scoreLabel);
	_scoreCounter = 0;
	
	addChild(paperBoy);

	//Collectables
	collectables.push_back(new SuperPaperCollectable((Sprite*)rootNode->getChildByName("superpaper")));
	collectableOnScreen = collectables[0];
	+collectableOnScreen->getSprite()->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));

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

	for (int i = 0; i < numOfBeltWheels; i++)
	{
		stringstream beltwheel; //Cant use to_string
		beltwheel << "beltwheel_" << i;
		beltWheels[i] = (Sprite*)root->getChildByName(beltwheel.str());
	}

	beltTopForeground = (Sprite*)root->getChildByName("Sprite_8");
	beltTopBackground = (Sprite*)root->getChildByName("belttop_7");
	beltbottom = (Sprite*)root->getChildByName("beltbottom_9");
	beltBackground = (Sprite*)root->getChildByName("beltbackground_10");


	root->addChild(curtain1);
	root->addChild(curtain2);

	for (int i = 0; i < numOfBeltWheels; i++)
	{
		root->addChild(beltWheels[i]);
	}

	root->addChild(beltTopForeground);
	root->addChild(beltbottom);
	root->addChild(beltBackground);

	curtain1->setGlobalZOrder(4);
	curtain2->setGlobalZOrder(4);

	for (int i = 0; i < numOfBeltWheels; i++)
	{
		beltWheels[i]->setGlobalZOrder(3);
	}

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
	updateCloudMovement(); 
	updateHouseCollision();
	policeman->update(t, paperBoy->getPaperboySprite());
	paperBoy->update(t);
	birdEnemy->Update();
	updateStage(t);
	handleCollectableCollisions();
	obstacles->update(t);
	updateBirdCollision();
	updateObstacleCollision();
	updateCollectables();
	
	//_scoreLabel->setText("Score" + _scoreCounter);
	stringstream text;
	text << _scoreCounter << endl;
	_scoreLabel->setText(text.str().c_str());
}

void HelloWorld::updateHouseMovement()
{
	//Movement
	for (int i = 0; i < numHouses; i++)
	{

		//Move Left
		houses[i]->houseSprite->setPositionX(houses[i]->houseSprite->getPositionX() - houses[i]->speed * worldSpeed);

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
					houses[i]->houseSprite->setPositionX(houses[numHouses-1]->houseSprite->getPositionX() + distance);
				}
				else
				{
					houses[i]->houseSprite->setPositionX(houses[i - 1]->houseSprite->getPositionX() + distance);
				}
				//reset
				houses[i]->windowBLSprite->setVisible(true);
				houses[i]->windowTLSprite->setVisible(true);
				houses[i]->windowTRSprite->setVisible(true);
				houses[i]->doorSprite->setVisible(true);
			
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

void HelloWorld::updateCloudMovement()
{
	//Movement
	for (int i = 0; i < numClouds; i++)
	{
		//Move Left
		clouds[i]->setPositionX(clouds[i]->getPositionX() - cloudSpeed * worldSpeed);

		clouds[i]->setPositionY((sin(clouds[i]->getPositionX() / 15) * 20 + 675));  //Divide by 10 slows it down, multiply by 8 to increase how much it bobs by and add 125 to increase overall height.

		//Wrap around
		if (clouds[i]->getPositionX() < (0 - clouds[i]->getBoundingBox().size.width))
		{
			float distance = 312;
			if (i == 0)
			{
				clouds[i]->setPositionX(clouds[numClouds - 1]->getPositionX() + distance);
			}
			else
			{
				clouds[i]->setPositionX(clouds[i - 1]->getPositionX() + distance);
			}
		}
	}
}

void HelloWorld::updateHouseCollision()
{
	int numOfNewspapers = paperBoy->getNumOfNewspapers();
	for (int i = 0; i < numHouses; i++)
	{
		for (int j = 0; j < numOfNewspapers; j++)
		{
			Newspaper* newspaper = paperBoy->getNewspaper(j);
			if (newspaper->thrown)
			{
				if (!houses[i]->windowBLHit)
				{
					if (newspaper->sprite->getBoundingBox().intersectsRect(houses[i]->windowBLSprite->getBoundingBox()))
					{
						houses[i]->windowBLSprite->setVisible(false);
						paperBoy->moveOffscreen(j);
						houses[i]->windowBLHit = true;
						policeman->moveCloser();
					}
				}
				if (!houses[i]->windowTLHit)
				{
					if (newspaper->sprite->getBoundingBox().intersectsRect(houses[i]->windowTLSprite->getBoundingBox()))
					{
						houses[i]->windowTLSprite->setVisible(false);
						paperBoy->moveOffscreen(j);
						houses[i]->windowTLHit = true;
						policeman->moveCloser();
					}
				}
				if (!houses[i]->windowTRHit)
				{
					if (newspaper->sprite->getBoundingBox().intersectsRect(houses[i]->windowTRSprite->getBoundingBox()))
					{
						houses[i]->windowTRSprite->setVisible(false);
						paperBoy->moveOffscreen(j);
						houses[i]->windowTRHit = true;
						policeman->moveCloser();
					}
				}
				if (!houses[i]->doorHit)
				{
					if (newspaper->sprite->getBoundingBox().intersectsRect(houses[i]->doorSprite->getBoundingBox()))
					{
						houses[i]->doorSprite->setVisible(false);
						paperBoy->moveOffscreen(j);
						houses[i]->doorHit = true;
						policeman->fallBack();
						_scoreCounter += 10;
					}
				}	
			}

		}


	}
}

Collectable * HelloWorld::getRandomCollectable()
{
	int num = cocos2d::RandomHelper::random_int(0, (int)collectables.size() - 1);
	return collectables[num];
}

void HelloWorld::updateCollectables()
{
	Vec2 position = collectableOnScreen->getSprite()->getPosition();
	
	collectableOnScreen->getSprite()->setPosition(position.x - 6, position.y);
	
	if (position.x < 0) 
	{
		collectableOnScreen = getRandomCollectable();
		Vec2 newPosition = Vec2(winSize.width * cocos2d::RandomHelper::random_int(3, 5), collectableOnScreen->getSprite()->getPosition().y);
		collectableOnScreen->getSprite()->setPosition(newPosition);
		collectableOnScreen->getSprite()->setVisible(true);	
	}
	
}

void HelloWorld::updateStage(float)
{
	for (int i = 0; i < numOfBeltWheels; i++)
	{
		beltWheels[i]->setRotation(beltWheels[i]->getRotation() - worldSpeed);
	}

	winSize = Director::getInstance()->getWinSize();
	Vec2 beltTopForegroundPosition = beltTopForeground->getPosition();
	beltTopForeground->setPosition(beltTopForegroundPosition.x - 1, beltTopForegroundPosition.y);
	Vec2 beltTopBackgroundPosition = beltTopBackground->getPosition();
	beltTopBackground->setPosition(beltTopBackgroundPosition.x - 1, beltTopBackgroundPosition.y);
	Vec2 beltBottomPosition = beltbottom->getPosition();
	beltbottom->setPosition(beltBottomPosition.x + 1, beltBottomPosition.y);
	if (beltTopForegroundPosition.x <= winSize.width / 2 - 25) {
		beltTopForeground->setPosition(winSize.width / 2, beltTopForegroundPosition.y);
	}
	if (beltTopBackgroundPosition.x <= winSize.width / 2 - 25) {
		beltTopBackground->setPosition(winSize.width / 2, beltTopBackgroundPosition.y);
	}
	if (beltBottomPosition.x >= winSize.width / 2 + 25) {
		beltbottom->setPosition(winSize.width / 2, beltBottomPosition.y);
	}
}

void HelloWorld::handleCollectableCollisions() 
{	
	int numOfNewspapers = paperBoy->getNumOfNewspapers();
	for (Collectable * c : collectables) 
	{	
		if (!c->getSprite()->isVisible()) continue;
			
		if (c->collided(paperBoy->getPaperboySprite())) 
		{
			c->handleEffect(paperBoy);
			continue;
				
		}
		//for (int j = 0; j < numOfNewspapers; j++)
		//{
		//	Newspaper* newspaper = paperBoy->getNewspaper(j);
		//	if (newspaper->thrown)
		//	{
		//		if (c->collided(newspaper->sprite)) 
		//		{
		//			paperBoy->moveOffscreen(j);
		//			c->handleEffect(paperBoy);
		//		}
		//	}
		//}
	}
}

void HelloWorld::updateObstacleCollision()
{
	if (paperBoy->getPaperboySprite()->getBoundingBox().intersectsRect(obstacles->getFireHydrantSprite()->getBoundingBox()))
	{
		if (!obstacles->isFireHydrantDropping()) {
			policeman->moveCloser();
		}
		obstacles->fireHydrantDrop();
	}

	if (paperBoy->getPaperboySprite()->getBoundingBox().intersectsRect(obstacles->getTrashCanSprite()->getBoundingBox()))
	{
		if (!obstacles->isTrashCanDropping()) {
			policeman->moveCloser();
		}
		obstacles->trashCanDrop();
	}

	//Makes obstacles fall before collision with the Pig.
	if ((obstacles->getTrashCanSprite()->getPosition().x - policeman->getSprite()->getPosition().x) <= 50) {
		obstacles->trashCanDrop();
	}
	if ((obstacles->getFireHydrantSprite()->getPosition().x - policeman->getSprite()->getPosition().x) <= 50) {
		obstacles->fireHydrantDrop();
	}
}

void HelloWorld::updateBirdCollision()
{
	int numOfNewspapers = paperBoy->getNumOfNewspapers();
	for (int i = 0; i < numOfNewspapers; i++)
	{
		Newspaper* newspaper = paperBoy->getNewspaper(i);
		if (newspaper->thrown)
		{
			if (newspaper->sprite->getBoundingBox().intersectsRect(birdEnemy->getRect()))
			{
				if (birdEnemy->colliding())
				{
					return;
				}
				birdEnemy->Run();
				paperBoy->moveOffscreen(i);
				birdEnemy->setColliding(true);

				//Add points for hitting flying stuff
				switch (birdEnemy->getType()) {
				case BirdLeft:
				case BirdRight:
					_scoreCounter += 40;
					break;
				case UFOLeft:
				case UFORight:
					_scoreCounter += 200;
					break;
				}
			}
		}
	}

	if (paperBoy->getPaperboySprite()->getBoundingBox().intersectsRect(birdEnemy->getRect()))
	{
		if (!birdEnemy->colliding()) {
			policeman->moveCloser();
		}
		birdEnemy->setColliding(true);
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
	Vec2 trajectory = touchStart - touchEnd;
	if (trajectory.length() < 5)
	{
		if (paperBoy->getReloadActive() && paperBoy->getReloadButton()->getBoundingBox().containsPoint(touch->getLocation()))
		{
			paperBoy->reloadNewspapers();
		}
		else
		{
			paperBoy->jump();
		}
	}

	else
	{
		paperBoy->throwPaper(touchStart, touchEnd);
	}
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}