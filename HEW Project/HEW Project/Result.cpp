#include "main.h"
#include "Result.h"
#include "input.h"
#include "scene.h"
#include <DxLib.h>

void Init_Result() {

}

void Uninit_Result() {

}

void Update_Result() {

	if (keyboard.IsTrigger(DIK_R)) {
		Scene_Change(SCENE_INDEX_TITLE);
	}

}

void Draw_Result() {

}