#pragma once

#include <Windows.h>
#include <d3dx9.h>

// スクリーン(クライアント領域)の幅
#define SCREEN_WIDTH  (1280)

 // スクリーン(クライアント領域)の高さ
#define SCREEN_HEIGHT  (720)             

// ウインドウクラスの名前
#define CLASS_NAME     "GameWindow"

// ウィンドウの名前
#define WINDOW_CAPTION "ゲームウィンドウ" 

// FPSロック
#define FPS_LOCK 60.0f

// 1秒あたりの時間 (Updateの中で使う)
#define SECONDS (1.0f/FPS_LOCK)

//ウィンドウハンドルのGetter
HWND GetHWND();
double frand();