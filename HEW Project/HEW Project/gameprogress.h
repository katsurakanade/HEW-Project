#pragma once
#include "ActionUI.h"

#define PROGRESS_WIDTH 1000
#define PROGRESS_HEIGHT  120

class GameProgress
{
public:

	GameProgress();	//コンストラクタ

	~GameProgress(); //デストラクタ

	//------------メンバ変数------------------

	float stime = 0.0f;

	float ProgressMax;

	float NowProgress;

	int Section;	//区間の変数

	bool GameFinish;

	bool MeasureFlag;

	float RunDistance;


	//------------メンバ関数------------------

	void Init();

	void Update(ActionUI &target);

	void Draw();

	int GetSection();

	//float Getstime();

	void SetMesureflag(bool flag);

	float GetProgressBarObjectPosx();

	void ChangeMeasure(float stime,float time2);
};

