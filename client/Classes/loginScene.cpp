#include "loginScene.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;

Scene* loginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = loginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool loginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto layer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui_login.json");
	this->addChild(layer);
    return true;
}