#pragma once

enum
{
	BT_GameStart,
	BT_BatonTouch,
};

class BatonTouch
{
public:
	BatonTouch();	//�R���X�g���N�^
	~BatonTouch();  //�f�X�g���N�^

	//------------�����o�ϐ�------------------
	bool Uninit_DoOnce = true;
	float Timer = 0;
	bool StateBaton;
	bool CharengeFlag = false;

	//------------�����o�֐�------------------

	void Init();
	void Uninit();
	// �o�g���^�b�`�X�V����(BTState:�Q�[���X�^�[�g�������ۂ�)
	void Update(int BTState);
	void Draw(int BTState);

	bool GetBatonState();
};

void Init_GameStart();
void Init_BatonTouch();