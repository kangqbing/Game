#include "AppDelegate.h"
#include "GameMgr.h"
#include "initScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::create("My Game");
		glview = GLView::createWithRect("My Game", cocos2d::Rect(0, 0, 1280, 720), 0.8f);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto screenSize = glview->getFrameSize();

	auto designSize = Size(1280, 720);

	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> searchPaths;

	if (screenSize.height > 320)
	{
		auto resourceSize = Size(1280, 720);
		searchPaths.push_back("ui");
		searchPaths.push_back("init");
		director->setContentScaleFactor(resourceSize.height/designSize.height);
	}
	else
	{
		auto resourceSize = Size(1280, 720);
		searchPaths.push_back("ui");
		searchPaths.push_back("init");
		director->setContentScaleFactor(resourceSize.height/designSize.height);
	}

	fileUtils->setSearchPaths(searchPaths);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
#endif

	director->getScheduler()->scheduleUpdate(GameMgr::getInstance(), 0, false);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
