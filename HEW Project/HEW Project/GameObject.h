#pragma once

#include "main.h"
#include "main.h"
#include "texture.h"

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

	GameObject(TextureIndex texture);

	// ���W
	D3DXVECTOR2 pos;

	// �\��
	void Draw();

	// �B���ݒ�
	void SetHide(bool hide);

};