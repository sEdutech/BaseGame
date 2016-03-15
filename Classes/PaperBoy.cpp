#include "PaperBoy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d;


PaperBoy::PaperBoy()
{
	this->init();
}

PaperBoy::~PaperBoy()
{
}

bool PaperBoy::init()
{

	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("PaperBoy.csb");
	addChild(rootNode);

	//Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, 0.0f));
	this->setAnchorPoint(Vec2(winSize.width / 2, winSize.height / 2));
	//this->scheduleUpdate();
	
	window.setRect(0, 0, winSize.width, winSize.height);
	mWinSize = winSize;

	//Set references to the Sprite objects 
	mPaperBoySprite = (Sprite*)rootNode->getChildByName("PaperBoy");
	rootNode->addChild(mPaperBoySprite);

	reloadSprite = (Sprite*)rootNode->getChildByName("Reload");
	reloadSprite->setPosition(-100,-100);
	reloadActive = false;

	//init newspapers
	for (int i = 0; i < totalNumNewspapers; i++)
	{
		stringstream ss;
		ss << "NewsPaper" << i;
		newspapers[i] = new Newspaper();
		newspapers[i]->sprite = (Sprite*)rootNode->getChildByName(ss.str());
		//rootNode->addChild(newspapers[i]->sprite);
		newspapers[i]->thrown = false;
		newspapers[i]->active = false;
		newspapers[i]->trajectory = Vec2(0,0);
	}

	//Set newspaper positions
	newspapers[0]->sprite->setPosition(mWinSize.width / 2, mWinSize.height / 4.5);
	newspapers[0]->active = true;
	newspapers[1]->sprite->setPosition(50 + newspapers[1]->sprite->getBoundingBox().size.width * totalNumNewspapers, mWinSize.height - newspapers[1]->sprite->getBoundingBox().size.height);

	for (int i = 2; i < totalNumNewspapers; i++)
	{
		newspapers[i]->sprite->setPosition(newspapers[i - 1]->sprite->getPositionX() - (newspapers[i]->sprite->getBoundingBox().size.width + 5), newspapers[i - 1]->sprite->getPositionY());
	}

	mPaperBoySprite->setPosition(mWinSize.width / 2, mWinSize.height / 6);
	projectileSpeed = 5.0f;
	return true;
}

PaperBoy* PaperBoy::create()
{
	PaperBoy* myNode = new PaperBoy();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}

void PaperBoy::throwPaper(Vec2 startPoint, Vec2 endPoint)
{
	if (currentNumNewspapers != 0) //if 0 need to reload
	{			
		int activeNewspaper = getActiveNewspaper(); 
		newspapers[activeNewspaper]->trajectory = (endPoint - startPoint);
		if (newspapers[activeNewspaper]->trajectory.length() > 0)
		{
			currentNumNewspapers -= 1;
			//To be used
			//projectileSpeed = trajectory.length() / 20;
			newspapers[activeNewspaper]->trajectory.normalize();

			newspapers[activeNewspaper]->thrown = true;
			newspapers[activeNewspaper]->active = false;
			newspapers[activeNewspaper]->sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));

			if (currentNumNewspapers != 0)
			{
				newspapers[activeNewspaper + 1]->active = true;
				newspapers[activeNewspaper + 1]->sprite->setPosition(mWinSize.width / 2, mWinSize.height / 4.5);
			}
		}
	}
}

void PaperBoy::reloadNewspapers()
{
	reloadSprite->setPosition(-100, -100);

	newspapers[0]->sprite->setPosition(mWinSize.width / 2, mWinSize.height / 4.5);
	newspapers[0]->active = true;
	newspapers[1]->sprite->setPosition(50 + newspapers[1]->sprite->getBoundingBox().size.width * totalNumNewspapers, mWinSize.height - newspapers[1]->sprite->getBoundingBox().size.height);

	for (int i = 2; i < totalNumNewspapers; i++)
	{
		newspapers[i]->sprite->setPosition(newspapers[i - 1]->sprite->getPositionX() - (newspapers[i]->sprite->getBoundingBox().size.width + 5), newspapers[i - 1]->sprite->getPositionY());
	}

	currentNumNewspapers = totalNumNewspapers;

	reloadActive = false;
}

void PaperBoy::moveOffscreen(int i)
{
	newspapers[i]->thrown = false;
	newspapers[i]->sprite->setPositionX(-100);
	newspapers[i]->sprite->stopAllActions();
	newspapers[i]->sprite->setRotation(0);
}

void PaperBoy::update(float delta)
{
	bool thrown = false;
	for (int i = 0; i < totalNumNewspapers; i++)
	{
		if (newspapers[i]->thrown == true)
		{
			newspapers[i]->sprite->setPosition(newspapers[i]->sprite->getPosition() + newspapers[i]->trajectory * projectileSpeed);
			if (!newspapers[i]->sprite->getBoundingBox().intersectsRect(window))
			{
				moveOffscreen(i);
			}
			thrown = true;
		}
	}

	if (currentNumNewspapers == 0 && !thrown)
	{
		reloadActive = true;
		reloadSprite->setPosition(50 + reloadSprite->getBoundingBox().size.width, mWinSize.height - reloadSprite->getBoundingBox().size.height);
	}
}

int PaperBoy::getActiveNewspaper()
{
	for (int i = 0; i < totalNumNewspapers; i++)
	{
		if (newspapers[i]->active == true)
		{
			return i;
		}
	}
}