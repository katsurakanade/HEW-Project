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
	UI[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_PUSH_PLUS_TITLE]);
	UI[0].Object.Pos.x = SCREEN_WIDTH - 150;
	UI[0].Object.Pos.y = SCREEN_HEIGHT - 100;
	UI[0].Object.Scale.x = 1.0f;
	UI[0].Object.Scale.y = 1.0f;
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
	if (DrawFlag == true)
	{
		//+ボタンでタイトルに戻る
		UI[0].Draw();
	}


}

//スコアの表示
void ResultScore::ScoreCreate(int value,float posX,float posY)
{
	ValueData = value;

	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		score[i].LoadTexture(TexturePassDict[TEXTURE_INDEX_NUMBER], 10, 4, 4, 300 / 4, 300 / 4);
		score[i].Object.Pos = D3DXVECTOR2(posX + (i*(300 / 4)), posY);
	}
}