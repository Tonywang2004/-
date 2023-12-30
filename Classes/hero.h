#ifndef HERO_H
#define HERO_H
#pragma once
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"const.h"
#include"ApplyLittleHero.h"
#include"weapon.h";
using namespace std;
using namespace cocos2d;
class Hero :public cocos2d::Node{
	friend class Player;
	friend class Weapon;
	friend class ImageSwitcher;
	friend class ApplyLittleHero;
protected:
public:
	float atn;//��������
	float def;//���������
	float hp_max;//����ֵ
	float hp_now;
	float mp_max;//����
	float mp_now;
	float as=1;//attack speed ����
	float ch=0.1;//critical hit ����
	float ch_ma=1.5;//magnification ����
	float ran;//range ���
	int price;
	int seat=0;
	float mp_increment=10;
	bool is_on_board=1;//�Ƿ��ϳ�	
	double target_distance;
	bool islive=1;
	Sprite* mine = nullptr;//�Լ�
	Vec2 hero_position;
	int kind[4] = {0};
	int level = 1;
	Weapon* wea=nullptr;
	void updateposition();
	ProgressTimer* hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	ProgressTimer* mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	Sprite* isdie;
	Sprite* getmine() const
	{ 
		return mine;
	}
	Hero* gettarget(Player enemy) const {
		return enemy.target;
	}
	Vec2 getposition() const {
		return mine->getPosition();
	}
	void setclick(int num)
	{
		click = num;
	}
	int getclick() const
	{
		return click;
	}
	int click = 0;
	int No;
	ApplyLittleHero* the;
	void enableMouseControl(bool enabled,ApplyLittleHero* the);
	cocos2d::EventListenerMouse* _Listener=nullptr; 
	bool listenerinit(); //�����������
	Hero::Hero(int num,int lv, ApplyLittleHero* ApplyLittleHero){
		level = lv;
		isdie = Sprite::create("die.png");
		switch (num)
		{
			case 1:
				sprite = Sprite::create("soldier.png");
				break;
			case 2:
				sprite = Sprite::create("supersoldier.png");
				break;
			case 3:
				sprite = Sprite::create("Demonsoldier.png");
				break;
			case 4:
				sprite = Sprite::create("shooter.png");
				break;
			case 5:
				sprite = Sprite::create("supershooter.png");
				break;
			case 6:
				sprite = Sprite::create("demonshooter.png");
				break;
		}
		mine = sprite;
		mine->setContentSize(Size(50, 50));
		//����λ��
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // �����СΪԭ����һ��
		hp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(20, 30)); // ���������λ��
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
		hp->setPosition(Vec2(20, 30)); // ������λ��
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // �����СΪԭ����һ��
		mp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(20, 40)); // ���������λ��
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
		mp->setPosition(Vec2(20, 40)); // ������λ��
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(20, 20));
		isdie->setPosition(Vec2(10, 10));
		isdie->setVisible(false);
		mine->addChild(isdie);
		//����ΪѪ�������Ƿ���������ĳ�ʼ��
		the = ApplyLittleHero;
		atn = 20 * level;
		def = 10 * level;
		as = 1;
		is_on_board = 0;
		ran = 10 * level;
		hp_max = 150 * level;
		hp_now = 150 * level;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
	}
	Sprite* sprite = nullptr;
	void hpsetmax() {
		hp->setPercentage(100);
	}
	void move_to_target(Player enemy_hero);
	void attack(Hero* enemy, ApplyLittleHero* the, Player enemy_hero);
	void skill_add(ApplyLittleHero* the, Player enemy_hero, ProgressTimer* hp);//����ʱ����������
	void skill(Hero* target, ApplyLittleHero* the, Vec2 fromposition, Vec2 toposition,ProgressTimer* myhp) const;//�����ⶥ�ż���
};
#endif