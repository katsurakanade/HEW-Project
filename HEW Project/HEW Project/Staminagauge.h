#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//�R���X�g���N�^

	~StaminaGauge();	//�f�X�g���N�^

	//------------�����o�ϐ�------------------

	float StaminaCount;

	bool Initflag = true;
	
	double StaminaScale=2.0;

	//------------�����o�֐�------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale);

	float GetStaminaCount();

	double GetStaminaScale();
};