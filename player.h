#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "HelloWorldScene.h"
#include "bank.h"
#include "weapon.h"
#include "const.h"
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
	int level = 0;//�ȼ�
	int max_hero_num = 0;//���ϳ���Ӣ���������
	int hero_num = 0;//����Ӣ������
	int storage_num = 0;//��սϯ��Ӣ������
	int kind[7] = { 0 };//����֡���ʦ��սʿ���̿͡���ħ����ʹ������
	bool lock;//���������̵�
	vector<Hero> storage;//����ϯ�����ڴ������Ѿ�����δ�ϳ���Ӣ��
	vector<Hero> hero_on_board;//�ϳ���Ӣ��
	vector<Weapon> weapon_for_player;//����ѻ����δ��Ӣ��װ�ϵ�װ��
	vector<Card>shop_for_player;//��ҵ��̵�
public:
	void switch_lock();//����/�����̵�
	void level_up();//����
	void cal_max_hero_num() { max_hero_num = level; }//���ϳ������Ӣ���������ڵȼ�
	void buy_exp();//������
	void buy_card(int index);// �����ƣ�indexΪ�̵���5�ſ��Ƶı��
	void sell_card(Card card);//��������
	void refreshshop();//ˢ���̵�
	void on_board(Card card);//����սϯ�ϵ�Ӣ�����ϳ�
	void off_board(Card card);//�����ϵ�Ӣ���Ƶ���սϯ��
	void syn_hero();//��3������Ӣ���Զ��ϳ�1������Ӣ��
	bool islose() const { return hp <= 0; }//�ж��Ƿ������Ϸ
	int damage(Player winner, bool iswin);//����ÿС�ֵ��˺�

};

//ССӢ��
class Role :public Sprite {
private:
	string image;
	Vec2 position;
public:
	Role(string s, int x = 0, int y = 0, int length = 40, int width = 40) :image(s), position(Vec2(x, y)) {
		auto role = Role::create(image, Rect(x, y, length, width));
		//Ĭ��λ��Ϊ(0,0)������Ĭ�ϳ���ֱ�Ϊ40��40
	}
	void move();
};

#endif
