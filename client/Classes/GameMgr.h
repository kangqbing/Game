#include "cocos2d.h"
#include "NetworkSession.h"
#include "../game_lib/base_define.h"
#include "../game_lib/singleton.h"
class GameMgr : public cocos2d::Node
{
public:	
	bool init();
	void update(float delta);
	void updateSceneState(EGameState nstate);

	static GameMgr* getInstance();
	static GameMgr* _instance;
};

