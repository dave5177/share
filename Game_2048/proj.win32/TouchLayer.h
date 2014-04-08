#ifndef _TOUCH_LAYER_H_
#define _TOUCH_LAYER_H_

#include "HomeScene.h"
#include "cocos2d.h"

///////////////////////////////////
//�Զ���Ĵ����㣬create�����setHomeScene
////////////////////////////////////
class TouchLayer : public cocos2d::CCLayer
{
public:
	TouchLayer();
	~TouchLayer();

	CREATE_FUNC(TouchLayer);

	/////////////////////////��д�ķ���///////////////////
	virtual bool init();

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	/////////////////////////�Զ���ķ���////////////////////////////

	//������������
	//CC_SYNTHESIZE(HomeScene*, m_pHomeScene, MHomeScene);

	void setHomeScene(HomeScene* homeScene);
	HomeScene* getHomeScene();
protected:

private:
	HomeScene* m_pHomeScene;
};

#endif //_TOUCH_LAYER_H_