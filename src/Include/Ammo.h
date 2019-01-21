#pragma once
#include "GameObject.h"
class CharacterObject;
class Ammo:public GameObject
{
private:
	int damage;

public:
	//Ammo�I�u�W�F�N�g�ɃO���t�B�b�N�A�����蔻��A�U���́A�e�𔭎˂����@�̂��G������������
	Ammo(int,bool);
	void Shot(int, int, double);
	void Update();
	int GetDamage() { return damage; }

	//�e�����������I�u�W�F�N�g��Ԃ�
	CharacterObject* ReturnHitObject();
	void DestroyAmmo();
};
