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
	auto moveTo = MoveTo::create(0, Vec2(1000, 150));
	auto moveTo2 = MoveTo::create(0, Vec2(1000, 150));
	
	obSpriteBox = (cocos2d::Sprite *) root->getChildByName("FireHydrant");
	root->addChild(obSpriteBox);
	obSpriteBox->runAction(moveTo);

	obRedSpriteBox = (cocos2d::Sprite *) root->getChildByName("TrashCan");
	root->addChild(obRedSpriteBox);
	obRedSpriteBox->runAction(moveTo2);

	float timer = 0.0f;
}

void Obstacles::update(float delta)
{
	timer += delta;

	auto moveBy = MoveBy::create(0, Vec2(-2, 0));
	auto moveBy2 = MoveBy::create(0, Vec2(-2, 0));
	
	obSpriteBox->runAction(moveBy);

	if (timer > 14.0f)
	{
		obRedSpriteBox->runAction(moveBy2);
	}

	if (timer > 28.0f)
	{
		timer = 0.0f;
		auto moveTo = MoveTo::create(0, Vec2(1000, 150));
		auto moveTo2 = MoveTo::create(0, Vec2(1000, 150));
		obSpriteBox->runAction(moveTo);
		obRedSpriteBox->runAction(moveTo2);
	}
}

