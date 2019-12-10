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

//�Q�[���X�^�[�g����(SL+SR+L�ŃX�^�[�g)=====================================
void Init_GameStart()
{

}




//�o�g���^�b�`����====================================================
void Init_BatonTouch()
{
	//StateBaton = false;
	Baton[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_TEST]);
	Baton[0].Object.Pos.x = 500.0f;
	Baton[0].Object.Pos.y = 500.0f;
	Baton[0].Object.Scale.x = 1.0f;

}


BatonTouch::BatonTouch()
{

}

BatonTouch::~BatonTouch()
{

}
void BatonTouch::Init()
{
}
void BatonTouch::Uninit()
{

}
void BatonTouch::Update()
{

	if (keyboard.IsTrigger(DIK_RETURN)) {
		GameState_Change(GAME_STATE_GAME);     //�Q�[���X�e�[�g�ɖ߂�
		//StateBaton = false;
	}
	
}
void BatonTouch::Draw()
{
	Baton[0].Draw();
}

bool BatonTouch::GetBatonState()
{
	return StateBaton;
}