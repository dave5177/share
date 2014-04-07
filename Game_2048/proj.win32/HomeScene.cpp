#include "HomeScene.h"
#include "NumberSprite.h"
#include "TouchLayer.h"
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <math.h>

USING_NS_CC;
using namespace std;


// on "init" you need to initialize your instance
bool HomeScene::init()
{
	//////////////////////////////��ʼ����Ա//////////////////////////
	for (int i=0; i<4; i++)
	{
		for (int j=0; j< 4; j++)
		{
			m_pNumberArr[i][j] = NULL;
		}
	}
	

	//////////////////////////////���Ԫ��////////////////////////
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	m_pBackLayer = CCLayer::create();
	this->addChild(m_pBackLayer, -100);//��ӱ���ͼ�㡣
	m_pActionLayer = CCLayer::create();
	this->addChild(m_pActionLayer, 0);//������
	m_pTouchLayer = TouchLayer::create();
	((TouchLayer*)m_pTouchLayer)->setHomeScene(this);//������
	this->addChild(m_pTouchLayer, 50);
	m_pMenuLayer = CCLayer::create();
	this->addChild(m_pMenuLayer, 100);//�˵���

	for (int i = 0; i< 4; i++)
	{
		for (int j=0; j<4; j++)
		{
			NumberSprite* ns = (NumberSprite*)m_pNumberArr[i][j];
			char str[2] = "0";
			if(ns) {
				sprintf_s(str, 2,"%d", ns->getMType());
			}
			m_pLabelDebug[i][j] = CCLabelTTF::create(str, "����", 50);
			m_pLabelDebug[i][j]->setPosition(ccp(180 + j * 240, 1130 - i * 240));
			m_pLabelDebug[i][j]->setColor(ccc3(0, 0, 0));
			m_pMenuLayer->addChild(m_pLabelDebug[i][j], 10);
		}
		
	}
	
	CCLabelBMFont* pFontDebug = CCLabelBMFont::create();

	CCSprite* pBackSprite = CCSprite::create("home_back.png");

    // position the sprite on the center of the screen
    pBackSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));//Ĭ����ͼƬ�е�Ϊê��

	m_pBackLayer->addChild(pBackSprite, 0);

    /////////////////////////////
    //��ť���
    CCMenuItemImage *pRankItem = CCMenuItemImage::create(
                                        "ListBtn_0.png",
                                        "ListBtn_1.png",
                                        this,
                                        menu_selector(HomeScene::menuCloseCallback));
    
	pRankItem->setPosition(ccp(560 + pRankItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - 380 - pRankItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(pRankItem);
    pMenu->setPosition(CCPointZero);
    m_pMenuLayer->addChild(pMenu, 20);

	CCSprite *pLogo = CCSprite::create("Logo.png");
	pLogo->setPosition(ccp(40 + pLogo->getContentSize().width / 2, origin.y + visibleSize.height - 180 - pLogo->getContentSize().height/2));
	m_pMenuLayer->addChild(pLogo, 0);

	CCSprite *pScoreBar = CCSprite::create("GamePoint.png");
	pScoreBar->setPosition(ccp(560 + pScoreBar->getContentSize().width / 2, origin.y + visibleSize.height - 180 - pScoreBar->getContentSize().height/2));
	m_pMenuLayer->addChild(pScoreBar, 0);

	///////////////��������������ֿ�/////////////////
	for (int i=0; i<2; i++)
	{
		this->createNumberSprite();
	}
	
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            //origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");


    // add the sprite as a child to this layer
    
    return true;
}

void HomeScene::createNumberSprite()
{
	vector<CCPoint> emptyMap;//��ͼ�����еĿո���
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j< 4; j++)
		{
			if (m_pNumberArr[i][j] == NULL)
			{
				emptyMap.push_back(ccp(i,j));
			}
		}
	}
	srand((unsigned)time(NULL));//�������������
	int point = rand() % (emptyMap.size());
	
	srand((unsigned)time(NULL));
	int type = rand() % 100;//0~99;
	NumberSprite* pNumberSprite;
	if(type < 10) {//10%�ĸ�������4
		pNumberSprite = NumberSprite::create(4, emptyMap[point], this);
		m_pNumberArr[(int)emptyMap[point].x][(int)emptyMap[point].y]=pNumberSprite;
	} else {//����2
		pNumberSprite = NumberSprite::create(2, emptyMap[point], this);
		m_pNumberArr[(int)emptyMap[point].x][(int)emptyMap[point].y]=pNumberSprite;
	}
	m_pActionLayer->addChild(pNumberSprite, 0);
	emptyMap.clear();
}

void HomeScene::handleTouch(CCPoint endTouchPoint)
{
	if (abs(m_touchStartPoint.x - endTouchPoint.x) > 50 || abs(m_touchStartPoint.y - endTouchPoint.y) > 50)
	{
		if (abs(m_touchStartPoint.x - endTouchPoint.x) > abs(m_touchStartPoint.y - endTouchPoint.y))//x�����ƶ��Ķ�,��Ϊ����
		{
			if(m_touchStartPoint.x > endTouchPoint.x)//����
			{
				leftSlide();
			} else {//����
				rightSlide();
			}
		} else {//����
			if(m_touchStartPoint.y > endTouchPoint.y)//����
			{
				upSlide();
			} else {//���»���
				downSlide();
			}
		}
		
	}
	
}

void HomeScene::removeNumSpr(CCSprite* tarNumSpr)
{
	NumberSprite* ns = (NumberSprite*)tarNumSpr;
	CCPoint point = ns->getMPoint();
	m_pNumberArr[(int)point.x][(int)point.y] = NULL;
	m_pActionLayer->removeChild(ns, false);
	
}

void HomeScene::moveNumberSprite(cocos2d::CCSprite* tarNumSpr, int row, int col)
{
	m_pNumberArr[row][col] = tarNumSpr;
	CCPoint cp = ((NumberSprite*)tarNumSpr)->getMPoint();
	m_pNumberArr[(int)cp.x][(int)cp.y] = NULL;
}

CCSprite** HomeScene::getNumberArr()
{
	return (CCSprite**)m_pNumberArr;
}

void HomeScene::update(float dt)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			NumberSprite* ns = (NumberSprite*)m_pNumberArr[i][j];
			char str[2] = "0";
			if(ns) {
				sprintf_s(str, 2,"%d", ns->getMType());
			}
			m_pLabelDebug[i][j]->setString(str);
		}
	}
	
}

void HomeScene::leftSlide()
{//����пո����ƶ����ټ��ϳɡ�
	bool moved = false;
	for (int i=0; i<4; i++)
	{
		NumberSprite* pLeftNumberSpr = NULL;
		for (int j=0; j<4; j++)
		{
			NumberSprite* pCurrentNum = (NumberSprite*)m_pNumberArr[i][j];
			if(j) {
				if(pCurrentNum){//��ǰ���������ֿ�
					if(pLeftNumberSpr) {//��������ֿ�
						if(pLeftNumberSpr->getMType() == pCurrentNum->getMType()) {//������ͬ�ϳ�
							pCurrentNum->synTo(pLeftNumberSpr);
							moved = true;
						} else if(pLeftNumberSpr->getMPoint().y + 1 < pCurrentNum->getMPoint().y){//����ߵ����ֿ��м���˸���
							pCurrentNum->moveTo(pCurrentNum->getMPoint().x, pLeftNumberSpr->getMPoint().y + 1);
							moved = true;
						}
					} else {//�ƶ��������
						pCurrentNum->moveTo(pCurrentNum->getMPoint().x, 0);
						moved = true;
					}
				}
			} else {//j==0,����ߵ���
				
			}
			if (pCurrentNum)
			{
				pLeftNumberSpr = pCurrentNum;
			}
			
		}
		
	}

	if(moved) {//����ƶ��˾�����һ�����ֿ�
		createNumberSprite();
	}
	
}

void HomeScene::rightSlide()
{
	bool moved = false;
	for (int i=0; i<4; i++)
	{
		NumberSprite* pRightNumberSpr = NULL;
		for (int j=3; j>=0; j--)//�����������
		{
			NumberSprite* pCurrentNum = (NumberSprite*)m_pNumberArr[i][j];
			if(j < 3) {
				if(pCurrentNum){//��ǰ���������ֿ�
					if(pRightNumberSpr) {//�ұ������ֿ�
						if(pRightNumberSpr->getMType() == pCurrentNum->getMType()) {//������ͬ�ϳ�
							pCurrentNum->synTo(pRightNumberSpr);
							moved = true;
						} else if(pRightNumberSpr->getMPoint().y - 1 > pCurrentNum->getMPoint().y){//���ұߵ����ֿ��м���˸���
							pCurrentNum->moveTo(pCurrentNum->getMPoint().x, pRightNumberSpr->getMPoint().y - 1);
							moved = true;
						}
					} else {//�ұ�û�����ֿ��ƶ������Ҷ�
						pCurrentNum->moveTo(pCurrentNum->getMPoint().x, 3);
						moved = true;
					}
				}
			}
			if (pCurrentNum)
			{
				pRightNumberSpr = pCurrentNum;
			}

		}

	}

	if(moved) {//����ƶ��˾�����һ�����ֿ�
		createNumberSprite();
	}
}

void HomeScene::upSlide()
{

}

void HomeScene::downSlide()
{

}

void HomeScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

HomeScene::HomeScene()
{

}

HomeScene::~HomeScene()
{
	//m_pNumberArr->release();//�ͷ�ccArray
}
