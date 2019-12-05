#pragma once

class BatonTouch
{
public:
	BatonTouch();	//コンストラクタ
	~BatonTouch();  //デストラクタ

	//------------メンバ変数------------------
	bool StateBaton;

	//------------メンバ関数------------------

	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetBatonState();
};

void Init_BatonTouch();