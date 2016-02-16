#ifndef  _POLICEMAN_H_
#define  _POLICEMAN_H_

#include "cocos2d.h"

class Policeman {
private:
	cocos2d::Sprite * sprite;

	float velocityX = 0.0f;
	int destinationX = 100;

	int distance;


	bool down = false;
	float offsetY;
public:

	cocos2d::Sprite * getSprite() {
		return sprite;
	}

	void update(float);
	void init(cocos2d::Node * root);

	void moveCloser(float);
	void fallBack(float);

	void setDistance(int distance) {
		this->distance = distance;
	}
};

#endif
