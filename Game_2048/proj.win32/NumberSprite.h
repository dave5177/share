#ifndef _NUMBER_SPRITE_H_
#define _NUMBER_SPRITE_H_

#include "cocos2d.h"
#include "HomeScene.h"

USING_NS_CC;


///////////////////////////////////
//地图数字块
/////////////////////////////////
class NumberSprite : public CCSprite
{
public:
	NumberSprite();
	~NumberSprite();

	static NumberSprite* create(int type, CCPoint point, HomeScene* pScene);

	//////////////////////////////////////////////////////////////////////////
	//主逻辑调用
	//CCNode默认并没有启用update事件，为了启用定时器，需要调用scheduleUpdate方法，并重载update以执行自己的代码。
	//对应的，我们可以使用unscheduleUpdate方法停止定时器。
	/////////////////////////////////////////////////////
	virtual void update(float dt);

	
	//CC_SYNTHESIZE_RETAIN(CCPoint, m_point, MPoint);
	void setMPoint(CCPoint point);

	CCPoint getMPoint();

	//////////////////////////////////////
	//类型2、4、8、16......2048
	/////////////////////////////////////
	CC_SYNTHESIZE(int, m_type, MType);

	//与指定格子中的数字合成
	void synTo(const int row, const int col);

	//移动到指定格子
	void moveTo(const int row, const int col);

	//合成，翻倍
	void doubleTo();

	//重设纹理
	void resetTexture();

private:
		//所处场景
	HomeScene* m_pScene;

	//////////////////////////////////
	//在地图上的位置。（0，0）~（3,3）
	//////////////////////////////////
	CCPoint m_point;
};

#endif
