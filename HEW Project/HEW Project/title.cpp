#include "title.h"
#include "scene.h"
#include "input.h"
#include "sprite.h"

static int x;
static int y;

void Init_Title() {

	x = 0;
	y = 0;

}

void Uninit_Title() {

}

void Update_Title() {

	if (Keyboard_IsPress(DIK_SPACE) ) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	if (GetIrzFlag()) {
		x += 10;
		SetIrzFlag(false);
	}

	x -= 1.0f;

}

void Draw_Title() {

	Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA, x, y);
}