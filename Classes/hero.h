#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"const.h"
#include"ApplyLittleHero.h"
#include"weapon.h";
using namespace std;
using namespace cocos2d;
class Hero;
class Hero :public cocos2d::Node{
	friend class Player;
	friend class ImageSwitcher;
protected:
public:
	float atn;//��������
	float def;//���������
	float hp_max=100;//����ֵ
	float hp_now=hp_max;
	float mp_max;//����
	float mp_now;
	float as=1;//attack speed ����
	float ch=0.1;//critical hit ����
	float ch_ma=1.5;//magnification ����
	float ran;//range ���
	int kind1;//�������� ���֡���ʦ��սʿ���̿�
	int kind2 = 0;//�������  ��ħ����ʹ����������
	int price;
	int seat[5] = { 0 };
	float mp_increment=10;
	bool is_onboard=1;//�Ƿ��ϳ�	
	double target_distance;
	bool islive=1;
	Hero* target=nullptr;//Ŀ��
	Sprite* mine = nullptr;//�Լ�
	Vec2 hero_position;
	vector<int> kind;
	int level = 1;
	Weapon* wea;
	Vec2 target_position;
	void updateposition();
	void get_target(Hero* hero, Player enemy);
	ProgressTimer* hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	ProgressTimer* mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	Sprite* isdie= Sprite::create("die.png");
	Sprite* getmine() 
	{ 
		return mine;
	}
	Hero* gettarget(Player enemy) {
		get_target(this, enemy);
		return target;
	}
	Vec2 getposition() {
		return mine->getPosition();
	}
	bool getclink() {
		return clink;
	}
	void move_to_target(ApplyLittleHero*the,Hero* enemy);
	bool isTouch(Touch* touch, Event* event);
	bool clink=0;
	int No;
	ApplyLittleHero* the;
	Hero::Hero(int num,int level, ApplyLittleHero* ApplyLittleHero){
		//// ��������������
		//auto listener = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);

		//// �󶨴�����ʼ�¼�
		//listener->onTouchBegan = CC_CALLBACK_2(Hero::isTouch, this);

		//// ����������ӵ��¼��ַ���
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		//����λ��
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // �����СΪԭ����һ��
		hp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // ���������λ��
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
		hp->setPosition(Vec2(50, 30)); // ������λ��
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // �����СΪԭ����һ��
		mp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // ���������λ��
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
		mp->setPosition(Vec2(50, 40)); // ������λ��
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
		ran = 10 * level;
		hp_max = 150 * level;
		hp_now = 150 * level;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
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
		mine =sprite;
	}
	Sprite* sprite = nullptr;
	void attack(Hero* enemy, ApplyLittleHero* the, Player enemy_hero);
	void skill_add(ApplyLittleHero* the, Player enemy_hero, ProgressTimer* hp);//����ʱ����������
	void skill(Hero* target, ApplyLittleHero* the, Vec2 fromposition, Vec2 toposition,ProgressTimer* myhp);//�����ⶥ�ż���
};
#endif