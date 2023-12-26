#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Bank.h"
#include "Weapon.h"
#include "Const.h"
USING_NS_CC;
using namespace std;

class Hero :public Sprite {
	friend class Player;
protected:
	int ad;//������
	int def;//������
	int hp_max;//�������ֵ
	int hp_now;//��ǰ����ֵ
	int mp_max = 5;//����
	int mp_now = 2;//��ǰ����ֵ
	int mp_per_second = 1;//ÿ���õ�����
	float as = 1;//attack speed ����
	float ch_rate = 0;//critical hit rate������
	float ch_ma = 2.0;//magnification �����˺�����
	float ran;//range ���
	Vec2 hero_postion;//Ӣ���ڳ��ϵ�λ��
	int seat = 0;//Ӣ���ڱ�սϯ�ϵ����,��ΧΪ1~MAX_STORAGE_NUM����1~4
	int kind[4] = { 0 };//����֡�սʿ����ħ
	int level = 1;//��ǰӢ�۵ĵȼ���������
	int price = 0;//�۸�
	Weapon weapon = NULL;//Ӣ�۵�װ��
	bool is_on_board = false;//��¼Ӣ���Ƿ��ڳ���
	bool click = false;//��־Ӣ���Ƿ����ѡ��
	int No;//Ӣ�۵����
public:
	//virtual void ultimate() = 0;
	Hero() {
		ad = 0;
		def = 0;
		hp_max = 0;
		hp_now = 0;
		mp_max = 0;
		mp_now = 0;
		mp_per_second = 1;
		as = 1;
		ch_rate = 0;
		ch_ma = 2.0;
		ran = 1;
		hero_postion = Vec2(0, 0);
		seat = 0;
		for (int i = 0; i < 4; i++)
			kind[i] = 0;
		level = 1;
		price = 0;
		weapon = NULL;
		is_on_board = false;
		click = false;
		No = 0;
	}
	Hero(int index) {
		No = index;
	}
	//��Ĭ�ϲ����Ĺ��캯��
	bool operator==(const Hero& other) const {
		return No == other.No;
	}
	Hero& operator=(const Hero& other) {
		return Hero(other.No);
	}
};

#endif 

