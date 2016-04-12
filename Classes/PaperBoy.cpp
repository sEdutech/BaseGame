#include "PaperBoy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d;


PaperBoy::PaperBoy()
{
	
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
	frontWheel = (Sprite*)rootNode->getChildByName("FrontWheel");
	backWheel = (Sprite*)rootNode->getChildByName("BackWheel");
	stick = (Sprite*)rootNode->getChildByName("Stick");

	reloadSprite = (Sprite*)rootNode->getChildByName("Reload");
	reloadSprite->setPosition(-100,-100);
	reloadActive = false;

	//Jump
	jumping = false;
	jumpCount = 0;

	//init newspapers
	for (int i = 0; i < totalNumNewspapers; i++)
	{
		stringstream ss;
		ss << "NewsPaper" << i;
		newspapers[i] = new Newspaper();
		newspapers[i]->sprite = (Sprite*)rootNode->getChildByName(ss.str());
		newspapers[i]->thrown = false;
		newspapers[i]->active = false;
		newspapers[i]->trajectory = Vec2(0,0);
	}

	//Set newspaper positions
	newspapers[0]->active = true;
	newspapers[0]->sprite->setPosition(100 + newspapers[0]->sprite->getBoundingBox().size.width * totalNumNewspapers, mWinSize.height - newspapers[0]->sprite->getBoundingBox().size.height);

	for (int i = 1; i < totalNumNewspapers; i++)
	{
		newspapers[i]->sprite->setPosition(newspapers[i - 1]->sprite->getPositionX() - (newspapers[i]->sprite->getBoundingBox().size.width + 5), newspapers[i - 1]->sprite->getPositionY());
	}

	mPaperBoySprite->setPosition(mWinSize.width / 2, mWinSize.height / 3.75);
	frontWheel->setPosition(mPaperBoySprite->getPositionX() + 30, mPaperBoySprite->getPositionY() - 35);
	backWheel->setPosition(mPaperBoySprite->getPositionX() - 30, mPaperBoySprite->getPositionY() - 35);
	stick->setPosition(mPaperBoySprite->getPositionX(), mPaperBoySprite->getPositionY() - 90);

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
	if (currentNumNewspapers != 0 && jumping == false) //if 0 need to reload
	{			
		int activeNewspaper = getActiveNewspaper(); 
		newspapers[activeNewspaper]->trajectory = (endPoint - startPoint);
		if (newspapers[activeNewspaper]->trajectory.length() > 0)
		{
			newspapers[activeNewspaper]->sprite->setPosition(mWinSize.width / 2, mWinSize.height / 4.5);
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
			}
		}
	}
}

void PaperBoy::reloadNewspapers()
{
	reloadSprite->setPosition(-100, -100);

	newspapers[0]->active = true;
	newspapers[0]->sprite->setPosition(100 + newspapers[0]->sprite->getBoundingBox().size.width * totalNumNewspapers, mWinSize.height - newspapers[0]->sprite->getBoundingBox().size.height);

	for (int i = 1; i < totalNumNewspapers; i++)
	{		
		moveOffscreen(i);
		newspapers[i]->sprite->setPosition(newspapers[i - 1]->sprite->getPositionX() - (newspapers[i]->sprite->getBoundingBox().size.width + 5), newspapers[i - 1]->sprite->getPositionY());
	}

	currentNumNewspapers = totalNumNewspapers;

	reloadActive = false;

	for (int i = 0; i < totalNumNewspapers; i++) {
		getNewspaper(i)->sprite->setTexture(cocos2d::CCTextureCache::sharedTextureCache()->addImage("NewsPaper.png"));
	}
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
	if (jumping == true)
	{
		frontWheel->setPosition(mPaperBoySprite->getPositionX() + 30, mPaperBoySprite->getPositionY() - 35);
		backWheel->setPosition(mPaperBoySprite->getPositionX() - 30, mPaperBoySprite->getPositionY() - 35);
		stick->setPosition(mPaperBoySprite->getPositionX(), mPaperBoySprite->getPositionY() - 90);

		jumpCount = jumpCount + 3;
		
		//Jump up
		if (jumpCount < 75)
		{
			mPaperBoySprite->setPosition(mPaperBoySprite->getPosition().x, mPaperBoySprite->getPosition().y + 4.0f);
		}

		//Hang
		else if (jumpCount > 75 && jumpCount <= 100)
		{
			mPaperBoySprite->setPosition(mPaperBoySprite->getPosition().x, mPaperBoySprite->getPosition().y - 0.5f);
		}

		//Jump down
		else if (jumpCount > 100)
		{
			mPaperBoySprite->setPosition(mPaperBoySprite->getPosition().x, mPaperBoySprite->getPosition().y - 2.0f);
		}

		//Original position
		if (mPaperBoySprite->getPosition().y < mWinSize.height / 3.75)
		{
			mPaperBoySprite->setPosition(mWinSize.width / 2, mWinSize.height / 3.75);

			jumping = false;
		}
	}

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

	if (currentNumNewspapers == 0)
	{
		reloadActive = true;
		reloadSprite->setPosition(50 + reloadSprite->getBoundingBox().size.width, mWinSize.height - reloadSprite->getBoundingBox().size.height);
	}

	frontWheel->setRotation(frontWheel->getRotation() +  worldSpeed);
	backWheel->setRotation(backWheel->getRotation() + worldSpeed);
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

void PaperBoy::jump()
{
	if (jumping == false)
	{
		jumping = true;
		jumpCount = 0;
	}
}

void PaperBoy::reloadSuperpapers()
{
	reloadSprite->setPosition(-100, -100);
	newspapers[0]->active = true;
	newspapers[0]->sprite->setPosition(100 + newspapers[0]->sprite->getBoundingBox().size.width * totalNumNewspapers, mWinSize.height - newspapers[0]->sprite->getBoundingBox().size.height);
	for (int i = 1; i < totalNumNewspapers; i++)
	{		
		moveOffscreen(i);
		newspapers[i]->sprite->setPosition(newspapers[i - 1]->sprite->getPositionX() - (newspapers[i]->sprite->getBoundingBox().size.width + 5), newspapers[i - 1]->sprite->getPositionY());
	}
	currentNumNewspapers = totalNumNewspapers;
	reloadActive = false;
}
