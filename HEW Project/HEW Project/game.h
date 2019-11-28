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


void Init_Game();
void Uninit_Game();
void Update_Game();
void Draw_Game();