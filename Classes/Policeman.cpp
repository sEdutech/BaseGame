
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
	if (destinationX >= floor(sprites[0]->getPosition().x)) {
		if (destinationX - floor(sprites[0]->getPosition().x) >= 30) {
			velocityX += speed * delta;
		}
		else {
			velocityX -= speed * 2 * delta;
		}
	}
	else if (destinationX <= floor(sprites[0]->getPosition().x)) {
		if (floor(sprites[0]->getPosition().x) - destinationX >= 30) {
			velocityX -= speed * delta;
		}
		else {
			velocityX += speed * 2 * delta;
		}
	}

	//if we have a destination to go to and not arrived
	if (floor(sprites[0]->getPosition().x) != destinationX) {
		if (floor(sprites[0]->getPosition().x) <= destinationX) { //if our destination is ahead of us
			position = Vec2(sprites[0]->getPosition().x + velocityX, 157.42 + offsetY);
		}
		else { //if our destination is behind us
			position = Vec2(sprites[0]->getPosition().x + velocityX, 157.42 + offsetY);
		}

	}
	else {//if we dont have a destination, reset our velocity for next destination and draw current pos
		if (velocityX != 0.0) velocityX = 0.0f;
		position = Vec2(destinationX, 157.42 + offsetY);
	}

	sprites[0]->setPosition(position);

	sprites[1]->setPosition(Vec2((position.x < wheelRelative.x ? position.x + wheelRelative.x : position.x - wheelRelative.x), (position.y < wheelRelative.y ? position.y + wheelRelative.y : position.y - wheelRelative.y)));
	sprites[2]->setPosition(Vec2((position.x < armRelative.x ? position.x + armRelative.x : position.x - armRelative.x), (position.y < armRelative.y ? position.y - armRelative.y : position.y + armRelative.y)));
	sprites[3]->setPosition(Vec2((position.x < legRelative.x ? position.x + legRelative.x : position.x - legRelative.x), (position.y < legRelative.y ? position.y - legRelative.y : position.y + legRelative.y)));



	//if we're colliding with the paperboy, don't want our sprites to overlap
	//game over?
	if (colliding(paperBoySprite)) {
		auto mainScene = MainMenu::createScene();
		CCDirector::getInstance()->replaceScene(mainScene);
	}


}

void Policeman::init(cocos2d::Node * root)
{
	sprites.push_back((cocos2d::Sprite *) root->getChildByName("policeman_body"));
	sprites.push_back((cocos2d::Sprite *) root->getChildByName("policeman_wheel"));
	sprites.push_back((cocos2d::Sprite *) root->getChildByName("policeman_arm"));
	sprites.push_back((cocos2d::Sprite *) root->getChildByName("policeman_front_leg"));


	wheelRelative = getRelativePosition(sprites[0], sprites[1]);
	armRelative = getRelativePosition(sprites[0], sprites[2]);
	legRelative = getRelativePosition(sprites[0], sprites[3]);

	Sequence* moveArm = Sequence::create(Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1), nullptr);
	sprites[2]->runAction(moveArm);

	destinationX = sprites[0]->getPosition().x;
}

Vec2 Policeman::getRelativePosition(cocos2d::Sprite * base, cocos2d::Sprite * child) {
	return Vec2(abs(base->getPosition().x - child->getPosition().x),
		abs(base->getPosition().y - child->getPosition().y));
}


void Policeman::moveCloser()
{
	if (velocityX > 0.0f) return;
	//sprites[2]->runAction(RepeatForever::create(RotateBy::create(1.0f, -20.0f)));
	//sprites[2]->runAction(Repeat::create(RotateBy::create(1.0f, -20.0f), 1));
	Sequence* moveArm = Sequence::create(Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1), nullptr);
	sprites[2]->runAction(moveArm);
	//moveArm->startWithTarget((cocos2d::Node *)sprites[2]);
	destinationX += distance;
}

void Policeman::fallBack()
{
	if (velocityX > 0.0f) return;
	destinationX -= distance;
}

bool Policeman::colliding(cocos2d::Sprite * paperBoySprite) {
	if (sprites[0]->getBoundingBox().intersectsRect(paperBoySprite->getBoundingBox())) {
		destinationX = sprites[0]->getPosition().x - 1;
		return true;
	}

	return false;
}