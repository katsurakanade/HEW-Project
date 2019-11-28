#pragma once

class GameOver
{
public:

	GameOver();		//コンストラクタ

	~GameOver();	//デストラクタ

	//------------メンバ変数------------------

	bool titleflag;

	float TimeCount;

	bool objflag;

	//------------メンバ関数------------------

	void Init();

	void Uninit();

	void Update();

	void Draw();

	//bool GetisUse();

	void GameOverisUse();

};