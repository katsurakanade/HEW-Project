#pragma once

typedef enum
{
	GAME_STATE_START,		//スタート待機、初期化
	GAME_STATE_GAME,		//メインゲーム
	GAME_STATE_BATONTOUCH,		//バトンタッチ
	GAME_STATE_GAME_OVER,		//ゲームオーバー
	GAME_STATE_GAME_CLEAR,		//ゲームクリア

	GAME_STATE_MAX

}GAME_STATE;

/*
プロトタイプ宣言
*/

// 走る処理
void Running();
// Debugパネル
void Debug_Panel();
// キャラクター処理
void CharacterMove();
// Debug走る (キーボード)
void Debug_Running();


void Init_Game();
void Init_GameState();     // ２区間, ３区間用Init
void Uninit_Game();
void Update_Game();
void Draw_Game();



//ゲームステート用
void GameState_Initialize(GAME_STATE index);
void GameState_Check(void);
void GameState_Change(GAME_STATE index);