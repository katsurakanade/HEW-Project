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
	"asset/texture/push_plus_title.png",
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
void GameObject::Delay_Move(float sec,float x,float y) {

/*
	if (arrow == ARROW_UP || arrow == ARROW_DOWN) {
		const float moveframeY = y / 60 / sec;

		if (Delay_Flag[0]) {
			Object.Pos.y += moveframeY;
		}
	}

	else if (arrow == ARROW_LEFT || arrow == ARROW_RIGHT){

		const float moveframeX = x / 60 / sec;

		if (Delay_Flag[0]) {
			Object.Pos.x += moveframeX;
		}
	}
*/

	

	const float moveframeY = y / 60 / sec;

	if (Delay_Flag[0]) {
		Object.Pos.y += moveframeY;
	}

	const float moveframeX = x / 60 / sec;

	if (Delay_Flag[0]) {
		Object.Pos.x += moveframeX;
	}



	Delay_Timer[0] += SECONDS;

	if (Delay_Timer[0] >= sec) {
		Delay_Flag[0] = false;
		Delay_Timer[0] = 0.0f;
	}

}

//--------------------------------------------------



//// r(半径)を指定して現在地から目的座標まで曲線で移動する関数(r <= 0 : r=0.01) ////

	// 関数呼んだ時だけ処理 //
// this->Object.Pos;     //自分の座標
// 相手の座標：引数の値
/*
	自分座標と相手座標(移動先)からベクトルA(Ax, Ay)を作る
	ベクトルAの距離を測って中点Mを取る

	○垂直ベクトルを取得する(求めるベクトル成分：Vx, Vy)
	式1：Vx^2 + Vy^2 = 1
	式2：Vx = -(Ay*Vy) / Ax
	→(-(Ay*Vy) / Ax)^2 + Vy^2 = 1
	Vy = ± 2Ax / sqrt(Ax^2 + Ay^2)
	Vx = -(Ay*Vy) / Ax に Vyを代入
	V(Vx, Vy)


	○外積計算
	ベクトルVを正規化する
	ベクトルV＊r(引数で指定した半径) = Vmax
	Vmax + M = 自分座標から相手座標までの角度を算出する原点O
	ベクトルAに対してベクトルB(自分座標→原点O)の外積を取る

	※時計回りの弧(曲線)を描きたいならベクトルAに対して右側(外積結果マイナス)の原点Oを採用する
	※反時計回りの弧(曲線)を描きたいならベクトルAに対して左側(外積結果プラス)の原点Oを採用する
	※→逆なら(*= -1)

	O→自分座標：ベクトルC
	O→相手座標：ベクトルD
	rad = acos( (C・D) / (C.Length * D.Length) )


	// 毎フレーム処理 //
//上で求めた「rad(ラジアン)」をsin(), cos()にぶち込んで移動量を計算

*/

//--------------------------------------------------

// 遅れ直線移動移動(時計回り==true, 曲線の弧の大きさ, オブジェクトの現在座標, 時間, x, y)
void GameObject::Delay_CurveMove(bool cw, float r, const D3DXVECTOR2 &pos, float sec, float x, float y)
{

	/*

	// 変数宣言
	float Rad;     //移動に使用するラジアンθ( ベクトルCとベクトルDの角度 )
	float rad_a;     //移動に使用するラジアンα( ベクトルAと-ベクトルCの角度 )
	D3DXVECTOR3 ThisPos = { pos.x, pos.y, 0.0f };     //自分座標(初期位置)
	D3DXVECTOR3 VecA;     //自分座標(初期位置)→移動先座標
	D3DXVECTOR3 VecB;     //自分座標(初期位置)→原点O
	D3DXVECTOR3 VecC;     //原点O→自分座標
	D3DXVECTOR3 VecD;     //原点O→相手座標
	D3DXVECTOR3 MovePos = {x, y, 0.0f};     //移動先座標(終点位置)
	D3DXVECTOR3 MiddlePoint;     //中点M
	D3DXVECTOR3 VecV;     //ベクトルAに対する垂直ベクトル
	D3DXVECTOR3 VecVmax;     //VecV * r (半径)
	D3DXVECTOR3 CenterPoint;     //原点O
	D3DXVECTOR3 VecABCrossOut;     //ベクトルAとベクトルBの外積結果


	// 処理ヘッド=============

	//ベクトルA作成
	VecA = MovePos - ThisPos;

	//中点M作成(相対距離)
	MiddlePoint.x = VecA.x / 2.0f;
	MiddlePoint.y = VecA.y / 2.0f;

	//垂直ベクトル:VecV作成(ｙが＋側)
	VecV.y = 2 * VecA.x / sqrt((VecA.x * VecA.x) + (VecA.y * VecA.y));
	VecV.x = -(VecA.y * VecV.y) / VecA.x;

	//VecV正規化
	D3DXVec3Normalize(&VecV, &VecV);

	//VecVを指定半径倍率に直す
	VecVmax = VecV * r;

	//原点Oを算出(座標)
	CenterPoint = VecVmax + MiddlePoint;

	//ベクトルBを作る
	VecB = MiddlePoint - ThisPos;

	//ベクトルAとベクトルBの外積
	D3DXVec3Cross(&VecABCrossOut, &VecA, &VecB);

	//時計回り、反時計回りを判別(原点Oの確定)
	if (cw)     // 時計回りの処理
	{
		if (!(VecABCrossOut < 0))     //逆だったら
		{
			CenterPoint *= -1;     // 逆側の原点Oを使用する
		}
	}
	else     // 反時計回りの処理
	{
		if (!(VecABCrossOut > 0))     //逆だったら
		{
			CenterPoint *= -1;     // 逆側の原点Oを使用する
		}
	}


	//ベクトルCと	ベクトルDを作る
	VecC = ThisPos - CenterPoint;
	VecC = MovePos - CenterPoint;


	//// ラジアンを求める ////
	Rad = acos(D3DXVec3Dot(&VecC, &VecD) / ( D3DXVec3Length(&VecC) * D3DXVec3Length(&VecD) ) );     //ベクトルCとベクトルDの角度
	VecC *= -1;     //ベクトルC反転
	rad_a = acos(D3DXVec3Dot(&VecA, &VecC) / ( D3DXVec3Length(&VecA) * D3DXVec3Length(&VecC) ) );     //ベクトルAと-ベクトルCの角度
	VecC *= -1;     //ベクトルC反転(元に戻す)



	//================移動処理(絶対距離)================

	const float moveframeY = ((D3DXVec3Length(&VecA) * sin(rad_a))  * sin(Rad)) / 60 / sec;

	if (Delay_Flag[0]) {
		Object.Pos.y += moveframeY;
	}

	const float moveframeX = ((D3DXVec3Length(&VecA) * cos(rad_a))  * cos(Rad)) / 60 / sec;

	if (Delay_Flag[0]) {
		Object.Pos.x += moveframeX;
	}



	Delay_Timer[0] += SECONDS;

	if (Delay_Timer[0] >= sec) {
		//Finalize処理
		Delay_Flag[0] = false;
		Delay_Timer[0] = 0.0f;





	}

	*/

}







void GameObject::Delay_Zoom(float sec,double scale) {

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

}

void GameObject::Delay_Rotate(float sec,double rotate) {

	const float rotateframe = rotate / 60 / sec;

	Delay_Timer[2] += SECONDS;

	if (Delay_Timer[2] >= sec) {
		Delay_Flag[2] = false;
		Delay_Timer[2] = 0.0f;
	}

	if (Delay_Flag[2]) {
		Object.Rotate += rotateframe * PI/180;
	}

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