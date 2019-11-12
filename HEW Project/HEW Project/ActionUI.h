// 23100 ƒAƒNƒVƒ‡ƒ“UI

#pragma once
#include "DxLib.h"
#include "main.h"
#include "GameObject.h"
#include <vector>

using namespace std;

typedef enum {

	ACTION_STATE_PRESSBUTTON_ABAC,
	ACTION_STATE_LONGJUMP,

	ACTION_STATE_MAX

}Action_State;

class ActionUI
{

private:

	int State;

	bool State_Switch;

	bool Finish_Flag;

	int progress;

	float State_Switch_Timer;

	vector <GameObject> Action_vector;

public:

	D3DXVECTOR2 Pos;

	D3DXVECTOR2 Interval;

	ActionUI();

	~ActionUI();

	void Init();

	void Update();

	void Draw();

	void Reset_Vector();

	void SetState(int n);

	void SetStateSwitch(bool n);

	int GetState();

	bool GetStateSwitch();

	int GetProgress();

	bool GetFinishFlag();

	int GetActionAmount();
};

