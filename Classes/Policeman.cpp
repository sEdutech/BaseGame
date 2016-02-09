#include "Policeman.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;


void Policeman::update(float delta)
{
	//cheap fix for now
	if (offset >= 4.0f) {
		down = true;
	} else if (offset <= -4.0f) {
		down = false;
	}


	if (down) {
		offset -= 0.2f;
	} else {
		offset += 0.2f;
	}

	Vec2 position; //static y position (187.42 base y position of policeman)

	if (floor(sprite->getPosition().x) != destinationX) {
		stringstream ss;
		ss << sprite->getPosition().x << endl;
		OutputDebugStringA(ss.str().c_str());
		position = Vec2(sprite->getPosition().x + 1, 187.42 + offset);
	}
	else {
		position = Vec2(sprite->getPosition().x, 187.42 + offset);
	}

	sprite->setPosition(position);



}

void Policeman::init(cocos2d::Node * root)
{

	sprite = (cocos2d::Sprite *) root->getChildByName("policeman");

}

void Policeman::setDestination(int destinationX)
{
}
