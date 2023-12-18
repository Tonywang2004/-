#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"HelloWorldScene.h"
using namespace std;
using namespace cocos2d;
class Hero :public cocos2d::Node{
	friend class player;
	friend class ImageSwitcher;
protected:

public:
	float atn;//��������
	float matk;//magic attack ħ��������
	float def;//���������
	float mr;//magic resistance ħ��
	float hp_max=100;//����ֵ
	float hp_now=hp_max;
	float mp_max;//����
	float mp_now;
	float as=1;//attack speed ����
	float ch;//critical hit ����
	float ch_ma;//magnification ����
	float ran;//range ���
	int kind1;//�������� ���֡���ʦ��սʿ���̿�
	int kind2 = 0;//�������  ��ħ����ʹ����������
	int prize;
	float mp_increment=10;
	bool is_ontheboard;//�Ƿ��ϳ�	
	double target_distance;
	Hero* target = nullptr;//Ŀ��
	Sprite* mine = nullptr;//�Լ�
	Vec2 hero_position;
	Vec2 target_position;
	void updateposition();
	void take_danmage(Hero* enemy,HelloWorld* the,int danmage=0);
	void get_target(Hero* hero, Player enermy);
	Sprite* getmine() { return mine; }
	Hero* gettarget() { return target; }
};
//class Hero {
//public:
//	cocos2d::ProgressTimer* mp; // MP������
//	cocos2d::ProgressTimer* hp; // HP������
//	float mp_increment;         // MP��������
//	int hp_max;                 // ���HP
//	int hp_current;             // ��ǰHP
//
//	Hero() {
//		// ��ʼ��MP��HP������
//		mp = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("mp_bar.png"));
//		mp->setType(cocos2d::ProgressTimer::Type::BAR);
//		mp->setPercentage(0); // ��ʼMPΪ0
//
//		hp = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("hp_bar.png"));
//		hp->setType(cocos2d::ProgressTimer::Type::BAR);
//		hp->setPercentage(100); // �����ʼHPΪ100%
//
//		mp_increment = 0.5f; // ÿ������0.5%
//		hp_max = 100;        // �������HPΪ100
//		hp_current = 100;    // ��ʼHPΪ100
//	}
//
//	void update(float dt) {
//		// ����MP
//		float newMpPercentage = mp->getPercentage() + mp_increment;
//		if (newMpPercentage >= 100.0f) {
//			// MP�ﵽ100%������MP������HP
//			newMpPercentage = 0.0f;
//
//			// ����HP�ĵ�ǰֵ��20%
//			hp_current -= hp_max * 0.2;
//			if (hp_current < 0) hp_current = 0;
//
//			// ����HP������
//			float newHpPercentage = static_cast<float>(hp_current) / hp_max * 100.0f;
//			hp->setPercentage(newHpPercentage);
//		}
//		mp->setPercentage(newMpPercentage);
//	}
//
//	void startMpRegeneration() {
//		// ÿ֡����update��������MP��HP
//		cocos2d::Director::getInstance()->getScheduler()->schedule(
//			CC_SCHEDULE_SELECTOR(Hero::update), this, 0, false);
//	}
//};
class Ghostride :public Hero {
public:
	Ghostride(HelloWorld* helloworld){
		the = helloworld;
		atn = 20;
		matk = 0;
		def = 10;
		as = 1;
		hp_max = 100;
		hp_now = 100;
		mp_max = 10;
		mp_now = 4;
		mine = gr;
		gr->setContentSize(Size(100, 100));
		updateposition();
	}
	HelloWorld* the;
	Sprite* gr = Sprite::create("player.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the,Player enemy_hero,ProgressTimer* hp);//����ʱ����������
	void skill(Hero* target,HelloWorld* the,Vec2 fromposition,Vec2 toposition) ;//�����ⶥ�ż���:������ɵз��������ֵ�ٷ�֮ʮ��Ѫ��
};
#endif