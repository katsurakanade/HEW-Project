#include <algorithm>
#include <vector>
#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "ActionSlot.h"
#include "ActionUI.h"
#include "GameData.h"
#include "Live2D.h"

// Debug Mode
#define DEBUG

/* 
プロトタイプ宣言
*/

// 走る処理
void Running();
// キャラクター処理
void CharacterMove();
// Debugパネル
void Debug_Panel();
// Debug走る (キーボード)
void Debug_Running();

/*
グローバル変数
*/

// スビート計算用
std::vector<int> Speed_Array;
int Max_Count;
int Judge_Count;
// アクションUI
ActionUI Action;
// アクションゲージ
ActionSlot Actionslot;
// キャラクター
Live2D Character;
// アクション失敗画像
GameObject Failed;

void Init_Game() {

	// アクションUI初期化
	Action.Init();
	Action.Pos.x = 700;
	Action.Pos.y = 200;
	Action.Interval.x = 150;
	Action.Interval.y = 0;

	// アクションゲージ初期化
	Actionslot.Pos.x = 80;
	Actionslot.Pos.y = 500;
	Actionslot.Load();
	
	// キャラクター初期化
	Character.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);
	Character.Zoom.x = 0.5f;
	Character.Zoom.y = 0.5f;
	Character.Pos.x = -580;
	Character.Pos.y = -150;

	// アクション失敗初期化
	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_FAILED]);
	Failed.Object.Pos.x = 600;
	Failed.Object.Pos.y = 200;

	// ゲームデータ初期化
	gamedata.Init();
	
}

void Uninit_Game() {

	Character.~Live2D();
	Action.~ActionUI();
}

void Update_Game() {

	Character.SetMontionIndex(GetRand(8));

	// アクションUI更新
	Action.Update();
	// アクションゲージ更新
	Actionslot.Update();
	// スビート更新
	gamedata.UpdateSpeed();

	// 走る処理
	Running();

	// キャラクター処理
	CharacterMove();
	

#ifdef DEBUG
	// Go Title
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}
	// Go Result
	if (keyboard.IsTrigger(DIK_ESCAPE)) {
		Scene_Change(SCENE_INDEX_RESULT);
	}

	Debug_Running();
#endif // DEBUG

}

void Draw_Game() {

	// アクションUI描画
	Action.Draw();
	
	// キャラクター描画
	Character.Draw();

	// アクションゲージ描画
	Actionslot.Draw();

	// アクション完成判定
	if (Action.GetFinishFlag()) {
		if (Action.GetProgress() == Action.GetActionAmount()) {
			Actionslot.AddValue(0.5);
		}
		else {
			Failed.Draw();
		}
		Action.SetState(GetRand(1));
	}

#ifdef DEBUG
	Debug_Panel();
#endif // DEBUG

}

void Running() {

	if (joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[0] = true;
		Speed_Array.push_back(joycon[1].GetGyro_Y());
	}

	if (joycon[1].Action_Judge[0] && joycon[1].GetGyro_Y() < -200) {
		joycon[1].Action_Judge[1] = true;
	}

	if (joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].GetGyro_Y() > 150) {
		joycon[1].Action_Judge[2] = true;
	}

	if ((joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].Action_Judge[2])) {
		for (int i = 0; i < 3; i++) {
			joycon[1].Action_Judge[i] = false;
		}
		vector<int>::iterator iter = max_element(Speed_Array.begin(), Speed_Array.end());
		Max_Count = *iter;
		Judge_Count += Max_Count;

		if (Judge_Count > 350) {
			gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
			gamedata.SetRunningSpeed(405);
			Judge_Count = 0;
		}

		Speed_Array.clear();
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

	switch (Action.GetState())
	{
	case ACTIONSLOT_GREAT:
		gamedata.AddActionPoint(50);
		break;
	case ACTIONSLOT_GOOD:
		gamedata.AddActionPoint(20);
		break;
	default:
		break;
	}
}

void CharacterMove() {

	// 右
	if (gamedata.GetRunningSpeed() >= 150 && Character.Zoom.x < 1.0) {
		Character.Pos.x += 5.0f;
		Character.Zoom.x += 0.0025f;
		Character.Zoom.y += 0.0025f;
		Character.Pos.y += 0.75f;
		Actionslot.Pos.x += 5.4f;
		Actionslot.Pos.y -= 0.75f;
		Actionslot.Scale += D3DXVECTOR2(0.0025f, 0.0025f);
		Actionslot.Fire_Offset += D3DXVECTOR2(0.45f, 0.25f);
	}

	// 左
	if (gamedata.GetRunningSpeed() <= 30 && Character.Zoom.x > 0.5) {
		Character.Pos.x -= 5.0f;
		Character.Zoom.x -= 0.0025f;
		Character.Zoom.y -= 0.0025f;
		Character.Pos.y -= 0.75f;
		Actionslot.Pos.x -= 5.4f;
		Actionslot.Pos.y += 0.75f;
		Actionslot.Scale -= D3DXVECTOR2(0.0025f, 0.0025f);
		Actionslot.Fire_Offset -= D3DXVECTOR2(0.45f, 0.25f);
	}

}

void Debug_Running() {
	
	if (keyboard.IsPress(DIK_RIGHTARROW)) {
		Judge_Count += 350;
	}

	if (Judge_Count > 350) {
		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
		gamedata.SetRunningSpeed(405);
		Judge_Count = 0;
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void Debug_Panel() {

	SetFontSize(24);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "走る距離 : %d", gamedata.GetRunningMeter());
	DrawFormatString(0, 30, GetColor(255, 255, 255), "アクションゲージ : %f", Actionslot.GetValue());
	DrawFormatString(0, 60, GetColor(255, 255, 255), "アクションゲージ状態 : %d", Actionslot.GetState());
	DrawFormatString(0, 90, GetColor(255, 255, 255), "アクション状態 : %d", Action.GetState());
	DrawFormatString(0, 120, GetColor(255, 255, 255), "スビート : %d", gamedata.GetRunningSpeed());
	DrawFormatString(0, 150, GetColor(255, 255, 255), "聖火 : %d", gamedata.Gethp());
	DrawFormatString(0, 180, GetColor(255, 255, 255), "アクションポイント： %d", gamedata.GetActionPoint());
}