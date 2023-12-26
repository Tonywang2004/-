#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "Weapon.h"
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

const int HERO_TYPES = 6;//Ӣ��������
const int cardtypes[3] = { 2,2,2 };//������1�ѿ���3�ѿ��ķֱ���2��2��2��
const int cardnums[3] = { 12,12,9 };//����3�ѿ�ÿ����9�ţ�����ÿ�ֿ���12��

//��������֡�սʿ����ħ
#define SHOOTER 1
#define SOLDIER 2
#define DEMON 3

//�ȼ������
const int exp_level_up[5] = { 0,2,6,15,36};
//exp_level_up[i]��ʾ��i-1������i����Ҫ�ľ���
//ÿ�غϽ��������Զ�+2���ʵ�һ�غϺ��������2��

const int MAX_LEVEL = 5;//��ߵȼ�
const int MAX_STORAGE_NUM = 4;//��սϯ�������������

//����װ�����������ף������
#define BOW 1
#define ARMOR 2
#define SPATULA 3
//�ϳ�װ����
#define HURRICANE 4 //¬���ȵ�쫷�
#define THORNMAIL 5 //����
#define NATUREFORCE 6 //��Ȼ֮������1�˿����ޣ�ֻ��ӵ��1����
#define SHIELDBOW 7 //�ܹ�
#define EXTRASHOOTER 8 //���������
#define EXTRASOLDIER 9 //����սʿ�

//װ����������
const int weapon_ad[10] = { 0,10,0,0,20,0,0,10,10,0 };
const int weapon_def[10] = { 0,0,10,0,0,20,0,10,0,10 };
const float weapon_as[10] = { 0,0.1,0,0,0.2,0,0,0.1,0.1,0 };

//װ���ϳ�·��
map<pair<int, int>, int> WeaponCombination = {
	{{BOW,BOW},HURRICANE},{{ARMOR,ARMOR},THORNMAIL},{{SPATULA,SPATULA},NATUREFORCE},{{BOW,ARMOR},SHIELDBOW},{{BOW,SPATULA},EXTRASHOOTER},{{ARMOR,SPATULA},EXTRASOLDIER}
};

//��սϯ��λ��
Vec2 storage_position[MAX_STORAGE_NUM + 1];
#endif

