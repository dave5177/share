#include "TouchLayer.h"

USING_NS_CC;

TouchLayer::TouchLayer()
{

}

TouchLayer::~TouchLayer()
{

}

bool TouchLayer::init()
{
	setTouchEnabled(true);
	return true;
}

void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("touch begin");
	if (pTouches->count() == 1)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());

		CCPoint touchStart = touch->getLocationInView();
		touchStart = CCDirector::sharedDirector()->convertToGL(touchStart);
		m_pHomeScene->m_touchStartPoint = touchStart;
	}

}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCLOG("touch end");
	if (pTouches->count() == 1)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());

		CCPoint touchEnd = touch->getLocationInView();
		touchEnd = CCDirector::sharedDirector()->convertToGL(touchEnd);
		m_pHomeScene->handleTouch(touchEnd);
	}
}

HomeScene* TouchLayer::getHomeScene()
{
	return m_pHomeScene;
}

void TouchLayer::setHomeScene(HomeScene* homeScene)
{
	m_pHomeScene = homeScene;
}