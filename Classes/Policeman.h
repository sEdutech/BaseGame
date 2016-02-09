#ifndef  _POLICEMAN_H_
#define  _POLICEMAN_H_

#include "cocos2d.h"

class Policeman {
private:

	cocos2d::Sprite * sprite;
	float offset;
	bool down = false;

	int destinationX = 100;

public:

	void update(float);
	void init(cocos2d::Node * root);

	void setDestination(int destinationX);
};

#endif
