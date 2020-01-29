
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

///Live2D Hiyori;

Menu TitleMenu(3);

GameObject Background;
GameObject Alpha;
static GameObject Logo;
static GameObject GameStart;

void Init_Title() {

	///Hiyori.LoadModel(Live2D_Dict["HIYORI"]);

	///Hiyori.Zoom.x = 3.0f;
	///Hiyori.Zoom.y = 3.0f;
	///Hiyori.Pos.x = -300.0f;
	///Hiyori.Pos.y = -450.0f;
	///////////////////////////////////////////////////////////////////
	TitleMenu.Pos.x = 700.0f;
	TitleMenu.Pos.y = 100.0f;
	TitleMenu.FontSize = 64.0f;

	TitleMenu.SelectText.push_back("�X�^�[�g");
	TitleMenu.SelectText.push_back("�`���[�g���A��");
	TitleMenu.SelectText.push_back("�I��");
	///////////////////////////////////////////////////////////////////

	// �w�i�e�N�X�`�����[�h
	Background.Object.Pos.x = 640.0f;
	Background.Object.Pos.y = 360.0f;
	Background.Object.Scale = { 0.7f, 0.7f };
	Background.LoadTexture(TextureDict["Title_BG"]);

	// �G�N�Z�����g���[�h�̔������̃e�N�X�`��������
	Alpha.Object.Pos = {640.0f, 360.0f};
	Alpha.Object.Scale = {1.0f, 1.0f};
	Alpha.LoadTexture(TextureDict["alphabg"]);

	// �^�C�g�����S�e�N�X�`�����[�h
	Logo.Object.Pos.x = 620.0f;
	Logo.Object.Pos.y = 360.0f;
	Logo.Object.Scale = { 0.3f, 0.3f };
	Logo.LoadTexture(TextureDict["Title_Logo"]);
	
	// �Q�[���X�^�[�g�e�N�X�`�����[�h
	GameStart.Object.Pos.x = 640.0f;
	GameStart.Object.Pos.y = 640.0f;
	GameStart.Object.Scale = { 0.23f, 0.23f };
	GameStart.LoadTexture(TextureDict["Title_GameStart"]);


	g_bEnd = false;

}

void Uninit_Title() {

	///Hiyori.~Live2D();

}

void Update_Title() {

	///Hiyori.SetMontionIndex(GetRand(8));


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

	Alpha.Draw();

	Logo.Draw();

	GameStart.Draw();

	//Hiyori.Draw();

	//TitleMenu.Draw();

}