#include "GameMgr.h"
#include "MTNotificationQueue.h"
#include "ClientSocket.h"
#include "initScene.h"
#include "../game_lib/garbo .h"
#include "loginScene.h"

GameMgr* GameMgr::_instance = nullptr;

GameMgr* GameMgr::getInstance()
{
	if (_instance==nullptr)
	{
		_instance= new GameMgr();
		if (_instance && _instance->init()) 
		{
			static CGarbo<GameMgr> garboGameMgr;
			garboGameMgr.autoRelease(_instance);
		}
		else
		{
			CC_SAFE_DELETE(_instance);
		}		
	}	
	return _instance;
}

bool GameMgr::init()
{
	bool bres = Node::init();
	if (bres)
	{
		updateSceneState(egs_init);
	}
	return bres;
}
void GameMgr::update(float delta)
{
	ClientSocket::get_instance().ProcessRecvdPacket();
}

void GameMgr::updateSceneState(EGameState nstate)
{
	Scene* pScene = NULL;
	switch (nstate)
	{
	case egs_init:
		Director::getInstance()->runWithScene(initScene::createScene());
		return ;
	case egs_login:
		pScene = loginScene::createScene();
		break;
	default:
		return;
	}
	Director::getInstance()->replaceScene(pScene);
}


