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
};

// ‰æ‘œƒpƒXƒxƒNƒgƒ‹
vector <const char *>TexturePassDict = {
	"asset/texture/start.png",
	"asset/texture/Exit.png",
	"asset/texture/airou.png",
	"asset/texture/luotianyi.png",//
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
	"asset/texture/effect.png",
	"asset/texture/game_over.png"
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
			char errmsg1[255] = "‰æ‘œ“Ç‚Ýž‚ÝƒGƒ‰[ ŠY“–‰æ‘œ–¼‚Í‚ ‚è‚Ü‚¹‚ñ\n";
			MessageBox(GetHWND(), errmsg1, "ŒxI", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "‰æ‘œ“Ç‚Ýž‚ÝƒGƒ‰[ ŠY“–‰æ‘œ‚Í‚ ‚è‚Ü‚¹‚ñ\n";
			MessageBox(GetHWND(), strcat(errmsg2,name), "ŒxI", MB_ICONWARNING);
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
			char errmsg1[255] = "‰æ‘œ“Ç‚Ýž‚ÝƒGƒ‰[ ŠY“–‰æ‘œ–¼‚Í‚ ‚è‚Ü‚¹‚ñ\n";
			MessageBox(GetHWND(), errmsg1, "ŒxI", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "‰æ‘œ“Ç‚Ýž‚ÝƒGƒ‰[ ŠY“–‰æ‘œ‚Í‚ ‚è‚Ü‚¹‚ñ\n";
			MessageBox(GetHWND(), strcat(errmsg2, name), "ŒxI", MB_ICONWARNING);
			exit(1);
		}
	}
}

void GameObject::Delay_Move(int arrow,float sec,float x,float y) {

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

	Delay_Timer[0] += SECONDS;

	if (Delay_Timer[0] >= sec) {
		Delay_Flag[0] = false;
		Delay_Timer[0] = 0.0f;
	}

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
		Object.Rotate += rotateframe;
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