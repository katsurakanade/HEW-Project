#pragma once

#define PROGRESS_WIDTH 1000
#define PROGRESS_HEIGHT  120

class GameProgress
{
public:

	GameProgress();	//�R���X�g���N�^

	~GameProgress();

	void Update();

	void Draw();


	int stime;		//�X�^�[�g�̎���

	float ProgressMax;

	float NowProgress;

	int Section;	//��Ԃ̕ϐ�

	bool GameFinish;


	//�����o�֐�
	bool GetBT_Move();

	int GetSection();

};

void Init_GameProgress();
