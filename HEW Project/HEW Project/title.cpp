#include <algorithm>
#include <vector>
#include "title.h"
#include "scene.h"
#include "input.h"
#include "IMGUI/imgui.h"
#include  "main.h"
#include "DxLib.h"
#include "Live2D.h"
#include "GameObject.h"
#include "Menu.h"

using namespace std;

int x;
int y;

static bool ShowDemoWindow = true;

static int acount ;

static int bcount;

static bool SameFlag;

std::vector<int>  Array;

Live2D Hiyori;

Menu TitleMenu(2);

void Init_Title() {

	Hiyori.LoadModel(Live2DModelPassDict[LIVE2D_INDEX_HIYORI]);

	Hiyori.Zoom.x = 3.0f;
	Hiyori.Zoom.y = 3.0f;
	Hiyori.Pos.x = -400.0f;
	Hiyori.Pos.y = -500.0f;
	
	TitleMenu.Pos.x = 700.0f;
	TitleMenu.Pos.y = 100.0f;
	TitleMenu.FontSize = 64.0f;

	TitleMenu.SelectText.push_back("スタート");
	TitleMenu.SelectText.push_back("終了");
}

void Uninit_Title() {

	Hiyori.~Live2D();

}

void Update_Title() {

	Hiyori.SetMontionIndex(GetRand(8));

	TitleMenu.Update();

	if (TitleMenu.GetSelectNow() == 0 &&  keyboard.IsTrigger(DIK_RETURN)) {
		Scene_Change(SCENE_INDEX_GAME);
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

	// Debug Window
	/*
	ImGui::Begin("Debug Window");
	ImGui::SetWindowSize(ImVec2(300.0f, 400.0f), 0);
	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), 0);
	ImGui::Text("LeftGyro : %d", joycon[0].GetGyro_X());
	ImGui::Text("RightGyro: %d", joycon[1].GetGyro_X());
	ImGui::Text("Count : %d", acount);
	ImGui::Text("CountB : %d", bcount);
	ImGui::Text("LEFT Old State : %d", joycon[0].GetOldState());
	ImGui::Text("RIGHT Old State : %d", joycon[1].GetOldState());
	ImGui::Checkbox("Up", &joycon[0].Action_Judge[0]);
	ImGui::Checkbox("Down", &joycon[0].Action_Judge[1]);
	ImGui::Checkbox("Up2", &joycon[0].Action_Judge[2]);
	ImGui::Checkbox("Same", &SameFlag);
	ImGui::End();
	*/

	if (joycon[0].GetOldState() == JOYCON_L && joycon[1].GetOldState() == JOYCON_R) {
		SameFlag = true;
	}

	if (joycon[0].IsTrigger(JOYCON_SCREENSHOT)) {
		SameFlag = false;
	}

	if (keyboard.IsTrigger(DIK_Z)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

}

void Draw_Title() {

	Hiyori.Draw();

	TitleMenu.Draw();

	DrawFormatString(700, 500, (255,255,255), "%d", TitleMenu.GetSelectNow());
}