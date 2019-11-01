#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"

void Init_Game() {


}

void Uninit_Game() {

}

void Update_Game() {

	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Game() {

}