#include "ActionSlot.h"

// �A�N�V�����Q�[�W�ő�l�A�ŏ��l
static const int VALUE_MAX = 90;
static const int VALUE_MIN = -60;

// �A�N�V�����Q�[�W��Ԓl
static const int VALUE_OVER = VALUE_MAX  * 0.9;
static const int VALUE_GREAT = VALUE_MAX * 0.8;
static const int VALUE_BAD = ((VALUE_MAX - VALUE_MIN) * 0.2) + VALUE_MIN;

// ��Ɍ��炷
static const float VALUE_DOWNSEC = 0.1f;

void ActionSlot::Load() {

	Fire.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);
	Hand.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);

}

void ActionSlot::Update() {
	
	if (Value > VALUE_MIN && Value < VALUE_MAX) {
		Value -= VALUE_DOWNSEC;
	}

	// Over ����
	if (Value >= VALUE_OVER) {
		State = ACTIONSLOT_OVER;
	}
	// Great ����
	else if (Value < VALUE_OVER && Value >VALUE_GREAT) {
		State = ACTIONSLOT_GREAT;
	}
	// Bad ����
	else if (Value < VALUE_BAD) {
		State = ACTIONSLOT_BAD;
	}
	// Good ����
	else {
		State = ACTIONSLOT_GOOD;
	}

	// �摜��]
	Fire.Object.Rotate = -(DOT * Value);
	Hand.Object.Rotate = -(DOT * Value) * 0.3;

}

void ActionSlot::Draw() {

	Fire.Draw((int)Pos.x, (int)Pos.y);
	Hand.Draw((int)Pos.x, (int)Pos.y);

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

void ActionSlot::AddValue(float value) {
	Value += value;
}

int ActionSlot::GetState() {
	return State;
}

float ActionSlot::GetValue() {
	return Value;
}

GameObject ActionSlot::GetFire() {
	return Fire;
}

GameObject ActionSlot::GetHand() {
	return Hand;
}