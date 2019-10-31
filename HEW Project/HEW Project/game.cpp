#include "game.h"
#include "input.h"
#include "texture.h"
#include "scene.h"

void Init_Game() {


}

void Uninit_Game() {

}

void Update_Game() {

	if (Keyboard_IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Game() {

	

}