#pragma once

#define PROGRESS_WIDTH 1000
#define PROGRESS_HEIGHT  120

class GameProgress
{
public:

	GameProgress();	//コンストラクタ

	~GameProgress();

	void Update();

	void Draw();


	int stime;		//スタートの時間

	float ProgressMax;

	float NowProgress;

	int Section;	//区間の変数

	bool GameFinish;


	//メンバ関数
	bool GetBT_Move();

	int GetSection();

};

void Init_GameProgress();
