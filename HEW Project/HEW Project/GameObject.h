#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include "main.h"
#include <vector>

// アニメフレームリミット
#define ANIME_CUT_LIMIT 36

using namespace std;

// テクスチャキー
typedef enum {

	TEXTURE_INDEX_START,
	TEXTURE_INDEX_END,
	TEXTURE_INDEX_AIROU,
	TEXTURE_INDEX_ACTION_SUCCESS,
	TEXTURE_INDEX_ACTION_DEFAULT,
	TEXTURE_INDEX_ACTION_FAILED,
	TEXTURE_INDEX_A,
	TEXTURE_INDEX_B,
	TEXTURE_INDEX_C,
	TEXTURE_INDEX_RIGHT,
	TEXTURE_INDEX_UP,
	TEXTURE_INDEX_SL,
	TEXTURE_INDEX_SR,
	TEXTURE_INDEX_ZL,
	TEXTURE_INDEX_FAILED,
	TEXTURE_INDEX_FIRE,
	TEXTURE_INDEX_ARM,
	TEXTURE_INDEX_PINK,
	TEXTURE_INDEX_PROGRESS_BAR,
	TEXTURE_INDEX_BAR_FRAME,
	TEXTURE_INDEX_BATON_TEST,
	TEXTURE_INDEX_STAMINA_GAUGE,


	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

// 色彩データ
typedef struct {

	// 色相
	float hue = 0;
	// 彩度
	float saturation = 0;
	// 明度
	float bright = 0;

}Color_Data;

// オブジェクトデータ
typedef struct {

	// 座標
	D3DXVECTOR2 Pos;
	// 拡大率
	D3DXVECTOR2 Scale;
	// 回転
	double Rotate = 0;

}Object_Data;

// ゲームオブジェクト
class GameObject {

private:

	// 遅れ処理用タイマー
	float Delay_Timer[3] = {0,0,0};
	// 遅く処理用フラグ
	bool Delay_Flag[3] = { true,true,true };
	// 画像サイズ
	D3DXVECTOR2 Size;

public:

	// ハンドル（アニメなし）
	int handle;

	// ハンドル配列（アニメあり）
	int Anime_handle[ANIME_CUT_LIMIT];

	// 色彩データ
	Color_Data Color;

	// オブジェクトデータ
	Object_Data Object;

	GameObject();

	~GameObject();

	// テクスチャロード (ファイルパス)
	// (アニメなし)(Initで使う)
	void LoadTexture(const char * name);

	// テクスチャロード (ファイルパス,フレーム数,横フレーム数,縦フレーム数,横画像サイズ,縦画像サイズ)
	// (アニメあり)(Initで使う)
	void LoadTexture(const char * name,int allcut,int xcut,int ycut,int xsize,int ysize);

	// 遅れ移動(方向,時間,x,y)
	// (必ずFlagを設定しないといけない)
	// (0:右 1: 左 2:上 3:下)
	void Delay_Move(int arrow,float sec,int x,int y,int speed);

	// 遅れ拡大(時間,拡大率,速度)
	// (必ずFlagを設定しないといけない)
	void Delay_Zoom(float sec,double scale,double speed);

	// 遅れ回転(時間,回転角度,速度)
	// (必ずFlagを設定しないといけない)
	void Delay_Rotate(float sec,double rotate,double speed);

	// 描画(透明)
	void Draw();
	
	// 部分描画(テクスチャx,テクスチャy,テクスチャxサイズ,テクスチャyサイズ,アルファ使う,反転処理使う)
	void Draw(int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	// アニメ描画(カット)
	void Draw_Anime(int cut);

	// カウスフィルター(重さ)
	void Gauss_Filter(int param);

	// HSBフィルター
	void HSB_Fillter();

	void SetDelayFlag(int index);

	// HSB設定
	void SetHSB(int hue, int saturation, int bright);

	// Getハンドル
	int GetHandle();

	// Get色彩データ
	Color_Data GetColorData();
};

// 画像パスベクトル
extern vector <const char *>TexturePassDict;