#pragma once

enum
{
	BT_GameStart,
	BT_BatonTouch,
};

class BatonTouch
{
public:
	BatonTouch();	//コンストラクタ
	~BatonTouch();  //デストラクタ

	//------------メンバ変数------------------
	bool Uninit_DoOnce = true;
	float Timer = 0;
	bool StateBaton;
	bool CharengeFlag = false;

	//------------メンバ関数------------------

	void Init();
	void Uninit();
	// バトンタッチ更新処理(BTState:ゲームスタート処理か否か)
	void Update(int BTState);
	void Draw(int BTState);

	bool GetBatonState();
};

void Init_GameStart();
void Init_BatonTouch();