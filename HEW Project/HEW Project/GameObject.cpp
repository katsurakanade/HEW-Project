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
};

void GameObject::LoadTexture(const char * name) {

	try {
		throw LoadGraph(name);
	}

	catch (int data) {

		if (data > 0) {
			handle = data;
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

void GameObject::Draw(int x,int y) {

	DrawGraph(x, y, this->handle, true);
}

void GameObject::Draw(int x, int y, int width, int height, bool use_alpha) {

	DrawExtendGraph(x, y, width, height, this->handle ,use_alpha);
}

void GameObject::Draw(int x, int y,int tsx,int tsy,int tex,int tey,bool use_alpha,bool turn) {

	DrawRectGraph(x, y, tsx, tsy, tex, tey,this->handle, use_alpha, turn);
}

void GameObject::Draw_Anime(int x,int y,int cut) {

	DrawGraph(x, y, Anime_handle[cut],TRUE);

}

void GameObject::Gauss_Filter(int param) {
	
	GraphFilter(this->handle, DX_GRAPH_FILTER_GAUSS, 16, param);

}


void GameObject::HSB_Fillter() {

	GraphFilter(this->handle, DX_GRAPH_FILTER_HSB, 0, this->Color.hue, this->Color.saturation, this->Color.bright);
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