#pragma once

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

	bool Initflag = true;

	bool MeasureFlag;

	//------------メンバ関数------------------

	void Init();

	void Update();

	void Draw();

	int GetSection();

	//float Getstime();

};

