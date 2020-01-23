#pragma once

typedef enum TUTO_STATE
{
	TUTO_STATE_START,		//スタート待機、初期化
	TUTO_STATE_GAME,		//チュートリアルゲーム
	TUTO_STATE_BATONTOUCH,		//バトンタッチ

	TUTO_STATE_MAX

};

void Init_Tutorial();
void Uninit_Tutorial();
void Update_Tutorial();
void Draw_Tutorial();

//ゲームステート用
void TutoState_Initialize(TUTO_STATE index);
void TutoState_Check(void);
void TutoState_Change(TUTO_STATE index);
void TutoRunning();
void TutoCharacterMove();
void Debug_TutoRunning();
