//13210_ゲーム進行バー
/*------------------------------------------------------------------
@brief	ゲームの進行バー
@author	萩原直之
@date	2019/12/05
-------------------------------------------------------------------*/
#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "GameData.h"
#include "DxLib.h"
#include "BatonTouch.h"
#include "game.h"
#include "ActionUI.h"

static GameObject ProgressBar[3];
static BatonTouch batontouch;
static ActionUI actionui;

void GameProgress::Init() 
{
		ProgressBar[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BAR_FRAME]);
		ProgressBar[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_PROGRESS_BAR]);
		ProgressBar[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

		ProgressBar[0].Object.Pos.x = SCREEN_WIDTH / 2;
		ProgressBar[0].Object.Pos.y = 100.0f;
		ProgressBar[0].Object.Scale.x = 1.0f;
		ProgressBar[0].Object.Scale.y = 1.0f;

		ProgressBar[1].Object.Pos.x = SCREEN_WIDTH / 2;
		ProgressBar[1].Object.Pos.y = 100.0f;
		ProgressBar[1].Object.Scale.x = 1.0f;
		ProgressBar[1].Object.Scale.y = 1.0f;


		ProgressBar[2].Object.Pos.x = 200.0f;
		ProgressBar[2].Object.Pos.y = 100.0f;
		ProgressBar[2].Object.Scale.x = 0.5f;
		ProgressBar[2].Object.Scale.y = 0.5f;

		//stime = 0.0f;
		stime = SECONDS;
		ProgressMax = 5000;
		NowProgress = 0.0f;
		Section = 0;
		RunDistance = 0.0f;		//ゲットした距離データを入れる
		GameFinish = false;
		MeasureFlag = false;

		actionui.SetState(0);
}



GameProgress::GameProgress()
{
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	//フレームでゲージを増やす処理
	if (MeasureFlag == false)
	{
		NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
		NowProgress += stime / 6.4f;

		//進行バーの増加処理
		//ProgressBar[1].Object.Scale.x = NowProgress/10000;

		//キャラアイコンの移動処理
		ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;		//+100.0fはアイコンの初期位置の指定

		if (stime < 5450.0f)	//90秒
		{

			stime++;

		}
	}

	//===================区間1===============================

	//10秒経ったら(1秒＝60)
	if (stime > 600.0f && stime < 660.0f) 
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;
	}
	//距離で計測する処理
	ChangeMeasure(600.0f,900.0f);
	
	//アクションチェンジポイントに着いたら
	//15秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 300 && ProgressBar[2].Object.Pos.x < 310) ||*/ (stime > 900.0f && stime < 960.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "アクションチェンジ");
		MeasureFlag = false;

		//アクションが変わる処理
		actionui.SetState(1);

	}

	//25秒経ったら(1秒＝60)
	if (stime > 1500.0f && stime < 1560.0f) 
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;

	}
	//距離で計測する処理
	ChangeMeasure(1500.0f,1800.0f);

	//30秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 450 && ProgressBar[2].Object.Pos.x < 460) || */(stime > 1800.0f && stime < 1860.0f))
	{
		MeasureFlag = false;

		//バトンタッチ処理
		if (Section == 0) {
			batontouch.StateBaton = true;
			GameState_Change(GAME_STATE_BATONTOUCH);
			Section = 1;

			//アクションが変わる処理
			actionui.SetState(2);

		}
	}
	//===================区間2===============================

	//40秒経ったら(1秒＝60)
	if (stime > 2400.0f && stime < 2460.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;

	}
	//距離で計測する処理
	ChangeMeasure(2400.0f,2700.0f);

	//45秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 600 && ProgressBar[2].Object.Pos.x < 660) || */(stime > 2700.0f && stime < 2760.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "アクションチェンジ");
		MeasureFlag = false;

		//アクションが変わる処理
		actionui.SetState(1);

	}

	//55秒経ったら(1秒＝60)
	if (stime > 3300.0f && stime < 3360.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;
	}
	//距離で計測する処理
	ChangeMeasure(3300.0f,3600.0f);

	//60秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 750 && ProgressBar[2].Object.Pos.x < 760) || */(stime > 3600.0f && stime < 3660.0f))
	{
		MeasureFlag = false;

		//バトンタッチ処理
		if (Section == 1) {
			batontouch.StateBaton = true;
			GameState_Change(GAME_STATE_BATONTOUCH);
			Section = 2;

			//アクションが変わる処理
			actionui.SetState(1);

		}
	}

	//===================区間3===============================

	//70秒経ったら(1秒＝60)
	if (stime > 4200.0f && stime < 4260.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;

	}
	//距離で計測する処理
	ChangeMeasure(4200.0f,4500.0f);

	//75秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 900 && ProgressBar[2].Object.Pos.x < 910) || */(stime > 4500.0f && stime < 4560.0f))
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "アクションチェンジ");
		MeasureFlag = false;

		//アクションが変わる処理
		actionui.SetState(2);

	}

	//85秒経ったら(1秒＝60)
	if (stime > 5100.0f && stime < 5160.0f)
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "残り10m!!");
		//距離で計測する処理に切り替え
		MeasureFlag = true;

	}
	//距離で計測する処理
	ChangeMeasure(5100.0f,5400.0f);

	//90秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 1050 && ProgressBar[2].Object.Pos.x < 1010) || */(stime > 5400.0f && stime < 5460.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "GOAL!!");
		MeasureFlag = false;

		//ゲームクリア処理
		if (Section == 2) {
			GameState_Change(GAME_STATE_GAME_CLEAR);
			Section = 3;
		}
	}

}

void GameProgress::Draw()
{
	//デバック用
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "経過:%d秒",  stime/60);
	//DrawFormatString(200, 500, GetColor(255, 255, 255), "airouの位置:%f", ProgressBar[2].Object.Pos.x);

	//プログレスバーのフレーム
	//ProgressBar[0].Draw(PROGRESS_WIDTH+20, PROGRESS_HEIGHT+20);
	ProgressBar[0].Draw();

	//増化するプログレスバー
	//ProgressBar[1].Draw(200, 60, NowProgress, PROGRESS_HEIGHT,TRUE,FALSE);
	ProgressBar[1].Draw();

	//キャラアイコン
	//ProgressBar[2].Draw(NowProgress+180.0f, 50, 2.0f,2.0f, 256, 256, TRUE, FALSE);
	ProgressBar[2].Draw();

	DrawFormatString(0, 300, GetColor(255, 255, 255), "Distance:%f", RunDistance);


}


int GameProgress::GetSection() {
	return Section;
}

void GameProgress::SetMesureflag(bool flag)
{
	MeasureFlag = flag;
}

float GameProgress::GetProgressBarObjectPosx()
{
	return ProgressBar[2].Object.Pos.x;
}

void GameProgress::ChangeMeasure(float time1, float time2)
{
	//距離で計測する処理
	if (MeasureFlag == true && stime >= time1 && stime <= time2)
	{
		if (keyboard.IsTrigger(DIK_RIGHTARROW))
		{
			RunDistance += gamedata.GetRunningDistance() / 1000;		//ゲットした距離データを入れる
			if (RunDistance >= gamedata.GetRunningDistance() / 1000)
			{
				NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
				NowProgress += stime / 6.4f;
				ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;
				stime += 15.0f;
				RunDistance = 0.0f;
			}

		}

	}

}