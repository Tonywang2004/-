#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "ApplyLittleHero.h"
#include "weapon.h"
#include "const.h"
#include <vector>
USING_NS_CC;
using namespace std;

//����һ������࣬������ҵĽ�Ǯ�����飬�ȼ���Ӣ�������
class Player {
	friend class Hero;
	friend class ApplyLittleHero;
private:
	int stage = 0;//��¼��ǰ��Ϸ�׶�
	int hp = 100;//�������ֵ
	int money = 0;//��Ǯ
	int exp = 0;//����
	int level = 1;//�ȼ�
	int max_hero_num = 0;//���ϳ���Ӣ���������
	int hero_alive = 0;//ÿ�ֶ��ĺ����Ӣ������
	int hero_num = 0;//���ϵ�Ӣ������
	int storage_num = 0;//��սϯ��Ӣ������
	int kind[4] = { 0 };//�սʿ�����֡���ħ
public:	
	std::vector<Hero*> bank;
	//װ���ϳ�·��
	map<pair<int, int>, int>WeaponCombination = {
		{{BOW,BOW},HURRICANE},{{ARMOR,ARMOR},THORNMAIL},{{SPATULA,SPATULA},NATUREFORCE},{{BOW,ARMOR},SHIELDBOW},{{BOW,SPATULA},EXTRASHOOTER},{{ARMOR,SPATULA},EXTRASHOOTER}
	};
	ApplyLittleHero* the;
	bool lock = false;//���������̵�
	Hero* storage[MAX_STORAGE_NUM + 1];//����ϯ�����ڴ������Ѿ�����δ�ϳ���Ӣ��
	std::vector<Hero*> hero_on_board;//�ϳ���Ӣ��
	std::vector<Weapon*> weapon_for_player;//����ѻ����δ��Ӣ��װ�ϵ�װ��
	std:: vector<Hero*> shop_for_player;//��ҵ��̵�
	bool HasNatureForce = false;//��־�Ƿ�ӵ��װ������Ȼ֮������ӵ�����1�˿�����
	bool rune[RUNE_TYPES + 1];//ǿ�����ģ�
	//���캯��
	Player(ApplyLittleHero* applylittlehero=nullptr) {
		stage = 0;
		hp = 100;
		money = 0;
		exp = 0;
		level = 1;
		max_hero_num = 0;
		hero_alive = 0;
		hero_num = 0;
		storage_num = 0;
		the = applylittlehero;
		for (int i = 0; i < 4; i++)
			kind[i] = 0;
		lock = false;
		for (int i = 0; i <= MAX_STORAGE_NUM; i++)
			storage[i] = NULL;
		HasNatureForce = false;
		for (int i = 0; i <= RUNE_TYPES; i++)
			rune[i] = false;
	}
	void cal_kind();//���������
	void use_kind();//ÿ����Ϸ��ʼǰ�Զ������ӳ�
	void cancel_kind();//ÿ����Ϸ�������Զ������ӳ�
	void switch_lock();//����/�����̵�
	void level_up();//����
	void cal_max_hero_num() { max_hero_num = level + HasNatureForce; }//���ϳ������Ӣ���������ڵȼ���ӵ��װ������Ȼ֮�������1�˿�����
	void buy_exp();//������
	void weapon_on(Hero* hero, Weapon* weapon);//Ӣ��װ��װ��
	void weapon_off(Hero* hero);//Ӣ��ж��װ��
	bool buy_check(Hero* hero);//�ж��Ƿ��ܹ�����Ӣ��
	void buy_hero(Hero* hero);// ����Ӣ��
	void sell_hero(Hero* hero);//����Ӣ��
	void refreshshop();//ˢ���̵�
	void on_board(Hero* hero);//����սϯ�ϵ�Ӣ�����ϳ�
	void off_board(Hero* hero);//�����ϵ�Ӣ���Ƶ���սϯ��
	void syn_hero();//��3������Ӣ���Զ��ϳ�1������Ӣ��
	void syn_hero(Hero* hero);//��3������Ӣ���Զ��ϳ�1������Ӣ�ۣ����أ�
	void syn_weapon(Weapon* fir, Weapon* sec);//�ϳ�װ��
	bool islose() const { return hp <= 0; }//�ж��Ƿ������Ϸ
	int damage(Player winner, bool iswin);//����ÿС�ֵ��˺�
	bool operator>(const Player& other) {
		return hp > other.hp;
	}
	bool operator<(const Player& other) {
		return hp < other.hp;
	}
	bool operator=(const Player& other) {
		return hp = other.hp;
	}
};

#endif