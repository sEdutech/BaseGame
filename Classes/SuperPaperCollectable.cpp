#include "SuperPaperCollectable.h"

bool SuperPaperCollectable::collided(cocos2d::Sprite * object)
{
	return object->getBoundingBox().intersectsRect(getSprite()->getBoundingBox());
}

void SuperPaperCollectable::handleEffect(PaperBoy * paperBoy)
{
	getSprite()->setVisible(false);

	//rest of effect
	//passed in the paperboy object so we can add to 'active powerups?'
}
