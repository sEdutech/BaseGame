#ifndef  _COLLECTABLE_H_
#define  _COLLECTABLE_H_

#include "cocos2d.h"
#include "PaperBoy.h"

class Collectable {
private:
	cocos2d::Sprite * sprite;

public:

	virtual bool collided(cocos2d::Sprite * object) = 0;
	virtual void handleEffect(PaperBoy * paperBoy) = 0;

	cocos2d::Sprite * getSprite() {
		return sprite;
	}

	void setSprite(cocos2d::Sprite * sprite) {
		this->sprite = sprite;
	}

};

#endif
