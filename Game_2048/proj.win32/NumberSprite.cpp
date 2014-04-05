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

	pResult->setPosition(ccp(180 + point.x * 240, 1130 - point.y * 240));
	pScene->changeMapInfo(type, point.x, point.y);

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

void NumberSprite::synTo(const int row, const int col)
{
	
	NumberSprite* tarNumSpr; 
	int type = m_pScene->getNumberSprInMap(tarNumSpr, row, col);
	if(tarNumSpr && type == m_type) {
		m_pScene->changeMapInfo(0, m_point.x, m_point.y);//当前格子设为空的
		moveTo(row, col);
		m_pScene->removeNumSpr(this);//移除自己

		tarNumSpr->doubleTo();//目标数字块翻倍。
	}
}

void NumberSprite::moveTo(const int row, const int col)
{
	m_pScene->changeMapInfo(0, m_point.x, m_point.y);//当前格子设为空的
	m_pScene->changeMapInfo(m_type, row, col);//目标格子设置
	m_point.x = row;
	m_point.y = col;
	//this->setPosition(ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));

	/////////////////////////////移动的动画////////////////////////
	CCMoveTo* actionMove = CCMoveTo::create(0.5f, ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));
}

void NumberSprite::doubleTo()
{
	m_type *= 2;//类型翻倍
	resetTexture();
	m_pScene->changeMapInfo(m_type, m_point.x, m_point.y);//改变地图格子的信息。

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

NumberSprite::NumberSprite()
{

}

NumberSprite::~NumberSprite()
{

}