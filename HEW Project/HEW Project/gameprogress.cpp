/*------------------------------------------------------------------
@brief	ゲームの進行バー
@author	萩原直之
@date	2019/11/12
-------------------------------------------------------------------*/
#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "DxLib.h"
#include <time.h>

static GameObject ProgressBar[3];

void Init_GameProgress() 
{

	ProgressBar[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BAR_FRAME]);
	ProgressBar[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_PROGRESS_BAR]);
	ProgressBar[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

}


GameProgress::GameProgress()
{
	stime = 0;
	stime = SECONDS;
	ProgressMax = 5000;
	NowProgress = 200.0f;
	Section = 0;
	GameFinish = false;
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
	NowProgress += stime/10;
	
	if (stime < 5450)	//90秒
	{

		stime++;

	}
	//===================区間1===============================

	//10秒経ったら(1秒＝60)
	if (stime > 600 && stime < 660) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//15秒経ったら(1秒＝60)
	if (stime > 900 && stime < 960) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "アクションチェンジ");

		//アクションが変わる処理

	}

	//25秒経ったら(1秒＝60)
	if (stime > 1500 && stime < 1560) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//30秒経ったら(1秒＝60)
	if (stime > 1800 && stime < 1860) 
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "バトンタッチ");

		//バトンタッチ処理
		if (Section == 0) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 1;
		}
	}
	//===================区間2===============================

	//40秒経ったら(1秒＝60)
	if (stime > 2400 && stime < 2460)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//45秒経ったら(1秒＝60)
	if (stime > 2700 && stime < 2760)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "アクションチェンジ");

		//アクションが変わる処理

	}

	//55秒経ったら(1秒＝60)
	if (stime > 3300 && stime < 3360)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//30秒経ったら(1秒＝60)
	if (stime > 3600 && stime < 3660)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "バトンタッチ");

		//バトンタッチ処理
		if (Section == 1) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 2;
		}
	}

	//===================区間3===============================

	//70秒経ったら(1秒＝60)
	if (stime > 4200 && stime < 4260)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//75秒経ったら(1秒＝60)
	if (stime > 4500 && stime < 4560)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "アクションチェンジ");

		//アクションが変わる処理

	}

	//85秒経ったら(1秒＝60)
	if (stime > 5100 && stime < 5160)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "残り10m!!");

		//距離で計測する処理

	}

	//90秒経ったら(1秒＝60)
	if (stime > 5400 && stime < 5460)
	{
		DrawFormatString(300, 0, GetColor(255, 255, 255), "GOAL!!");

		//バトンタッチ処理
		if (Section == 2) {
			Scene_Change(SCENE_INDEX_BATON_TOUCH);
			//BT_Move = true;
			Section = 3;
		}
	}

}

void GameProgress::Draw()
{
	//デバック用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "経過:%d秒",  stime/60);

	//プログレスバーのフレーム
	ProgressBar[0].Draw(160, 40, PROGRESS_WIDTH+20, PROGRESS_HEIGHT+20, TRUE);

	//増化するプログレスバー
	ProgressBar[1].Draw(200, 50, NowProgress+200.0f, PROGRESS_HEIGHT,TRUE);

	//キャラアイコン
	ProgressBar[2].Draw(NowProgress+180.0f, 50, 2.0f,2.0f, 256, 256, TRUE, FALSE);

}


int GameProgress::GetSection() {
	return Section;
}