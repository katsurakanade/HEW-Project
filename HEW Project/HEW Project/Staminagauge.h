#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//コンストラクタ

	~StaminaGauge();	//デストラクタ

	//------------メンバ変数------------------

	float StaminaCount;

	bool Initflag = true;
	
	double StaminaScale_x=2.0;

	double StaminaScale_y = 2.0;


	//------------メンバ関数------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale_x, double scale_y);

	float GetStaminaCount();

	double GetStaminaScale();
};