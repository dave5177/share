#include "HomeScene.h"
#include "NumberSprite.h"
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <math.h>

USING_NS_CC;
using namespace std;


// on "init" you need to initialize your instance
bool HomeScene::init()
{
	//////////////////////////////初始化成员//////////////////////////
	m_pNumberArr = CCArray::create();
	m_pNumberArr->retain();//增加一次引用，类销毁的时候需要手动释放

	for (int i=0; i<4; i++)
	{
		for (int j=0; j< 4; j++)
		{
			m_pMapInfo[i][j] = 0;
		}
	}
	

	//////////////////////////////添加元素////////////////////////
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	m_pBackLayer = CCLayer::create();
	this->addChild(m_pBackLayer, -100);//添加背景图层。
	m_pActionLayer = CCLayer::create();
	this->addChild(m_pActionLayer, 0);//动作层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setHomeScene(this);//触摸层
	this->addChild(m_pTouchLayer, 50);
	m_pMenuLayer = CCLayer::create();
	this->addChild(m_pMenuLayer, 100);//菜单层

	CCSprite* pBackSprite = CCSprite::create("home_back.png");

    // position the sprite on the center of the screen
    pBackSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));//默认以图片中点为锚点

	m_pBackLayer->addChild(pBackSprite, 0);

    /////////////////////////////
    //按钮添加
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

	///////////////最初生成两个数字块/////////////////
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
	vector<CCPoint> emptyMap;//地图中所有的空格子
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j< 4; j++)
		{
			if (m_pMapInfo[i][j] == 0)
			{
				emptyMap.push_back(ccp(i,j));
			}
		}
	}
	srand((unsigned)time(NULL));//设置随机数种子
	int point = rand() % (emptyMap.size());
	
	srand((unsigned)time(NULL));
	int type = rand() % 100;//0~99;
	NumberSprite* pNumberSprite;
	if(type < 10) {//10%的概率生成4
		pNumberSprite = NumberSprite::create(4, emptyMap[point]);
		m_pNumberArr->addObject(pNumberSprite);
	} else {//生成2
		pNumberSprite = NumberSprite::create(2, emptyMap[point]);
		m_pNumberArr->addObject(pNumberSprite);
	}
	m_pActionLayer->addChild(pNumberSprite, 0);
}

void HomeScene::changeMapInfo(const int type, const int row, const int col)
{
	m_pMapInfo[row][col] = type;
}

int HomeScene::getNumberSprInMap(NumberSprite* resultNum, const int row, const int col)
{
	NumberSprite* numSpr;
	CCObject *cObj;
	CCARRAY_FOREACH(m_pNumberArr, cObj)
	{
		numSpr = (NumberSprite*)cObj;
		CCPoint point = numSpr->getMPoint();
		if (point.x == row && point.y == col)
		{
			resultNum = numSpr;
			return numSpr->getMType();
		}
	}

	return 0;
}

void HomeScene::handleTouch(CCPoint endTouchPoint)
{
	if (abs(m_touchStartPoint.x - endTouchPoint.x) > 50 && abs(m_touchStartPoint.y - endTouchPoint.y) > 50)
	{
		if (abs(m_touchStartPoint.x - endTouchPoint.x) > abs(m_touchStartPoint.y - endTouchPoint.y))//x方向移动的多,则为左右
		{
			if(m_touchStartPoint.x > endTouchPoint.x)//向左
			{
				leftSlide();
			} else {//向右
				rightSlide();
			}
		} else {//上下
			if(m_touchStartPoint.y > endTouchPoint.y)//向上
			{
				upSlide();
			} else {//向下滑动
				downSlide();
			}
		}
		
	}
	
}

void HomeScene::removeNumSpr(NumberSprite* tarNumSpr)
{
	m_pActionLayer->removeChild(tarNumSpr, true);
}

void HomeScene::leftSlide()
{//左边有空格先移动。再检测合成。
	bool moved = false;
	for (int i=0; i<4; i++)
	{
		NumberSprite* pLeftNumberSpr;
		for (int j=0; j<4; j++)
		{
			NumberSprite* pCurrentNum;
			int type = getNumberSprInMap(pCurrentNum, i, j);
			if(j) {
				if(type){//当前格子有数字块
					if(pLeftNumberSpr) {//左边有数字块
						if(pLeftNumberSpr->getMType() == type) {//数字相同合成
							pCurrentNum->synTo(pLeftNumberSpr->getMPoint().x, pLeftNumberSpr->getMPoint().y);
							moved = true;
						} else if(pLeftNumberSpr->getMPoint().x + 1 < pCurrentNum->getMPoint().x){//和左边的数字块中间空了格子
							pCurrentNum->moveTo(pLeftNumberSpr->getMPoint().x + 1, pLeftNumberSpr->getMPoint().y);
							moved = true;
						}
					} else {//移动到最左端
						pCurrentNum->moveTo(0, pLeftNumberSpr->getMPoint().y);
						moved = true;
					}
				}
			} else {//j==0,最左边的列
				
			}
			pLeftNumberSpr = pCurrentNum;
		}
		
	}

	if(moved) {//如果移动了就生成一个数字块
		createNumberSprite();
	}
	
}

void HomeScene::rightSlide()
{

}

void HomeScene::upSlide()
{

}

void HomeScene::downSlide()
{

}

void HomeScene::update(float dt)
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
	//m_pNumberArr->release();//释放ccArray
}

TouchLayer::TouchLayer()
{

}

TouchLayer::~TouchLayer()
{

}

bool TouchLayer::init()
{

}

void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());

		CCPoint touchStart = touch->getLocationInView();
		touchStart = CCDirector::sharedDirector()->convertToGL(touchStart);
		m_pHomeScene->m_touchStartPoint = touchStart;
	}
	
}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());

		CCPoint touchEnd = touch->getLocationInView();
		touchEnd = CCDirector::sharedDirector()->convertToGL(touchEnd);
		m_pHomeScene->handleTouch(touchEnd);
	}
}

HomeScene* TouchLayer::getHomeScene()
{
	return m_pHomeScene;
}

void TouchLayer::setHomeScene(HomeScene* homeScene)
{
	m_pHomeScene = homeScene;
}