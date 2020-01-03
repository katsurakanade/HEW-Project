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


//直線移動(相対座標を指定)
void GameObject::Delay_Move(float sec,float x,float y)
{

	if (Delay_Flag[0])
	{

		Delay_Timer[0] += SECONDS;

		if (Delay_Timer[0] >= sec) {
			Delay_Flag[0] = false;
			Delay_Timer[0] = 0.0f;
			return;
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

}



// 遅れ直線移動移動(時計回り==true, 曲線の弧の大きさ(0~10), 時間, x, y)
void GameObject::Delay_CurveMove(bool cw, float CurveSize, float sec, float x, float y)
{

	if (Delay_Flag[0])
	{
		// 変数宣言
		static bool DoOnece = true;     //初回のみ処理
		static D3DXVECTOR2 VecA;     // 現在座標→移動先座標
		D3DXVECTOR2 VecB;     // ベクトルAに対する垂直ベクトル
		D3DXVECTOR2 VecV;     // １フレーム毎の実際の移動座標
		float VecABcrossOut;     // ベクトルAとベクトルBの外積結果
		static float Rad = 0;     //弧を描くラジアンの値

		// 処理ヘッド ----------------------


	// 時間計測
		Delay_Timer[0] += SECONDS;

		// Finalize処理
		if (Delay_Timer[0] >= sec) {
			Delay_Flag[0] = false;
			Delay_Timer[0] = 0.0f;

			DoOnece = true;     //次使う用
			return;
		}




		// 初回処理
		if (DoOnece)
		{
			VecA = { x, y };     //ベクトルAを作成
			DoOnece = false;
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
		{     // 時計回りの処理
			if (VecABcrossOut < 0)     //ベクトルAの右側にある
			{
				VecB *= -1;
			}
		}
		else
		{     // 反時計回り
			if (VecABcrossOut > 0)     //ベクトルAの左側にある
			{
				VecB *= -1;
			}
		}


		// ベクトルVを求める
		VecV = VecB * (CurveSize * cos(Rad));


		//================ 移動処理 ================

		const float moveframeX = (x / 60 / sec) + VecV.x;
		//const float moveframeX = cos(Rad);

		if (Delay_Flag[0]) {
			Object.Pos.x += moveframeX;
		}

		const float moveframeY = (y / 60 / sec) + VecV.y;
		//const float moveframeY = cos(Rad);

		if (Delay_Flag[0]) {
			Object.Pos.y += moveframeY;
		}


		// ベクトルAの移動処理
		VecA.x -= x / 60 / sec;
		VecA.y -= y / 60 / sec;

	}// if (Delay_Flag[0])


}




void GameObject::Delay_Zoom(float sec,double scale) {

	if (Delay_Flag[1])
	{

		const float zoomframe = scale / 60 / sec;

		Delay_Timer[1] += SECONDS;

		if (Delay_Timer[1] >= sec) {
			Delay_Flag[1] = false;
			Delay_Timer[1] = 0.0f;
		}

		if (Delay_Flag[1]) {
			Object.Scale.x += zoomframe;
			Object.Scale.y += zoomframe;
		}

	}// if (Delay_Flag[1])

}

void GameObject::Delay_Rotate(float sec,double rotate) {

	if (Delay_Flag[2])
	{

		const float rotateframe = rotate / 60 / sec;

		Delay_Timer[2] += SECONDS;

		if (Delay_Timer[2] >= sec) {
			Delay_Flag[2] = false;
			Delay_Timer[2] = 0.0f;
		}

		if (Delay_Flag[2]) {
			Object.Rotate += rotateframe * PI / 180;
		}

	}// if (Delay_Flag[2])

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