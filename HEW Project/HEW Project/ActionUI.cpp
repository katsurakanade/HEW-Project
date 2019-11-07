// 23100 ƒAƒNƒVƒ‡ƒ“UI

#include "input.h"
#include <vector>
#include <algorithm>
#include "ActionUI.h"
#include "GameObject.h"

using namespace std;

vector <const char *> PRESSBUTTON_ABAC_PASS;
vector <const char *> PRESSBUTTON_PASSS;

ActionUI::ActionUI()
{

	State = 0;
	State_Switch = true;
	progress = 0;
	Finish_Flag = false;

	// PRESSBUTTON
	//PRESSBUTTON_PASS.push_back(TexturePassDict[TEXTURE_INDEX_START]);
	//PRESSBUTTON_PASS.push_back(TexturePassDict[TEXTURE_INDEX_END]);

	PRESSBUTTON_ABAC_PASS.push_back(TexturePassDict[TEXTURE_INDEX_A]);
	PRESSBUTTON_ABAC_PASS.push_back(TexturePassDict[TEXTURE_INDEX_B]);
	PRESSBUTTON_ABAC_PASS.push_back(TexturePassDict[TEXTURE_INDEX_A]);
	PRESSBUTTON_ABAC_PASS.push_back(TexturePassDict[TEXTURE_INDEX_C]);

	PRESSBUTTON_PASSS.push_back(TexturePassDict[TEXTURE_INDEX_END]);
	PRESSBUTTON_PASSS.push_back(TexturePassDict[TEXTURE_INDEX_START]);
	PRESSBUTTON_PASSS.push_back(TexturePassDict[TEXTURE_INDEX_END]);

}

ActionUI::~ActionUI()
{

}

void ActionUI::Update() {

	if (State_Switch) {

		switch (State)
		{
		case ACTION_STATE_PRESSBUTTON_ABAC:
			GameObject onetime[4];
			for (int i = 0; i < 4; i++) {
				onetime[i].LoadTexture(PRESSBUTTON_ABAC_PASS[i]);
				Action_vector.push_back(onetime[i]);
			}
			break;
			/*
		case ACTION_STATE_PRESSBUTTON2:
			GameObject onetimes[3];
			for (int i = 0; i < 3; i++) {
				onetimes[i].LoadTexture(PRESSBUTTON_PASSS[i]);
				Action_vector.push_back(onetimes[i]);
			}
			break;
			*/
			/*
		default:
			break;
			*/
		}

		State_Switch = false;
	}

	switch (State)
	{
	case ACTION_STATE_PRESSBUTTON_ABAC:
		switch (progress)
		{
		case 0:
			if (keyboard.IsTrigger(DIK_A)) {
				progress++;
				Action_vector[0].Gauss_Filter(500);
			}
			break;
		case 1:
			if (keyboard.IsTrigger(DIK_B)) {
				progress++;
				Action_vector[1].Gauss_Filter(500);
			}
			break;
		case 2:
			if (keyboard.IsTrigger(DIK_A)) {
				progress++;
				Action_vector[2].Gauss_Filter(500);
			}
			break;
		case 3:
			if (keyboard.IsTrigger(DIK_C)) {
				progress++;
				Action_vector[3].Gauss_Filter(500);
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

	if (Finish_Flag) {
		State_Switch_Timer += SECONDS;
	}

	if (State_Switch_Timer  >= 2.0f) {
		progress = 0;
		State_Switch = true;
		State_Switch_Timer = 0.0f;
		Finish_Flag = false;
		Reset_Vector();
	}

}

void ActionUI::Draw() {

	for (int i = 0; i < Action_vector.size(); i++) {
		Action_vector[i].Draw(Pos.x + (Interval.x * i ), Pos.y + (Interval.y * i));
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