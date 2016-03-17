#pragma once
#include "cocos2d.h"


using namespace cocos2d;

class Obstacles : public cocos2d::Node
{
public:
	Obstacles();

	~Obstacles();

	void init(cocos2d::Node * root);

	void update(float delta);

private:
	cocos2d::Sprite * obSpriteBox;
	cocos2d::Sprite * obRedSpriteBox;
	float timer;
};

