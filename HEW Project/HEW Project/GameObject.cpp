#define _CRT_SECURE_NO_WARNINGS

#include <d3dx9.h>
#include "mydirect3d.h"
#include "GameObject.h"
#include "DxLib.h"
#include <algorithm>
#include "main.h"
#include <string.h>

map <const char*, const char*> TextureDict = {
	{"Start","asset/texture/start.png"},
	{"Exit","asset/texture/exit.png"},
	{"Airou","asset/texture/airou.png"},
	{"Action1","asset/texture/action1.png"},
	{"Action2","asset/texture/action2.png"},
	{"Action3","asset/texture/action3.png"},
	{"A","asset/texture/a.png"},
	{"B","asset/texture/b.png"},
	{"C","asset/texture/c.png"},
	{"Right","asset/texture/right.png"},
	{"Up","asset/texture/up.png"},
	{"SL","asset/texture/SL.png"},
	{"SR","asset/texture/SR.png"},
	{"ZL","asset/texture/ZL.png"},
	{"Failed","asset/texture/Failde.png"},
	{"arm","asset/texture/arm.png"},
	{"pink","asset/texture/pink.png"},
	{"Progressbar","asset/texture/progressbar.png"},
	{"Bar_frame","asset/texture/bar_frame.png"},
	{"Batontouch_test","asset/texture/Batontouch_test.png"},
	{"Stamina_frame","asset/texture/stamina_frame.png"},
	{"Over","asset/texture/OVER.png"},
	{"Great","asset/texture/GREAT.png"},
	{"Good","asset/texture/GOOD.png"},
	{"Bad","asset/texture/BAD.png"},
	{"Number","asset/texture/Number.png"},
	{"Title","asset/texture/Title.jpg"},
	{"alpha","asset/texture/alpha.png"},
	{"excellent","asset/texture/excellent.png"},
	{"alphabg","asset/texture/alphabg.png"},
};

// 画像パスベクトル
vector <const char *>TexturePassDict = {
	"asset/texture/start.png",
	"asset/texture/Exit.png",
	"asset/texture/airou.png",
	"asset/texture/action1.png",
	"asset/texture/action2.png",
	"asset/texture/action3.png",
	"asset/texture/a.png",
	"asset/texture/b.png",
	"asset/texture/c.png",
	"asset/texture/right.png",
	"asset/texture/up.png",
	"asset/texture/SL.png",
	"asset/texture/SR.png",
	"asset/texture/ZL.png",
	"asset/texture/Failed.png",
	"asset/texture/holyfire.png",
	"asset/texture/arm.png",
	"asset/texture/pink.png",
	"asset/texture/progressbar.png",
	"asset/texture/bar_frame.png",
	"asset/texture/Batontouch_test.png",
	"asset/texture/stamina_frame.png",
	"asset/texture/OVER.png",
	"asset/texture/GREAT.png",
	"asset/texture/GOOD.png",
	"asset/texture/BAD.png",
	"asset/texture/Number.png",
	"asset/texture/BackGround.png",
	"asset/texture/game_over.png",
	"asset/texture/Fire.png",
	"asset/texture/Left.png",
	"asset/texture/result.png",
	"asset/texture/Game_Clear.png",
	"asset/texture/push_plus_title.png",
	"asset/texture/BatontattchBG.png",
	"asset/texture/BatonCharenge.png",
	"asset/texture/Baton1000P.png",
};

GameObject::GameObject() {
	Object.Scale.x = 1.0f;
	Object.Scale.y = 1.0f;
}

GameObject::~GameObject() {
	
}

void GameObject::LoadTexture(const char * name) {

	try {
		throw LoadGraph(name);
	}

	catch (int data) {

		if (data != -1) {
			handle = data;
			GetGraphSizeF(handle, &Size.x, &Size.y);
		}

		else if (name == NULL) {
			char errmsg1[255] = "画像読み込みエラー 該当画像名はありません\n";
			MessageBox(GetHWND(), errmsg1, "警告！", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "画像読み込みエラー 該当画像はありません\n";
			MessageBox(GetHWND(), strcat(errmsg2,name), "警告！", MB_ICONWARNING);
			exit(1);
		}
	}
}

void GameObject::LoadTexture(const char *name, int allcut, int xcut, int ycut, int xsize, int ysize) {

	try {
		throw LoadDivGraph(name, allcut, xcut, ycut, xsize, ysize, Anime_handle);
	}

	catch (int data) {

		if (data != -1) {
			handle = data;
			GetGraphSizeF(handle, &Size.x, &Size.y);
		}

		else if (name == NULL) {
			char errmsg1[255] = "画像読み込みエラー 該当画像名はありません\n";
			MessageBox(GetHWND(), errmsg1, "警告！", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "画像読み込みエラー 該当画像はありません\n";
			MessageBox(GetHWND(), strcat(errmsg2, name), "警告！", MB_ICONWARNING);
			exit(1);
		}
	}
}



// (true:終了, false:実行中) 遅れ直線移動移動(時間,x,y)
// (必ずFlagを設定しないといけない)
bool GameObject::Delay_Move(float sec,float x,float y)
{
	bool PlayFlag = false;     // true:終了, false:実行中

	// 処理ヘッダ

	if (Delay_Flag[0])
	{

		Delay_Timer[0] += SECONDS;

		if (Delay_Timer[0] >= sec) {
			Delay_Flag[0] = false;
			Delay_Timer[0] = 0.0f;
			PlayFlag = true;     // エフェクト終了
			return PlayFlag;
		}


		const float moveframeY = y / 60 / sec;

		if (Delay_Flag[0]) {
			Object.Pos.y += moveframeY;
		}

		const float moveframeX = x / 60 / sec;

		if (Delay_Flag[0]) {
			Object.Pos.x += moveframeX;
		}

	}// if (Delay_Flag[0])

	return PlayFlag;
}

// (true:終了, false:実行中) 遅れ曲線移動移動(反時計回り==true, 曲線の弧の大きさ(0.0f~10.0f程度), 時間, ベクトルA保持値, ラジアン保持値)
// (必ずFlagを設定しないといけない)
bool GameObject::Delay_CurveMove(bool cw, float CurveSize, float sec, D3DXVECTOR2& VecA, float& Rad)
{
	bool PlayFlag = false;     // true:終了, false:実行中

	// 処理ヘッダ

	if (Delay_Flag[1])
	{
		// 変数宣言
		D3DXVECTOR2 VecB;     // ベクトルAに対する垂直ベクトル
		D3DXVECTOR2 VecV;     // １フレーム毎の実際の移動座標
		float VecABcrossOut;     // ベクトルAとベクトルBの外積結果

		// 処理ヘッド ----------------------


	// 時間計測
		Delay_Timer[1] += SECONDS;

		// Finalize処理
		if (Delay_Timer[1] >= sec) {
			Delay_Flag[1] = false;
			Delay_Timer[1] = 0.0f;
			PlayFlag = true;     // エフェクト終了
			return PlayFlag;
		}



		Rad += PI / 60 / sec;     //１フレームあたりのラジアン増加量


		//// ベクトルBを求める(Byは＋側選択) ////
		VecB.y = 2.0f * VecA.x / sqrt((VecA.x * VecA.x) + (VecA.y * VecA.y));
		VecB.x = -(VecA.y * VecB.y) / VecA.x;

		// ベクトルAとベクトルBの外積を取得
		VecABcrossOut = VecA.x * VecB.y - VecB.x * VecA.y;
		
		// ベクトルBを正規化する
		D3DXVec2Normalize(&VecB, &VecB);

		// ベクトルBの向き判断
		if (cw)
		{     // 反時計回りの処理
			if (VecABcrossOut < 0)     //ベクトルAの左側にある
			{
				VecB *= -1;
			}
		}
		else
		{     // 時計回り
			if (VecABcrossOut > 0)     //ベクトルAの右側にある
			{
				VecB *= -1;
			}
		}


		// ベクトルVを求める
		VecV = VecB * (CurveSize * cos(Rad));


		//================ 移動処理 ================

		const float moveframeX = (VecA.x / 60 / sec) + VecV.x;

		if (Delay_Flag[1]) {
			Object.Pos.x += moveframeX;
		}

		const float moveframeY = (VecA.y / 60 / sec) + VecV.y;

		if (Delay_Flag[1]) {
			Object.Pos.y += moveframeY;
		}


		// ベクトルAの移動処理
		VecA.x -= VecA.x / 60 / sec;
		VecA.y -= VecA.y / 60 / sec;

	}// if (Delay_Flag[1])

	return PlayFlag;
}

// (true:終了, false:実行中) 遅れ拡大(時間,拡大率)
// (必ずFlagを設定しないといけない)
bool GameObject::Delay_Zoom(float sec,double scale)
{
	bool PlayFlag = false;     // true:終了, false:実行中

	// 処理ヘッダ

	if (Delay_Flag[2])
	{

		const float zoomframe = scale / 60 / sec;

		Delay_Timer[2] += SECONDS;

		if (Delay_Timer[2] >= sec) {
			Delay_Flag[2] = false;
			Delay_Timer[2] = 0.0f;
			PlayFlag = true;     // エフェクト終了
			return PlayFlag;
		}

		if (Delay_Flag[2]) {
			Object.Scale.x += zoomframe;
			Object.Scale.y += zoomframe;
		}

	}// if (Delay_Flag[2])

	return PlayFlag;
}

// (true:終了, false:実行中) 遅れ回転(時間,回転角度)
// (必ずFlagを設定しないといけない)
bool GameObject::Delay_Rotate(float sec,double rotate)
{
	bool PlayFlag = false;     // true:終了, false:実行中

	// 処理ヘッダ

	if (Delay_Flag[3])
	{

		const float rotateframe = rotate / 60 / sec;

		Delay_Timer[3] += SECONDS;

		if (Delay_Timer[3] >= sec) {
			Delay_Flag[3] = false;
			Delay_Timer[3] = 0.0f;
			PlayFlag = true;     // エフェクト終了
			return PlayFlag;
		}

		if (Delay_Flag[3]) {
			Object.Rotate += rotateframe * PI / 180;
		}

	}// if (Delay_Flag[3])

	return PlayFlag;
}

void GameObject::Draw() {

	DrawRotaGraph3((int)Object.Pos.x, (int)Object.Pos.y, Size.x / 2, Size.y / 2, Object.Scale.x, Object.Scale.y, Object.Rotate, handle, true, false);
}

void GameObject::Draw(float x, float y) {

	DrawRotaGraph3((int)Object.Pos.x, (int)Object.Pos.y, x ,y , Object.Scale.x, Object.Scale.y, Object.Rotate, handle, true, false);
}

void GameObject::Draw(int tsx,int tsy,int tex,int tey,bool use_alpha,bool turn) {

	DrawRectGraph(Object.Pos.x,Object.Pos.y, tsx, tsy, tex, tey,this->handle, use_alpha, turn);
}

void GameObject::Draw_Anime(int cut) {

	DrawRotaGraph3((int)Object.Pos.x, (int)Object.Pos.y, Size.x / 2 , Size.y / 2, Object.Scale.x, Object.Scale.y, Object.Rotate, Anime_handle[cut], true, false);
}

void GameObject::Gauss_Filter(int param) {
	
	GraphFilter(this->handle, DX_GRAPH_FILTER_GAUSS, 16, param);

}

void GameObject::HSB_Fillter() {

	GraphFilter(this->handle, DX_GRAPH_FILTER_HSB, 0, (int)this->Color.hue, (int)this->Color.saturation, (int)this->Color.bright);
}

void GameObject::Trans_Color(int r,int g,int b) {

	SetTransColor(r, g, b);

}

void GameObject::Destroy() {

	DeleteGraph(handle);

	if (Anime_handle[0] != NULL) {
		for (int i = 0; i < sizeof(Anime_handle) / sizeof(Anime_handle[0]); i++) {
			DeleteGraph(Anime_handle[i]);
		}
	}
}

void GameObject::SetDelayFlag(int index) {

	Delay_Flag[index] = true;

}

void GameObject::SetHSB(int hue,int saturation,int bright) {

	this->Color.hue = hue;
	this->Color.saturation = saturation;
	this->Color.bright = bright;
}



int GameObject::GetHandle() {
	return handle;
}

Color_Data GameObject::GetColorData() {
	return Color;
}

bool GameObject::GetDelayFlag(int index) {
	return Delay_Flag[index];
}

float GameObject::GetDelayTimer(int index) {
	return Delay_Timer[index];
}