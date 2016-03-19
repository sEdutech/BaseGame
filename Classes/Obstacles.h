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

	Sprite* getFireHydrantSprite() { return fireHydrant; };

	Sprite* getTrashCanSprite() { return trashCan; };

	void fireHydrantDrop() { fireHydrantDropping = true; };

	void trashCanDrop() { trashCanDropping = true; };

private:
	Sprite * fireHydrant;
	Sprite * trashCan;

	bool fireHydrantOnScreen;
	bool trashCanOnScreen;

	bool fireHydrantDropping;
	bool trashCanDropping;

	float timer;

	Size winSize;
};

