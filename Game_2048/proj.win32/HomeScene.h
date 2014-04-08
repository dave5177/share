#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>

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

	void restartGame(cocos2d::CCObject* pSender);

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
	void removeNumSpr(cocos2d::CCSprite* tarNumSpr);

	//移动一个数字块到指定行列
	void moveNumberSprite(cocos2d::CCSprite* tarNumSpr, int row, int col);

	cocos2d::CCSprite** getNumberArr();

	//每次触摸时开始的点
	cocos2d::CCPoint m_touchStartPoint;

	//增加分数
	void addScore(int score);

	//检测游戏是否结束
	bool checkGameOver();

	bool leftCanMove();
	bool rightCanMove();
	bool upCanMove();
	bool downCanMove();


	cocos2d::CCSize m_VisibleSize;//可视区域size
	cocos2d::CCPoint m_Origin;//原点
private:
	cocos2d::CCLayer* m_pBackLayer;//背景层
	cocos2d::CCLayer* m_pActionLayer;//动作层
	cocos2d::CCLayer* m_pMenuLayer;//菜单层
	cocos2d::CCLayer* m_pTouchLayer;//触摸层

	cocos2d::CCSprite* m_pLogoSprite;//logo图标
	cocos2d::CCSprite* m_pGameOverSprite;//游戏结束
	cocos2d::CCMenu* m_pMainMenu;//
	cocos2d::CCMenuItemImage *m_pStartItem;//重新开始游戏按钮

	cocos2d::CCSprite* m_pNumberArr[4][4];
	cocos2d::CCLabelTTF* m_pLabelDebug[4][4];//地图调试信息。显示每个格子上的type类型；

	cocos2d::CCArray* m_pRemoveNum;

	int m_score;//分数

	cocos2d::CCLabelTTF* m_pScoreTTF;
};



#endif // __HOME_SCENE_H__