// 21000 タイトル画面

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

using namespace std;

int x;
int y;

static bool ShowDemoWindow = true;

static int acount ;

static int bcount;

static bool SameFlag;

std::vector<int>  Array;

Live2D Hiyori;

Menu TitleMenu(3);

ActionUI Action;

GameObject Success;

GameObject test;

void Init_Title() {

	Hiyori.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);
	Success.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);
	test.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);

	Hiyori.Zoom.x = 3.0f;
	Hiyori.Zoom.y = 3.0f;
	Hiyori.Pos.x = -400.0f;
	Hiyori.Pos.y = -500.0f;
	
	TitleMenu.Pos.x = 700.0f;
	TitleMenu.Pos.y = 100.0f;
	TitleMenu.FontSize = 64.0f;

	TitleMenu.SelectText.push_back("スタート");
	TitleMenu.SelectText.push_back("チュートリアル");
	TitleMenu.SelectText.push_back("終了");

	Action.Pos.x = 500;
	Action.Pos.y = 600;
	Action.Interval.x = 150;
	Action.Interval.y = 0;

}

void Uninit_Title() {

	Hiyori.~Live2D();

}

void Update_Title() {

	Hiyori.SetMontionIndex(GetRand(8));

	TitleMenu.Update();

	Action.Update();

	if (TitleMenu.GetSelectNow() == 0 &&  keyboard.IsTrigger(DIK_RETURN)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	if (TitleMenu.GetSelectNow() == 2 && keyboard.IsTrigger(DIK_RETURN)) {
		exit(1);
	}
	
	/*
	 x += (joycon[0].GetGyro_X() / 20);
     y += (joycon[0].GetGyro_Y() / 20);
	 
	 if (joycon[0].GetGyro_Y() > 150) {
		 joycon[0].Action_Judge[0] = true;
		 Array.push_back(joycon[0].GetGyro_Y());
	 }

	 if (joycon[0].Action_Judge[0] && joycon[0].GetGyro_Y() < -200) {
		 joycon[0].Action_Judge[1] = true;
	 }

	 if (joycon[0].Action_Judge[0] && joycon[0].Action_Judge[1] && joycon[0].GetGyro_Y() > 150) {
		 joycon[0].Action_Judge[2] = true;
	 }

	 if ((joycon[0].Action_Judge[0] && joycon[0].Action_Judge[1] && joycon[0].Action_Judge[2]) ){
		 for (int i = 0; i < 3; i++) {
			 joycon[0].Action_Judge[i] = false;
		 }
		 vector<int>::iterator iter = max_element(Array.begin(),Array.end());
		 bcount = *iter;
		 acount += bcount;
		 Array.clear();
	}
	*/

	/*
	if (joycon[0].GetOldState() == JOYCON_L && joycon[1].GetOldState() == JOYCON_R) {
		SameFlag = true;
	}

	if (joycon[0].IsTrigger(JOYCON_SCREENSHOT)) {
		SameFlag = false;
	}
	*/

	if (keyboard.IsTrigger(DIK_Z)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	if (keyboard.IsTrigger(DIK_L)) {
		Action.SetStateSwitch(true);
		Action.Reset_Vector();
	}

	if (keyboard.IsTrigger(DIK_1)) {
		Action.SetState(0);
	}

	if (keyboard.IsTrigger(DIK_2)) {
		Action.SetState(1);
	}
	
	if (keyboard.IsTrigger(DIK_G)) {
		for (int i = 0; i < 50; i++) {
			LoadGraph(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);
		}
	}

}

void Draw_Title() {

	Hiyori.Draw();

	Action.Draw();

	TitleMenu.Draw();

	if (Action.GetFinishFlag()) {
		Success.Draw(0, 0, 256, 256, TRUE);
	}

	//DrawString(0, 0, "Now Loading", (255, 255, 255));
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "非同期読み込みの数 %d", GetASyncLoadNum());


	//test.Draw(0, 0);
}