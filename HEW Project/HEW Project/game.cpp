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
// Debugパネル
void Debug_Panel();

/*
グローバル変数
*/

// スビート計算用
std::vector<int> Speed_Array;
static int Max_Count;
static int Judge_Count;
// アクションUI
ActionUI Action;
// アクションゲージ
ActionSlot Actionslot;
// ゲームデータ
GameData gamedata;

Live2D Character;


void Init_Game() {

	// アクションUI初期化
	Action.Init();
	Action.Pos.x = 500;
	Action.Pos.y = 600;
	Action.Interval.x = 150;
	Action.Interval.y = 0;

	// アクションゲージ初期化
	Actionslot.Pos.x = 350;
	Actionslot.Pos.y = 280;
	Actionslot.Load();
	
	Character.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_RICE]);
	Character.Zoom.x = 2.5f;
	Character.Zoom.y = 2.5f;
	Character.Pos.x = -400;
	Character.Pos.y = 100;
}

void Uninit_Game() {

	Character.~Live2D();

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

#ifdef DEBUG
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}
#endif // DEBUG

}

void Draw_Game() {

	// アクションUI描画
	Action.Draw();
	// アクションゲージ描画
	Actionslot.Draw();

	Character.Draw();

	// アクション完成判定
	if (Action.GetFinishFlag()) {
		if (Action.GetProgress() == Action.GetActionAmount()) {
			Actionslot.AddValue(0.5);
		}
		else {
		
		}
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

		if (Judge_Count > 1000) {
			gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
			Judge_Count = 0;
		}

		gamedata.SetRunningSpeed(405);

		Speed_Array.clear();
	}

	if (gamedata.GetRunningSpeed() > 0) {
		gamedata.AddRunningSpeed(-15);
	}

	gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
}

void Debug_Panel() {

	SetFontSize(24);
	DrawFormatString(600, 200, GetColor(255, 255, 255), "走る距離 : %d", gamedata.GetRunningMeter());
	DrawFormatString(600, 250, GetColor(255, 255, 255), "アクションゲージ : %f", Actionslot.GetValue());
}