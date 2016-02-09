#include "MainMenu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainMenu.csb");
	addChild(rootNode);

	// Start Button

	auto startButton = rootNode->getChildByName<cocos2d::ui::Button*>("startButton");
	startButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {

		auto mainScene = HelloWorld::createScene();

		switch (type)
		{

		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			CCDirector::getInstance()->replaceScene(mainScene);

			break;
		default:
			break;
		}
	});

	return true;
}
