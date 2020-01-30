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
#include "Tutorial.h"
#include "Live2D.h"

static GameObject ProgressBar[3];
static BatonTouch batontouch;
static ActionUI Actionui;
static Live2D Chara;

int p1[2] = { 0,0 };
int p2[2] = {0,0};
int p3[2] = {0,0};

void GameProgress::Init() 
{

		ProgressBar[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_PROGRESS_BAR]);
		ProgressBar[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

		Chara.LoadModel(Live2D_Dict["KYARA"]);
		Chara.Zoom.x = 0.25f;
		Chara.Zoom.y = 0.25f;
		Chara.Pos.x = -400.0f;
		Chara.Pos.y = 250.0f;



		ProgressBar[1].Object.Pos.x = SCREEN_WIDTH / 2;
		ProgressBar[1].Object.Pos.y = 100.0f;
		ProgressBar[1].Object.Scale.x = 0.6f;
		ProgressBar[1].Object.Scale.y = 0.6f;


		ProgressBar[2].Object.Pos.x = 200.0f;
		ProgressBar[2].Object.Pos.y = 100.0f;
		ProgressBar[2].Object.Scale.x = 0.5f;
		ProgressBar[2].Object.Scale.y = 0.5f;

		ProgressBar[0].LoadTexture(TextureDict["10m"]);
		ProgressBar[0].Object.Pos.x = 0.0f;
		ProgressBar[0].Object.Pos.y = 0.0f;
		ProgressBar[0].Object.Scale.x = 0.4f;
		ProgressBar[0].Object.Scale.y = 0.4f;


		//stime = 0.0f;
		stime = SECONDS;
		ProgressMax = 5000;
		NowProgress = 0.0f;
		Section = 0;
		RunDistance = 0.0f;		//ゲットした距離データを入れる
		GameFinish = false;
		MeasureFlag = false;

		

		p1[0] = (rand() % 4) + 1;
	

		p2[0] = (rand() % 5);
		p2[1] = (rand() % 5);

		while (p2[0] == p2[1]) {
			p2[1] = (rand() % 5);
		}

		p3[0] = (rand() % 5);
		p3[1] = (rand() % 5);

		while (p3[0] == p3[1]) {
			p3[1] = (rand() % 5);
		}
}



GameProgress::GameProgress()
{
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update(ActionUI &target)
{
	//フレームでゲージを増やす処理
	if (MeasureFlag == false)
	{
		NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
		NowProgress += stime / 6.4f;

		//進行バーの増加処理
		//ProgressBar[1].Object.Scale.x = NowProgress/10000;

		//キャラアイコンの移動処理
		//ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;		//+100.0fはアイコンの初期位置の指定
		Chara.Pos.x = NowProgress - 540.0f;		//+100.0fはアイコンの初期位置の指定


		//残り10mの表示
		//ProgressBar[0].Object.Pos.x = ProgressBar[2].Object.Pos.x + 90.0f;
		ProgressBar[0].Object.Pos.x = Chara.Pos.x + 720.0f;
		ProgressBar[0].Object.Pos.y = Chara.Pos.y - 200.0f;


		if (stime < 5450.0f)	//90秒
		{

			stime++;

		}
	}

	//===================区間1===============================

	//10秒経ったら(1秒＝60)
	if (stime > 600.0f && stime < 660.0f) 
	{

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
		target.ResetAll();
		target.State = p1[0];
		
	}

	//25秒経ったら(1秒＝60)
	if (stime > 1500.0f && stime < 1560.0f) 
	{

		//距離で計測する処理に切り替え
		MeasureFlag = true;


	}
	//距離で計測する処理
	ChangeMeasure(1500.0f,1800.0f);


	if (Tutoflag == true&& (stime > 1800.0f && stime < 1860.0f))
	{
		TutoState_Change(TUTO_STATE_BATONTOUCH);
		Tutoflag = false;
	}

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
			target.ResetAll();
			target.State = p2[0];

		}
	}
	//===================区間2===============================

	//42秒経ったら(1秒＝60)
	if (stime > 2520.0f && stime < 2580.0f)
	{
		//距離で計測する処理に切り替え
		MeasureFlag = true;

		
	}
	//距離で計測する処理
	ChangeMeasure(2520.0f,2820.0f);

	//47秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 600 && ProgressBar[2].Object.Pos.x < 660) || */(stime > 2820.0f && stime < 2880.0f))
	{
		DrawFormatString(300, 300, GetColor(255, 255, 255), "アクションチェンジ");
		MeasureFlag = false;

		//アクションが変わる処理
		target.ResetAll();
		target.State = p2[1];

	}

	//58秒経ったら(1秒＝60)
	if (stime > 3480.0f && stime < 3540.0f)
	{
		//距離で計測する処理に切り替え
		MeasureFlag = true;
	}
	//距離で計測する処理
	ChangeMeasure(3480.0f,3780.0f);

	//63秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 750 && ProgressBar[2].Object.Pos.x < 760) || */(stime > 3780.0f && stime < 3840.0f))
	{
		MeasureFlag = false;

		//バトンタッチ処理
		if (Section == 1) {
			batontouch.StateBaton = true;
			GameState_Change(GAME_STATE_BATONTOUCH);
			Section = 2;

			//アクションが変わる処理
			target.ResetAll();
			target.State = p3[0];

		}
	}

	//===================区間3===============================

	//74秒経ったら(1秒＝60)
	if (stime > 4440.0f && stime < 4500.0f)
	{
		//距離で計測する処理に切り替え
		MeasureFlag = true;

		
	}
	//距離で計測する処理
	ChangeMeasure(4440.0f,4740.0f);

	//79秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 900 && ProgressBar[2].Object.Pos.x < 910) || */(stime > 4740.0f && stime < 4800.0f))
	{
		DrawFormatString(300, 400, GetColor(255, 255, 255), "アクションチェンジ");
		MeasureFlag = false;

		//アクションが変わる処理
		target.ResetAll();
		target.State = p3[1];

	}

	//90秒経ったら(1秒＝60)
	if (stime > 5400.0f && stime < 5460.0f)
	{
		//距離で計測する処理に切り替え
		MeasureFlag = true;

	}
	//距離で計測する処理
	ChangeMeasure(5400.0f,5700.0f);

	//90秒経ったら(1秒＝60)
	if (/*(ProgressBar[2].Object.Pos.x > 1050 && ProgressBar[2].Object.Pos.x < 1010) || */(stime > 5700.0f && stime < 5760.0f))
	{
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
	ProgressBar[1].Draw();

	//ProgressBar[2].Draw();
	Chara.Draw();

	//残り１０ｍ
	if (stime > 600.0f && stime < 660.0f|| stime > 1500.0f && stime < 1560.0f||  stime > 2520.0f && stime < 2580.0f ||
		stime > 3480.0f && stime < 3540.0f || stime > 4440.0f && stime < 4500.0f || stime > 5400.0f && stime < 5460.0f) {
		ProgressBar[0].Draw();
	}

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
	//return ProgressBar[2].Object.Pos.x;
	return Chara.Pos.x;

}

void GameProgress::ChangeMeasure(float time1, float time2)
{
	int running_sp = gamedata.GetRunningSpeed();

	//距離で計測する処理
	if (MeasureFlag == true && stime >= time1 && stime <= time2)
	{
		//走るスピードが350を超えたら
		if (running_sp >=350)
		{
			RunDistance += gamedata.GetRunningDistance() / 1000;		//ゲットした距離データを入れる
			if (RunDistance >= gamedata.GetRunningDistance() / 1000)
			{
				NowProgress = NowProgress / ProgressMax * PROGRESS_WIDTH;
				NowProgress += stime / 6.4f;
				//ProgressBar[2].Object.Pos.x = NowProgress + 100.0f;
				Chara.Pos.x = NowProgress - 540.0f;
				stime += 15.0f;
				RunDistance = 0.0f;
				running_sp = 0;
			}

		}

	}

}