#include "game.h"
#include "GameObject.h"
#include "input.h"
#include "texture.h"
#include "Menu.h"
#include "scene.h"

LPDIRECT3DTEXTURE9 *TEXTUREARRAY = new LPDIRECT3DTEXTURE9[3];

static Menu *main = new Menu(2);

void Init_Game() {

	TEXTUREARRAY[0] = Texture_GetTexture(TEXTURE_INDEX_YUKIDARUMA);
	TEXTUREARRAY[1] = Texture_GetTexture(TEXTURE_INDEX_YUKIDARUMA);

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