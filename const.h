#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "HelloWorldScene.h"
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

//�ȼ������
const int exp_level_up[9] = { 0,0,2,6,10,20,36,56,80 };
//exp_level_up[i]��ʾ��i-1������i����Ҫ�ľ���
//ÿ�غϽ��������Զ�+2���ʵ�һ�غϺ��������2��

const int MAX_LEVEL = 8;//��ߵȼ�
const int MAX_STORAGE_NUM = 6;//��սϯ�������������
#endif

