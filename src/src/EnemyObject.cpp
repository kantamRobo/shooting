#include "Include\EnemyObject.h"
#include "DxLib.h"
#include "Include\Ammo.h"
#include "Include\Admin.h"
#include "Include\Define.h"
#include <math.h>


EnemyObject::EnemyObject(int m_unit_graphic_handle, int m_bullet_graphic_handle, UnitAdmin* m_Uadmin,EnemyType EType,Tag m_tag)
	:DestroyedEnemyNum(0)
{
	GraphicHandle = m_unit_graphic_handle;
	unit_admin = m_Uadmin;
	Type = EType;
	hitzone = HITDETECTIONZONE;
	//�G���ǂ�����true�ɂ���
	isEnemy = true;
	tag = m_tag;
	
	for (int i = 0; i < MAX_AMMO; i++)
	{
		ammo[i] = make_shared<Ammo>(m_bullet_graphic_handle,isEnemy);   
	}
	
}


EnemyObject::~EnemyObject()
{
		
}
//�G���o��������
void EnemyObject::Instantiate(double m_x, double m_y, double m_angle)
{
	position.x = m_x;
	position.y = m_y;

	

	Angle= m_angle;

	isActive = true;
	health = 2;
	
}

void EnemyObject::Update()
{
   
	if (GetisActive())
	{
		
		for (int i = 0; i < MAX_AMMO; i++) {
			ammo[i]->Update();
		}

		Move();
		Attack();
		Set_AngleBetweenEnemyandPlayer();
		
	}

	if (health < 0)
	{
		Death();
		
	}
}
void EnemyObject::Move()
{
	/*Move()*/
		//�ړ�
		//Air1�̏ꍇ�͓ːi���Ă���
	if (Type == EnemyType::Air1)
	{
		//�Q�l:�O�p�֐��̎g����#COS,SIN�֐�
		 //http://wiki.hosiken.jp/petc/?Mame%2F%BB%B0%B3%D1%B4%D8%BF%F4%A4%CE%BB%C8%A4%A4%CA%FD
		position.x += cos(Angle) * ENEMY_SPEED;
		position.y += sin(Angle) * ENEMY_SPEED;
	}

}

void EnemyObject::Attack()
{
	/*Attack()*/
	rapid++;
	rapid %= RAPID_RATE;
	if (rapid == 9) {
		for (int i = 0; i < MAX_AMMO; i++)
		{
			if (!ammo[i]->GetisActive())
			{
				if (distance < DISTANCE_RANGE)//�������ɓ�������
					ammo[i]->Shot(position.x, position.y, Angle);
				break;
			}
		}
	}
}

void EnemyObject::Set_AngleBetweenEnemyandPlayer()
{
	/*Set_Angle()*/
	Vector2D target_positon = unit_admin->GetClosetPosition(*this);
	distance = Vector2D::Distance(this->position, target_positon);
	if (target_positon != Vector2D(0, 0))
	{

		Angle = atan2(target_positon.y - this->position.y, target_positon.x - this->position.x);
	}
}
void EnemyObject::Death()
{
	unit_admin->DecreaseEnemyCount();
	
}