#include "GameData.h"
#include "main.h"
#include <vector>
#include "DxLib.h"

const int speed1 = 360;     //futuu
const int speed2 = 315;     //osoi
const int speed3 = 405;     //hayai

static const float InitPosY = 600;

static int seHandle = -1;     // SEƒnƒ“ƒhƒ‹

GameData gamedata;

GameData::GameData()
{
	
}

GameData::~GameData()
{

}

void GameData::Init() {

	hp = 3;
	Running_Distance = 0;
	Running_Speed = 0;
	Action_Point = 0;

	ExcellentMode = false;
	ExcellentModeInitFlag = false;
	ExcellentTimer = 0.0f;

	seHandle = LoadSoundMem("asset/sound/SE/excellent.mp3");

}

void GameData::UpdateSpeed() {

	Running_meter = (Running_Distance / 100);
}

void GameData::InitExcellentMode() {
	
	ExcellentMode = true;
}

void GameData::UpdateExcellentMode(vector <ActionPointAnime*> actionpoint) {
	static bool DoOnce = true;

	if (DoOnce) { PlaySoundMem(seHandle, DX_PLAYTYPE_BACK); DoOnce = false; }     // SEÄ¶

	ExcellentTimer += SECONDS;

	if (ExcellentTimer > 3.0f) {
		ExcellentModeInitFlag = false;
		ExcellentMode = false;
		ExcellentTimer = 0.0f;
		ExcellentModeCount = 0;
		DoOnce = true;
	}

}

void GameData::DrawExcellentMode() {

}


void GameData::Addhp(int value) {
	hp += value;
}

void GameData::AddRunningDistance(int value) {
	Running_Distance += value;
}

void GameData::AddRunningSpeed(int value) {
	Running_Speed += value;
}

void GameData::AddActionPoint(int value) {
	Action_Point += value;
}

void GameData::SetGameMode(int value) {
	GameMode = value;
}

void GameData::SetRunningSpeed(int value) {
	Running_Speed = value;
}

void GameData::SetActionPoint(int value) {
	Action_Point = value;
}

bool GameData::GetExcellentMode() {
	return ExcellentMode;
}

float GameData::GetExcellentTimer() {
	return ExcellentTimer;
}


int GameData::GetGameMode() {
	return GameMode;
}

int GameData::Gethp() {
	return hp;
}

int GameData::GetRunningDistance() {
	return Running_Distance;
}

int GameData::GetRunningSpeed() {
	return Running_Speed;
}

int GameData::GetRunningMeter() {
	return Running_meter;
}

int GameData::GetActionPoint() {
	return Action_Point;
}

void GameData::Action_Point_Update(int value) {

	switch (value)
	{
	case ACTIONSLOT_OVER:
		Action_Point += 150;
		Action_Affect_State = ACTIONSLOT_OVER;
		break;

	case ACTIONSLOT_GREAT:
		Action_Point += 120;
		Action_Affect_State = ACTIONSLOT_GREAT;
		break;

	case ACTIONSLOT_GOOD:
		Action_Point += 50;
		Action_Affect_State = ACTIONSLOT_GOOD;
		break;

	case ACTIONSLOT_BAD:
		Action_Affect_State = ACTIONSLOT_BAD;
		break;

	default:
		break;
	}
	
}

ActionPointAnime::ActionPointAnime() {


}

ActionPointAnime::~ActionPointAnime() {

	for (int i = 0; i < 3; i++) {
		self[i].Destroy();
		self[i].~GameObject();
	}
}

void ActionPointAnime::Create(int value) {

	ValueData = value;

	if (ValueData >= 100) {

		self[0].LoadTexture(TextureDict["all"], 10, 4, 4, 280 / 4, 280 / 4);
		self[1].LoadTexture(TextureDict["all"], 10, 4, 4, 280 / 4, 280 / 4);
		self[2].LoadTexture(TextureDict["all"], 10, 4, 4, 280 / 4, 280 / 4);

		self[0].Object.Pos = D3DXVECTOR2(PosX + (0 * (280 / 4) * self[0].Object.Scale.x), PosY);
		self[1].Object.Pos = D3DXVECTOR2(PosX + (1 * (280 / 4) * self[1].Object.Scale.x), PosY);
		self[2].Object.Pos = D3DXVECTOR2(PosX + (2 * (280 / 4) * self[2].Object.Scale.x), PosY);
	}

	else if (ValueData <= 100) {

		for (int i = 0; i < 2; i++) {
			self[i].LoadTexture(TextureDict["all"], 10, 4, 4, 280 / 4, 280 / 4);
			self[i].Object.Pos = D3DXVECTOR2(PosX + (i * (300 / 4) * self[i].Object.Scale.x), PosY);

		}
	}
}

void ActionPointAnime::Update() {

	for (int i = 0; i < 3; i++) {

		if (self[i].Object.Pos.y > InitPosY - 200.0) {
			self[i].Object.Pos.y -= 5.0f;
		}

		if (self[i].Object.Pos.y <= InitPosY - 200.0) {
			timer += SECONDS;
		}

		if (timer > 0.1f) {
			self[i].Object.Pos.x -= 20.0f;
		}

		if (self[i].Object.Pos.x < -200) {
			OutFlag = true;
			this->~ActionPointAnime();
		}
	}
}

void ActionPointAnime::Draw() {
	
	if (!OutFlag) {

		if (ValueData >= 100) {
			self[0].Draw_Anime(ValueData / 100);
			self[1].Draw_Anime((ValueData / 10) / 10);
			self[2].Draw_Anime(0);
		}

		else if (ValueData <= 99) {
			self[0].Draw_Anime(ValueData / 10);
			self[1].Draw_Anime(ValueData % 10);
		}
	}

}

