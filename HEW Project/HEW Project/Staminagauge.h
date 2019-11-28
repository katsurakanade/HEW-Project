#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//コンストラクタ

	~StaminaGauge();	//デストラクタ

	//------------メンバ変数------------------

	double StaminaCount;

	float FlameCount;

	double NowCount;

	bool Initflag = true;
	
	double StaminaScale_x = 2.0;

	double StaminaScale_y = 2.0;


	//------------メンバ関数------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale_x, double scale_y);

	double GetStaminaCount();

	//入っているステートで減少させる
	void  StaminaState(int state);

	//scaleを少しずつ減らす関数
	void StaminaReduce(double s_count);
};