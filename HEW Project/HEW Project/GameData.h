#pragma once

class GameData
{
private:

	int hp;

	int Running_Distance;

	int Running_Speed;

	int	 Running_meter;

public:

	GameData();

	~GameData();

	void UpdateSpeed();

	void Addhp(int value);

	void AddRunningDistance(int value);

	void AddRunningSpeed(int value);

	void SetRunningSpeed(int value);

	int Gethp();

	int GetRunningDistance();

	int GetRunningSpeed();

	int GetRunningMeter();
};

