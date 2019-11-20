// 23100 アクションUI

#include "input.h"
#include <vector>
#include <algorithm>
#include "ActionUI.h"
#include "GameObject.h"

using namespace std;

// トランポリン
vector <const char *> TRAMPOLINING_PASS;
// バランスボード
vector <const char*>	 BALANCEBOARD_PASS;

vector <const char*>  LONG_JUMP_PASS;

static GameObject onetime[8];

ActionUI::ActionUI()
{

}

ActionUI::~ActionUI()
{
	Action_vector.clear();
}

void ActionUI::Init() {

	State = ACTION_STATE_BALANCEBOARD;
	State_Switch = true;
	progress = 0;
	Finish_Flag = false;

	// トランポリン
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SL]);
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SR]);
	TRAMPOLINING_PASS.push_back(TexturePassDict[TEXTURE_INDEX_UP]);

	// バランスボード
	BALANCEBOARD_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SL]);
	BALANCEBOARD_PASS.push_back(TexturePassDict[TEXTURE_INDEX_SR]);

	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_RIGHT]);
	LONG_JUMP_PASS.push_back(TexturePassDict[TEXTURE_INDEX_UP]);

}

void ActionUI::Update() {

	if (State_Switch) {

		switch (State)
		{
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
		case ACTION_STATE_LONGJUMP:
			for (int i = 0; i < 4; i++) {
				onetime[i].LoadTexture(LONG_JUMP_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;
		default:
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
			if (joycon[LEFT_JOYCON].GetGyro_X() < -100  && joycon[LEFT_JOYCON].GetOldState() == (JOYCON_SL_LEFT + JOYCON_SR_LEFT)) {
				Action_vector[2].Gauss_Filter(500);
				progress = 3;
				Finish_Flag = true;
			}
			break;
			// バランスボード
		case ACTION_STATE_BALANCEBOARD:
			// Failed
			if (joycon[LEFT_JOYCON].GetGyro_Y() < -150 || joycon[LEFT_JOYCON].GetGyro_Y() > 150) {
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
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	
	if (Finish_Flag) {
		State_Switch_Timer += SECONDS;
	}

	if (State_Switch_Timer  >= 0.7f) {
		progress = 0;
		State_Switch = true;
		State_Switch_Timer = 0.0f;
		Finish_Flag = false;
		Reset_Vector();
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