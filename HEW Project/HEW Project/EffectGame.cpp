#include "EffectGame.h"
#include "Effect.h"
#include <vector>
#include "Live2D.h"
#include "ActionSlot.h"
#include "Tutorial.h"

static EffectGame *EG;
static std::vector<EffectGame*> EGStorage;     // EffectGameをnewした時のポインタ格納先
int EffectGame::MaxEffectNum = 0;     // メモリを取得したエフェクトの数

// EffectGameManager------------------------------------------------VV
void EGManager::Init()
{
}
void EGManager::Uninit()
{
}
void EGManager::Update()
{
	bool flag = false;     // deleteでズレが出た時のフラグ

	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Update();     //各エフェクトの更新処理
		if (EGStorage[i]->DeleteFlag)
		{
			// アニメーションが終わったものを削除
			EffectGame *wark = EGStorage[i];     // 消したいアニメーションのアドレス保存

			EG->MaxEffectNum--;
			EGStorage.erase(EGStorage.begin() + EGStorage[i]->MyEffectNum);
			delete wark;     // メモリ削除
			flag = true;
		}
		if (flag && i < EGStorage[i]->MaxEffectNum)
		{
			EGStorage[i]->MyEffectNum--;
		}
		
	}
}
void EGManager::Draw()
{
	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Draw();
	}
}
// EffectGameManager------------------------------------------------AA

// EffectManager------------------------------------------------------VV

EffectGame::EffectGame(void (EffectGame::*fp_CallFunc)())
{
	// エフェクト確保
	for (int i = 0; i < MaxParticleNum; i++)
	{
		eft[i] = new Effect(this);
	}
	MyEffectNum = MaxEffectNum;
	MaxEffectNum++;
	// 自分のポインタ格納
	EGStorage.push_back(this);
	// 関数ポインタを格納
	fpCallFunc = fp_CallFunc;
}
EffectGame::~EffectGame()
{
	for (int i = 0; i < MaxParticleNum; i++)
	{
		eft[i]->obj.Destroy();    // パーティクル画像のメモリ解放
	}
	delete[] *eft;     // パーティクルのメモリ解放

}
void EffectGame::Init()
{
}
void EffectGame::Uninit()
{
}
void EffectGame::Update()
{
	(this->*fpCallFunc)();     // このインスタンスで呼びたい関数を呼ぶ(関数ポインタ)
}
void EffectGame::Draw()
{
	for (int i = 0; i < MaxAryNum; i++)
	{
		if (eft[i]->IsDraw)
		{
			eft[i]->obj.Draw();
		}
	}
}
void EffectGame::E_end()
{
	int SNCnt = 0;     // SleepNowの数カウント
	for (int i = 0; i < MaxAryNum; i++)     // IUMANを使う
	{
		if (eft[i]->lastSleepFlag)
		{
			SNCnt++;
		}
	}
	if (SNCnt == MaxAryNum)     //アニメーション終了
	{
		DeleteFlag = true;     // デリートフラグを立てる
	}
}
// EffectManager------------------------------------------------------AA






//===========================================================================================================
// アニメーションさせたいエフェクトをアニメーションさせたい順に並べる //
// 使うエフェクトの要素数は全てthis->eft.[0]から
// 名前は「E_シーン名(半角小文字のみ)_エフェクト名」     (例えばGameシーンのアクション成功エフェクトなら... void E_game_ActionSuccess() )


////////////////////////////////////////////////////// サンプルプログラム //////////////////////////////////////////////////////
void EffectGame::E_game_Sample()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);     // エフェクトパーティクル[0]のテクスチャロード
		eft[0]->obj.Object.Pos.x = 600.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[0]->obj.Object.Pos.y = 350.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[1]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_A]);     // エフェクトパーティクル[1]のテクスチャロード
		eft[1]->obj.Object.Pos.x = 800.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[1]->obj.Object.Pos.y = 250.0f;     // エフェクトパーティクル[0]の初期X座標


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////

	// 1個目のアニメーション
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Move(3.0f, 100.0f, 200.0f);
	eft[0]->Sleep(2.000f);
	eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	eft[1]->Sleep(2.0);

	// 2個目のアニメーション
	eft[0]->Zoom(2.0001f, 0.5f);
	eft[0]->Sleep(2.0001f);
	eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	eft[1]->Sleep(3.0);
	eft[1]->LastSleep(0.0001f);

	// 3個目のアニメーション
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	eft[0]->Sleep(5.0f);
	eft[0]->LastSleep(0.0001f);
	
	

	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_Sample()
{
	new EffectGame(&EffectGame::E_game_Sample);
}
////////////////////////////////////////////////////// サンプルプログラム //////////////////////////////////////////////////////



////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// タイトル(title) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////
void EffectGame::E_tutorial_AAA()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////

		eft[0]->obj.LoadTexture(TextureDict["gaze"]);     // エフェクトパーティクル[0]のテクスチャロード
		eft[0]->obj.Object.Pos.x = 870.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[0]->obj.Object.Pos.y = 250.0f;     // エフェクトパーティクル[0]の初期Y座標
		eft[0]->obj.Object.Scale.x = 3.95f;
		eft[0]->obj.Object.Scale.y = 1.0f;

		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////

		// 1個目のアニメーション
	eft[0]->Zoom(0.3f, 0.2f);
	eft[0]->Sleep(0.300f);
	eft[0]->Zoom(0.3f, -0.2f);
	eft[0]->Sleep(0.301f);

	eft[0]->LastSleep(0.0001f);


	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_tutorial_AAA()
{
	new EffectGame(&EffectGame::E_tutorial_AAA);
}

void EffectGame::E_tutorial_up()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////

		eft[0]->obj.LoadTexture(TextureDict["up_arrow"]);     // エフェクトパーティクル[0]のテクスチャロード

		eft[0]->obj.Object.Pos.x = 500.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[0]->obj.Object.Pos.y = 550.0f;   // エフェクトパーティクル[0]の初期Y座標

		//eft[0]->obj.Object.Pos.x = (GetActionSlot()->Pos.x + 0.0f);     // エフェクトパーティクル[0]の初期X座標
		//eft[0]->obj.Object.Pos.y = (GetActionSlot()->Pos.y + 0.0f);     // エフェクトパーティクル[0]の初期Y座標

		eft[0]->obj.Object.Scale.x = 0.8f;
		eft[0]->obj.Object.Scale.y = 0.8f;


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////

		// 1個目のアニメーション
	eft[0]->Curve(true, 2.0, 0.5, 10, -100);
	eft[0]->Sleep(0.50f);
	//eft[0]->Zoom(0.3f, -0.2f);
	//eft[0]->Sleep(0.301f);


	eft[0]->LastSleep(0.0001f);


	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_tutorial_up()
{
	new EffectGame(&EffectGame::E_tutorial_up);
}

////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////

// エフェクト関数:アクション成功
void EffectGame::E_game_ActionSucsess()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////

		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_A]);     // エフェクトパーティクル[0]のテクスチャロード
		eft[0]->obj.Object.Pos.x = 600.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[0]->obj.Object.Pos.y = 350.0f;     // エフェクトパーティクル[0]の初期Y座標
		
		eft[1]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);     // エフェクトパーティクル[1]のテクスチャロード
		eft[1]->obj.Object.Pos.x = 800.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[1]->obj.Object.Pos.y = 250.0f;     // エフェクトパーティクル[0]の初期X座標

		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////


	// 1個目のアニメーション
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Sleep(4.0f);
	eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	eft[1]->Sleep(2.0);

	// 2個目のアニメーション
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Sleep(2.0001);
	eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	eft[1]->Sleep(3.0);
	eft[1]->LastSleep(0.0001f);

	// 3個目のアニメーション
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	eft[0]->Sleep(5.0f);
	eft[0]->LastSleep(0.0001f);


	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_ActionSucsess()
{
	new EffectGame(&EffectGame::E_game_ActionSucsess);
}

//=======================================================================================================================
//=======================================================================================================================
void EffectGame::E_game_GreatEffect()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[2]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[2]のテクスチャロード

		eft[2]->obj.Object.Scale.x = 0.1f;
		eft[2]->obj.Object.Scale.y = 0.1f;

		eft[2]->obj.Object.Pos.x = 500.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[2]->obj.Object.Pos.y = 360.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[3]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[3]のテクスチャロード

		eft[3]->obj.Object.Scale.x = 0.1f;
		eft[3]->obj.Object.Scale.y = 0.1f;

		eft[3]->obj.Object.Pos.x = 500.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[3]->obj.Object.Pos.y = 420.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[4]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[4]のテクスチャロード

		eft[4]->obj.Object.Scale.x = 0.1f;
		eft[4]->obj.Object.Scale.y = 0.1f;

		eft[4]->obj.Object.Pos.x = 350.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[4]->obj.Object.Pos.y = 360.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[5]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[5]のテクスチャロード

		eft[5]->obj.Object.Scale.x = 0.1f;
		eft[5]->obj.Object.Scale.y = 0.1f;

		eft[5]->obj.Object.Pos.x = 350.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[5]->obj.Object.Pos.y = 420.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[10]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[5]のテクスチャロード

		eft[10]->obj.Object.Scale.x = 0.1f;
		eft[10]->obj.Object.Scale.y = 0.1f;

		eft[10]->obj.Object.Pos.x = 420.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[10]->obj.Object.Pos.y = 320.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[11]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // エフェクトパーティクル[5]のテクスチャロード

		eft[11]->obj.Object.Scale.x = 0.1f;
		eft[11]->obj.Object.Scale.y = 0.1f;

		eft[11]->obj.Object.Pos.x = 420.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[11]->obj.Object.Pos.y = 450.0f;     // エフェクトパーティクル[0]の初期Y座標



		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////
	// 1個目のアニメーション

	eft[2]->Move(0.5, 100, -100);
	eft[2]->Sleep(0.50001);
	eft[2]->LastSleep(0.0001f);

	eft[3]->Move(0.5, 100, 100);
	eft[3]->Sleep(0.50002);
	eft[3]->LastSleep(0.0001f);

	eft[4]->Move(0.5, -100, -100);
	eft[4]->Sleep(0.50003);
	eft[4]->LastSleep(0.0001f);

	eft[5]->Move(0.5, -100, 100);
	eft[5]->Sleep(0.50004);
	eft[5]->LastSleep(0.0001f);

	eft[10]->Move(0.5, 0, -120);
	eft[10]->Sleep(0.50005);
	eft[10]->LastSleep(0.0001f);

	eft[11]->Move(0.5, 0, 120);
	eft[11]->Sleep(0.50006);
	eft[11]->LastSleep(0.0001f);


	//2個目のアニメーション


	//3個目のアニメーション



	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_GreatEffect()
{
	new EffectGame(&EffectGame::E_game_GreatEffect);
}
//===================================================================================================================
//===================================================================================================================
void EffectGame::E_game_BadEffect()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[6]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_CROSS]);     // エフェクトパーティクル[6]のテクスチャロード
		eft[6]->obj.Object.Pos.x = 800.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[6]->obj.Object.Pos.y = 250.0f;     // エフェクトパーティクル[0]の初期Y座標


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////
	// 1個目のアニメーション
	eft[6]->Curve(false, 3.0, 3.0, -600, -250);
	eft[6]->Sleep(3.5001);



	//2個目のアニメーション
	eft[6]->Rotate(3.0f, 360);
	eft[6]->Curve(false, 4.0, 3.0, -800, 400);
	eft[6]->Sleep(3.0001);
	eft[6]->LastSleep(0.0001f);

	//3個目のアニメーション



	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_BadEffect()
{
	new EffectGame(&EffectGame::E_game_BadEffect);
}
//==========================================================================================================================
//===========================================================================================================================
void EffectGame::E_game_OverEffect()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[7]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_ASE]);     // エフェクトパーティクル[7]のテクスチャロード
		eft[7]->obj.Object.Pos.x = 200.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[7]->obj.Object.Pos.y = 200.0f;     // エフェクトパーティクル[0]の初期Y座標


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////
	// 1個目のアニメーション
	eft[7]->Rotate(3.0f, -20.0f);
	eft[7]->Curve(true, 4.0, 6.0, -50, 200);
	eft[7]->Sleep(6.5001);
	eft[7]->LastSleep(0.0001f);
	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_OverEffect()
{
	new EffectGame(&EffectGame::E_game_OverEffect);
}
//======================================================================================================================
//=======================================================================================================================
void EffectGame::E_game_RunEffect()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[8]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_FIRE]);     // エフェクトパーティクル[8]のテクスチャロード
		eft[10]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_HANABI]);     // エフェクトパーティクル[8]のテクスチャロード
		eft[11]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_HANABI]);     // エフェクトパーティクル[8]のテクスチャロード
		eft[10]->obj.Object.Scale.x = 0.1f;
		eft[10]->obj.Object.Scale.y = 0.1f;
		eft[11]->obj.Object.Scale.x = 0.1f;
		eft[11]->obj.Object.Scale.y = 0.1f;

		eft[8]->obj.Object.Pos.x = 250.0f;     // エフェクトパーティクル[0]の初期X座標======火
		eft[8]->obj.Object.Pos.y = 900.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[10]->obj.Object.Pos.x = 450.0f;     // エフェクトパーティクル[0]の初期X座標	=======★★
		eft[10]->obj.Object.Pos.y = 300.0f;     // エフェクトパーティクル[0]の初期Y座標

		eft[11]->obj.Object.Pos.x = 150.0f;     // エフェクトパーティクル[0]の初期X座標	=======★★
		eft[11]->obj.Object.Pos.y = 300.0f;     // エフェクトパーティクル[0]の初期Y座標


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////
	// 1個目のアニメーション
	eft[8]->Zoom(0.5f, 3.0f);//===========火
	eft[8]->Move(0.5f, 0.0f, -500.0f);
	eft[8]->Sleep(2.0001);
	eft[8]->LastSleep(0.0001f);

	eft[10]->Sleep(1.05001);//======★★
	eft[10]->Curve(false, 5.0f, 1.0f, 300, -200);
	eft[10]->Sleep(1.0001);
	eft[10]->LastSleep(0.0002f);

	eft[11]->Sleep(1.05001);
	eft[11]->Curve(true, 5.0f, 1.0f, -300, -200);
	eft[11]->Sleep(1.0001);
	eft[11]->LastSleep(0.0002f);


	//2個目のアニメーション

	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_RunEffect()
{
	new EffectGame(&EffectGame::E_game_RunEffect);
}
//=========================================================================================================================
//=========================================================================================================================
void EffectGame::E_game_JoyconEffect()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////
		eft[9]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_JOYCON]);     // エフェクトパーティクル[9]のテクスチャロード
		eft[9]->obj.Object.Pos.x = 900.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[9]->obj.Object.Pos.y = 350.0f;     // エフェクトパーティクル[0]の初期Y座標
		eft[9]->obj.Object.Scale.x = 0.1f;
		eft[9]->obj.Object.Scale.y = 0.1f;


		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////
	// 1個目のアニメーション
	eft[9]->Zoom(0.3f, 0.1f);
	eft[9]->Sleep(.3001);
	eft[9]->Rotate(0.5f, 10.0f);
	eft[9]->Sleep(0.5001);
	eft[9]->Rotate(0.5f, -20.0f);
	eft[9]->Sleep(0.5002);
	eft[9]->Zoom(0.3f, -0.1f);
	eft[9]->Sleep(0.3002);

	//2個目のアニメーション
	eft[9]->Zoom(0.3f, 0.1f);
	eft[9]->Sleep(.3001);
	eft[9]->Rotate(0.5f, 10.0f);
	eft[9]->Sleep(0.5001);
	eft[9]->Rotate(0.5f, -20.0f);
	eft[9]->Sleep(0.5002);
	eft[9]->Zoom(0.3f, -0.1f);
	eft[9]->Sleep(0.3002);
	eft[9]->LastSleep(0.0001f);

	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_JoyconEffect()
{
	new EffectGame(&EffectGame::E_game_JoyconEffect);
}


// バトンタッチ1000Pゲット
void EffectGame::E_game_Baton1000P()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////

		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_1000P]);     // エフェクトパーティクル[0]のテクスチャロード
		eft[0]->obj.Object.Pos.x = 640.0f;     // エフェクトパーティクル[0]の初期X座標
		eft[0]->obj.Object.Pos.y = 360.0f;     // エフェクトパーティクル[0]の初期Y座標
		eft[0]->obj.Object.Scale.x = 0.5f;
		eft[0]->obj.Object.Scale.y = 0.5f;

		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////

	eft[0]->Zoom(0.5f, 1.7f);
	eft[0]->Sleep(2.3f);
	eft[0]->LastSleep(0.0001f);

	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_Baton1000P()
{
	new EffectGame(&EffectGame::E_game_Baton1000P);
}


////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

