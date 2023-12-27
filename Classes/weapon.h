#ifndef _WEAPON_H_
#define _WEAPON_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "player.h"
#include "const.h"
USING_NS_CC;
//װ���ϳ�·��
class Weapon {
	friend class Player;
	friend class Role;
	friend class Hero;
private:
	int ad = 0;//attack damage������
	int ap = 0;//ability power��ǿ
	int def = 0;//���������
	int mr = 0;//magic resistance ħ��
	int hp_max = 0;//�������ֵ
	int mp_per_second = 0;//ÿ���õ�����
	float as = 0;//attack speed ����
	float ch_rate = 0;//critical hit rate������
	float ch_ma = 0;//critical hit magnification �����˺�����
	int No;
	std::map<std::pair<int, int>, int> combination = {
	{{WAND,SWORD},TECHGUN},{{WAND,ARMOR},HOURGLASS},{{WAND,SPATULA},EXTRAMAGICIAN},{{SWORD,ARMOR},MALMORTIUS},{{SWORD,SPATULA},EXTRASHOOTER},
	{{ARMOR,SPATULA},EXTRASOLDIER},{{WAND,WAND},DEATHCAP},{{SWORD,SWORD},INFINITYEDGE},{{ARMOR,ARMOR},MERCURYCLOAK},{{SPATULA,SPATULA},NATUREFORCE}
	};
public:
	Weapon(int number) {
		//weapon = Weapon::create(image[number]);
		//ad = AD[number];
		//ap = AP[number];
		//def = DEF[number];
		//mr = MR[number];
		//hp_max = HP_MAX[number];
		//mp_per_second = MP_PER_SECOND[number];
		//as = AS[number];
		//ch_rate = CH_RATE[number];
		//ch_ma = CH_MA[number];
	}
	Sprite* weapon;
	Weapon* check_combination(Weapon* fir, Weapon* sec);
};
#endif
