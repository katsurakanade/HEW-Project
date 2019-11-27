#pragma once

class StaminaGauge
{
public:

	StaminaGauge();		//�R���X�g���N�^

	~StaminaGauge();	//�f�X�g���N�^

	//------------�����o�ϐ�------------------

	double StaminaCount;

	float FlameCount;

	double NowCount;

	bool Initflag = true;
	
	double StaminaScale_x = 2.0;

	double StaminaScale_y = 2.0;


	//------------�����o�֐�------------------

	void Init();

	void Update();

	void Draw();

	void SetStaminaGauge(double scale_x, double scale_y);

	double GetStaminaCount();

	//�����Ă���X�e�[�g�Ō���������
	void  StaminaState(int state);

	//scale�����������炷�֐�
	void StaminaReduce(double s_count);
};