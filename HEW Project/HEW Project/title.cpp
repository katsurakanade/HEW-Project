#include "title.h"
#include "scene.h"
#include "input.h"
#include "GameObject.h"
#include "Menu.h"
#include "texture.h"

LPDIRECT3DTEXTURE9 *Menu_TextureArray = new LPDIRECT3DTEXTURE9[3];
static Menu  *main = new Menu(2);


void Init_Title() {

	Menu_TextureArray[0] = Texture_GetTexture(TEXTURE_INDEX_MENUSTART);
	Menu_TextureArray[1] = Texture_GetTexture(TEXTURE_INDEX_MENUEXIT);

	
}

void Uninit_Title() {


}

void Update_Title() {

	if (main->UpdateSelectMenu() == 0) {
		Scene_Change(SCENE_INDEX_GAME);
	}

	else if (main->UpdateSelectMenu() == 1) {
		exit(1);
	}

	

}

void Draw_Title() {

	main->Draw(Menu_TextureArray, 550, 400, 100, 128, 64);
}