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
	
	ACTIONSLOT_MAX,

}ACTIONSLOT_STATE_INDEX;

// アクションゲージ
class ActionSlot
{
private:

	// 状態
	int State;
	// 値
	float Value;
	// 聖火台オブジェクト
	GameObject FireBase;
	// 聖火オブジェクト
	GameObject Fire;
	// 手オブジェクト
	GameObject Hand;

public:

	float offsect_dis;

	// 座標
	D3DXVECTOR2 Pos;

	// 拡大率
	D3DXVECTOR2 Scale;

	// 聖火偏移
	D3DXVECTOR2 Fire_Offset;
	
	void Load();

	void Update(double stamina,bool flag);

	void Draw();

	ActionSlot();

	~ActionSlot();

	void AddValue(float value);

	int GetState();

	float GetValue();

	GameObject GetFire();

	GameObject GetHand();

};

