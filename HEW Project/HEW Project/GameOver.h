#pragma once

class GameOver
{
public:

	GameOver();		//コンストラクタ

	~GameOver();	//デストラクタ

	//------------メンバ変数------------------

	bool titleflag = false;

	float TimeCount = SECONDS;

	bool objflag = false;

	//------------メンバ関数------------------

	void Init();

	void Uninit();

	void Update();

	void Draw();

	//bool GetisUse();

	void GameOverisUse();

};


//ゲームステート用
void Init_GameOver();

