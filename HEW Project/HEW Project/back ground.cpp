#include <algorithm>
#include <vector>
#include "gameprogress.h"
#include "GameObject.h"
#include "input.h"
#include "scene.h"
#include "main.h"
#include "DxLib.h"
#include <time.h>
#include "back ground.h"



static GameObject obj[1];
static int GameFrame;




void BACK_GROUND::BACK_GROUND_Init()
{
	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_LUOTIANYI]);

	//ゲーム内のフレームを[SECONDS]の数値に初期化した
	GameFrame = SECONDS;

	GameFrame_pos = 0.0;
	

	GameFrame_spd = 3.0;
	


}


void BACK_GROUND::BACK_GROUND_Update()
{
	GameFrame_pos++;

	if (GameFrame_pos > 100)
	{
		GameFrame_pos--;

	}

}

void BACK_GROUND::BACK_GROUND_Draw()
{
	//デバック用
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "経過:%d秒", stime / 60);


}