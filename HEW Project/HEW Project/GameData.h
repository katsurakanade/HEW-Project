#pragma once

class GameData
{
private:
	
	// 聖火
	int hp;
	// 走る距離
	int Running_Distance;
	// 走るスビート
	int Running_Speed;
	// 走る距離(メートル換算した)
	int	 Running_meter;
	// アクションポイント
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