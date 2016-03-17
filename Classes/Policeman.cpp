#include "Policeman.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;


void Policeman::update(float delta, cocos2d::Sprite * paperBoySprite)
{
	if (offsetY >= 4.0f) {
		down = true;
	}
	else if (offsetY <= -4.0f) {
		down = false;
	}


	if (down) {
		offsetY -= 0.2f;
	}
	else {
		offsetY += 0.2f;
	}

	Vec2 position;


	//setting velocity for policeman
	if (destinationX >= floor(sprite->getPosition().x)) {
		if (destinationX - floor(sprite->getPosition().x) >= 30) {
			velocityX += speed * delta;
		}
		else {
			velocityX -= speed * 2 * delta;
		}
	}
	else if (destinationX <= floor(sprite->getPosition().x)) {
		if (floor(sprite->getPosition().x) - destinationX >= 30) {
			velocityX -= speed * delta;
		}
		else {
			velocityX += speed * 2 * delta;
		}
	}

	//if we have a destination to go to and not arrived
	if (floor(sprite->getPosition().x) != destinationX) {
		if (floor(sprite->getPosition().x) <= destinationX) { //if our destination is ahead of us
			position = Vec2(sprite->getPosition().x + velocityX, 187.42 + offsetY);
		}
		else { //if our destination is behind us
			position = Vec2(sprite->getPosition().x + velocityX, 187.42 + offsetY);
		}

	}
	else {//if we dont have a destination, reset our velocity for next destination and draw current pos
		if (velocityX != 0.0) velocityX = 0.0f;
		position = Vec2(destinationX, 187.42 + offsetY);
	}

	sprite->setPosition(position);

	//if we're colliding with the paperboy, don't want our sprites to overlap
	//game over?
	if (colliding(paperBoySprite)) {
		auto mainScene = MainMenu::createScene();
		CCDirector::getInstance()->replaceScene(mainScene);
	}
}

void Policeman::init(cocos2d::Node * root)
{
	sprite = (cocos2d::Sprite *) root->getChildByName("policeman");
	destinationX = sprite->getPosition().x;
}

void Policeman::moveCloser() 
{
	if (velocityX > 0.0f) return;
	destinationX += distance;
}

void Policeman::fallBack() 
{
	if (velocityX > 0.0f) return;
	destinationX -= distance;
}

bool Policeman::colliding(cocos2d::Sprite * paperBoySprite) {
	if (sprite->getBoundingBox().intersectsRect(paperBoySprite->getBoundingBox())) {
		destinationX = sprite->getPosition().x - 1;
		return true;
	}

	return false;
}