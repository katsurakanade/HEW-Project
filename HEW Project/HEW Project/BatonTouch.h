#pragma once

class BatonTouch
{
public:
	BatonTouch();	//�R���X�g���N�^
	~BatonTouch();  //�f�X�g���N�^

	//------------�����o�ϐ�------------------
	bool StateBaton;

	//------------�����o�֐�------------------

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetBatonState();
};

void Init_BatonTouch();