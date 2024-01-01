/*
Position is used to save a coordinate of the scene and the
state(whether there is a sprite or not) of the saved coordinate
*/


#pragma once
#include"cocos2d.h"
USING_NS_CC;
class myPosition
{
public:
	int x;//������
	int y;//������
	int state;//��ʾ��ǰλ���Ƿ�Ϊ��
	myPosition();//���캯�����޲���
	myPosition(int tx, int ty);//���캯������tx��ty��������
	void Setsprite();//���ñ���
	void Removesprite();//�Ƴ�����
	bool IsEmpty();//�ж��Ƿ�Ϊ��
	void operator=(myPosition p);//���ص��ں�
};

