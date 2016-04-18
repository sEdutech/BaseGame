#include "MainMenu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/Soundtrack.mp3");
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

	//curtain = (Sprite*)rootNode->getChildByName("curtain");
	//addChild(curtain);

	// Start Button

	auto startButton = rootNode->getChildByName<cocos2d::ui::Button*>("startButton");
	startButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {

		auto mainScene = HelloWorld::createScene();

		this->scheduleUpdate();

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

void MainMenu::update(float t)
{
	//curtain->setPosition(curtain->getPosition().x, curtain->getPosition().y - 0.1 * t);
}