#include "initScene.h"
#include "cocostudio/CocoStudio.h"
#include "GameMgr.h"
#include <cmath>
USING_NS_CC;

Scene* initScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = initScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool initScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite_bg = Sprite::create("init_bg.png");
	sprite_bg->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(sprite_bg);

	auto sprite_girl = Sprite::create("init_girl.png");
	sprite_girl->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(sprite_girl);

	Array *pArray = Array::create();
	float radius = 100;
	for (int i=0; i<100; i++)
	{
		pArray->addObject(MoveTo::create(0.1f, Point(sin(i*360/100.0f)*radius, cos(i*360/100.0f))*radius));
	}


	sprite_girl->runAction(Sequence::createWithTwoActions(, CallFunc::create(this, SEL_CallFunc(&initScene::EndinitScene))));

    return true;
}

void initScene::EndinitScene()
{
	GameMgr::getInstance()->updateSceneState(egs_login);
}
