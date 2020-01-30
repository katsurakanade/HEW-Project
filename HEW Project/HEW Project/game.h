#pragma once

typedef enum
{
	GAME_STATE_START,		//�X�^�[�g�ҋ@�A������
	GAME_STATE_GAME,		//���C���Q�[��
	GAME_STATE_BATONTOUCH,		//�o�g���^�b�`
	GAME_STATE_GAME_OVER,		//�Q�[���I�[�o�[
	GAME_STATE_GAME_CLEAR,		//�Q�[���N���A

	GAME_STATE_MAX

}GAME_STATE;

/*
�v���g�^�C�v�錾
*/

// ���鏈��
void Running();
// Debug�p�l��
void Debug_Panel();
// �L�����N�^�[����
void CharacterMove();
// Debug���� (�L�[�{�[�h)
void Debug_Running();


void Init_Game();
void Init_GameState();     // �Q���, �R��ԗpInit
void Uninit_Game();
void Update_Game();
void Draw_Game();



//�Q�[���X�e�[�g�p
void GameState_Initialize(GAME_STATE index);
void GameState_Check(void);
void GameState_Change(GAME_STATE index);