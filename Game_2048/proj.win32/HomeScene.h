#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>

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

	void restartGame(cocos2d::CCObject* pSender);

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
	void removeNumSpr(cocos2d::CCSprite* tarNumSpr);

	//�ƶ�һ�����ֿ鵽ָ������
	void moveNumberSprite(cocos2d::CCSprite* tarNumSpr, int row, int col);

	cocos2d::CCSprite** getNumberArr();

	//ÿ�δ���ʱ��ʼ�ĵ�
	cocos2d::CCPoint m_touchStartPoint;

	//���ӷ���
	void addScore(int score);

	//�����Ϸ�Ƿ����
	bool checkGameOver();

	bool leftCanMove();
	bool rightCanMove();
	bool upCanMove();
	bool downCanMove();


	cocos2d::CCSize m_VisibleSize;//��������size
	cocos2d::CCPoint m_Origin;//ԭ��
private:
	cocos2d::CCLayer* m_pBackLayer;//������
	cocos2d::CCLayer* m_pActionLayer;//������
	cocos2d::CCLayer* m_pMenuLayer;//�˵���
	cocos2d::CCLayer* m_pTouchLayer;//������

	cocos2d::CCSprite* m_pLogoSprite;//logoͼ��
	cocos2d::CCSprite* m_pGameOverSprite;//��Ϸ����
	cocos2d::CCMenu* m_pMainMenu;//
	cocos2d::CCMenuItemImage *m_pStartItem;//���¿�ʼ��Ϸ��ť

	cocos2d::CCSprite* m_pNumberArr[4][4];
	cocos2d::CCLabelTTF* m_pLabelDebug[4][4];//��ͼ������Ϣ����ʾÿ�������ϵ�type���ͣ�

	cocos2d::CCArray* m_pRemoveNum;

	int m_score;//����

	cocos2d::CCLabelTTF* m_pScoreTTF;
};



#endif // __HOME_SCENE_H__