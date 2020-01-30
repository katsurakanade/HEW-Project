#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include "ResultScore.h"
#include <DxLib.h>


ResultScore::ResultScore()
{

}

ResultScore::~ResultScore()
{

}


void ResultScore::Init()
{
	UI[0].LoadTexture(TextureDict["ranking_board"]);
	UI[0].Object.Pos.x = SCREEN_WIDTH - 250;
	UI[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	UI[0].Object.Scale.x = 1.0f;
	UI[0].Object.Scale.y = 1.0f;

	UI[1].LoadTexture(TextureDict["no1"]);
	UI[1].Object.Pos.x = SCREEN_WIDTH - 275;
	UI[1].Object.Pos.y = 180;
	UI[1].Object.Scale.x = 1.0f;
	UI[1].Object.Scale.y = 1.0f;

	UI[2].LoadTexture(TextureDict["no2"]);
	UI[2].Object.Pos.x = SCREEN_WIDTH - 250;
	UI[2].Object.Pos.y = 400;
	UI[2].Object.Scale.x = 1.0f;
	UI[2].Object.Scale.y = 1.0f;

	UI[3].LoadTexture(TextureDict["no3"]);
	UI[3].Object.Pos.x = SCREEN_WIDTH - 250;
	UI[3].Object.Pos.y = 600;
	UI[3].Object.Scale.x = 1.0f;
	UI[3].Object.Scale.y = 1.0f;

	UI[4].LoadTexture(TextureDict["kyori"]);
	UI[4].Object.Pos.x = SCREEN_WIDTH / 2 - 100;
	UI[4].Object.Pos.y = SCREEN_HEIGHT / 2 - 50;
	UI[4].Object.Scale.x = 1.0f;
	UI[4].Object.Scale.y = 1.0f;

	UI[5].LoadTexture(TextureDict["logo_AP"]);
	UI[5].Object.Pos.x = SCREEN_WIDTH / 2 - 220;
	UI[5].Object.Pos.y = SCREEN_HEIGHT / 2 + 100;
	UI[5].Object.Scale.x = 1.0f;
	UI[5].Object.Scale.y = 1.0f;

	UI[6].LoadTexture(TextureDict["total_score"]);
	UI[6].Object.Pos.x = 200;
	UI[6].Object.Pos.y = 110;
	UI[6].Object.Scale.x = 1.0f;
	UI[6].Object.Scale.y = 1.0f;

	UI[7].LoadTexture(TexturePassDict[TEXTURE_INDEX_PUSH_PLUS_TITLE]);
	UI[7].Object.Pos.x = 160;
	UI[7].Object.Pos.y = SCREEN_HEIGHT - 50;
	UI[7].Object.Scale.x = 1.0f;
	UI[7].Object.Scale.y = 1.0f;



	FrameTime = SECONDS;
}

void ResultScore::Update()
{
	FrameTime++;
	
	//+ボタンでタイトルに戻るの表示
	if (FrameTime >= 405)
	{
		DrawFlag = true;
		if (FrameTime >= 455)
		{
			DrawFlag = false;
			FrameTime = 355;
		}

	}
}

void ResultScore::Draw() 
{
	if (ValueData >= 10000000 && ValueData <= 99999999) {
		score[0].Draw_Anime(ValueData / 10000000);
		score[1].Draw_Anime((ValueData / 1000000) % 10);
		score[2].Draw_Anime((ValueData / 100000) % 10);
		score[3].Draw_Anime((ValueData / 10000) % 10);
		score[4].Draw_Anime((ValueData / 1000) % 10);
		score[5].Draw_Anime((ValueData / 100) % 10);
		score[6].Draw_Anime((ValueData / 10) % 10);
		score[7].Draw_Anime(ValueData % 10);
	}

	else if (ValueData >= 1000000 && ValueData <= 9999999) {
		score[0].Draw_Anime(ValueData / 1000000);
		score[1].Draw_Anime((ValueData / 100000) % 10);
		score[2].Draw_Anime((ValueData / 10000) % 10);
		score[3].Draw_Anime((ValueData / 1000) % 10);
		score[4].Draw_Anime((ValueData / 100) % 10);
		score[5].Draw_Anime((ValueData / 10) % 10);
		score[6].Draw_Anime(ValueData % 10);
	}

	else if (ValueData >= 100000 && ValueData <= 999999) {
		score[0].Draw_Anime(ValueData / 100000);
		score[1].Draw_Anime((ValueData / 10000) % 10);
		score[2].Draw_Anime((ValueData / 1000) % 10);
		score[3].Draw_Anime((ValueData / 100) % 10);
		score[4].Draw_Anime((ValueData / 10) % 10);
		score[5].Draw_Anime(ValueData % 10);
	}

	else if (ValueData >= 10000 && ValueData <= 99999) {
		score[0].Draw_Anime(ValueData / 10000);
		score[1].Draw_Anime((ValueData / 1000) % 10);
		score[2].Draw_Anime((ValueData / 100) % 10);
		score[3].Draw_Anime((ValueData / 10) % 10);
		score[4].Draw_Anime(ValueData % 10);
	}

	else if (ValueData >= 1000 && ValueData <= 9999) {
		score[0].Draw_Anime(ValueData / 1000);
		score[1].Draw_Anime((ValueData / 100) % 10);
		score[2].Draw_Anime((ValueData / 10) % 10);
		score[3].Draw_Anime(ValueData % 10);
	}
	
	else if (ValueData >= 100&& ValueData <= 999) {
		score[0].Draw_Anime(ValueData / 100);
		score[1].Draw_Anime((ValueData / 10) % 10);
		score[2].Draw_Anime(ValueData % 10);
	}

	else if (ValueData <= 99) {
		score[0].Draw_Anime(ValueData / 10);
		score[1].Draw_Anime(ValueData % 10);
	}

	//ランキングボード
	UI[0].Draw();
	UI[1].Draw();
	UI[2].Draw();
	UI[3].Draw();
	UI[4].Draw();
	UI[5].Draw();
	UI[6].Draw();


	if (DrawFlag == true)
	{
		//+ボタンでタイトルに戻るの描画
		UI[7].Draw();
	}


}

//スコアの表示
void ResultScore::ScoreCreate(int value,float posX,float posY)
{
	ValueData = value;

	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		score[i].LoadTexture(TextureDict["all"], 10, 4, 3, 280 / 4, 280 / 4);
		score[i].Object.Pos = D3DXVECTOR2(posX + (i*(280 / 4 - 40)), posY);
		score[i].Object.Scale.x = 0.6f;
		score[i].Object.Scale.y = 0.6f;

	}
}

void ResultScore::ScoreCreate(int value, float posX, float posY,float ScaleX,float ScaleY)
{
	ValueData = value;

	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		score[i].LoadTexture(TextureDict["all"], 10, 4, 3, 280 / 4, 280 / 4);
		score[i].Object.Pos = D3DXVECTOR2(posX + (i*(280 / 4 - 20)), posY);
		score[i].Object.Scale.x = ScaleX;
		score[i].Object.Scale.y = ScaleY;

	}
}

void ResultScore::ScoreCreate(int value, float posX, float posY, float ScaleX, float ScaleY,double Rotate)
{
	ValueData = value;

	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		score[i].LoadTexture(TextureDict["all"], 10, 4, 3, 280 / 4, 280 / 4);
		score[i].Object.Pos = D3DXVECTOR2(posX + (i*(280 / 4 - 20)), posY);
		score[i].Object.Scale.x = ScaleX;
		score[i].Object.Scale.y = ScaleY;
		score[i].Object.Rotate = Rotate;

	}
}