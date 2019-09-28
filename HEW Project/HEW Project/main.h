#pragma once

#include <Windows.h>
#include <d3dx9.h>

// �X�N���[��(�N���C�A���g�̈�)�̕�
#define SCREEN_WIDTH  (1280)

 // �X�N���[��(�N���C�A���g�̈�)�̍���
#define SCREEN_HEIGHT  (720)             

// �E�C���h�E�N���X�̖��O
#define CLASS_NAME     "GameWindow"

// �E�B���h�E�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" 

// FPS���b�N
#define FPS_LOCK 60.0f

// 1�b������̎��� (Update�̒��Ŏg��)
#define SECONDS (1.0f/FPS_LOCK)

//�E�B���h�E�n���h����Getter
HWND GetHWND();
double frand();