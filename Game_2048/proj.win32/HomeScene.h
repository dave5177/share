#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>
#include "NumberSprite.h"
#include "TouchLayer.h"

using namespace std;


////////////////////////场景///////////////////
class HomeScene : public cocos2d::CCScene
{
public:

	HomeScene();
	~HomeScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
    void menuCloseCallback(cocos2d::CCObject* pSender);

	//////////////////////////////////////////////////////////////////////////
	//主逻辑调用
	//CCNode默认并没有启用update事件，为了启用定时器，需要调用scheduleUpdate方法，并重载update以执行自己的代码。
	//对应的，我们可以使用unscheduleUpdate方法停止定时器。
	/////////////////////////////////////////////////////
	virtual void update(float dt);
    
    // implement the "static node()" method manually
	//cocos2d-x宏定义的静态create方法
    CREATE_FUNC(HomeScene);
	
	//随机生成数字块
	void createNumberSprite();

	//改变地图信息
	void changeMapInfo(const int type, const int row, const int col);

	//获取指定行列上的数字块，取到就存储在第一个指针参数里，并返回其type。如果该位置没有数字块则返回0
	int getNumberSprInMap(NumberSprite* resultNum, const int row, const int col);

	//触摸结束处理，参数为抬起时的像素点。
	void handleTouch(cocos2d::CCPoint endTouchPoint);

	//左滑处理
	void leftSlide();

	//右滑处理
	void rightSlide();

	//上滑
	void upSlide();

	//下滑
	void downSlide();

	//移除一个数字块
	void removeNumSpr(NumberSprite* tarNumSpr);

	//cocos2d-x的宏定义get和set成员，第一个参数是成员类型，第二个参数是成员名，第三个参数是get和set的成员函数名
	CC_SYNTHESIZE(cocos2d::CCArray*, m_pNumberArr, NumberArr);

	//每次触摸时开始的点
	CCPoint m_touchStartPoint;

private:
	cocos2d::CCLayer* m_pBackLayer;//背景层
	cocos2d::CCLayer* m_pActionLayer;//动作层
	cocos2d::CCLayer* m_pMenuLayer;//菜单层
	TouchLayer* m_pTouchLayer;//触摸层

	int m_pMapInfo[4][4];//地图信息（0~2048）。0为空。

};



#endif // __HOME_SCENE_H__
