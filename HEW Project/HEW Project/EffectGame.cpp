#include "EffectGame.h"
#include "Effect.h"
#include <vector>


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
	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Update();
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
	MaxEffectNum++;
	// 自分のポインタ格納
	EGStorage.push_back(this);
	// 関数ポインタを格納
	fpCallFunc = fp_CallFunc;
}
EffectGame::~EffectGame()
{
	MaxEffectNum--;
	// 自分のポインタを削除
	EGStorage.erase(EGStorage.begin() + MaxEffectNum);
	// メモリ解放
	///delete[] eft;     // エラー出る
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
		delete this;     //自分を消す
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
	//eft[0]->Zoom(2.0f, 0.5f);
	//eft[0]->Sleep(4.0f);
	///eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	///eft[1]->Sleep(2.0);

	// 2個目のアニメーション
	//eft[0]->Zoom(2.0f, 0.5f);
	//eft[0]->Sleep(2.0001);
	///eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	///eft[1]->Sleep(3.0);
	///eft[1]->LastSleep(0.0001f);

	// 3個目のアニメーション
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	//eft[0]->Curve(true, 3.0, 2.0, -100, -200.0001);
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

////////////////////////////////////////////////////// チュートリアル(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////

// エフェクト関数:アクション成功
void EffectGame::E_game_ActionSucsess()
{
	if (DoOnce)
	{
		//// ※----- エフェクトの初期設定 -----※ ////



		//// ※----- エフェクトの初期設定 -----※ ////
		DoOnce = false;     // 消さない!!
	}

	//// ※-----------------------↓ここから下にエフェクトアニメーションを書く ↓-----------------------※ ////



	//// ※-----------------------↑ ここから上にエフェクトアニメーションを書く ↑-----------------------※ ////
	E_end();     // 必ずコピー！ //
}
// 上(↑)のエフェクト関数に書いた関数名の頭に「call_」を付ける。
void call_E_game_ActionSucsess()
{
	new EffectGame(&EffectGame::E_game_ActionSucsess);
}



////////////////////////////////////////////////////// ゲーム(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// リザルト(result) //////////////////////////////////////////////////////

