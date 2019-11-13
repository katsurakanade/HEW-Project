#pragma once

#include <Windows.h>
#include <d3dx9.h>

// スクリーン(クライアント領域)の幅
#define SCREEN_WIDTH  1280

 // スクリーン(クライアント領域)の高さ
#define SCREEN_HEIGHT  720

// ウインドウクラスの名前
#define CLASS_NAME     "GameWindow"

// ウィンドウの名前
#define WINDOW_CAPTION "聖火リレー" 

// FPSロック
#define FPS_LOCK 60.0f

// 1秒あたりの時間 (Updateの中で使う)
#define SECONDS (1.0f/FPS_LOCK)

#define PI 3.1415926

#define DOT (PI / 180.0f)

//ウィンドウハンドルのGetter
HWND GetHWND();
double frand();

typedef struct Vertex2D_tag
{
	// 頂点座標（座標変換済み頂点）
	D3DXVECTOR4 position;
	// 頂点カラー(32Bit ARGB指定)
	D3DCOLOR	color;
	// テクスチャ座標
	D3DXVECTOR2 texcoord;

} Vertex2D;