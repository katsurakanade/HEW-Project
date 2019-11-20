#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//�R���X�g���N�^

	~StaminaGauge();	//�f�X�g���N�^

	//------------�����o�ϐ�------------------

	float StaminaCount;

	bool Initflag = true;
	
	double StaminaScale_x=2.0;

	double StaminaScale_y = 2.0;


	//------------�����o�֐�------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale_x, double scale_y);

	float GetStaminaCount();

	double GetStaminaScale();
};