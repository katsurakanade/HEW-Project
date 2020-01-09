#include "EffectGame.h"
#include "Effect.h"
#include <vector>


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
	for (int i = 0; i < EG->MaxEffectNum; i++)
	{
		EGStorage[i]->Update();
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
	MaxEffectNum++;
	// �����̃|�C���^�i�[
	EGStorage.push_back(this);
	// �֐��|�C���^���i�[
	fpCallFunc = fp_CallFunc;
}
EffectGame::~EffectGame()
{
	MaxEffectNum--;
	// �����̃|�C���^���폜
	EGStorage.erase(EGStorage.begin() + MaxEffectNum);
	// ���������
	///delete[] eft;     // �G���[�o��
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
		delete this;     //����������
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
	//eft[0]->Zoom(2.0f, 0.5f);
	//eft[0]->Sleep(4.0f);
	///eft[1]->Curve(true, 3.0, 2.0, 300, 100);
	///eft[1]->Sleep(2.0);

	// 2�ڂ̃A�j���[�V����
	//eft[0]->Zoom(2.0f, 0.5f);
	//eft[0]->Sleep(2.0001);
	///eft[1]->Curve(false, 3.0, 2.4, -300, -100);
	///eft[1]->Sleep(3.0);
	///eft[1]->LastSleep(0.0001f);

	// 3�ڂ̃A�j���[�V����
	eft[0]->Curve(false, 3.0, 5.0, -100, -200);
	//eft[0]->Curve(true, 3.0, 2.0, -100, -200.0001);
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

////////////////////////////////////////////////////// �`���[�g���A��(tutorial) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// �Q�[��(game) //////////////////////////////////////////////////////

// �G�t�F�N�g�֐�:�A�N�V��������
void EffectGame::E_game_ActionSucsess()
{
	if (DoOnce)
	{
		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////



		//// ��----- �G�t�F�N�g�̏����ݒ� -----�� ////
		DoOnce = false;     // �����Ȃ�!!
	}

	//// ��-----------------------���������牺�ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////



	//// ��-----------------------�� ���������ɃG�t�F�N�g�A�j���[�V���������� ��-----------------------�� ////
	E_end();     // �K���R�s�[�I //
}
// ��(��)�̃G�t�F�N�g�֐��ɏ������֐����̓��Ɂucall_�v��t����B
void call_E_game_ActionSucsess()
{
	new EffectGame(&EffectGame::E_game_ActionSucsess);
}



////////////////////////////////////////////////////// �Q�[��(game) //////////////////////////////////////////////////////



////////////////////////////////////////////////////// ���U���g(result) //////////////////////////////////////////////////////

////////////////////////////////////////////////////// ���U���g(result) //////////////////////////////////////////////////////

