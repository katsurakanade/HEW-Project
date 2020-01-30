#include <algorithm>
#include <vector>
#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "GameData.h"
#include "Live2D.h"
#include "GameClear.h"
#include "back ground.h"

static GameClear gameclear;
static GameObject clear[3];

void GameClear::Init()
{
	objflag = false;

	clear[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BACKGROUND]);
	clear[0].Object.Pos.x = SCREEN_WIDTH / 2;
	clear[0].Object.Pos.y = SCREEN_HEIGHT / 2;
	clear[0].Object.Scale.x = 1.00f;
	clear[0].Object.Scale.y = 1.00f;

	clear[1].LoadTexture(TextureDict["alphabg"]);
	clear[1].Object.Pos.x = 0;
	clear[1].Object.Pos.y = 0;
	clear[1].Object.Scale.x = 10.0f;
	clear[1].Object.Scale.y = 10.0f;


	clear[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAME_CLEAR]);
	clear[2].Object.Pos.x = SCREEN_WIDTH / 2;
	clear[2].Object.Pos.y = SCREEN_HEIGHT/2;
	clear[2].Object.Scale.x = 1.0f;
	clear[2].Object.Scale.y = 1.0f;

	TimeCount = 0.0f;
}


void Init_GameClear()
{
	gameclear.Init();
}

GameClear::~GameClear()
{
}


void GameClear::Update()
{
	//ゲームクリアテクスチャの表示
	objflag = true;
	TimeCount++;
	if (TimeCount >= 180)
	{
		// リザルト画面にシーン遷移
		if (keyboard.IsPress(DIK_RETURN) || joycon[0].IsPress(JOYCON_MIN)) {
			Scene_Change(SCENE_INDEX_RESULT);
			objflag = false;

		}

	}

}


void GameClear::Draw()
{
	if (objflag == true)
	{
		clear[0].Draw();
		clear[1].Draw();
		clear[2].Draw();


	}
}

