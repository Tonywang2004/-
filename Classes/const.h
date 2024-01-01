#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "ApplyLittleHero.h"
#include<map>
#include<algorithm>
#include<utility>
#include<string>

USING_NS_CC;
const int cardtypes[4] = { 4,3,3,2 };//������1�ѿ���4�ѿ��ķֱ���4��3��3��2��
const int cardnums[4] = { 12,12,12,9 };//����4�ѿ�ÿ����9�ţ�����ÿ�ֿ���12��

//��������֡���ʦ��սʿ���̿͡���ħ����ʹ������
#define SHOOTER 0
#define MAGICIAN 1
#define SOLDIER 2
#define ASSASSIN 3
#define DEMON 4
#define ANGEL 5
#define GHOST 6
#define Demonsoldier 1
//����װ����ħ�ȣ��������ף������
#define WAND 1
#define SWORD 2
#define ARMOR 3
#define SPATULA 4
//�ϳ�װ����
#define TECHGUN 5 //�Ƽ�ǹ
#define HOURGLASS 6 //ɳ©
#define EXTRAMAGICIAN 7 //���ⷨʦ�
#define MALMORTIUS 8 //��ħ��
#define EXTRASHOOTER 9 //���������
#define EXTRASOLDIER 10 //����սʿ�
#define DEATHCAP 11 //��ñ
#define INFINITYEDGE 12 //�޾�֮��
#define MERCURYCLOAK 13 //ˮ������
#define NATUREFORCE 14 //��Ȼ֮������1�˿����ޣ�ֻ��ӵ��1����

const Vec2 storage_position[5] = { {0,0}, {50,50},{50,100},{50,150} ,{50,200} };
//�ȼ������
const int exp_level_up[9] = { 0,0,2,6,10,20,36,56,80 };
//exp_level_up[i]��ʾ��i-1������i����Ҫ�ľ���
//ÿ�غϽ��������Զ�+2���ʵ�һ�غϺ��������2��
const int MAX_LEVEL = 8;//��ߵȼ�
const int MAX_STORAGE_NUM = 4;//��սϯ�������������
#endif

