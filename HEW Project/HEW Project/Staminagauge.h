#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//コンストラクタ

	~StaminaGauge();	//デストラクタ

	//------------メンバ変数------------------

	float StaminaCount;

	bool Initflag = true;
	
	double StaminaScale=2.0;

	//------------メンバ関数------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale);

	float GetStaminaCount();

	double GetStaminaScale();
};