#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "gameprogress.h"

GameProgress gameprogress;

void Init_Game() {
	gameprogress.stime;
}

void Uninit_Game() {
	gameprogress.~GameProgress();
}

void Update_Game() {

	gameprogress.Update();
	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Game() {

	gameprogress.Draw();

}