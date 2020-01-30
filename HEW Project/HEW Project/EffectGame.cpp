#include "EffectGame.h"
#include "Effect.h"
#include <vector>
#include "Live2D.h"
#include "ActionSlot.h"
#include "Tutorial.h"

static EffectGame *EG;
static std::vector<EffectGame*> EGStorage;     // EffectGame��new�������̃|�C���^�i�[��
int EffectGame::MaxEffectNum = 0;     // ���������擾�����G�t�F�N�g�̐�

// EffectGameManager------------------------------------------------VV
void EGManager::Init()
{
}
void EGManager::Uninit()
{
}
void EGManager::Update()
{
	bool flag = false;     // delete�ŃY�����o�����̃t���O

	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Update();     //�e�G�t�F�N�g�̍X�V����
		if (EGStorage[i]->DeleteFlag)
		{
			// �A�j���[�V�������I��������̂��폜
			EffectGame *wark = EGStorage[i];     // ���������A�j���[�V�����̃A�h���X�ۑ�

			EG->MaxEffectNum--;
			EGStorage.erase(EGStorage.begin() + EGStorage[i]->MyEffectNum);
			delete wark;     // �������폜
			flag = true;
		}
		if (flag && i < EGStorage[i]->MaxEffectNum)
		{
			EGStorage[i]->MyEffectNum--;
		}
		
	}
}
void EGManager::Draw()
{
	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Draw();
	}
}
// EffectGameManager------------------------------------------------AA

// EffectManager------------------------------------------------------VV

EffectGame::EffectGame(void (EffectGame::*fp_CallFunc)())
{
	// �G�t�F�N�g�m��
	for (int i = 0; i < MaxParticleNum; i++)
	{
		eft[i] = new Effect(this);
	}
	MyEffectNum = MaxEffectNum;
	MaxEffectNum++;
	// �����̃|�C���^�i�[
	EGStorage.push_back(this);
	// �֐��|�C���^���i�[
	fpCallFunc = fp_CallFunc;
}
EffectGame::~EffectGame()
{
	for (int i = 0; i < MaxParticleNum; i++)
	{
		eft[i]->obj.Destroy();    // �p�[�e�B�N���摜�̃��������
	}
	delete[] *eft;     // �p�[�e�B�N���̃��������

}
void EffectGame::Init()
{
}
void EffectGame::Uninit()
{
}
void EffectGame::Update()
{
	(this->*fpCallFunc)();     // ���̃C���X�^���X�ŌĂт����֐����Ă�(�֐��|�C���^)
}
void EffectGame::Draw()
{
	for (int i = 0; i < MaxAryNum; i++)
	{
		if (eft[i]->IsDraw)
		{
			eft[i]->obj.Draw();
		}
	}
}
void EffectGame::E_end()
{
	int SNCnt = 0;     // SleepNow�̐��J�E���g
	for (int i = 0; i < MaxAryNum; i++)     // IUMAN���g��
	{
		if (eft[i]->lastSleepFlag)
		{
			SNCnt++;
		}
	}
	if (SNCnt == MaxAryNum)     //�A�j���[�V�����I��
	{
		DeleteFlag = true;     // �f���[�g�t���O�𗧂Ă�
	}
}
// EffectManager------------------------------------------------------AA






//===========================================================================================================
// �A�j���[�V�������������G�t�F�N�g���A�j���[�V���������������ɕ��ׂ� //
// �g���G�t�F�N�g�̗v�f���͑S��this->eft.[0]����
// ���O�́uE_�V�[����(���p�������̂�)_�G�t�F�N�g���v     (�Ⴆ��Game�V�[���̃A�N�V���������G�t�F�N�g�Ȃ�... void E_game_ActionSuccess() )


////////////////////////////////////////////////////// �T���v���v���O���� //////////////////////////////////////////////////////
void EffectGame::E_game_Sample()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);     // �G�t�F�N�g�p�[�e�B�N��[0]�̃e�N�X�`�����[�h
		eft[0]->obj.Object.Pos.x = 600.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[0]->obj.Object.Pos.y = 350.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[1]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_A]);     // �G�t�F�N�g�p�[�e�B�N��[1]�̃e�N�X�`�����[�h
		eft[1]->obj.Object.Pos.x = 800.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[1]->obj.Object.Pos.y = 250.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////

	// 1�ڂ̃A�j���[�V����
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Move(3.0f, 100.0f, 200.0f);
	eft[0]->Sleep(2.000f);
	eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	eft[1]->Sleep(2.0);

	// 2�ڂ̃A�j���[�V����
	eft[0]->Zoom(2.0001f, 0.5f);
	eft[0]->Sleep(2.0001f);
	eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	eft[1]->Sleep(3.0);
	eft[1]->LastSleep(0.0001f);

	// 3�ڂ̃A�j���[�V����
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	eft[0]->Sleep(5.0f);
	eft[0]->LastSleep(0.0001f);
	
	

	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_Sample()
{
	new EffectGame(&EffectGame::E_game_Sample);
}
////////////////////////////////////////////////////// �T���v���v���O���� //////////////////////////////////////////////////////



////////////////////////////////////////////////////// �^�C�g��(title) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// �^�C�g��(title) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// �`���[�g���A��(tutorial) //////////////////////////////////////////////////////
void EffectGame::E_tutorial_AAA()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////

		eft[0]->obj.LoadTexture(TextureDict["gaze"]);     // �G�t�F�N�g�p�[�e�B�N��[0]�̃e�N�X�`�����[�h
		eft[0]->obj.Object.Pos.x = 870.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[0]->obj.Object.Pos.y = 250.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W
		eft[0]->obj.Object.Scale.x = 3.95f;
		eft[0]->obj.Object.Scale.y = 1.0f;

		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////

		// 1�ڂ̃A�j���[�V����
	eft[0]->Zoom(0.3f, 0.2f);
	eft[0]->Sleep(0.300f);
	eft[0]->Zoom(0.3f, -0.2f);
	eft[0]->Sleep(0.301f);

	eft[0]->LastSleep(0.0001f);


	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_tutorial_AAA()
{
	new EffectGame(&EffectGame::E_tutorial_AAA);
}

void EffectGame::E_tutorial_up()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////

		eft[0]->obj.LoadTexture(TextureDict["up_arrow"]);     // �G�t�F�N�g�p�[�e�B�N��[0]�̃e�N�X�`�����[�h

		eft[0]->obj.Object.Pos.x = 500.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[0]->obj.Object.Pos.y = 550.0f;   // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		//eft[0]->obj.Object.Pos.x = (GetActionSlot()->Pos.x + 0.0f);     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		//eft[0]->obj.Object.Pos.y = (GetActionSlot()->Pos.y + 0.0f);     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[0]->obj.Object.Scale.x = 0.8f;
		eft[0]->obj.Object.Scale.y = 0.8f;


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////

		// 1�ڂ̃A�j���[�V����
	eft[0]->Curve(true, 2.0, 0.5, 10, -100);
	eft[0]->Sleep(0.50f);
	//eft[0]->Zoom(0.3f, -0.2f);
	//eft[0]->Sleep(0.301f);


	eft[0]->LastSleep(0.0001f);


	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_tutorial_up()
{
	new EffectGame(&EffectGame::E_tutorial_up);
}

////////////////////////////////////////////////////// �`���[�g���A��(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// �Q�[��(game) //////////////////////////////////////////////////////

// �G�t�F�N�g�֐�:�A�N�V��������
void EffectGame::E_game_ActionSucsess()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////

		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_A]);     // �G�t�F�N�g�p�[�e�B�N��[0]�̃e�N�X�`�����[�h
		eft[0]->obj.Object.Pos.x = 600.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[0]->obj.Object.Pos.y = 350.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W
		
		eft[1]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_AIROU]);     // �G�t�F�N�g�p�[�e�B�N��[1]�̃e�N�X�`�����[�h
		eft[1]->obj.Object.Pos.x = 800.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[1]->obj.Object.Pos.y = 250.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W

		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////


	// 1�ڂ̃A�j���[�V����
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Sleep(4.0f);
	eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	eft[1]->Sleep(2.0);

	// 2�ڂ̃A�j���[�V����
	eft[0]->Zoom(2.0f, 0.5f);
	eft[0]->Sleep(2.0001);
	eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	eft[1]->Sleep(3.0);
	eft[1]->LastSleep(0.0001f);

	// 3�ڂ̃A�j���[�V����
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	eft[0]->Sleep(5.0f);
	eft[0]->LastSleep(0.0001f);


	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_ActionSucsess()
{
	new EffectGame(&EffectGame::E_game_ActionSucsess);
}

//=======================================================================================================================
//=======================================================================================================================
void EffectGame::E_game_GreatEffect()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[2]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[2]�̃e�N�X�`�����[�h

		eft[2]->obj.Object.Scale.x = 0.1f;
		eft[2]->obj.Object.Scale.y = 0.1f;

		eft[2]->obj.Object.Pos.x = 500.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[2]->obj.Object.Pos.y = 360.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[3]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[3]�̃e�N�X�`�����[�h

		eft[3]->obj.Object.Scale.x = 0.1f;
		eft[3]->obj.Object.Scale.y = 0.1f;

		eft[3]->obj.Object.Pos.x = 500.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[3]->obj.Object.Pos.y = 420.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[4]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[4]�̃e�N�X�`�����[�h

		eft[4]->obj.Object.Scale.x = 0.1f;
		eft[4]->obj.Object.Scale.y = 0.1f;

		eft[4]->obj.Object.Pos.x = 350.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[4]->obj.Object.Pos.y = 360.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[5]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[5]�̃e�N�X�`�����[�h

		eft[5]->obj.Object.Scale.x = 0.1f;
		eft[5]->obj.Object.Scale.y = 0.1f;

		eft[5]->obj.Object.Pos.x = 350.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[5]->obj.Object.Pos.y = 420.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[10]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[5]�̃e�N�X�`�����[�h

		eft[10]->obj.Object.Scale.x = 0.1f;
		eft[10]->obj.Object.Scale.y = 0.1f;

		eft[10]->obj.Object.Pos.x = 420.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[10]->obj.Object.Pos.y = 320.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[11]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_STAR]);     // �G�t�F�N�g�p�[�e�B�N��[5]�̃e�N�X�`�����[�h

		eft[11]->obj.Object.Scale.x = 0.1f;
		eft[11]->obj.Object.Scale.y = 0.1f;

		eft[11]->obj.Object.Pos.x = 420.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[11]->obj.Object.Pos.y = 450.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W



		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	// 1�ڂ̃A�j���[�V����

	eft[2]->Move(0.5, 100, -100);
	eft[2]->Sleep(0.50001);
	eft[2]->LastSleep(0.0001f);

	eft[3]->Move(0.5, 100, 100);
	eft[3]->Sleep(0.50002);
	eft[3]->LastSleep(0.0001f);

	eft[4]->Move(0.5, -100, -100);
	eft[4]->Sleep(0.50003);
	eft[4]->LastSleep(0.0001f);

	eft[5]->Move(0.5, -100, 100);
	eft[5]->Sleep(0.50004);
	eft[5]->LastSleep(0.0001f);

	eft[10]->Move(0.5, 0, -120);
	eft[10]->Sleep(0.50005);
	eft[10]->LastSleep(0.0001f);

	eft[11]->Move(0.5, 0, 120);
	eft[11]->Sleep(0.50006);
	eft[11]->LastSleep(0.0001f);


	//2�ڂ̃A�j���[�V����


	//3�ڂ̃A�j���[�V����



	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_GreatEffect()
{
	new EffectGame(&EffectGame::E_game_GreatEffect);
}
//===================================================================================================================
//===================================================================================================================
void EffectGame::E_game_BadEffect()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[6]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_CROSS]);     // �G�t�F�N�g�p�[�e�B�N��[6]�̃e�N�X�`�����[�h
		eft[6]->obj.Object.Pos.x = 800.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[6]->obj.Object.Pos.y = 250.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	// 1�ڂ̃A�j���[�V����
	eft[6]->Curve(false, 3.0, 3.0, -600, -250);
	eft[6]->Sleep(3.5001);



	//2�ڂ̃A�j���[�V����
	eft[6]->Rotate(3.0f, 360);
	eft[6]->Curve(false, 4.0, 3.0, -800, 400);
	eft[6]->Sleep(3.0001);
	eft[6]->LastSleep(0.0001f);

	//3�ڂ̃A�j���[�V����



	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_BadEffect()
{
	new EffectGame(&EffectGame::E_game_BadEffect);
}
//==========================================================================================================================
//===========================================================================================================================
void EffectGame::E_game_OverEffect()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[7]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_ASE]);     // �G�t�F�N�g�p�[�e�B�N��[7]�̃e�N�X�`�����[�h
		eft[7]->obj.Object.Pos.x = 200.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[7]->obj.Object.Pos.y = 200.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	// 1�ڂ̃A�j���[�V����
	eft[7]->Rotate(3.0f, -20.0f);
	eft[7]->Curve(true, 4.0, 6.0, -50, 200);
	eft[7]->Sleep(6.5001);
	eft[7]->LastSleep(0.0001f);
	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_OverEffect()
{
	new EffectGame(&EffectGame::E_game_OverEffect);
}
//======================================================================================================================
//=======================================================================================================================
void EffectGame::E_game_RunEffect()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[8]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_FIRE]);     // �G�t�F�N�g�p�[�e�B�N��[8]�̃e�N�X�`�����[�h
		eft[10]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_HANABI]);     // �G�t�F�N�g�p�[�e�B�N��[8]�̃e�N�X�`�����[�h
		eft[11]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_HANABI]);     // �G�t�F�N�g�p�[�e�B�N��[8]�̃e�N�X�`�����[�h
		eft[10]->obj.Object.Scale.x = 0.1f;
		eft[10]->obj.Object.Scale.y = 0.1f;
		eft[11]->obj.Object.Scale.x = 0.1f;
		eft[11]->obj.Object.Scale.y = 0.1f;

		eft[8]->obj.Object.Pos.x = 250.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W======��
		eft[8]->obj.Object.Pos.y = 900.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[10]->obj.Object.Pos.x = 450.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W	=======����
		eft[10]->obj.Object.Pos.y = 300.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W

		eft[11]->obj.Object.Pos.x = 150.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W	=======����
		eft[11]->obj.Object.Pos.y = 300.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	// 1�ڂ̃A�j���[�V����
	eft[8]->Zoom(0.5f, 3.0f);//===========��
	eft[8]->Move(0.5f, 0.0f, -500.0f);
	eft[8]->Sleep(2.0001);
	eft[8]->LastSleep(0.0001f);

	eft[10]->Sleep(1.05001);//======����
	eft[10]->Curve(false, 5.0f, 1.0f, 300, -200);
	eft[10]->Sleep(1.0001);
	eft[10]->LastSleep(0.0002f);

	eft[11]->Sleep(1.05001);
	eft[11]->Curve(true, 5.0f, 1.0f, -300, -200);
	eft[11]->Sleep(1.0001);
	eft[11]->LastSleep(0.0002f);


	//2�ڂ̃A�j���[�V����

	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_RunEffect()
{
	new EffectGame(&EffectGame::E_game_RunEffect);
}
//=========================================================================================================================
//=========================================================================================================================
void EffectGame::E_game_JoyconEffect()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		eft[9]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_JOYCON]);     // �G�t�F�N�g�p�[�e�B�N��[9]�̃e�N�X�`�����[�h
		eft[9]->obj.Object.Pos.x = 900.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[9]->obj.Object.Pos.y = 350.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W
		eft[9]->obj.Object.Scale.x = 0.1f;
		eft[9]->obj.Object.Scale.y = 0.1f;


		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	// 1�ڂ̃A�j���[�V����
	eft[9]->Zoom(0.3f, 0.1f);
	eft[9]->Sleep(.3001);
	eft[9]->Rotate(0.5f, 10.0f);
	eft[9]->Sleep(0.5001);
	eft[9]->Rotate(0.5f, -20.0f);
	eft[9]->Sleep(0.5002);
	eft[9]->Zoom(0.3f, -0.1f);
	eft[9]->Sleep(0.3002);

	//2�ڂ̃A�j���[�V����
	eft[9]->Zoom(0.3f, 0.1f);
	eft[9]->Sleep(.3001);
	eft[9]->Rotate(0.5f, 10.0f);
	eft[9]->Sleep(0.5001);
	eft[9]->Rotate(0.5f, -20.0f);
	eft[9]->Sleep(0.5002);
	eft[9]->Zoom(0.3f, -0.1f);
	eft[9]->Sleep(0.3002);
	eft[9]->LastSleep(0.0001f);

	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_JoyconEffect()
{
	new EffectGame(&EffectGame::E_game_JoyconEffect);
}


// �o�g���^�b�`1000P�Q�b�g
void EffectGame::E_game_Baton1000P()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////

		eft[0]->obj.LoadTexture(TexturePassDict[TEXTURE_INDEX_BATON_1000P]);     // �G�t�F�N�g�p�[�e�B�N��[0]�̃e�N�X�`�����[�h
		eft[0]->obj.Object.Pos.x = 640.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���X���W
		eft[0]->obj.Object.Pos.y = 360.0f;     // �G�t�F�N�g�p�[�e�B�N��[0]�̏���Y���W
		eft[0]->obj.Object.Scale.x = 0.5f;
		eft[0]->obj.Object.Scale.y = 0.5f;

		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////

	eft[0]->Zoom(0.5f, 1.7f);
	eft[0]->Sleep(2.3f);
	eft[0]->LastSleep(0.0001f);

	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_Baton1000P()
{
	new EffectGame(&EffectGame::E_game_Baton1000P);
}


////////////////////////////////////////////////////// �Q�[��(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ���U���g(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// ���U���g(result) //////////////////////////////////////////////////////

