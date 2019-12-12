#pragma once
#include "ActionSlot.h"

// ゲームモード状態
typedef enum {

	GAMEMODE_MATCH,
	GAMEMODE_SINGLE,
	GAMEMODE_MAX,

}GameModeState;


class ActionPointAnime {

private:

	const int PosX = 500;
	const int PosY = 500;

	float timer = 0;

	int ValueData;

public:

	GameObject self[3];

	bool OutFlag = false;

	void Create(int value);

	void Update();

	ActionPointAnime();

	~ActionPointAnime();

	void Draw();

};

class GameData
{
private:
	
	// ゲームモード
	int GameMode = -1;
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
	// アクションエフェクト状態
	int Action_Affect_State;

public:

	GameData();

	~GameData();

	void Init();

	void UpdateSpeed();

	void Action_Point_Update(int value);

	void Addhp(int value);

	void AddRunningDistance(int value);

	void AddRunningSpeed(int value);

	void AddActionPoint(int value);

	void SetGameMode(int value);

	void SetRunningSpeed(int value);

	void SetActionPoint(int value);
	
	int GetGameMode();

	int Gethp();

	int GetRunningDistance();

	int GetRunningSpeed();

	int GetRunningMeter();

	int GetActionPoint();

};


extern GameData gamedata;