#pragma once

class GameOver
{
public:

	GameOver();		//�R���X�g���N�^

	~GameOver();	//�f�X�g���N�^

	//------------�����o�ϐ�------------------

	bool titleflag;

	float TimeCount;

	bool objflag;

	//------------�����o�֐�------------------

	void Init();

	void Uninit();

	void Update();

	void Draw();

	//bool GetisUse();

	void GameOverisUse();

};