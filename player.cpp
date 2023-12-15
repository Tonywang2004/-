#include "cocos2d.h"
#include "hero.h"
#include "bank.h"
#include "weapon.h"
#include "player.h"
#include <vector>
#include <set>
USING_NS_CC;
using namespace std;

void Player::switch_lock() {
	lock = 1 - lock;
}

void Player::level_up() {
	exp -= exp_level_up[level];
	if (level < MAX_LEVEL)
		level++;
}

void Player::buy_exp() {
	if (money >= 4) {
		money -= 4;
		exp += 4;
		if (exp >= exp_level_up[level] && level < MAX_LEVEL)
			level_up();
	}
}

void Player::buy_card(int index) {
	if (index >= 0 && index < shop_for_player.size()) {
		// ���ѹ���Ŀ��ƴ������б����Ƴ�
		shop_for_player.erase(shop_for_player.begin() + index);
		money -= shop_for_player[index].price;
	}
}

void Player::sell_card(Card card) {
	
}

void Player::refreshshop() {
	//�Ƚ�����̵�����Ŀ��Ʒ����ܿ���
	bank.insert(bank.end(), shop_for_player.begin(), shop_for_player.end());
	shop_for_player.clear();

	//�̵�һ��ˢ��ֻ��5�ſ���
	random_shuffle(bank.begin(), bank.end());
	for (int i = 0; i < 5 && !bank.empty(); ++i) {
		shop_for_player.push_back(bank.back());
		bank.pop_back();
	}
}

void Player::syn_hero() {
	multiset<int>myset;
	for (int i = 0; i < hero_on_board.size(); ++i)
		myset.insert(hero_on_board[i].No);
	for (int i = 0; i < storage.size(); ++i)
		myset.insert(storage[i].No);
	for (const auto& num : myset) {
		if (myset.count(num) >= 3) {

		}
	}
}

int Player::damage(Player winner, bool iswin) {
	if (iswin)
		return 0;
	return winner.hero_num * 2 + winner.stage;//���ÿ����Ϸ���˺��ɵз����Ӣ�������͵�ǰ�׶ξ���
}

void Role::move() {
	auto listener = EventListenerMouse::create();

}