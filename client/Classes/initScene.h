#ifndef __init_SCENE_H__
#define __init_SCENE_H__

#include "cocos2d.h"

class initScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void EndinitScene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(initScene);
};

#endif // __HELLOWORLD_SCENE_H__
