#include "SuperPaperCollectable.h"

bool SuperPaperCollectable::collided(cocos2d::Sprite * object)
{
	return object->getBoundingBox().intersectsRect(getSprite()->getBoundingBox());
}

void SuperPaperCollectable::handleEffect(PaperBoy * paperBoy)
{
	getSprite()->setVisible(false);

	paperBoy->reloadSuperpapers();

	for (int i = 0; i < 3; i++) {
		paperBoy->getNewspaper(i)->sprite->setTexture(cocos2d::CCTextureCache::sharedTextureCache()->addImage("superpaper.png"));
	}
	
	//rest of effect
	//passed in the paperboy object so we can add to 'active powerups?'
}