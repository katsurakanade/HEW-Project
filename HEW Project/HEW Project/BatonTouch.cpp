#include "game.h"
#include "input.h"
#include "GameObject.h"
#include "GameData.h"
#include "scene.h"
#include "gameprogress.h"
#include "BatonTouch.h"
#include "DxLib.h"
#include "Live2D.h"
#include "EffectGame.h"

GameObject Baton[10];
GameProgress Progress;

//�Q�[���X�^�[�g����(SL+SR+L�ŃX�^�[�g)=====================================
void Init_GameStart()
{
	// �uSL+SR+L�v�������I�摜
	Baton[6].LoadTexture(TexturePassDict[TEXTURE_INDEX_GAMESTART]);
	Baton[6].Object.Pos.x = 740.0f;
	Baton[6].Object.Pos.y = 360.0f;
	Baton[6].Object.Scale.x = 0.7f;
	Baton[6].Object.Scale.y = 0.7f;
}




//�o�g���^�b�`����====================================================
void Init_BatonTouch()
{
	//StateBaton = false;


	// �uSL+SR+L+�U��I�v�摜
	Baton[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_CHARENGE]);
	Baton[0].Object.Pos.x = 740.0f;
	Baton[0].Object.Pos.y = 360.0f;
	Baton[0].Object.Scale.x = 0.7f;
	Baton[0].Object.Scale.y = 0.7f;


	// �u�o�g���^�b�`��...�v�摜
	Baton[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG]);
	Baton[1].Object.Pos.x = 1920.0f;
	Baton[1].Object.Pos.y = 360.0f;
	Baton[1].Object.Scale.x = 1.0f;

	///-----------------------����������--------------------------- ///

	// �w�i�A���t�@�l100%
	Baton[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_5]);
	Baton[2].Object.Pos.x = 640.0f;
	Baton[2].Object.Pos.y = 360.0f;
	Baton[2].Object.Scale.x = 1.0f;

	// �w�i�A���t�@�l80%
	Baton[3].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_4]);
	Baton[3].Object.Pos.x = 640.0f;
	Baton[3].Object.Pos.y = 360.0f;
	Baton[3].Object.Scale.x = 1.0f;

	// �w�i�A���t�@�l60%
	Baton[4].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_3]);
	Baton[4].Object.Pos.x = 640.0f;
	Baton[4].Object.Pos.y = 360.0f;
	Baton[4].Object.Scale.x = 1.0f;

	// �w�i�A���t�@�l40%
	Baton[5].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_2]);
	Baton[5].Object.Pos.x = 640.0f;
	Baton[5].Object.Pos.y = 360.0f;
	Baton[5].Object.Scale.x = 1.0f;

	// �w�i�A���t�@�l20%
	Baton[7].LoadTexture(TexturePassDict[TEXTURE_INDEX_OKBATONTOUCHI_BG_1]);
	Baton[7].Object.Pos.x = 640.0f;
	Baton[7].Object.Pos.y = 360.0f;
	Baton[7].Object.Scale.x = 1.0f;



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

// �o�g���^�b�`�X�V����(BTState:�Q�[���X�^�[�g�������ۂ�)
void BatonTouch::Update(int BTState)
{
	Timer += SECONDS;     // ���Ԍv��


	// �Q�[���X�^�[�g����(�Q�[�����񏈗�)==================================
	if (BTState == BT_GameStart)
	{
		// �uSL+SR+L�v����������Q�[���X�e�[�g�ɑJ��
		if (keyboard.IsTrigger(DIK_RETURN) || joycon[0].GetOldState() == JOYCON_L + JOYCON_SL_LEFT + JOYCON_SR_LEFT) {               ///���C���ӏ�
			GameState_Change(GAME_STATE_GAME);     //�Q�[���X�e�[�g�ɑJ��
		}
	}
	// =======================================================


	// �o�g���^�b�`����(�w�i�E���獷������)==================================
	else if (BTState == BT_BatonTouch)
	{

		static bool DoOnce = true;

		if (Timer <= 3.0f)
		{
			// 3�b�ȓ��ɁuSL+SR+L+�U��v��������1000P�l��
			if (!CharengeFlag) {  ///���C���ӏ�
				if (keyboard.IsTrigger(DIK_RETURN)){
					gamedata.AddActionPoint(1000.0);
						CharengeFlag = true;
						call_E_game_Baton1000P();     // 1000P�A�j���[�V����
				}
				else if (joycon[0].GetOldState() == JOYCON_L + JOYCON_SL_LEFT + JOYCON_SR_LEFT && joycon[0].GetGyro_Y() >= 200) {
					gamedata.AddActionPoint(1000.0);
					CharengeFlag = true;
					call_E_game_Baton1000P();     // 1000P�A�j���[�V����
				}
			}
		}
		else
		{     // 3�b�o�߂�����o�g���^�b�`����

			if (DoOnce) { PlaySoundFile("asset/sound/BGM/title.mp3", DX_PLAYTYPE_BACK); DoOnce = false; }

			// �E����w�i����������
			if (Baton[1].Object.Pos.x > 640.0f)
			{
				Baton[1].Object.Pos.x -= 50.0f;
			}
			else
			{
				Baton[1].Object.Pos.x = 640.0f;
				Baton[1].Object.Pos.y = 360.0f;
			}



			// �u20�b�o�߁v������Q�[���X�e�[�g�ɑJ��
			if ((Timer - 3.0f) >= 20.0f)
			{     // ���̋�ԃX�^�[�g
				StopSoundFile();     // BGM���~�߂�
				DoOnce = true;     // DoOnce���Z�b�g
				GameState_Change(GAME_STATE_GAME);     //�Q�[���X�e�[�g�ɑJ��
			}

		}



	}
	// =======================================================

}
void BatonTouch::Draw(int BTState)
{

	// �Q�[���X�^�[�g����
	if (BTState == BT_GameStart)
	{

		// �uSL+SR+L�v�������I�@�\��
		Baton[6].Draw();

	}

	// �o�g���^�b�`����
	else if (BTState == BT_BatonTouch)
	{

		if (Timer <= 3.0f)
		{
			// �uSL+SR+L+�U��v�摜�\��
			Baton[0].Draw();
		}
		else
		{
			// �u20�b�o�߁v������Q�[���X�e�[�g�ɑJ��
			if ((Timer - 3.0f) >= 15.0f && (Timer - 3.0f) < 16.0f)
			{     // �c��T�b
				Baton[2].Draw();
			}
			else if ((Timer - 3.0f) >= 16.0f && (Timer - 3.0f) < 17.0f)
			{     // �c��S�b
				Baton[3].Draw();
			}
			else if ((Timer - 3.0f) >= 17.0f && (Timer - 3.0f) < 18.0f)
			{     // �c��R�b
				Baton[4].Draw();
			}
			else if ((Timer - 3.0f) >= 18.0f && (Timer - 3.0f) < 19.0f)
			{     // �c��Q�b
				Baton[5].Draw();
			}
			else if ((Timer - 3.0f) >= 19.0f && (Timer - 3.0f) <= 21.0f)
			{     // �c��P�b
				Baton[7].Draw();
			}
			else
			{
				// �w�i�\��
				Baton[1].Draw();
			}

		}

	}

}

bool BatonTouch::GetBatonState()
{
	return StateBaton;
}