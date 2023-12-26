#include "cocos2d.h"
#include "Hero.h"
#include "Bank.h"
#include "Weapon.h"
#include "Player.h"
#include "Const.h"
#include <vector>
#include <set>
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

void Player::switch_lock() {
	lock = 1 - lock;
}

void Player::level_up() {
	exp -= exp_level_up[level];
	if (level < MAX_LEVEL)
		level++;
	cal_max_hero_num();
}

void Player::buy_exp() {
	if (money >= 4) {
		money -= 4;
		exp += 2;
		if (exp >= exp_level_up[level] && level < MAX_LEVEL)
			level_up();
	}
}

void Player::weapon_on(Hero *hero, Weapon *weapon) {
	for (int i = 0; i < weapon_for_player.size(); i++) {
		if (weapon_for_player[i].click) {
			weapon_for_player.erase(weapon_for_player.begin() + i);
			break;
		}
	}
	hero->ad += weapon->ad;
	hero->def += weapon->def;
	hero->as += weapon->as;
	hero->hp_max += weapon->hp_max;
	hero->ch_rate += weapon->ch_rate;
	if (weapon->No == EXTRASHOOTER)
		hero->kind[SHOOTER]++;
	if (weapon->No == EXTRASOLDIER)
		hero->kind[SOLDIER]++;
	hero->weapon = Weapon(weapon->No);
}

void Player::weapon_off(Hero *hero) {
	hero->ad -= hero->weapon.ad;
	hero->def -= hero->weapon.def;
	hero->as -= hero->weapon.as;
	hero->hp_max -= hero->weapon.hp_max;
	hero->ch_rate -= hero->weapon.ch_rate;
	if (hero->weapon.No == EXTRASHOOTER)
		hero->kind[SHOOTER]--;
	if (hero->weapon.No == EXTRASOLDIER)
		hero->kind[SOLDIER]--;
	hero->weapon = NULL;
	weapon_for_player.push_back(hero->weapon);
}

bool Player::buy_check(Hero *hero) {
	//�жϵ�ǰ��Ǯ�Ƿ��㹻
	if (money < hero->price)
		return false;
	//����п�λ����Թ���
	if (hero_num < max_hero_num || storage_num < MAX_STORAGE_NUM)
		return true;
	//��û�п�λ�ҹ��������������кϳɣ���Ҳ���Թ���
	int arr[HERO_TYPES + 1] = { 0 };
	arr[hero->No]++;
	for (int i = 0; i < hero_on_board.size(); i++)
		arr[hero_on_board[i].No]++;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		arr[storage[i].No]++;
	for (int i = 1; i <= HERO_TYPES; i++) {
		if (arr[i] >= 3)
			return true;
	}
	return false;
}

//�ڵ��ô˺���֮ǰһ��Ҫ�ȵ���buy_check()�����ж��Ƿ��ܽ��й���
void Player::buy_hero(Hero *hero) {
	// ���ѹ���Ŀ��ƴ������б����Ƴ�
	for (int i = 0; i < shop_for_player.size(); i++) {
		if (shop_for_player[i].click) {
			shop_for_player.erase(shop_for_player.begin() + i);
			money -= shop_for_player[i].price;
			break;
		}
	}

	//�������������Ƿ��ܽ���Ӣ�ۺϳ�
	syn_hero(hero);//�˺����������Ӣ�۷��뱸սϯ/���أ��������Ƿ��ܽ���Ӣ�۵ĺϳ�
	syn_hero();//���ܻ�ϳ�����Ӣ��
}

void Player::sell_hero(Hero *hero) {
	weapon_off(hero);
	if (hero->is_on_board) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			if (hero_on_board[i].click) {
				hero_on_board.erase(hero_on_board.begin() + i);
				hero_num--;
			}
		}
	}
	else {
		for (int i = 1; i <= MAX_STORAGE_NUM; i++) {
			if (storage[i].click) {
				storage[i] = NULL;
				storage_num--;
			}
		}
	}
	//���߼�Ӣ�۲�ֳ�1��Ӣ�۷������ܿ��ƿ���
	for (int i = 1; i <= hero->level * 3; i++)
		bank.push_back(Hero(hero->No / pow(100, hero->level)));
	money += hero->price;
}

void Player::refreshshop() {
	//�Ƚ�����̵�����Ŀ��Ʒ����ܿ���
	bank.insert(bank.end(), shop_for_player.begin(), shop_for_player.end());
	shop_for_player.clear();

	//�̵�һ��ˢ��ֻ��4�ſ���
	random_shuffle(bank.begin(), bank.end());
	for (int i = 0; i < 4 && !bank.empty(); ++i) {
		shop_for_player.push_back(bank.back());
		bank.pop_back();
	}
}

void Player::on_board(Hero *hero) {
	storage[hero->seat] = NULL;
	storage_num--;
	hero_on_board.push_back(*hero);
	hero->is_on_board = true;
	hero_num++;
}

void Player::off_board(Hero* hero) {
	for (int i = 0; i < hero_on_board.size(); i++) {
		if(hero_on_board[i].click){
			hero_on_board.erase(hero_on_board.begin() + i);
			break;
		}
	}
	hero_num--;
	hero->is_on_board = false;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		if (storage[i] == NULL)
			storage[i] = *hero;
	storage_num++;
}

//���ڿ��ܻ�ϳ�����Ӣ�ۣ���ÿ�ε��øú���ʱ����Ҫ�������Σ��ڶ����޲�����
void Player::syn_hero() {
	bool is_on_board = false;//�����жϺϳɵ�Ӣ���ڳ��ϻ����ڱ�սϯ�������ǣ��������кϳɵ�Ӣ��������һ���ڳ��ϣ���ϳɵ�Ӣ���ڳ���
	int arr[HERO_TYPES + 1] = { 0 };
	for (int i = 0; i < hero_on_board.size(); i++)
		arr[hero_on_board[i].No]++;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		arr[storage[i].No]++;
	for (int i = 0; i <= HERO_TYPES; i++) {
		if (arr[i] >= 3) {
			for (int j = 0; j < hero_on_board.size(); j++) {
				if (hero_on_board[j].No == i) {
					is_on_board = true;
					weapon_off(&hero_on_board[j]);
					hero_on_board.erase(hero_on_board.begin() + j);
					hero_num--;
				}
			}
			for (int j = 1; j <= MAX_STORAGE_NUM; j++) {
				if (storage[j].No == i) {
					weapon_off(&storage[j]);
					storage[j] = NULL;
					storage_num--;
				}
			}
			if (is_on_board)
				hero_on_board.push_back(Hero(i * pow(100, hero_on_board[i].level)));
			else {
				for (int k = 1; k <= MAX_STORAGE_NUM; k++) {
					if (storage[k] == NULL)
						storage[k] = Hero(i * pow(100, hero_on_board[i].level));
				}
			}
		}
	}
}

//���ڿ��ܻ�ϳ�����Ӣ�ۣ���ÿ�ε��øú���ʱ����Ҫ�������Σ��ڶ����޲�����
void Player::syn_hero(Hero *hero) {
	//���Ƚ������Ӣ�۷��ڱ�սϯ
	if (storage_num < MAX_STORAGE_NUM) {
		for (int i = 1; i <= MAX_STORAGE_NUM; i++) {
			if (storage[i] == NULL)
				storage[i] = *hero;
		}
		hero->is_on_board = false;
		storage_num++;
	}
	else {
		hero_on_board.push_back(*hero);
		hero->is_on_board = true;
		hero_num++;
	}
	syn_hero();
}

void Player::syn_weapon(Weapon *fir, Weapon *sec) {
	int num1 = min(fir->No, sec->No), num2 = max(fir->No, sec->No);
	pair<int, int>key = { num1,num2 };
	if (WeaponCombination.find(key) != WeaponCombination.end()) {
		for (int i = 0; i < weapon_for_player.size(); i++) {
			if (weapon_for_player[i].click)
				weapon_for_player.erase(weapon_for_player.begin() + i);
		}
		int newkey = WeaponCombination[key];
		if (newkey == NATUREFORCE) {
			HasNatureForce = true;//��־ӵ��װ������Ȼ֮����
			cal_max_hero_num();
		}
		Weapon* syn = new Weapon(newkey);
		weapon_for_player.push_back(*syn);
	}
}

int Player::damage(Player winner, bool iswin) {
	if (iswin)
		return 0;
	return winner.hero_alive * 4 + winner.stage * 2; //���ÿ����Ϸ���˺��ɵз����Ӣ�������͵�ǰ�׶ξ���
}
