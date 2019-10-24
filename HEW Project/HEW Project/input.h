
#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

/* game pad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

/*
JoyCon�C���^�[�t�F�[�X
JoyConDriver + vJoy  �Ŏg���Ă�������
JoyConDriver�ݒ�FCombine JoyCons
*/

// JoyCon�� 
#define JOYCON_LEFTSTICK_DOWN 1024L  // 10
#define JOYCON_LEFTSTICK_UP 4096L  // 11
#define JOYCON_LEFTSTICK_RIGHT 32768L  // 15
#define JOYCON_LEFTSTICK_LEFT 65536l  // 16

#define JOYCON_DOWN 0x00000001l  // 1
#define JOYCON_UP 0x00000002l // 2
#define JOYCON_RIGHT 0x00000004l // 3
#define JOYCON_LEFT 0x00000008l // 4
#define JOYCON_SR_LEFT 0x00000010l //5
#define JOYCON_SL_LEFT 0x00000020l //6
#define JOYCON_L 0x00000040l // 7
#define JOYCON_ZL 0x00000080l // 8
#define JOYCON_MIN 0x000000100l // 9
#define JOYCON_L3  0x00000800l // 12
#define JOYCON_SCREENSHOT 0x00002000l // 14

// JoyCon�E

#define JOYCON_RIGHTSTICK_DOWN 33554432L  // 25
#define JOYCON_RIGHTSTICK_UP 268435456l  // 2
#define JOYCON_RIGHTSTICK_RIGHT 1073741824l  // 3
#define JOYCON_RIGHTSTICK_LEFT 2147483648l  // 4

#define JOYCON_Y 131072L // 17
#define JOYCON_X 262144L // 18
#define JOYCON_B 524288L // 19
#define JOYCON_A 1048576L // 20
#define JOYCON_SR_RIGHT 2097152L // 21
#define JOYCON_SL_RIGHT 4194304L // 22
#define JOYCON_R  8388608L // 23
#define JOYCON_ZR  16777216L //  24
#define JOYCON_PLUS 67108864L // 26
#define JOYCON_R3 134217728L // 27
#define JOYCON_HOME   536870912L // 29

bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);
void Keyboard_Finalize(void);
void Keyboard_Update(void);

bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

//---------------------------- game pad
bool GamePad_Initialize(HINSTANCE hInstance, HWND hWnd);
void GamePad_Finalize(void);
void GamePad_Update(void);

BOOL GamePad_IsPress(int padNo, DWORD button);
BOOL GamePad_IsTrigger(int padNo, DWORD button);

LONG GetJoyConAcc(int number);