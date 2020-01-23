#pragma once
#include "ActionUI.h"

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

	bool MeasureFlag;

	float RunDistance;


	//------------�����o�֐�------------------

	void Init();

	void Update(ActionUI &target);

	void Draw();

	int GetSection();

	//float Getstime();

	void SetMesureflag(bool flag);

	float GetProgressBarObjectPosx();

	void ChangeMeasure(float stime,float time2);
};

