#pragma once

class GameOver
{
public:

	GameOver();		//�R���X�g���N�^

	~GameOver();	//�f�X�g���N�^

	//------------�����o�ϐ�------------------

	bool titleflag = false;

	float TimeCount = SECONDS;

	bool objflag = false;

	//------------�����o�֐�------------------

	void Init();

	void Uninit();

	void Update();

	void Draw();

	//bool GetisUse();

	void GameOverisUse();

};


//�Q�[���X�e�[�g�p
void Init_GameOver();

