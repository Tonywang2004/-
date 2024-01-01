#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define ROLETAG 111

class playerroleLayer : public Layer
{
public:
	int camp = 1;  // 1�����ҷ�  0����з�
	float max_blood = 10;
	float cur_blood = 10;
	Vec2 cur_position;

	ProgressTimer* healthBar;//Ѫ����
	static playerroleLayer* createLayer(int tag);
	void attack(playerroleLayer* target);   //ССӢ�۷������

	int getCamp() {
		return camp;
	}

	float getMaxBlood() {
		return max_blood;
	}

	float getCurBlood() {
		return cur_blood;
	}

	Vec2 getCurPos() {
		return cur_position;
	}
	
};

