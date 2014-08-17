#include "AppDelegate.h"
#include "AppManager.h"
#include "OpeningLayer.h"
#ifdef COCOS2D_DEBUG
#include "Test.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();
    auto fileutil = FileUtils::getInstance();
    
    director->setOpenGLView(eglView);
	
#ifdef COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
    Test *test = new Test();
    test->run();
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    
    // Resolution設定
    const Resource* res = AppManager::getInstance()->getResource();
    std::vector<std::string> searchPath;
    searchPath.push_back(res->directory);
    fileutil->setSearchResolutionsOrder(searchPath);
    eglView->setDesignResolutionSize(res->size.width, res->size.height, res->policy);
    director->setContentScaleFactor(res->scaleFactor);
    
    // ccbiのロード
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("OpeningLayer", OpeningLayerLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("Opening.ccbi");
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
