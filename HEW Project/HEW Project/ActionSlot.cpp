#include "ActionSlot.h"
#include "GameData.h"
#include "Staminagauge.h"

// �A�N�V�����Q�[�W�ő�l�A�ŏ��l
static const float VALUE_MAX = 90.0;
static const float VALUE_MIN = -30.0;

// �A�N�V�����Q�[�W��Ԓl
static const float VALUE_OVER = VALUE_MAX * 0.9;
static const float VALUE_GREAT = VALUE_MAX * 0.75;
static const float VALUE_BAD = ((VALUE_MAX - VALUE_MIN) * 0.1) + VALUE_MIN;

// ��Ɍ��炷
static const float VALUE_DOWNSEC = 0.1f;

static D3DXVECTOR2 Hand_mullet;

float StaminaTimer = 0.0;

bool plusflag;

void ActionSlot::Load() {

	FireBase.LoadTexture(TexturePassDict[TEXTURE_INDEX_FIREBASE]);
	Hand.LoadTexture(TexturePassDict[TEXTURE_INDEX_ARM]);
	Fire.LoadTexture(TexturePassDict[TEXTURE_INDEX_FIRE]);

	Scale = D3DXVECTOR2(0.20f, 0.20f);

	FireBase.Object.Scale = Scale;
	Hand.Object.Scale = Scale;
	Fire.Object.Scale = Scale;

	FireBase.Object.Pos = Pos;
	Hand.Object.Pos = Pos;
	Fire.Object.Pos = Pos;

	Hand_mullet = FireBase.Object.Pos;

	Fire_Offset = D3DXVECTOR2(0.0f, 0.0f);

	Value = 0;

	plusflag = true;

	offsect_dis = 1.0f;
}

void ActionSlot::Update(double stamina) {

	StaminaTimer += SECONDS;

	if (StaminaTimer >= 0.7) {
		Value -= (1 / stamina);
		StaminaTimer = 0.0f;
	}

	// �펞���炷
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
		FireBase.Object.Scale.x -= 0.2f;
		FireBase.Object.Scale.y -= 0.2f;
		//FireBase.Color.bright-= 10;
		//FireBase.HSB_Fillter();
	}

	// Good ����
	else if (Value > VALUE_BAD && Value < VALUE_GREAT) {
		State = ACTIONSLOT_GOOD;
	}

	// BAD����
	if (State == ACTIONSLOT_BAD) {
		gamedata.Addhp(-1);
		Value = VALUE_DEFAULT;
	}



	// ��ʒu�ύX
	Hand.Object.Pos.x = Pos.x - 130;
	Hand.Object.Pos.y = Pos.y - 50;

	// ���Έʒu�v�Z
	if (FireBase.Object.Rotate >= 0) {
		FireBase.Object.Pos.x = Hand.Object.Pos.x + 220 + Fire_Offset.x + ((Hand.Object.Rotate * 20)) + ((Scale.x + 0.8) * Value);
		FireBase.Object.Pos.y = Hand.Object.Pos.y + 30 + Fire_Offset.y + (Hand.Object.Rotate * 200) - ((Scale.y + 0.8) * Value);
	}

	else {
		FireBase.Object.Pos.x = Hand.Object.Pos.x + 220 + Fire_Offset.x + ((Hand.Object.Rotate * 120)) + ((Scale.x + 0.8) * Value * 0.50);
		FireBase.Object.Pos.y = Hand.Object.Pos.y + 30 + Fire_Offset.y + (Hand.Object.Rotate * 120) - ((Scale.y + 0.8) * Value * 2.00);
	}


	Fire.Object.Pos.x = FireBase.Object.Pos.x + (Hand.Object.Rotate * 70);
	Fire.Object.Pos.y = FireBase.Object.Pos.y - 100;

	// �摜��]
	FireBase.Object.Rotate = -(DOT * Value);
	Hand.Object.Rotate = -(DOT * Value);
	Fire.Object.Rotate = -(DOT * Value);

	// �摜�g��
	FireBase.Object.Scale = Scale + D3DXVECTOR2(0.60, 0.60);
	Hand.Object.Scale = Scale + D3DXVECTOR2(0.30, 0.30);
	Fire.Object.Scale = Scale + D3DXVECTOR2(0.70, 0.70);

	Fire.Color.saturation = -rand() % 31 + 15;
	Fire.Color.bright = -rand() % 11 + 5;

	Fire.HSB_Fillter();
}

void ActionSlot::Draw() {

	FireBase.Draw();
	Hand.Draw(0, 0);
	//Fire.Draw();
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
	FireBase.~GameObject();
	Hand.~GameObject();
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
	return FireBase;
}

GameObject ActionSlot::GetHand() {
	return Hand;
}