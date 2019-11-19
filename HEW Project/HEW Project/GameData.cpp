#include "GameData.h"

const int speed1 = 360;     //futuu
const int speed2 = 315;     //osoi
const int speed3 = 405;     //hayai

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
}

void GameData::UpdateSpeed() {

	Running_meter = (Running_Distance / 100);
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

void GameData::SetRunningSpeed(int value) {
	Running_Speed = value;
}

void GameData::SetActionPoint(int value) {
	Action_Point = value;
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