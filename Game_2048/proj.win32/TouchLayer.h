#ifndef _TOUCH_LAYER_H_
#define _TOUCH_LAYER_H_

#include "HomeScene.h"
#include "cocos2d.h"

///////////////////////////////////
//自定义的触摸层，create后必须setHomeScene
////////////////////////////////////
class TouchLayer : public cocos2d::CCLayer
{
public:
	TouchLayer();
	~TouchLayer();

	CREATE_FUNC(TouchLayer);

	/////////////////////////重写的方法///////////////////
	virtual bool init();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	/////////////////////////自定义的方法////////////////////////////

	//定义所处场景
	//CC_SYNTHESIZE(HomeScene*, m_pHomeScene, MHomeScene);

	void setHomeScene(HomeScene* homeScene);
	HomeScene* getHomeScene();
protected:

private:
	HomeScene* m_pHomeScene;
};

#endif //_TOUCH_LAYER_H_