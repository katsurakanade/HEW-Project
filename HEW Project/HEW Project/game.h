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


void Init_Game();
void Uninit_Game();
void Update_Game();
void Draw_Game();