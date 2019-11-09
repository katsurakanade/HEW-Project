#pragma once
#include "GameObject.h"
#include "main.h"
#include "input.h"

// アクションゲージ状態
typedef enum {

	ACTIONSLOT_OVER,
	ACTIONSLOT_GREAT,
	ACTIONSLOT_GOOD,
	ACTIONSLOT_BAD,

}ACTIONSLOT_STATE_INDEX;

// アクションゲージ
class ActionSlot
{
private:

	// 状態
	int State;
	// 値
	int Value;
	// 聖火オブジェクト
	GameObject Fire;
	// 手オブジェクト
	GameObject Hand;

public:

	// 座標
	D3DXVECTOR2 Pos;
	
	void Load();

	void Update();

	void Draw();

	ActionSlot();

	~ActionSlot();

	int GetState();

	int GetValue();

	GameObject GetFire();

	GameObject GetHand();

};

