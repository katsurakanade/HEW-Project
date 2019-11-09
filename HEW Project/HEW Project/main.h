#pragma once

#include <Windows.h>
#include <d3dx9.h>

// �X�N���[��(�N���C�A���g�̈�)�̕�
#define SCREEN_WIDTH  1280

 // �X�N���[��(�N���C�A���g�̈�)�̍���
#define SCREEN_HEIGHT  720

// �E�C���h�E�N���X�̖��O
#define CLASS_NAME     "GameWindow"

// �E�B���h�E�̖��O
#define WINDOW_CAPTION "���΃����[" 

// FPS���b�N
#define FPS_LOCK 60.0f

// 1�b������̎��� (Update�̒��Ŏg��)
#define SECONDS (1.0f/FPS_LOCK)

#define PI 3.1415926

#define DOT (PI / 180.0f)

//�E�B���h�E�n���h����Getter
HWND GetHWND();
double frand();

typedef struct Vertex2D_tag
{
	// ���_���W�i���W�ϊ��ςݒ��_�j
	D3DXVECTOR4 position;
	// ���_�J���[(32Bit ARGB�w��)
	D3DCOLOR	color;
	// �e�N�X�`�����W
	D3DXVECTOR2 texcoord;

} Vertex2D;