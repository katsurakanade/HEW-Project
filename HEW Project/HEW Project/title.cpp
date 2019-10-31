#include <algorithm>
#include <vector>
#include "title.h"
#include "scene.h"
#include "input.h"
#include "texture.h"
#include "IMGUI/imgui.h"
#include  "main.h"
#include "DxLib.h"
#include "texture.h"


using namespace std;

int x;
int y;

static bool ShowDemoWindow = true;

static int acount ;

static int bcount;

static bool SameFlag;

std::vector<int>  Array;

Texture a;

int model;

void Init_Title() {

	a.Load(TexturePassDict[TEXTURE_INDEX_START]);


	model = Live2D_LoadModel("C:/Users/katsu/Desktop/CubismSdkForNative-4-beta.1/Samples/Res/Haru/Haru.model3.json");

	Live2D_Model_SetTranslate(model, -300, 0);
	Live2D_Model_SetExtendRate(model, 1, 1);
}

void Uninit_Title() {
	Live2D_DeleteModel(model);
}

void Update_Title() {

	if (Live2D_Model_IsMotionFinished(model)) {
		Live2D_Model_StartMotion(model, "Idle", GetRand(8));
	}

	Live2D_Model_Update(model, SECONDS);

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

	//main->Draw(Menu_TextureArray, 500 + x, 400 + y, 150, 256, 128);	

	a.Draw(0,0,200,80,false);

	Live2D_RenderBegin();

	Live2D_Model_Draw(model);

	Live2D_RenderEnd();
}