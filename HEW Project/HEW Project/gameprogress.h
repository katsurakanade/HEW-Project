#pragma once

#define PROGRESS_WIDTH 1000
#define PROGRESS_HEIGHT  120

class GameProgress
{
public:

	GameProgress();	//�R���X�g���N�^

	~GameProgress(); //�f�X�g���N�^

	//------------�����o�ϐ�------------------

	float stime = 0.0f;

	float ProgressMax;

	float NowProgress;

	int Section;	//��Ԃ̕ϐ�

	bool GameFinish;

	bool Initflag = true;

	bool MeasureFlag;

	//------------�����o�֐�------------------

	void Init();

	void Update();

	void Draw();

	int GetSection();

	//float Getstime();

};

