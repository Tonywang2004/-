#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "Weapon.h"
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

const int HERO_TYPES = 6;//Ӣ��������
const int cardnums[7] = { 0,12,12,12,12,9,9 };//3�ѿ�ÿ����9�ţ�����ÿ�ֿ���12��

//����Ӣ��
//1�ѿ�
const int _Soldier_ = 1;
const int _Shooter_ = 2;
//2�ѿ�
const int _Supersoldier_ = 3;
const int _Supershooter_ = 4;
//3�ѿ�
const int _Demonsoldier_ = 5;
const int _Demonshooter_ = 6;

//�����սʿ�����֡���ħ
const int SOLDIER = 1;
const int SHOOTER = 2;
const int DEMON = 3;

//�ȼ������
const int exp_level_up[5] = { 0,2,6,15,36};
//exp_level_up[i]��ʾ��i-1������i����Ҫ�ľ���
//ÿ�غϽ��������Զ�+2���ʵ�һ�غϺ��������2��

const int MAX_LEVEL = 5;//��ߵȼ�
const int MAX_STORAGE_NUM = 4;//��սϯ�������������

//װ������
const int WEAPON_TYPES = 9;
//����װ�����������ף������
const int BOW = 1;
const int ARMOR = 2;
const int SPATULA = 3;
//�ϳ�װ����
const int HURRICANE = 4; //¬���ȵ�쫷�
const int THORNMAIL = 5; //����
const int NATUREFORCE = 6; //��Ȼ֮������1�˿����ޣ�ֻ��ӵ��1����
const int SHIELDBOW = 7; //�ܹ�
const int EXTRASHOOTER = 8; //���������
const int EXTRASOLDIER = 9; //����սʿ�

//װ����������
const int weapon_atn[10] = { 0,10,0,0,20,0,0,10,10,0 };
const int weapon_def[10] = { 0,0,10,0,0,20,0,10,0,10 };
const float weapon_as[10] = { 0,0.1,0,0,0.2,0,0,0.1,0.1,0 };


//ǿ������ Rune��ǿ���˺��������˺������⾭�飬�����Ǯ�������ظ�
const int RUNE_TYPES = 5;
//ǿ���˺���ÿ�ζԾֻ�ʤ������˺�+5
const int MOREDAMAGE = 1;
//�����˺���ÿ�ζԾ�ʧ�ܺ��յ��˺�-3
const int LESSDAMAGE = 2;
//���⾭�飺ÿ�ζԾֽ����������4���飨���ܳ����ȼ����ޣ�
const int EXTRAEXP = 3;
//�����Ǯ��ÿ�ζԾֽ����������2��Ǯ
const int EXTRAMONEY = 4;
//�����ظ��������ظ�20������ֵ���ɳ�������ֵ���ޣ�
const int RECOVERY = 5;
#endif
