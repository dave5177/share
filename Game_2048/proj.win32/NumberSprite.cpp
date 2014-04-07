#include "NumberSprite.h"
#include "HomeScene.h"

USING_NS_CC;

NumberSprite* NumberSprite::create(int type, CCPoint point, HomeScene* pScene)
{
	//return CCSprite::create(pszFileName);
	NumberSprite *pResult = new NumberSprite();

	char pFileName[1024];
	sprintf_s(pFileName, 20, "%d.png", type);
	pResult = (NumberSprite*)CCSprite::create(pFileName);

	//pResult->autorelease();
	pResult->m_point = point;
	
	pResult->m_type = type;

	pResult->m_pScene = pScene;

	pResult->setPosition(ccp(180 + point.y * 240, 1130 - point.x * 240));

	//////////////////////生成时从小到大的动画///////////////////////
	CCScaleTo *toSmall = CCScaleTo::create(0.0f, 0.1f, 0.1f);//从最小缩放
	CCScaleTo *toBig = CCScaleTo::create(0.3f, 1, 1);
	CCAction *createAction = CCSequence::create(toSmall, toBig, NULL);
	pResult->runAction(createAction);
	return pResult;
}

void NumberSprite::update(float dt)//主逻辑。
{

}

void NumberSprite::synTo(NumberSprite* tarNumber)
{
	int type = tarNumber->getMType();
	int row = tarNumber->getMPoint().x;
	int col = tarNumber->getMPoint().y;
	CCLOG("合成：目标位置：%d, %d；目标类型：%d", row, col, type);
	//moveTo(row, col);
	m_pScene->removeNumSpr(this);//移除自己

	tarNumber->doubleTo();//目标数字块翻倍。
}

void NumberSprite::moveTo(const int row, const int col)
{
	m_pScene->moveNumberSprite(this, row, col);
	m_point.x = row;
	m_point.y = col;
	//this->setPosition(ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));

	/////////////////////////////移动的动画////////////////////////
	CCMoveTo* actionMove = CCMoveTo::create(0.2f, ccp(180 + m_point.y * 240, 1130 - m_point.x * 240));
	this->runAction(actionMove);
}

void NumberSprite::doubleTo()
{
	m_type *= 2;//类型翻倍
	resetTexture();

	////////////////////////一闪的合成动画///////////////////
	CCScaleTo *toSmall = CCScaleTo::create(0.0f, 0.5f, 0.5f);//从最小缩放
	CCScaleTo *toBig = CCScaleTo::create(0.3f, 1, 1);
	CCAction *synAction = CCSequence::create(toSmall, toBig, NULL);
	this->runAction(synAction);
}

void NumberSprite::resetTexture()
{
	char pFileName[1024];
	sprintf_s(pFileName, 20, "%d.png", m_type);
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(pFileName));
}

CCPoint NumberSprite::getMPoint()
{
	return m_point;
}

void NumberSprite::setMPoint(CCPoint point)
{
	m_point = point;
}

int NumberSprite::getMType()
{
	return m_type;
}

void NumberSprite::setMType(int type) 
{
	m_type = type;
}

NumberSprite::NumberSprite()
{

}

NumberSprite::~NumberSprite()
{

}