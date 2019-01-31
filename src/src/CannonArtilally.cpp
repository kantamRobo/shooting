#include "include/CannonArtilally.h"
#include "Include/Vector2D.h"
#include "Include/Admin.h"
#include "Include/Define.h"
#include "Include/Ammo.h"
#include <iostream>
#include "DxLib.h"
CannonArtilally::CannonArtilally(int m_ghandle, int m_bullet_graphic_handle,bool m_isEnemy)
{
	ThereisEnemy_Hit = false;
	ammo_rapid = 0;
	//敵を取得する
	GraphicHandle = m_ghandle;
	isEnemy = m_isEnemy;
	for (int i = 0; i < MAX_AMMO; i++)
	{
		try {
			ammo[i] = make_unique<Ammo>(m_bullet_graphic_handle, !isEnemy);
		}
		catch (const std::bad_alloc& error)
		{
			std::cout << "メモリの確保に失敗しました" << error.what() << '\n';
		}
	}
}


CannonArtilally::~CannonArtilally()
{
}

void CannonArtilally::IncreaseAmmo_rapid()
{
	ammo_rapid++;
}

void CannonArtilally::DevideAmmo_rapid(int rate)
{
	ammo_rapid %= rate;
}
void CannonArtilally::Instantiate(double m_Angle,double m_x,double m_y)
{
	Angle = m_Angle;
	position.x = m_x;
	position.y = m_y;

	isActive = true;
}

void CannonArtilally::Update()
{
	for (int i = 0; i < MAX_AMMO; i++)
	{
		ammo[i]->Update();
	}

	//弾に当たった敵がいないなら(ThereisEnemyHitがfalse）Vector2D(0,0)を返す
	Vector2D target_position = TargetPos;

	if (target_position != Vector2D(0, 0))
	{
		Angle =atan2(target_position.x,target_position.y);
	}

	IncreaseAmmo_rapid();
	DevideAmmo_rapid(RAPID_RATE);




	if (GetAmmo_rapid() == 9)
	{
		for (int i = 0; i < MAX_AMMO; i++)
		{
			if (!ammo[i]->GetisActive())
			{
				if (target_position != Vector2D(0, 0)) {
					ammo[i]->Shot(position.x, position.y, Angle);

					break;
				}
			}
		}
	}
}

void CannonArtilally::DrawObject()
{
	if (isActive)
	{
		DrawRotaGraph(static_cast<int>(position.x), static_cast<int> (position.y), 1.0, Angle + PI / 2, GraphicHandle, static_cast<int>(1));
	}

	for (int i = 0; i < MAX_AMMO; i++)
	{
		ammo[i]->DrawObject();
	}
}

