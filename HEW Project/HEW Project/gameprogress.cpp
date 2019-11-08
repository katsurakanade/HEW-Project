/*------------------------------------------------------------------
@brief	ゲームの進行バー
@author	萩原直之
@date	2019/11/07
-------------------------------------------------------------------*/

#include "gameprogress.h"
#include "GameObject.h"
#include "scene.h"
#include "main.h"
#include <time.h>

GameObject ProgressObj;

GameProgress::GameProgress()
{
	stime = SECONDS;
	ProgressObj.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);
}

GameProgress::~GameProgress()
{

}

void GameProgress::Update()
{
	stime++;
	if (stime > 300) //5秒経ったら
	{
		Scene_Change(SCENE_INDEX_TITLE);
		//初期化
		stime = 0;
	}
	
}

void GameProgress::Draw()
{
	//デバック用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "経過:%d秒",  stime/60);
	ProgressObj.Draw(100, 100);

}
