#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate() {
}
void AppDelegate::initGLContextAttrs()
{ 
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    //初始化导演
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("The_Red-Headed_League", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }
director->getOpenGLView()->setDesignResolutionSize
(960,640, ResolutionPolicy::SHOW_ALL);
    // 显示 FPS
    director->setDisplayStats(true);
    // 设置 FPS. 
    director->setAnimationInterval(1.0 / 60);
    FileUtils::getInstance()->addSearchPath("res");
    //创建一个场景
    auto scene = HelloWorld::createScene();
    // run
    director->runWithScene(scene);
    return true;
}
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
