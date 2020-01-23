
#include <algorithm>
#include <vector>
#include "title.h"
#include "scene.h"
#include "input.h"
#include  "main.h"
#include "DxLib.h"
#include "Live2D.h"
#include "GameObject.h"
#include "Menu.h"
#include "ActionUI.h"
#include "ActionSlot.h"
#include "GameData.h"
#define DEBUG

using namespace std;
static bool g_bEnd = false;

Live2D Hiyori;

Menu TitleMenu(3);

GameObject Background;

void Init_Title() {

	Hiyori.LoadModel(Live2D_Dict["HIYORI"]);

	Hiyori.Zoom.x = 3.0f;
	Hiyori.Zoom.y = 3.0f;
	Hiyori.Pos.x = -300.0f;
	Hiyori.Pos.y = -450.0f;
	
	TitleMenu.Pos.x = 700.0f;
	TitleMenu.Pos.y = 100.0f;
	TitleMenu.FontSize = 64.0f;

	TitleMenu.SelectText.push_back("スタート");
	TitleMenu.SelectText.push_back("チュートリアル");
	TitleMenu.SelectText.push_back("終了");
	
	Background.Object.Pos.x = 640.0f;
	Background.Object.Pos.y = 360.0f;
	Background.LoadTexture(TextureDict["Title"]);

	g_bEnd = false;

}

void Uninit_Title() {

	Hiyori.~Live2D();

}

void Update_Title() {

	Hiyori.SetMontionIndex(GetRand(8));


	/*
	TitleMenu.Update();

	switch (TitleMenu.GetSelectNow())
	{
	case 0:
		if (keyboard.IsPress(DIK_RETURN) || joycon[LEFT_JOYCON].IsPress(JOYCON_L)) {
			Scene_Change(SCENE_INDEX_GAME);
		}
		break;
	case 1:
		break;
	case 2:
		if (keyboard.IsPress(DIK_RETURN) || joycon[LEFT_JOYCON].IsPress(JOYCON_L)) {
			exit(1);
		}
		break;
	default:
		break;
	}
	*/

	if (joycon[0].IsPress(JOYCON_MIN)) {
		Scene_Change(SCENE_INDEX_GAME);
		gamedata.SetGameMode(GAMEMODE_MATCH);
	}

	if (joycon[1].IsPress(JOYCON_PLUS)) {
		Scene_Change(SCENE_INDEX_GAME);
		gamedata.SetGameMode(GAMEMODE_SINGLE);
	}

#ifdef DEBUG
	if (keyboard.IsTrigger(DIK_Z)) {
		Scene_Change(SCENE_INDEX_TUTORIAL);
		gamedata.SetGameMode(GAMEMODE_MATCH);
	}

	if (keyboard.IsTrigger(DIK_X)) {
		Scene_Change(SCENE_INDEX_GAME);
		gamedata.SetGameMode(GAMEMODE_SINGLE);
	}

#endif // DEBUG


}

void Draw_Title() {

	Background.Draw();

	//Hiyori.Draw();

	//TitleMenu.Draw();

}