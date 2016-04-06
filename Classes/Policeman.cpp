
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

	if (destinationX > floor(sprites[0]->getPosition().x)) {
		position = Vec2(sprites[0]->getPosition().x + 1, 137.42 + offsetY);
	}
	else if (destinationX < floor(sprites[0]->getPosition().x)) {
		position = Vec2(sprites[0]->getPosition().x - 1, 137.42 + offsetY);
	}

	if (floor(sprites[0]->getPosition().x != destinationX)) {

	}
	else {
		position = Vec2(destinationX, 137.42 + offsetY);
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

	sprites[1]->setRotation(sprites[1]->getRotation() + 2.0f);

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
		Repeat::create(RotateBy::create(1.0f, -40.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +40.0f), 1),
		Repeat::create(RotateBy::create(1.0f, -40.0f), 1), nullptr);
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

	Sequence* moveArm = Sequence::create(Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, -20.0f), 1),
		Repeat::create(RotateBy::create(1.0f, +20.0f), 1), nullptr);
	sprites[2]->runAction(moveArm);

	destinationX += distance;
}

void Policeman::fallBack()
{
	if (velocityX > 0.0f) return;
	if (sprites[0]->getPosition().x <= 10) return;
	destinationX -= distance;
}

bool Policeman::colliding(cocos2d::Sprite * paperBoySprite) {
	if (sprites[0]->getBoundingBox().intersectsRect(paperBoySprite->getBoundingBox())) {
		destinationX = sprites[0]->getPosition().x - 1;
		return true;
	}

	return false;
}