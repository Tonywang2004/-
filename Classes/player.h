#ifndef PLAYER_H
#define PLAYER_H
#include "cocos2d.h"
#include"weapon.h"
using namespace std;
using namespace cocos2d;
class Card;
//����һ������࣬������ҵĽ�Ǯ�����飬�ȼ���Ӣ�������
class Player {
	friend class Hero;
	friend class Card;
	friend class Weapon;
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
	bool HasNatureForce = false;//��־�Ƿ�ӵ��װ������Ȼ֮������ӵ�����1�˿�����
public:
	vector<Hero*> storage;//����ϯ�����ڴ������Ѿ�����δ�ϳ���Ӣ��
	vector<Hero*> hero_on_board;//�ϳ���Ӣ��
	vector<Weapon*> weapon_for_player;//����ѻ����δ��Ӣ��װ�ϵ�װ��
	vector<Hero*>shop_for_player;//��ҵ��̵�
	void switch_lock();//����/�����̵�
	void level_up();//����
	void cal_max_hero_num() { max_hero_num = level + HasNatureForce; }//���ϳ������Ӣ���������ڵȼ���ӵ��װ������Ȼ֮�������1�˿�����
	void buy_exp();//������
	void buy_card(int index);// �����ƣ�indexΪ�̵���5�ſ��Ƶı��
	void sell_card(Card card);//��������
	void refreshshop();//ˢ���̵�
	void on_board(Card card);//����սϯ�ϵ�Ӣ�����ϳ�
	void off_board(Card card);//�����ϵ�Ӣ���Ƶ���սϯ��
	void syn_hero();//��3������Ӣ���Զ��ϳ�1������Ӣ��
	bool islose() const { return hp <= 0; }//�ж��Ƿ������Ϸ
	int damage(Player winner, bool iswin);//����ÿС�ֵ��˺�
	bool Player::isTouch(Touch* touch, Event* event);
};
#endif