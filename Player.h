#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "Bank.h"
#include "Weapon.h"
#include "Const.h"
#include <vector>
USING_NS_CC;
using namespace std;

//����һ������࣬������ҵĽ�Ǯ�����飬�ȼ���Ӣ�������
class Player {
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
	int kind[4] = { 0 };//����֡�սʿ����ħ
	bool lock = false;//���������̵�
	Hero storage[MAX_STORAGE_NUM + 1];//����ϯ�����ڴ������Ѿ�����δ�ϳ���Ӣ��
	vector<Hero> hero_on_board;//�ϳ���Ӣ��
	vector<Weapon> weapon_for_player;//����ѻ����δ��Ӣ��װ�ϵ�װ��
	vector<Hero> shop_for_player;//��ҵ��̵�
	bool HasNatureForce = false;//��־�Ƿ�ӵ��װ������Ȼ֮������ӵ�����1�˿�����
public:
	Player(){}//���캯��
	void switch_lock();//����/�����̵�
	void level_up();//����
	void cal_max_hero_num() { max_hero_num = level + HasNatureForce; }//���ϳ������Ӣ���������ڵȼ���ӵ��װ������Ȼ֮�������1�˿�����
	void buy_exp();//������
	void weapon_on(Hero *hero, Weapon *weapon);//Ӣ��װ��װ��
	void weapon_off(Hero *hero);//Ӣ��ж��װ��
	bool buy_check(Hero *hero);//�ж��Ƿ��ܹ�����Ӣ��
	void buy_hero(Hero *hero);// ����Ӣ��
	void sell_hero(Hero *hero);//����Ӣ��
	void refreshshop();//ˢ���̵�
	void on_board(Hero *hero);//����սϯ�ϵ�Ӣ�����ϳ�
	void off_board(Hero *hero);//�����ϵ�Ӣ���Ƶ���սϯ��
	void syn_hero();//��3������Ӣ���Զ��ϳ�1������Ӣ��
	void syn_hero(Hero *hero);//��3������Ӣ���Զ��ϳ�1������Ӣ�ۣ����أ�
	void syn_weapon(Weapon *fir, Weapon *sec);//�ϳ�װ��
	bool islose() const { return hp <= 0; }//�ж��Ƿ������Ϸ
	int damage(Player winner, bool iswin);//����ÿС�ֵ��˺�
};

#endif
