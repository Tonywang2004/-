#include"weapon.h"
//��һ��ΪС�����ڶ���Ϊ����������Ϊһ���µ�װ��������Ϊnullptr
Weapon* Weapon::check_combination(Weapon* fir,Weapon* sec)
{
	pair<int, int> key = { fir->No,sec->No };
	if (combination.find(key) != combination.end()) {
		int newkey = combination[key];
		Weapon* newweapon = new Weapon(newkey);
		return newweapon;
	}
	return nullptr;
}