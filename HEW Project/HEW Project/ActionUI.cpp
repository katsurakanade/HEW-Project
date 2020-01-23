// 23100 アクションUI

#include "input.h"
#include <vector>
#include <algorithm>
#include "ActionUI.h"
#include "GameObject.h"

using namespace std;

// 上下アクション判定基準 (Change All)
static const int ACTION_UP_JUDGE = -150;

// トランポリン
vector <const char *> TRAMPOLINING_PASS;
// バランスボード
vector <const char*>	 BALANCEBOARD_PASS;
// ハードル
//vector <const char*> HURDLE_PASS;

vector <const char*>  LONG_JUMP_PASS;
// 重量挙げ
vector <const char*>  WEIGHT_PASS;
// 段違い平行棒
vector <const char*>  UNEVENBARS_PASS;

ActionUI::ActionUI()
{
	
}

ActionUI::~ActionUI()
{
	Action_vector.clear();
	vector<GameObject>().swap(Action_vector);
}

int* ActionUI::getRandNR(int min, int max, int num) {
	int tol = max - min + 1;
	int a[30000];
	static int b[30000];
	int i, j;
	for (i = 0; i < tol; i++) {
		*(a + i) = min + i;
	}
	srand(time(0));
	int ctr;
	for (i = 0; i < num; i++) {
		ctr = rand() % (tol - i);
		b[i] = a[ctr];
		for (j = ctr; j < (tol - 1 - i); j++) {
			a[j] = a[j + 1];
		}
	}
	return b;
}

void ActionUI::Init() {

	//State = ACTION_STATE_LONGJUMP;
	State_Switch = true;
	progress = 0;
	Finish_Flag = false;
	UNEVENBARS_rnd = GetRand(1);

	// トランポリン
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SL]);
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SR]);
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_HANDUP]);

	// バランスボード
	BALANCEBOARD_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SL]);
	BALANCEBOARD_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SR]);

	// ハードル
	//HURDLE_PASS.push_back(TexturePassDict[TEXTURE_INDEX_UP]);
	//HURDLE_PASS.push_back(TexturePassDict[TEXTURE_INDEX_ZL]);

	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_HANDUP]);

	// 重量挙げ
	WEIGHT_PASS.push_back(TexturePassDict[TEXTURE_INDEX_HANDUP]);
	WEIGHT_PASS.push_back(TexturePassDict[TEXTURE_INDEX_LEFT]);
	WEIGHT_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	WEIGHT_PASS.push_back(TexturePassDict[TEXTURE_INDEX_HANDDOWN]);

	// 段違い平行棒
	UNEVENBARS_PASS.push_back(TexturePassDict[TEXTURE_INDEX_ROTATE]);
	UNEVENBARS_PASS.push_back(TexturePassDict[TEXTURE_INDEX_LEFT]);
	UNEVENBARS_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);

	Action_vector.clear();

}

void ActionUI::Update() {

	if (State_Switch) {

		switch (State)
		{

		case ACTION_STATE_LONGJUMP:
			for (int i = 0; i < 4; i++) {
				onetime[i].LoadTexture(LONG_JUMP_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;

			// トランポリン
		case ACTION_STATE_TRAMPOLINING:
			for (int i = 0; i < 3; i++) {
				onetime[i].LoadTexture(TRAMPOLINING_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;
			// バランスボード
		case ACTION_STATE_BALANCEBOARD:
			for (int i = 0; i < 2; i++) {
				onetime[i].LoadTexture(BALANCEBOARD_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;
			// ハードル
			/*
		case ACTION_STATE_HURDLE:
			for (int i = 0; i < 2; i++) {
				onetime[i].LoadTexture(HURDLE_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;
			*/
		
			// 重量挙げ
		case ACTION_STATE_WEIGHT:
			for (int i = 0; i < 4; i++) {
				onetime[i].LoadTexture(WEIGHT_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;

		case ACTION_STATE_UNEVENBARS:
			onetime[0].LoadTexture(UNEVENBARS_PASS[0]);
			Action_vector.push_back(onetime[0]);

			if (UNEVENBARS_rnd == 0){
				onetime[1].LoadTexture(UNEVENBARS_PASS[1]);
				Action_vector.push_back(onetime[1]);
			}
			else if (UNEVENBARS_rnd == 1) {
				onetime[1].LoadTexture(UNEVENBARS_PASS[2]);
				Action_vector.push_back(onetime[1]);
			}

			break;
		}

		State_Switch = false;
	}

	if (!Finish_Flag) {
		switch (State)
		{			
			// トランポリン
		case ACTION_STATE_TRAMPOLINING:
			if (joycon[LEFT_JOYCON].IsTrigger(JOYCON_SL_LEFT)) {
				Action_vector[0].Gauss_Filter(500);
			}
			if (joycon[LEFT_JOYCON].IsTrigger(JOYCON_SR_LEFT)) {
				Action_vector[1].Gauss_Filter(500);
			}
			if (joycon[LEFT_JOYCON].GetGyro_X() < ACTION_UP_JUDGE) {
				if (joycon[LEFT_JOYCON].GetOldState() == (JOYCON_SL_LEFT + JOYCON_SR_LEFT) || 
					joycon[LEFT_JOYCON].GetOldState() == (JOYCON_SL_LEFT + JOYCON_SR_LEFT + JOYCON_L)) {
					Action_vector[2].Gauss_Filter(500);
					progress = 3;
					Finish_Flag = true;
				}
			}
			break;
			// バランスボード
		case ACTION_STATE_BALANCEBOARD:
			// Failed
			if (joycon[LEFT_JOYCON].GetGyro_Y() < ACTION_UP_JUDGE || joycon[LEFT_JOYCON].GetGyro_Y() > -ACTION_UP_JUDGE) {
				Finish_Flag = true;
			}
			if (joycon[LEFT_JOYCON].IsTrigger(JOYCON_SL_LEFT)) {
				Action_vector[0].Gauss_Filter(500);
				progress++;
			}
			if (joycon[LEFT_JOYCON].IsTrigger(JOYCON_SR_LEFT)) {
				Action_vector[1].Gauss_Filter(500);
				progress++;
			}
			if (progress >= 2) {
				Finish_Flag = true;
			}

			break;

			// ハードル
			/*
		case ACTION_STATE_HURDLE:

			if (progress == 0 && joycon[LEFT_JOYCON].GetGyro_X() < ACTION_UP_JUDGE) {
				Action_vector[0].Gauss_Filter(500);
				progress++;
			}

			if (progress == 1 && joycon[LEFT_JOYCON].IsTrigger(JOYCON_ZL)) {
				Action_vector[1].Gauss_Filter(500);
				progress++;

			}

			if (progress >= 2) {
				Finish_Flag = true;
			}

			break;
			*/

		case ACTION_STATE_LONGJUMP:
			switch (progress)
			{
			case 0:
				if (joycon[0].IsTrigger(JOYCON_RIGHT) || keyboard.IsTrigger(DIK_RIGHTARROW)) {
					progress++;
					Action_vector[0].Gauss_Filter(500);
				}
				else if (joycon[0].GetTrigger() != NULL && !joycon[0].IsTrigger(JOYCON_RIGHT)) {
					Finish_Flag = true;
				}
				else if (joycon[0].GetGyro_Y() > 300) {
					Finish_Flag = true;
				}
				break;
			case 1:
				if (joycon[0].IsTrigger(JOYCON_RIGHT) || keyboard.IsTrigger(DIK_RIGHTARROW)) {
					progress++;
					Action_vector[1].Gauss_Filter(500);
				}
				else if (joycon[0].GetTrigger() != NULL && !joycon[0].IsTrigger(JOYCON_RIGHT)) {
					Finish_Flag = true;
				}
				else if (joycon[0].GetGyro_Y() > 300) {
					Finish_Flag = true;
				}
				break;
			case 2:
				if (joycon[0].IsTrigger(JOYCON_RIGHT) || keyboard.IsTrigger(DIK_RIGHTARROW)) {
					progress++;
					Action_vector[2].Gauss_Filter(500);
				}
				else if (joycon[0].GetTrigger() != NULL && !joycon[0].IsTrigger(JOYCON_RIGHT)) {
					Finish_Flag = true;
				}
				else if (joycon[0].GetGyro_Y() > 300) {
					Finish_Flag = true;
				}
				break;
			case 3:
				if (joycon[0].GetGyro_Y() > 300 || keyboard.IsTrigger(DIK_UPARROW)) {
					progress++;
					Action_vector[3].Gauss_Filter(500);
				}
				else if (joycon[0].GetTrigger() != NULL) {
					Finish_Flag = true;
				}
				break;
			case 4:
				Finish_Flag = true;
				break;
			
			}
			break;

			// 重量挙げ
		case ACTION_STATE_WEIGHT:

			if (progress == 0 && joycon[0].GetGyro_X() < -300) {
				progress++;
				Action_vector[0].Gauss_Filter(500);
			}

			if (progress == 1) {

				if (joycon[0].GetOldState() == (JOYCON_UP + JOYCON_DOWN) || joycon[0].GetOldState() == (JOYCON_UP + JOYCON_DOWN + JOYCON_L)) {
					progress++;
					Action_vector[1].Gauss_Filter(500);
					Action_vector[2].Gauss_Filter(500);
				}
			}

			if (progress == 2 && joycon[0].GetGyro_X() > 300) {
				progress++;
				Finish_Flag = true;
			}

			if (progress == 1) {
				if (joycon[0].GetGyro_X() > 300) {
					Finish_Flag = true;
				}
			}
			break;

			// 段違い平行棒
		case ACTION_STATE_UNEVENBARS:
			
			if (joycon[0].IsPress(JOYCON_STICK_LEFT)) {
				UNEVENBARS_Array[0] = true;
			}

			if (joycon[0].IsPress(JOYCON_STICK_RIGHT)) {
				UNEVENBARS_Array[1] = true;
			}

			if (joycon[0].IsPress(JOYCON_STICK_UP)) {
				UNEVENBARS_Array[2] = true;
			}

			if (joycon[0].IsPress(JOYCON_STICK_DOWN)) {
				UNEVENBARS_Array[3] = true;
			}
			
			if (UNEVENBARS_Array[0] == true && UNEVENBARS_Array[1] == true && UNEVENBARS_Array[2] == true && UNEVENBARS_Array[3] == true) {
				if (progress == 0) {
					Action_vector[0].Gauss_Filter(500);
					progress++;	
				}
			}

			if (progress == 1) {

				if (UNEVENBARS_rnd == 0) {

					if (joycon[0].IsPress(JOYCON_UP)) {
						progress++;
						Action_vector[1].Gauss_Filter(500);
						Finish_Flag = true;
					}

					else if (joycon[0].IsPress(JOYCON_DOWN)) {
						Finish_Flag = true;
					}
				}

				else if (UNEVENBARS_rnd == 1) {
					if (joycon[0].IsPress(JOYCON_DOWN)) {
						progress++;
						Action_vector[1].Gauss_Filter(500);
						Finish_Flag = true;
					}

					else if (joycon[0].IsPress(JOYCON_UP)) {
						Finish_Flag = true;
					}
				}

			}

			break;
		}
	}
	
	if (Finish_Flag) {
		State_Switch_Timer += SECONDS;
	}

	if (State_Switch_Timer  >= 0.2f) {
		ResetAll();
	}

}

void ActionUI::Draw() {

	for (int i = 0; i < Action_vector.size(); i++) {
		Action_vector[i].Object.Pos.x = Pos.x + (Interval.x * i);
		Action_vector[i].Object.Pos.y = Pos.y + (Interval.y * i);
		Action_vector[i].Draw();
	}

	// if ex

}

void ActionUI::Reset_Vector() {
	Action_vector.clear();
}

void ActionUI::SetState(int n) {
	State = n;
}

void ActionUI::SetStateSwitch(bool n) {
	State_Switch = n;
}

int ActionUI::GetState() {
	return State;
}

bool ActionUI::GetStateSwitch() {
	return State_Switch;
}

int ActionUI::GetProgress() {
	return progress;
}

bool ActionUI::GetFinishFlag() {
	return Finish_Flag;
}

int ActionUI::GetActionAmount() {
	return Action_vector.size();
}

void ActionUI::ResetAll() {
	progress = 0;
	for (int i = 0; i < 4; i++) {
		UNEVENBARS_Array[i] = false;
	}
	UNEVENBARS_rnd = GetRand(1);
	State_Switch = true;
	State_Switch_Timer = 0.0f;
	Finish_Flag = false;
	Reset_Vector();
}