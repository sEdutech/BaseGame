#ifndef  _SUPERPAPER_COLLECTABLE_H_
#define  _SUPERPAPER_COLLECTABLE_H_

#include "cocos2d.h"
#include "Collectable.h"

class SuperPaperCollectable : public Collectable {

public:

	SuperPaperCollectable(cocos2d::Sprite * sprite) {
		this->setSprite(sprite);
	}

	bool collided(cocos2d::Sprite * object);
	void handleEffect(PaperBoy * paperBoy);

};

#endif