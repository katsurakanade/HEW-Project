#pragma once

typedef enum TUTO_STATE
{
	TUTO_STATE_START,		//�X�^�[�g�ҋ@�A������
	TUTO_STATE_GAME,		//�`���[�g���A���Q�[��
	TUTO_STATE_BATONTOUCH,		//�o�g���^�b�`

	TUTO_STATE_MAX

};

void Init_Tutorial();
void Uninit_Tutorial();
void Update_Tutorial();
void Draw_Tutorial();

//�Q�[���X�e�[�g�p
void TutoState_Initialize(TUTO_STATE index);
void TutoState_Check(void);
void TutoState_Change(TUTO_STATE index);
void TutoRunning();
void TutoCharacterMove();
void Debug_TutoRunning();
