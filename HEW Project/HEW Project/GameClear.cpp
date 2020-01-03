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
#include "GameClear.h"

static GameClear gameclear;
static GameObject clear[1];

void GameClear::Init()
{
	objflag = false;
	clear[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAME_CLEAR]);
	clear[0].Object.Pos.x = SCREEN_WIDTH / 2;
	clear[0].Object.Pos.y = 100.0f;
	clear[0].Object.Scale.x = 1.0f;
	clear[0].Object.Scale.y = 1.0f;

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
		if (keyboard.IsPress(DIK_RETURN) || joycon[LEFT_JOYCON].IsPress(JOYCON_L)) {
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
	}
}

