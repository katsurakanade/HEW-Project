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
#include "GameData.h"

using namespace std;

std::vector<int>  Array;

Live2D Hiyori;

Menu TitleMenu(3);

ActionUI Action;

GameObject Success;

GameObject Failed;

GameObject test;

GameData gamedata;

static int acount;

static int bcount;

void Init_Title() {

	Hiyori.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);
	Success.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_SUCCESS]);
	Failed.LoadTexture(TexturePassDict[TEXTURE_INDEX_ACTION_FAILED]);
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

	gamedata.UpdateSpeed();

	if (TitleMenu.GetSelectNow() == 0 &&  keyboard.IsTrigger(DIK_RETURN)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	if (TitleMenu.GetSelectNow() == 2 && keyboard.IsTrigger(DIK_RETURN)) {
		exit(1);
	}
	 
	 if (joycon[1].GetGyro_Y() > 150) {
		 joycon[1].Action_Judge[0] = true;
		 Array.push_back(joycon[1].GetGyro_Y());
	 }

	 if (joycon[1].Action_Judge[0] && joycon[1].GetGyro_Y() < -200) {
		 joycon[1].Action_Judge[1] = true;
	 }

	 if (joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].GetGyro_Y() > 150) {
		 joycon[1].Action_Judge[2] = true;
	 }

	 if ((joycon[1].Action_Judge[0] && joycon[1].Action_Judge[1] && joycon[1].Action_Judge[2]) ){
		 for (int i = 0; i < 3; i++) {
			 joycon[1].Action_Judge[i] = false;
		 }
		vector<int>::iterator iter = max_element(Array.begin(),Array.end());
		acount = *iter;
		bcount += acount;

		if (bcount > 1000) {
			gamedata.AddRunningDistance(gamedata.GetRunningSpeed());
			bcount = 0;
		}

		gamedata.SetRunningSpeed(405);

		Array.clear();
	}
	
	 if (gamedata.GetRunningSpeed() > 0) {
		 gamedata.AddRunningSpeed(-15);
	 }

		gamedata.AddRunningDistance(gamedata.GetRunningSpeed());

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


}

void Draw_Title() {

	Hiyori.Draw();

	Action.Draw();

	TitleMenu.Draw();

	if (Action.GetFinishFlag()) {
		if (Action.GetProgress() == 4) {
			Success.Draw(0, 0, 256, 256, TRUE);
		}
		else {
			Failed.Draw(0, 0, 256, 256, TRUE);
		}
	}

	SetFontSize(28);
	DrawFormatString(700, 400, (255, 255, 255), "Speed : %d", gamedata.GetRunningSpeed());
	DrawFormatString(700, 450, (255, 255, 255), "Distance : %d", gamedata.GetRunningMeter());
	DrawFormatString(700, 500, (255, 255, 255), "Hp : %d", gamedata.Gethp());

	//DrawFormatString(700, 550, (255, 255, 255), "%d", joycon[1].Action_Judge[0]);
	//DrawFormatString(700, 600, (255, 255, 255), "%d", joycon[1].Action_Judge[1]);
	//DrawFormatString(700, 650, (255, 255, 255), "%d", joycon[1].Action_Judge[2]);
	//DrawFormatString(800, 650, (255, 255, 255), "%d", bcount);

	//test.Draw(0, 0);
}