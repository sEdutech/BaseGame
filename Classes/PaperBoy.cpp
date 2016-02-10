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

	mWinSize = winSize;

	//Set references to the Sprite objects 
	mPaperBoySprite = (Sprite*)rootNode->getChildByName("PaperBoy");
	rootNode->addChild(mPaperBoySprite);

	mPaperMoving = (Sprite*)rootNode->getChildByName("NewsPaper");
	rootNode->addChild(mPaperMoving);
	mPaperMoving->setVisible(false);

	mPaperThrown = false;

	mPaperBoySprite->setPosition(mWinSize.width / 2, mWinSize.height / 6);
	mPaperMoving->setPosition(mWinSize.width / 2, mWinSize.height / 2);
	projectileSpeed = 0.0f;
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
	trajectory = (endPoint - startPoint);
	//To be used
	float speed = trajectory.length();
	trajectory.normalize();
	mPaperThrown = true;
}

void PaperBoy::update(float delta)
{
	mPaperMoving->setVisible(true);
	if (mPaperThrown == true)
	{
		mPaperMoving->setPosition(mPaperMoving->getPosition() + trajectory);
	}
}