#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "bank.h"
#include "weapon.h"
#include "const.h"
USING_NS_CC;
using namespace std;

class Card;

class Hero :public Sprite {
	friend class Card;
	friend class Shop;
	friend class Player;
	friend class Role;
	friend class ImageSwitcher;
protected:
	int ad;//attack damage������
	int ap;//ability power��ǿ
	int def;//���������
	int mr;//magic resistance ħ��
	int hp_max;//�������ֵ
	int hp_now;//��ǰ����ֵ
	int mp_max = 5;//����
	int mp_now = 2;//��ǰ����ֵ
	int mp_per_second = 1;//ÿ���õ�����
	float as = 1;//attack speed ����
	float ch_rate = 0;//critical hit rate������
	float ch_ma = 2.0;//magnification �����˺�����
	float ran;//range ���
	Vec2 postion;//Ӣ���ڳ��ϵ�λ��
	vector<int>kind;//����֡���ʦ��սʿ���̿͡���ħ����ʹ������
	int level = 1;//��ǰӢ�۵ĵȼ���������
	Weapon weapon[3];//Ӣ�۵�װ����
	bool is_on_board;//��¼Ӣ���Ƿ��ڳ���
	int No;//Ӣ�۵����
public:
	//virtual void ultimate() = 0;
	Hero() {
		No = pow(100, level) * No;
	}//��Ĭ�ϲ����Ĺ��캯��
	bool operator==(const Hero& other) const {
		return No == other.No;
	}
};

//����
class Card {
	friend class Player;
private:
	int price;//�۸�
	string image;//����ͼƬ
	Hero hero;//���ƶ�Ӧ��Ӣ��
public:
	Card(int p, string s, int x = 0, int y = 0, int length = 40, int width = 40) :price(p), image(s) {
		// ���ؿ���ͼƬ��Ϊ����
		// Ĭ��λ��Ϊ(0,0)������Ĭ�ϳ���ֱ�Ϊ40��40
		auto hero = Hero::create(image,Rect(x,y,length,width));
	}
};
#endif 

