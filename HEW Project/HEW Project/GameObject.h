#pragma once

#include "main.h"
#include "main.h"
#include "texture.h"

/*
�Q�[���I�u�W�F�N�g�F�@	
�Q�[�����g���I�u�W�F�N�g�̃x�[�X�A��{�ق��N���X�̌p���p
*/

class GameObject {

private:

	// �e�N�X�`��
	TextureIndex Texture;

	// ��
	int width;

	// ��
	int height;

	// �B��
	bool Display_Hide = false;

public:

	// �R���X�g���N�^ (�e�N�X�`��)
	GameObject(TextureIndex texture);

	// ���W
	D3DXVECTOR2 pos;

	// �\��
	void Draw();

	// �B���ݒ�
	void SetHide(bool hide);

};