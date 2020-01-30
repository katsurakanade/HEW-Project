#include <algorithm>
#include <vector>
#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "ActionSlot.h"
#include "ActionUI.h"
#include "GameData.h"
#include "Live2D.h"
#include "GameOver.h"
#include "BackGround.h"
#include "gameprogress.h"

static GameOver gameOver;
static GameObject obj[2];


static GameProgress progress;

GameOver::GameOver() 
{

}

GameOver::~GameOver()
{
}

void Init_GameOver()
{
	gameOver.Init();
}


void GameOver::Init() 
{

	obj[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAME_OVER]);
	obj[0].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	obj[0].Object.Scale.x = 1.5;
	obj[0].Object.Scale.y = 1.5;

	obj[1].LoadTexture(TextureDict["push_minus_title"]);
	obj[1].Object.Pos.x = SCREEN_WIDTH / 2;
	obj[1].Object.Pos.y = SCREEN_HEIGHT / 2 + 200;
	obj[1].Object.Scale.x = 1.0f;
	obj[1].Object.Scale.y = 1.0f;


	titleflag = false;
	TimeCount = SECONDS;
	objflag = false;
}


void GameOver::Uninit()
{
}

void GameOver::Update()
{
	GameOverisUse();
}

void GameOver::Draw() 
{
	if (TimeCount >= 1.0f)
	{
		obj[0].Draw();

	}
	//タイトルへ戻るの表示
	if (objflag == true)
	{
		obj[1].Draw();

	}
}

/*
bool GameOver::GetisUse()
{
	return isUse;
}
*/

void GameOver::GameOverisUse()
{

	if (gamedata.Gethp() == 0)
	{
		//ゲームオーバーステートに入る
		TimeCount++;
		titleflag = true;

		//ゲームオーバーテクスチャの表示

		if (TimeCount >= 120.0f)
		{
			objflag = true;

			if (TimeCount >= 170.0f)
			{
				TimeCount = 70.0f;
				objflag = false;
			}

		}
		if (titleflag == true && keyboard.IsTrigger(DIK_Z)|| titleflag == true && joycon[0].IsPress(JOYCON_MIN)) {
			Scene_Change(SCENE_INDEX_TITLE);

		}

	}

}
