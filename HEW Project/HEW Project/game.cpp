#include "game.h"
#include "GameObject.h"
#include "input.h"
#include "texture.h"
#include "Menu.h"
#include "scene.h"

void Init_Game() {

	

}

void Uninit_Game() {

}

void Update_Game() {

	if (Keyboard_IsTrigger(DIK_R) || GamePad_IsTrigger(0,JOYCON_HOME)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}


}

void Draw_Game() {


}