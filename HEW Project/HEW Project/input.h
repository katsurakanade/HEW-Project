/*
Copyright <2019> <Kanade Katsura>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <string>

using namespace std;

#define	NUM_KEY_MAX			(256)

// game pad用設定値
#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

#define JOYCON_MAX 2

/*
JoyConインターフェース
JoyConDriver + vJoy  で使ってください
JoyConDriver設定：Combine JoyCons
*/

// JoyCon左 
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

// JoyCon右

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

//bool GamePad_Initialize(HINSTANCE hInstance, HWND hWnd);
//void GamePad_Finalize(void);
//void GamePad_Update(void);

//BOOL GamePad_IsPress(int padNo, DWORD button);
//BOOL GamePad_IsTrigger(int padNo, DWORD button);

class Keyboard {

private:

	LPDIRECTINPUTDEVICE8 DevKeyboard = NULL;

	BYTE	 KeyState[NUM_KEY_MAX];

	BYTE	 KeyStateTrigger[NUM_KEY_MAX];

	BYTE	 KeyStateRelease[NUM_KEY_MAX];

public:

	bool Initialize(HINSTANCE hInstance, HWND hWnd);

	void Finalize(void);

	void Update();

	bool IsPress(int nKey);

	bool IsTrigger(int nKey);

	bool IsRelease(int nKey);
};

class JoyCon {

private:

	DWORD	 Accelerometer;

	DWORD State;

	DWORD Trigger;

public:

	LPDIRECTINPUTDEVICE8 Device = NULL;

	bool Initialize(HINSTANCE hInstance, HWND hWnd);

	void Finalize();

	void Update();

	BOOL IsPress(DWORD button);

	BOOL IsTrigger(DWORD button);

	DWORD GetTrigger();

	void SetAccelerometer(DWORD data);

	DWORD GetAccelerometer();
};

extern Keyboard keyboard;
extern JoyCon joycon[JOYCON_MAX];