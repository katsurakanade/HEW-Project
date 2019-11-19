#include "ActionSlot.h"
#include "GameData.h"

// �A�N�V�����Q�[�W�ő�l�A�ŏ��l
static const float VALUE_MAX = 60.0;
static const float VALUE_MIN = -60.0;

// �A�N�V�����Q�[�W��Ԓl
static const float VALUE_OVER = VALUE_MAX  * 0.75;
static const float VALUE_GREAT = VALUE_MAX * 0.3;
static const float VALUE_BAD = ((VALUE_MAX - VALUE_MIN) * 0.2) + VALUE_MIN;

// ��Ɍ��炷
static const float VALUE_DOWNSEC = 0.1f;

static D3DXVECTOR2 Hand_mullet;

void ActionSlot::Load() {

	Fire.LoadTexture(TexturePassDict[TEXTURE_INDEX_FIRE]);
	Hand.LoadTexture(TexturePassDict[TEXTURE_INDEX_ARM]);

	this->Scale = D3DXVECTOR2(0.20f,0.20f);

	Fire.Object.Scale = this->Scale;
	Hand.Object.Scale = this->Scale;

	Fire.Object.Pos = Pos ;
	Hand.Object.Pos = Pos;

	Hand_mullet = Fire.Object.Pos;

	this->Fire_Offset = D3DXVECTOR2(40.0f, 50.0f);

	Value = 0;
}

void ActionSlot::Update() {

	// �펞���炷
	if (Value > VALUE_MIN && Value < VALUE_MAX) {
		Value	 -= VALUE_DOWNSEC;
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
		Fire.Object.Scale.x -= 0.2f;
		Fire.Object.Scale.y -= 0.2f;
		Fire.Color.bright-= 50;
		Fire.HSB_Fillter();
	}

	// Good ����
	else if (Value > VALUE_BAD && Value < VALUE_GREAT) {
		State = ACTIONSLOT_GOOD;
	}

	// BAD����
	if (State == ACTIONSLOT_BAD) {
		gamedata.Addhp(-1);
		Value = 10;
	}

	// ��ʒu�ύX
	Hand.Object.Pos.x = Pos.x;
	Hand.Object.Pos.y = Pos.y;

	// ���Έʒu�v�Z
	Fire.Object.Pos.x = Pos.x + (Fire_Offset.x * cos(Hand.Object.Rotate));
	Fire.Object.Pos.y = Pos.y + (Fire_Offset.y * sin(Hand.Object.Rotate));

	// �摜��]
	Fire.Object.Rotate = -(DOT * Value);
	Hand.Object.Rotate = -(DOT * Value);

	// �摜�g��
	Fire.Object.Scale = this->Scale;
	Hand.Object.Scale = this->Scale;
}

void ActionSlot::Draw() {

	Fire.Draw();
	Hand.Draw();

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