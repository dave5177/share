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

	//////////////////////����ʱ��С����Ķ���///////////////////////
	CCScaleTo *toSmall = CCScaleTo::create(0.0f, 0.1f, 0.1f);//����С����
	CCScaleTo *toBig = CCScaleTo::create(0.3f, 1, 1);
	CCAction *createAction = CCSequence::create(toSmall, toBig, NULL);
	pResult->runAction(createAction);
	return pResult;
}

void NumberSprite::update(float dt)//���߼���
{

}

void NumberSprite::synTo(const int row, const int col)
{
	
	NumberSprite* tarNumSpr; 
	int type = m_pScene->getNumberSprInMap(tarNumSpr, row, col);
	if(tarNumSpr && type == m_type) {
		m_pScene->changeMapInfo(0, m_point.x, m_point.y);//��ǰ������Ϊ�յ�
		moveTo(row, col);
		m_pScene->removeNumSpr(this);//�Ƴ��Լ�

		tarNumSpr->doubleTo();//Ŀ�����ֿ鷭����
	}
}

void NumberSprite::moveTo(const int row, const int col)
{
	m_pScene->changeMapInfo(0, m_point.x, m_point.y);//��ǰ������Ϊ�յ�
	m_pScene->changeMapInfo(m_type, row, col);//Ŀ���������
	m_point.x = row;
	m_point.y = col;
	//this->setPosition(ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));

	/////////////////////////////�ƶ��Ķ���////////////////////////
	CCMoveTo* actionMove = CCMoveTo::create(0.5f, ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));
}

void NumberSprite::doubleTo()
{
	m_type *= 2;//���ͷ���
	resetTexture();
	m_pScene->changeMapInfo(m_type, m_point.x, m_point.y);//�ı��ͼ���ӵ���Ϣ��

	////////////////////////һ���ĺϳɶ���///////////////////
	CCScaleTo *toSmall = CCScaleTo::create(0.0f, 0.5f, 0.5f);//����С����
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