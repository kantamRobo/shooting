#include "DxLib.h"
#include "Include\Admin.h"
#include "Include/Maintask.h"
#include <iostream>
#include "Include/Define.h"
using namespace std;


int Process(char key[256])
{
	if (ScreenFlip() != 0)return false;//表画面と裏画面を入れ替える
	if (ProcessMessage() != 0)return false;//メッセージの自動処理
	if (ClearDrawScreen() != 0)return false;//描画している画面を消去する
	if (GetHitKeyStateAll(key) != 0)return false;//キーボードの入力をする

	return true;

	//falseならループから抜ける。


}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(true);//trueにするとウインドウを表示する
	SetGraphMode(SCREEN_HEIGHT_MAX, SCREEN_WIDTH_MAX, 16);//(横の長さ、縦の長さ、カラービット）
	DxLib_Init();//DxLibの初期化
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetWindowText("うじゃうじゃシューティング");//ウインドウタイトル
	
	
	

	
	
	unique_ptr<Maintask> maintask;
	
	try {
		maintask = make_unique<Maintask>();
	}
	catch (bad_alloc)
	{
		"maintaskのメモリ領域の確保に失敗しました";
	}
	while (Process(maintask->Getkey())) {//メインループ

		maintask->Update();
			
										 /*
		switch (status)
		{
		case STATUS::TITLE:
			DrawGraph(0, 0, bg1handle, 0);
			if (maintask->Getkey()[KEY_INPUT_Z] == 1) {
				unit_admin->InitGame();
				status = STATUS::GAME;
			}
			break;
		case STATUS::CONFIG:
			//更新する
			//
		case STATUS::GAME:
			/*MainTaskクラスを作る

			unit_admin->Check_Collision_BullettoCharacterObject();
			
			unit_admin->Update();
			unit_admin->Draw();
			unit_admin->DrawHitPoint();
			if (unit_admin->GetGameoverFlag()) {
				status = STATUS::RESULT;
			}
			if (unit_admin->GetGameClearFlag())
			{
				status = STATUS::CLEAR;
			}
			break;
		case STATUS::RESULT:
			DrawFormatString(50, 50, GetColor(100, 100, 100), "%d", unit_admin->Get_Score());
			break;
		case STATUS::CLEAR:
				DrawGraph(0, 0, bg2handle, 0);
				break;
		}
	*/
	}

	DxLib_End();

	return 0;
}