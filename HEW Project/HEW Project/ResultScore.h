#pragma once

#define NUMBER_OF_DIGITS	(8)

class ResultScore
{

private:
	//------------メンバ変数------------------

	int ValueData;
    float FrameTime = 0.0f;
	bool DrawFlag = false;
public:

	GameObject score[8];
	GameObject UI[1];

	ResultScore();	//コンストラクタ

	~ResultScore(); //デストラクタ




	//------------メンバ関数------------------

	void Init();

	void Update();

	void Draw();

	void ScoreCreate(int value,float posX,float posY);
};

