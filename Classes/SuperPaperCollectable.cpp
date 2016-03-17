#include "SuperPaperCollectable.h"

bool SuperPaperCollectable::collided(cocos2d::Sprite * object)
{
	return object->getBoundingBox().intersectsRect(getSprite()->getBoundingBox());
}
