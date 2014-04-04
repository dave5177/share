#ifndef _NUMBER_SPRITE_H_
#define _NUMBER_SPRITE_H_

#include "cocos2d.h"
#include "HomeScene.h"

USING_NS_CC;


///////////////////////////////////
//��ͼ���ֿ�
/////////////////////////////////
class NumberSprite : public CCSprite
{
public:
	NumberSprite();
	~NumberSprite();

	static NumberSprite* create(int type, CCPoint point, HomeScene* pScene);

	//////////////////////////////////////////////////////////////////////////
	//���߼�����
	//CCNodeĬ�ϲ�û������update�¼���Ϊ�����ö�ʱ������Ҫ����scheduleUpdate������������update��ִ���Լ��Ĵ��롣
	//��Ӧ�ģ����ǿ���ʹ��unscheduleUpdate����ֹͣ��ʱ����
	/////////////////////////////////////////////////////
	virtual void update(float dt);

	
	//CC_SYNTHESIZE_RETAIN(CCPoint, m_point, MPoint);
	void setMPoint(CCPoint point);

	CCPoint getMPoint();

	//////////////////////////////////////
	//����2��4��8��16......2048
	/////////////////////////////////////
	CC_SYNTHESIZE(int, m_type, MType);

	//��ָ�������е����ֺϳ�
	void synTo(const int row, const int col);

	//�ƶ���ָ������
	void moveTo(const int row, const int col);

	//�ϳɣ�����
	void doubleTo();

	//��������
	void resetTexture();

private:
		//��������
	HomeScene* m_pScene;

	//////////////////////////////////
	//�ڵ�ͼ�ϵ�λ�á���0��0��~��3,3��
	//////////////////////////////////
	CCPoint m_point;
};

#endif
