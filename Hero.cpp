#include<iostream>
#include "HelloWorldScene.h"
#include "Hero.h"
using namespace std;
using namespace cocos2d;
extern Player my_hero;
extern Player enemy_hero;
void Ghostride::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//����������
	updateposition();
	ProgressTimer* mp = nullptr;
	mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	mp->setType(ProgressTimer::Type::BAR);
	mp->setScaleX(0.25); // �����СΪԭ����һ��
	mp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
	mp->setMidpoint(Vec2(hero_position.x, hero_position.y - 20)); // ���������λ��
	mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
	mp->setPosition(hero_position.x, hero_position.y - 20); // ������λ��
	mp->setPercentage(mp_now * 100 / mp_max);
	the->addChild(mp); // ����������ӵ�������
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	Vec2 toposition = target_position;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		if (newMpPercentage >= 100.0f) {
			// MP�ﵽ100%������MP������HP
			newMpPercentage = 0.0f;
			// ����HP�ĵ�ǰֵ��20%
			skill(target, the, fromposition, toposition);
			// ����HP������
			float newHpPercentage = hp->getPercentage() - 10;
			hp->setPercentage(newHpPercentage);
		}
		mp->setPercentage(newMpPercentage);
		}, 0.5f, scheduleKey);
}
void Ghostride::skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition) {
	auto sprite = Sprite::create("ghostride.png");//����һ��ǿ�������ľ���ͼ��
	sprite->setContentSize(Size(100, 100));
	sprite->setPosition(fromposition);
	the->addChild(sprite);
	auto moveto = MoveTo::create(0.1f, toposition);//�ƶ���Ŀ��λ��
	Hide* hideAction = Hide::create();
	Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
	sprite->runAction(sequence);
}
void Hero::updateposition()
{
	hero_position = mine->getPosition();
}
void Ghostride::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//�Եз�Ϊ����չ��
	ImageSwitcher imageswitch("ghostride.png", "player.png", this);
	get_target(this, enemy_hero);
	ProgressTimer* hp = nullptr;
	hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	hp->setType(ProgressTimer::Type::BAR);
	hp->setScaleX(0.25); // �����СΪԭ����һ��
	hp->setScaleY(0.5); // �߶ȷŴ�Ϊԭ��������
	hp->setPercentage(100);
	hp->setMidpoint(Vec2(target_position.x, target_position.y - 30)); // ���������λ��
	hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // ����������
	hp->setPosition(target_position.x, target_position.y - 30); // ������λ��
	the->addChild(hp);
	string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	float hp_maxmax = hp_max;
	float internal = as;
	float danmage = atn - enemy->def + matk - enemy->mr;
	the->schedule([=](float dt) {
		float hp_nownow = hp->getPercentage() - danmage;
		if (hp_nownow < 0)
			hp_nownow = 0;
		// ����HP������
		float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
		hp->setPercentage(newHpPercentage);
		}, internal, scheduleKey);
	skill_add(the, enemy_hero, hp);
}
void Hero::get_target(Hero* hero, Player enemy)
{
	double minDistance = 99999999;
	int index = 0;
	//��ȡ���������Ӣ��
	if (enemy.hero_for_player.size() != 0) {
		for (int i = 0; i < enemy.hero_for_player.size(); i++)
		{
			double delta_position_square = (enemy.hero_for_player[i]->mine->getPosition().x - hero->mine->getPosition().x) * (enemy.hero_for_player[i]->mine->getPosition().x - hero->mine->getPosition().x) + (enemy.hero_for_player[i]->mine->getPosition().y - hero->mine->getPosition().y) * (enemy.hero_for_player[i]->mine->getPosition().y - hero->mine->getPosition().y);
			if (minDistance > delta_position_square) {
				minDistance = delta_position_square;
				index = i;
			}
		}
		//Ŀ��仯
		target = enemy.hero_for_player[index];
		target_position = target->mine->getPosition();
		target_distance = sqrt(minDistance);
	}
	else
		target = nullptr;
}
