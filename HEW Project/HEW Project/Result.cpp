#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include "GameData.h"
#include "GameObject.h"
#include <DxLib.h>

static GameObject obj[1];

void Init_Result()
{

	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_RESULT]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.0f;
	obj[0].Object.Scale.y = 1.0f;

}

void Uninit_Result()
{

}

void Update_Result()
{
	int TotalScore;

	int Distance_p = gamedata.GetRunningDistance();

	int Action_p = gamedata.GetActionPoint();

	TotalScore = Distance_p + Action_p;

	DrawFormatString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , GetColor(255, 255, 255), "çáåv:%d", TotalScore);


	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result()
{

	obj[0].Draw();
}



