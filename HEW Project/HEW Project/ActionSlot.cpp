#include "ActionSlot.h"

// アクションゲージ最大値、最小値
static const int VALUE_MAX = 90;
static const int VALUE_MIN = -60;

// アクションゲージ状態値
static const int VALUE_OVER = VALUE_MAX  * 0.9;
static const int VALUE_GREAT = VALUE_MAX * 0.8;
static const int VALUE_BAD = ((VALUE_MAX - VALUE_MIN) * 0.2) + VALUE_MIN;

// 常に減らす
static const int VALUE_DOWNSEC = 1;

void ActionSlot::Load() {

	Fire.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);
	Hand.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

}

void ActionSlot::Update() {
	
	if (Value > VALUE_MIN && Value < VALUE_MAX) {
		Value += VALUE_DOWNSEC;
	}

	// Over 判定
	if (Value >= VALUE_OVER) {
		State = ACTIONSLOT_OVER;
	}
	// Great 判定
	else if (Value < VALUE_OVER && Value >VALUE_GREAT) {
		State = ACTIONSLOT_GREAT;
	}
	// Bad 判定
	else if (Value < VALUE_BAD) {
		State = ACTIONSLOT_BAD;
	}
	// Good 判定
	else {
		State = ACTIONSLOT_GOOD;
	}

	// 画像回転
	Fire.Object.Rotate = (DOT * Value);
	Hand.Object.Rotate = (DOT * Value) * 0.3;

	if (keyboard.IsPress(DIK_DOWNARROW)) {
		Value--;
	}

	if (keyboard.IsPress(DIK_UPARROW)) {
		Value++;
	}

}

void ActionSlot::Draw() {

	Fire.Draw(Pos.x, Pos.y);
	Hand.Draw(Pos.x, Pos.y);

}

ActionSlot::ActionSlot()
{

	Pos.x = 0;
	Pos.y = 0;
	State = -1;
	Value = 0;

}

ActionSlot::~ActionSlot()
{

}

int ActionSlot::GetState() {
	return State;
}

int ActionSlot::GetValue() {
	return Value;
}

GameObject ActionSlot::GetFire() {
	return Fire;
}

GameObject ActionSlot::GetHand() {
	return Hand;
}