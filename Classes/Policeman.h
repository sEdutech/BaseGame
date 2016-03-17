#ifndef  _POLICEMAN_H_
#define  _POLICEMAN_H_

#include "cocos2d.h"
#include "MainMenu.h"

class Policeman {
private:
	cocos2d::Sprite * sprite;

	float velocityX = 0.0f;
	float friction = 8.0f;
	float speed = 2.0f;
	int destinationX = 100;


	int distance;


	bool down = false;
	float offsetY;
public:

	cocos2d::Sprite * getSprite() {
		return sprite;
	}

	void update(float, cocos2d::Sprite *);
	void init(cocos2d::Node * root);

	void moveCloser();
	void fallBack();

	bool colliding(cocos2d::Sprite *);

	void setDistance(int distance) {
		this->distance = distance;
	}
};

#endif
