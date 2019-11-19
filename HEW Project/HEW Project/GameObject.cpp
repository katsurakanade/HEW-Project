#define _CRT_SECURE_NO_WARNINGS

#include <d3dx9.h>
#include "mydirect3d.h"
#include "GameObject.h"
#include "DxLib.h"
#include <algorithm>
#include "main.h"
#include <string.h>

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

		if (data > 0) {
			handle = data;
			GetGraphSizeF(handle, &Size.x, &Size.y);
		}
		else {
			char errmsg[255] = "画像読み込みエラー\n";
			MessageBox(GetHWND(), strcat(errmsg,name), "警告！", MB_ICONWARNING);
			exit(1);
		}
	}
}

void GameObject::LoadTexture(const char *name, int allcut, int xcut, int ycut, int xsize, int ysize) {

	try {
		throw LoadDivGraph(name, allcut, xcut, ycut, xsize, ysize, Anime_handle);
	}

	catch (int data) {
		if (data < 0) {
			char errmsg[255] = "画像読み込みエラー\n";
			MessageBox(GetHWND(), strcat(errmsg, name), "警告！", MB_ICONWARNING);
		}
	}
}

void GameObject::Delay_Move(int arrow,float sec,int x,int y,int speed) {

	if (Delay_Flag[0]) {
		Delay_Timer[0] += SECONDS;
	}

	if (Delay_Timer[0] >= sec) {

		if (arrow == 0) {
			Object.Pos.x += speed;
		}

		if (arrow == 1) {
			Object.Pos.x -= speed;
		}

		if (arrow == 2) {
			Object.Pos.y += speed;
		}

		if (arrow == 3) {
			Object.Pos.y -= speed;
		}

	}

	if (arrow == 0 && Object.Pos.x >= x) {
		Delay_Timer[0] = 0.0f;
		Delay_Flag[0] = false;
	}

	else if (arrow == 1 && Object.Pos.x <= x) {
		Delay_Timer[0] = 0.0f;
		Delay_Flag[0] = false;
	}

	else if (arrow == 2 && Object.Pos.y >= y) {
		Delay_Timer[0] = 0.0f;
		Delay_Flag[0] = false;
	}

	else if (arrow == 3 && Object.Pos.y <= y) {
		Delay_Timer[0] = 0.0f;
		Delay_Flag[0] = false;
	}
}

void GameObject::Delay_Zoom(float sec,double scale,double speed) {

	if (Delay_Flag[1]) {
		Delay_Timer[1] += SECONDS;
	}

	if (Delay_Timer[1] >= sec) {
		Object.Scale.x += speed;
		Object.Scale.y += speed;
	}

	if (Object.Scale.x >= scale) {
		Delay_Timer[1] = 0.0f;
		Delay_Flag[1] = false;
	}

}

void GameObject::Delay_Rotate(float sec,double rotate,double speed) {

	if (Delay_Flag[2]) {
		Delay_Timer[2] += SECONDS;
	}

	if (Delay_Timer[2] >= sec) {
		Object.Rotate += (DOT * speed);
	}

	if (Object.Rotate >= (DOT * rotate)) {
		Delay_Timer[2] = 0.0f;
		Delay_Flag[2] = false;
	}

}

void GameObject::Draw() {

	DrawRotaGraph3((int)Object.Pos.x, (int)Object.Pos.y, Size.x / 2, Size.y / 2, Object.Scale.x, Object.Scale.y, Object.Rotate, handle, true, false);
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