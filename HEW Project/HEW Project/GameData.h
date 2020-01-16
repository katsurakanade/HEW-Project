#pragma once
#include "ActionSlot.h"
#include "GameObject.h"
#include "BackGround.h"


// �Q�[�����[�h���
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
	
	// �Q�[�����[�h
	int GameMode = -1;
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
	// �A�N�V�����G�t�F�N�g���
	int Action_Affect_State;
	// �G�N�Z�����g�t���O
	bool ExcellentMode = false;

	// �G�N�Z�����g�^�C�}�[
	float ExcellentTimer;


public:

	bool ExcellentModeInitFlag = false;

	int ExcellentModeCount = 0;


	GameData();

	~GameData();

	void Init();

	void UpdateSpeed();

	void InitExcellentMode();

	void UpdateExcellentMode(vector <ActionPointAnime*> actionpoint);

	void DrawExcellentMode();


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

	bool GetExcellentMode();

	float GetExcellentTimer();

};


extern GameData gamedata;