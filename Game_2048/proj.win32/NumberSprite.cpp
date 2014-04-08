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

	pResult->m_new = false;

	pResult->setPosition(ccp(180 + point.y * 240, 1130 - point.x * 240));

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

void NumberSprite::synTo(NumberSprite* tarNumber)
{
	m_pTarNumber = tarNumber;
	int type = tarNumber->getMType();
	int row = tarNumber->getMPoint().x;
	int col = tarNumber->getMPoint().y;
	CCLOG("�ϳɣ�Ŀ��λ�ã�%d, %d��Ŀ�����ͣ�%d", row, col, type);
	m_pScene->removeNumSpr(this);//�Ƴ��Լ�
	tarNumber->doubleTo();
	
	/*int cells = 0;
	if (m_point.x != row)
	{
	cells = abs(m_point.x - row);
	} else {
	cells = abs(m_point.y - col);
	}*/

	/////////////////////////////�ƶ��Ķ���////////////////////////
	//CCMoveTo* actionMove = CCMoveTo::create(0.05f * cells, ccp(180 + m_point.y * 240, 1130 - m_point.x * 240));
	//this->runAction(actionMove);
	//this->runAction(CCSequence::create(actionMove, CCCallFunc::create(m_pScene,callfunc_selector(NumberSprite::moveCallBack)), NULL));//��cccallfunc����һ���ص���������
	
}

void NumberSprite::moveTo(const int row, const int col)
{
	m_pScene->moveNumberSprite(this, row, col);
	int cells = 0;
	if (m_point.x != row)
	{
		cells = abs(m_point.x - row);
	} else {
		cells = abs(m_point.y - col);
	}

	m_point.x = row;
	m_point.y = col;
	//this->setPosition(ccp(180 + m_point.x * 240, 1130 - m_point.y * 240));

	/////////////////////////////�ƶ��Ķ���////////////////////////
	CCMoveTo* actionMove = CCMoveTo::create(0.05f * cells, ccp(180 + m_point.y * 240, 1130 - m_point.x * 240));
	this->runAction(actionMove);
}

void NumberSprite::moveCallBack()
{
	m_pScene->removeNumSpr(this);//�Ƴ��Լ�
	m_pTarNumber->doubleTo();//Ŀ�����ֿ鷭����
	m_pTarNumber = NULL;
}

void NumberSprite::doubleTo()
{
	m_type *= 2;//���ͷ���
	m_pScene->addScore(m_type);
	m_new = true;
	resetTexture();

	////////////////////////һ���ĺϳɶ���///////////////////
	CCScaleTo *toSmall = CCScaleTo::create(0.0f, 0.8f, 0.8f);//����С����
	CCScaleTo *toBig = CCScaleTo::create(0.2f, 1, 1);
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

bool NumberSprite::isNew()
{
	return m_new;
}

void NumberSprite::setNew(bool valueNew)
{
	m_new = valueNew;
}

NumberSprite::NumberSprite()
{

}

NumberSprite::~NumberSprite()
{

}