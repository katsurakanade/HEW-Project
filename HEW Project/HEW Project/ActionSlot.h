#pragma once
#include "GameObject.h"
#include "main.h"
#include "input.h"

// �A�N�V�����Q�[�W���
typedef enum {

	ACTIONSLOT_OVER,
	ACTIONSLOT_GREAT,
	ACTIONSLOT_GOOD,
	ACTIONSLOT_BAD,
	
	ACTIONSLOT_MAX,

}ACTIONSLOT_STATE_INDEX;

// �A�N�V�����Q�[�W
class ActionSlot
{
private:

	// ���
	int State;
	// �l
	float Value;
	// ���Α�I�u�W�F�N�g
	GameObject FireBase;
	// ���΃I�u�W�F�N�g
	GameObject Fire;
	// ��I�u�W�F�N�g
	GameObject Hand;

public:

	float offsect_dis;

	// ���W
	D3DXVECTOR2 Pos;

	// �g�嗦
	D3DXVECTOR2 Scale;

	// ���ΕΈ�
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

