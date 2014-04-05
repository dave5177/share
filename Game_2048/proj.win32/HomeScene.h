#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>
#include "NumberSprite.h"
#include "TouchLayer.h"

using namespace std;


////////////////////////����///////////////////
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
	//���߼�����
	//CCNodeĬ�ϲ�û������update�¼���Ϊ�����ö�ʱ������Ҫ����scheduleUpdate������������update��ִ���Լ��Ĵ��롣
	//��Ӧ�ģ����ǿ���ʹ��unscheduleUpdate����ֹͣ��ʱ����
	/////////////////////////////////////////////////////
	virtual void update(float dt);
    
    // implement the "static node()" method manually
	//cocos2d-x�궨��ľ�̬create����
    CREATE_FUNC(HomeScene);
	
	//����������ֿ�
	void createNumberSprite();

	//�ı��ͼ��Ϣ
	void changeMapInfo(const int type, const int row, const int col);

	//��ȡָ�������ϵ����ֿ飬ȡ���ʹ洢�ڵ�һ��ָ��������������type�������λ��û�����ֿ��򷵻�0
	int getNumberSprInMap(NumberSprite* resultNum, const int row, const int col);

	//����������������Ϊ̧��ʱ�����ص㡣
	void handleTouch(cocos2d::CCPoint endTouchPoint);

	//�󻬴���
	void leftSlide();

	//�һ�����
	void rightSlide();

	//�ϻ�
	void upSlide();

	//�»�
	void downSlide();

	//�Ƴ�һ�����ֿ�
	void removeNumSpr(NumberSprite* tarNumSpr);

	//cocos2d-x�ĺ궨��get��set��Ա����һ�������ǳ�Ա���ͣ��ڶ��������ǳ�Ա����������������get��set�ĳ�Ա������
	CC_SYNTHESIZE(cocos2d::CCArray*, m_pNumberArr, NumberArr);

	//ÿ�δ���ʱ��ʼ�ĵ�
	CCPoint m_touchStartPoint;

private:
	cocos2d::CCLayer* m_pBackLayer;//������
	cocos2d::CCLayer* m_pActionLayer;//������
	cocos2d::CCLayer* m_pMenuLayer;//�˵���
	TouchLayer* m_pTouchLayer;//������

	int m_pMapInfo[4][4];//��ͼ��Ϣ��0~2048����0Ϊ�ա�

};



#endif // __HOME_SCENE_H__
