#include "Policeman.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;


void Policeman::update(float delta)
{
	//cheap fix for now
	if (offsetY >= 4.0f) {
		down = true;
	} else if (offsetY <= -4.0f) {
		down = false;
	}


	if (down) {
		offsetY -= 0.2f;
	} else {
		offsetY += 0.2f;
	}

	Vec2 position;

	if (floor(sprite->getPosition().x) != destinationX) {
		
		if (floor(sprite->getPosition().x) > destinationX) {
			position = Vec2(sprite->getPosition().x + 1, 187.42 + offsetY);
		}
		else {
			position = Vec2(sprite->getPosition().x - 1, 187.42 + offsetY);
		}

	}
	else {
		position = Vec2(sprite->getPosition().x, 187.42 + offsetY);
	}

	sprite->setPosition(position);



}

void Policeman::init(cocos2d::Node * root)
{

	sprite = (cocos2d::Sprite *) root->getChildByName("policeman");

}

void Policeman::moveCloser(float deltaTime) {
	destinationX = destinationX + distance;
	stringstream ss;
	ss << destinationX << " - " << distance << "distance to increase" << endl;
	OutputDebugStringA(ss.str().c_str());
}

void Policeman::fallBack(float deltaTime) {
	destinationX =  destinationX - distance;
	stringstream ss;
	ss << destinationX << " - " << distance << "distance to increase" << endl;
	OutputDebugStringA(ss.str().c_str());
}
