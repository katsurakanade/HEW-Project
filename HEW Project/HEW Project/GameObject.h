#pragma once
#include <d3d9.h>
#include "DxLib.h"
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

	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

// 色彩データ
typedef struct {

	int hue = 0;
	int saturation = 0;
	int bright = 0;

}Color_Data;

typedef struct {

	double Scale = 1.0;
	double Rotate = 0;

}Object_Data;

// ゲームオブジェクト
class GameObject {

private:

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

	// 描画(x,y)(透明)
	void Draw(int x, int y);
	
	// 描画(x,y,アルファ使う)
	void Draw(int x, int y, bool use_alpha);

	// 部分描画(x,y,テクスチャx,テクスチャy,テクスチャxサイズ,テクスチャyサイズ,アルファ使う,反転処理使う)
	void Draw(int x, int y, int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	// アニメ描画(x,y,カット)
	void Draw_Anime(int x,int y,int cut);

	// カウスフィルター(重さ)
	void Gauss_Filter(int param);

	// HSBフィルター
	void HSB_Fillter();

	// HSB設定
	void SetHSB(int hue, int saturation, int bright);

	// Getハンドル
	int GetHandle();

	// Get色彩データ
	Color_Data GetColorData();
};

// 画像パスベクトル
extern vector <const char *>TexturePassDict;