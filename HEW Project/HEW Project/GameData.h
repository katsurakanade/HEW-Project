#pragma once

class GameData
{
private:
	
	// ����
	int hp;
	// ���鋗��
	int Running_Distance;
	// ����X�r�[�g
	int Running_Speed;
	// ���鋗��(���[�g�����Z����)
	int	 Running_meter;
	// �A�N�V�����|�C���g
	int Action_Point;

public:

	GameData();

	~GameData();

	void Init();

	void UpdateSpeed();

	void Addhp(int value);

	void AddRunningDistance(int value);

	void AddRunningSpeed(int value);

	void AddActionPoint(int value);

	void SetRunningSpeed(int value);

	void SetActionPoint(int value);

	int Gethp();

	int GetRunningDistance();

	int GetRunningSpeed();

	int GetRunningMeter();

	int GetActionPoint();
};

extern GameData gamedata;