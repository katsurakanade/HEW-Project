#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "GameData.h"
#include "scene.h"
#include "gameprogress.h"
#include "BatonTouch.h"
#include "DxLib.h"
#include "Live2D.h"
#include "EffectGame.h"

GameObject Baton[10];
GameProgress Progress;

//ゲームスタート処理(SL+SR+Lでスタート)=====================================
void Init_GameStart()
{
	// 「SL+SR+L」を押せ！画像
	Baton[6].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAMESTART]);
	Baton[6].Object.Pos.x = 740.0f;
	Baton[6].Object.Pos.y = 360.0f;
	Baton[6].Object.Scale.x = 0.7f;
	Baton[6].Object.Scale.y = 0.7f;
}




//バトンタッチ処理====================================================
void Init_BatonTouch()
{
	//StateBaton = false;


	// 「SL+SR+L+振れ！」画像
	Baton[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_CHARENGE]);
	Baton[0].Object.Pos.x = 740.0f;
	Baton[0].Object.Pos.y = 360.0f;
	Baton[0].Object.Scale.x = 0.7f;
	Baton[0].Object.Scale.y = 0.7f;


	// 「バトンタッチ中...」画像
	Baton[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG]);
	Baton[1].Object.Pos.x = 1920.0f;
	Baton[1].Object.Pos.y = 360.0f;
	Baton[1].Object.Scale.x = 1.0f;

	///-----------------------↓未実装↓--------------------------- ///

	// 背景アルファ値100%
	Baton[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_5]);
	Baton[2].Object.Pos.x = 640.0f;
	Baton[2].Object.Pos.y = 360.0f;
	Baton[2].Object.Scale.x = 1.0f;

	// 背景アルファ値80%
	Baton[3].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_4]);
	Baton[3].Object.Pos.x = 640.0f;
	Baton[3].Object.Pos.y = 360.0f;
	Baton[3].Object.Scale.x = 1.0f;

	// 背景アルファ値60%
	Baton[4].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_3]);
	Baton[4].Object.Pos.x = 640.0f;
	Baton[4].Object.Pos.y = 360.0f;
	Baton[4].Object.Scale.x = 1.0f;

	// 背景アルファ値40%
	Baton[5].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_2]);
	Baton[5].Object.Pos.x = 640.0f;
	Baton[5].Object.Pos.y = 360.0f;
	Baton[5].Object.Scale.x = 1.0f;

	// 背景アルファ値20%
	Baton[7].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_1]);
	Baton[7].Object.Pos.x = 640.0f;
	Baton[7].Object.Pos.y = 360.0f;
	Baton[7].Object.Scale.x = 1.0f;



}


BatonTouch::BatonTouch()
{
}
BatonTouch::~BatonTouch()
{
}
void BatonTouch::Init()
{
}


void BatonTouch::Uninit()
{

}

// バトンタッチ更新処理(BTState:ゲームスタート処理か否か)
void BatonTouch::Update(int BTState)
{
	Timer += SECONDS;     // 時間計測


	// ゲームスタート処理(ゲーム初回処理)==================================
	if (BTState == BT_GameStart)
	{
		// 「SL+SR+L」を押したらゲームステートに遷移
		if (keyboard.IsTrigger(DIK_RETURN) || joycon[0].GetOldState() == JOYCON_L + JOYCON_SL_LEFT + JOYCON_SR_LEFT) {               ///←修正箇所
			GameState_Change(GAME_STATE_GAME);     //ゲームステートに遷移
		}
	}
	// =======================================================


	// バトンタッチ処理(背景右から差し込む)==================================
	else if (BTState == BT_BatonTouch)
	{

		static bool DoOnce = true;

		if (Timer <= 3.0f)
		{
			// 3秒以内に「SL+SR+L+振る」をしたら1000P獲得
			if (!CharengeFlag) {  ///←修正箇所
				if (keyboard.IsTrigger(DIK_RETURN)){
					gamedata.AddActionPoint(1000.0);
						CharengeFlag = true;
						call_E_game_Baton1000P();     // 1000Pアニメーション
				}
				else if (joycon[0].GetOldState() == JOYCON_L + JOYCON_SL_LEFT + JOYCON_SR_LEFT && joycon[0].GetGyro_Y() >= 200) {
					gamedata.AddActionPoint(1000.0);
					CharengeFlag = true;
					call_E_game_Baton1000P();     // 1000Pアニメーション
				}
			}
		}
		else
		{     // 3秒経過したらバトンタッチ処理

			if (DoOnce) { PlaySoundFile("asset/sound/BGM/title.mp3", DX_PLAYTYPE_BACK); DoOnce = false; }

			// 右から背景を差し込む
			if (Baton[1].Object.Pos.x > 640.0f)
			{
				Baton[1].Object.Pos.x -= 50.0f;
			}
			else
			{
				Baton[1].Object.Pos.x = 640.0f;
				Baton[1].Object.Pos.y = 360.0f;
			}



			// 「20秒経過」したらゲームステートに遷移
			if ((Timer - 3.0f) >= 20.0f)
			{     // 次の区間スタート
				StopSoundFile();     // BGMを止める
				DoOnce = true;     // DoOnceリセット
				GameState_Change(GAME_STATE_GAME);     //ゲームステートに遷移
			}

		}



	}
	// =======================================================

}
void BatonTouch::Draw(int BTState)
{

	// ゲームスタート処理
	if (BTState == BT_GameStart)
	{

		// 「SL+SR+L」を押せ！　表示
		Baton[6].Draw();

	}

	// バトンタッチ処理
	else if (BTState == BT_BatonTouch)
	{

		if (Timer <= 3.0f)
		{
			// 「SL+SR+L+振る」画像表示
			Baton[0].Draw();
		}
		else
		{
			// 「20秒経過」したらゲームステートに遷移
			if ((Timer - 3.0f) >= 15.0f && (Timer - 3.0f) < 16.0f)
			{     // 残り５秒
				Baton[2].Draw();
			}
			else if ((Timer - 3.0f) >= 16.0f && (Timer - 3.0f) < 17.0f)
			{     // 残り４秒
				Baton[3].Draw();
			}
			else if ((Timer - 3.0f) >= 17.0f && (Timer - 3.0f) < 18.0f)
			{     // 残り３秒
				Baton[4].Draw();
			}
			else if ((Timer - 3.0f) >= 18.0f && (Timer - 3.0f) < 19.0f)
			{     // 残り２秒
				Baton[5].Draw();
			}
			else if ((Timer - 3.0f) >= 19.0f && (Timer - 3.0f) <= 21.0f)
			{     // 残り１秒
				Baton[7].Draw();
			}
			else
			{
				// 背景表示
				Baton[1].Draw();
			}

		}

	}

}

bool BatonTouch::GetBatonState()
{
	return StateBaton;
}