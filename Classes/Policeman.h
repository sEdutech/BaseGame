#ifndef  _POLICEMAN_H_
#define  _POLICEMAN_H_

#include "cocos2d.h"
#include "MainMenu.h"
#include <vector>

using namespace std;

USING_NS_CC;


class Policeman {
private:
	cocos2d::Sprite * sprite;

	vector<cocos2d::Sprite *> sprites;

	Vec2 armRelative;
	Vec2 wheelRelative;
	Vec2 legRelative;

	float velocityX = 0.0f;
	float friction = 8.0f;
	float speed = 2.0f;
	int destinationX = 100;


	int distance;


	bool down = false;
	float offsetY;
public:

	cocos2d::Sprite * getSprite() {
		return sprites[0];
	}

	void update(float, cocos2d::Sprite *);
	void init(cocos2d::Node * root);

	void moveCloser();
	void fallBack();

	Vec2 getRelativePosition(cocos2d::Sprite *, cocos2d::Sprite *);


	bool colliding(cocos2d::Sprite *);

	void setDistance(int distance) {
		this->distance = distance;
	}
};

#endif