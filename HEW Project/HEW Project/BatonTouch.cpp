#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "scene.h"
#include "gameprogress.h"
#include "BatonTouch.h"
#include "DxLib.h"
#include "Live2D.h"

GameObject Baton[1];
GameProgress Progress;

void Init_BatonTouch()
{
	Baton[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_TEST]);
	Baton[0].Object.Pos.x = 500.0f;
	Baton[0].Object.Pos.y = 500.0f;
	Baton[0].Object.Scale.x = 1.0f;

}
void Uninit_BatonTouch()
{

}
void Update_BatonTouch()
{
	if (keyboard.IsTrigger(DIK_RETURN)) {
		Scene_Change(SCENE_INDEX_GAME);
	}

}
void Draw_BatonTouch()
{
	Baton[0].Draw();
}