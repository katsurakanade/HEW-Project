// 23100 アクションUI

#pragma once
#include "DxLib.h"
#include "main.h"
#include "GameObject.h"
#include <vector>

using namespace std;

typedef enum {

	// トランポリン
	ACTION_STATE_TRAMPOLINING,
	// バランスボード
	ACTION_STATE_BALANCEBOARD,
	// ハードル
	ACTION_STATE_HURDLE,

	ACTION_STATE_LONGJUMP,

	ACTION_STATE_WEIGHT,

	ACTION_STATE_UNEVENBARS,

	ACTION_STATE_MAX

}Action_State;

class ActionUI
{

private:

	GameObject onetime[8];

	int State;

	bool State_Switch;

	bool Finish_Flag;

	int progress;

	float State_Switch_Timer;

	vector <GameObject> Action_vector;

	bool UNEVENBARS_Array[4] = { false,false,false,false };
	int UNEVENBARS_progress = 0;
	int UNEVENBARS_rnd = -1;

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

