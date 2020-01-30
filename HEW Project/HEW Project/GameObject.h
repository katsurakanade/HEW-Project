#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include "main.h"
#include <vector>
#include <map>

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
	TEXTURE_INDEX_FIREBASE,
	TEXTURE_INDEX_ARM,
	TEXTURE_INDEX_PINK,
	TEXTURE_INDEX_PROGRESS_BAR,
	TEXTURE_INDEX_BAR_FRAME,
	TEXTURE_INDEX_BATON_ActionBoard,
	TEXTURE_INDEX_STAMINA_GAUGE,
	TEXTURE_INDEX_OVER,
	TEXTURE_INDEX_GREAT,
	TEXTURE_INDEX_GOOD,
	TEXTURE_INDEX_BAD,
	TEXTURE_INDEX_NUMBER,
	TEXTURE_INDEX_BACKGROUND,
	TEXTURE_INDEX_GAME_OVER,
	TEXTURE_INDEX_FIRE,
	TEXTURE_INDEX_LEFT,
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_GAME_CLEAR,
	TEXTURE_INDEX_PUSH_PLUS_TITLE,
	TEXTURE_INDEX_HANDDOWN,
	TEXTURE_INDEX_HANDUP,
	TEXTURE_INDEX_KEEP,
	TEXTURE_INDEX_ROTATE,
	TEXTURE_INDEX_TUTORIAL_LOGO,
	TEXTURE_INDEX_RESULT_BG,
	TEXTURE_INDEX_LEFT_ARROW,
	TEXTURE_INDEX_BATONTATTCH_BG,
	TEXTURE_INDEX_BATON_CHARENGE,
	TEXTURE_INDEX_BATON_1000P,
	TEXTURE_INDEX_GAMESTART,
	TEXTURE_INDEX_OKBATONTOUCHI_BG,
	TEXTURE_INDEX_OKBATONTOUCHI_BG_1,
	TEXTURE_INDEX_OKBATONTOUCHI_BG_2,
	TEXTURE_INDEX_OKBATONTOUCHI_BG_3,
	TEXTURE_INDEX_OKBATONTOUCHI_BG_4,
	TEXTURE_INDEX_OKBATONTOUCHI_BG_5,



	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

//方向キー
typedef enum {
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,

	ARROW_MAX,
}ARROW_KEY;

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

protected:

	// 遅れ処理用タイマー
	float Delay_Timer[4] = { 0,0,0,0 };
	// 遅く処理用フラグ
	bool Delay_Flag[4] = { false,false,false,false };
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

	// (true:終了, false:実行中) 遅れ直線移動移動(時間,x,y)
	// (必ずFlagを設定しないといけない)
	bool Delay_Move(float sec,float x,float y);

	// (true:終了, false:実行中) 遅れ曲線移動移動(時計回り==true, 曲線の弧の大きさ(0.0f~10.0f程度), 時間, ベクトルA保持値, ラジアン保持値)
	// (必ずFlagを設定しないといけない)
	bool Delay_CurveMove(bool cw, float CurveSize, float sec, D3DXVECTOR2 &VecA, float& Rad);

	// (true:終了, false:実行中) 遅れ拡大(時間,拡大率)
	// (必ずFlagを設定しないといけない)
	bool Delay_Zoom(float sec,double scale);

	// (true:終了, false:実行中) 遅れ回転(時間,回転角度)
	// (必ずFlagを設定しないといけない)
	bool Delay_Rotate(float sec,double rotate);

	// 描画(透明)
	void Draw();
	
	// 描画(回転中心指定)
	void Draw(float x,float y);
	
	// 部分描画(テクスチャx,テクスチャy,テクスチャxサイズ,テクスチャyサイズ,アルファ使う,反転処理使う)
	void Draw(int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	// アニメ描画(カット)
	void Draw_Anime(int cut);

	// カウスフィルター(重さ)
	void Gauss_Filter(int param);

	// HSBフィルター
	void HSB_Fillter();

	void Trans_Color(int r, int g, int b);

	// 削除
	// (画像メモリ)
	void Destroy();

	// 遅れフラグ設定(インデックス)
	void SetDelayFlag(int index);

	// HSB設定
	void SetHSB(int hue, int saturation, int bright);

	// Getハンドル
	int GetHandle();

	// Get色彩データ
	Color_Data GetColorData();

	bool GetDelayFlag(int index);

	float GetDelayTimer(int index);
};

// 画像パスベクトル
extern vector <const char *>TexturePassDict;

extern map <const char*, const char*> TextureDict;