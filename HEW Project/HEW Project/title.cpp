#include "title.h"
#include "scene.h"
#include "input.h"

void Init_Title() {

}

void Uninit_Title() {

}

void Update_Title() {

	if (Keyboard_IsPress(DIK_SPACE) ) {
		Scene_Change(SCENE_INDEX_GAME);
	}

}

void Draw_Title() {

}