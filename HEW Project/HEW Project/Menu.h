#pragma once
#include "Menu.h"
#include "GameObject.h"

/*
���j���[�V�X�e���F
�I��p���j���[�����N���X�ł��B
�g���O�K���O���[�o���Ńe�N�X�`���z��p�ӂ��Ă��������B
(2019/10/3 ���܏㉺�I�������Ή����܂��B)
*/

class Menu
{

private:

	//	�I������
	int Arrow;

	// ���ܑI�����Ă����I����
	int select_now;

public:

	// �R���X�g���N�^(�I������)
	Menu(int arrow);

	//	�f�X�g���N�^
	~Menu();

	/*	
	�I����
	(Update�̒��Ŏg���Ă�������)
	(Return  �I�����Ă���I����)
	*/
	int UpdateSelectMenu();

	// �\��(�e�N�X�`���z��,���ʒu,�c�ʒu,�Ԋu,�e�N�X�`����,�e�N�X�`���c)
	void Draw(LPDIRECT3DTEXTURE9 texturearray[], int sx, int sy, int interval,int tx,int tw);
};

