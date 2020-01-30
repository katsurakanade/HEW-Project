#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include <DxLib.h>
#include "ResultScore.h"

static GameObject obj[3];
static ResultScore score[6];
static ResultScore ui;
static int g_TotalScore;
double ranking[RANKING_MAX] = { 0 ,0,0 };


void Init_Result()
{

	//走った距離
	int Distance_p = gamedata.GetRunningDistance();

	//アクションポイント
	int Action_p = gamedata.GetActionPoint();

	//合計スコア
	g_TotalScore = ((Distance_p * 3 / 2 + (Action_p * 2) / 2)*2);


	//ランキングの読み込み
	Ranking_Read();

	//ソートしたランキングの反映
	Ranking_Sort(g_TotalScore);

	//画面の背景表示
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.00f;
	obj[0].Object.Scale.y = 1.00f;

	obj[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_RESULT_BG]);
	obj[1].Object.Pos.x = 400.0f;
	obj[1].Object.Pos.y = 460.0f;
	obj[1].Object.Scale.x = 0.75f;
	obj[1].Object.Scale.y = 0.75f;

	obj[2].LoadTexture(TextureDict["board"]);
	obj[2].Object.Pos.x = 300;
	obj[2].Object.Pos.y = 125;
	obj[2].Object.Scale.x = 1.0f;
	obj[2].Object.Scale.y = 0.7f;

	ui.Init();

	
	//ランキングの表示
	for (int i = 0; i < RANKING_MAX; i++)
	{
		score[i].ScoreCreate(ranking[i], SCREEN_WIDTH - 380, 200 + 200 * i);

	}

	//走った距離の表示
	score[3].ScoreCreate(Distance_p, SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 );

	//アクションポイントの表示
	score[4].ScoreCreate(Action_p, SCREEN_WIDTH / 2 - 490, SCREEN_HEIGHT / 2 + 100);

	//合計スコアの表示
	score[5].ScoreCreate(g_TotalScore, 220, 100, 1.2f, 1.2f);

}

void Uninit_Result()
{

}

void Update_Result()
{
	ui.Update();

	if (keyboard.IsTrigger(DIK_R)|| joycon[0].IsPress(JOYCON_MIN)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result()
{

	obj[0].Draw();
	obj[1].Draw();
	obj[2].Draw();


	ui.Draw();


	//デバック用
	/*
	for (int i = 0; i < RANKING_MAX; i++)
	{
		DrawFormatString(0, i*30, GetColor(255, 255, 255), "%d 位", i + 1);

		DrawFormatString(100, i*30, GetColor(255, 255, 255), "%f \n", ranking[i]);

	}*/


	//DrawFormatString(0, 0, GetColor(255, 255, 255), "走った距離:%d", gamedata.GetRunningDistance());

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "アクションポイント:%d", gamedata.GetActionPoint());

	//DrawFormatString(500, 0, GetColor(255, 255, 255), "合計:%d", g_TotalScore);

	score[0].Draw();
	score[1].Draw();
	score[2].Draw();
	score[3].Draw();
	score[4].Draw();
	score[5].Draw();

}




void Ranking_Sort(double score) {
	FILE* fp;

	fopen_s(&fp, "file.bin", "wb");

	if (fp == NULL)
	{
		printf("%sのオープンに失敗しました。\n", "file.bin");
		return;
	}

	int i;
	int j;

	//ランキングの降順処理
	for (i = 0; i < RANKING_MAX; i++) {//1位から比較
		//今の順位よりも高ければそれが今回の順位となる
		//(1位より高ければ1位、1位より低く2位より高ければ2位、…)
		if (score > ranking[i]) {
			for (j = RANKING_MAX - 1; j > i; j--) {//今回の順位以降のスコアをずらす
				ranking[j] = ranking[j - 1];
			}
			ranking[i] = score;//今回のスコアを記憶
			break;//以降の順位は調べない
		}
	}
	//ランキングの保存
	fwrite(ranking, sizeof(ranking), 5, fp);

	fclose(fp);
}

void Ranking_Read() {

	FILE* fp;

	fopen_s(&fp, "file.bin", "rb");

	if (fp == NULL)
	{
		printf("%sのオープンに失敗しました。\n", "file.bin");
		return;
	}

	fread(ranking, sizeof(ranking), 5, fp);
	fclose(fp);
}

