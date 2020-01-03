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

// �摜�p�X�x�N�g��
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
			char errmsg1[255] = "�摜�ǂݍ��݃G���[ �Y���摜���͂���܂���\n";
			MessageBox(GetHWND(), errmsg1, "�x���I", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "�摜�ǂݍ��݃G���[ �Y���摜�͂���܂���\n";
			MessageBox(GetHWND(), strcat(errmsg2,name), "�x���I", MB_ICONWARNING);
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
			char errmsg1[255] = "�摜�ǂݍ��݃G���[ �Y���摜���͂���܂���\n";
			MessageBox(GetHWND(), errmsg1, "�x���I", MB_ICONWARNING);
			exit(1);
		}

		else {
			char errmsg2[255] = "�摜�ǂݍ��݃G���[ �Y���摜�͂���܂���\n";
			MessageBox(GetHWND(), strcat(errmsg2, name), "�x���I", MB_ICONWARNING);
			exit(1);
		}
	}
}


//�����ړ�(���΍��W���w��)
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



// �x�꒼���ړ��ړ�(���v���==true, �Ȑ��̌ʂ̑傫��(0~10), ����, x, y)
void GameObject::Delay_CurveMove(bool cw, float CurveSize, float sec, float x, float y)
{

	if (Delay_Flag[0])
	{
		// �ϐ��錾
		static bool DoOnece = true;     //����̂ݏ���
		static D3DXVECTOR2 VecA;     // ���ݍ��W���ړ�����W
		D3DXVECTOR2 VecB;     // �x�N�g��A�ɑ΂��鐂���x�N�g��
		D3DXVECTOR2 VecV;     // �P�t���[�����̎��ۂ̈ړ����W
		float VecABcrossOut;     // �x�N�g��A�ƃx�N�g��B�̊O�ό���
		static float Rad = 0;     //�ʂ�`�����W�A���̒l

		// �����w�b�h ----------------------


	// ���Ԍv��
		Delay_Timer[0] += SECONDS;

		// Finalize����
		if (Delay_Timer[0] >= sec) {
			Delay_Flag[0] = false;
			Delay_Timer[0] = 0.0f;

			DoOnece = true;     //���g���p
			return;
		}




		// ���񏈗�
		if (DoOnece)
		{
			VecA = { x, y };     //�x�N�g��A���쐬
			DoOnece = false;
		}


		Rad += PI / 60 / sec;     //�P�t���[��������̃��W�A��������


		//// �x�N�g��B�����߂�(By�́{���I��) ////
		VecB.y = 2.0f * VecA.x / sqrt((VecA.x * VecA.x) + (VecA.y * VecA.y));
		VecB.x = -(VecA.y * VecB.y) / VecA.x;

		// �x�N�g��A�ƃx�N�g��B�̊O�ς��擾
		VecABcrossOut = VecA.x * VecB.y - VecB.x * VecA.y;
		
		// �x�N�g��B�𐳋K������
		D3DXVec2Normalize(&VecB, &VecB);

		// �x�N�g��B�̌������f
		if (cw)
		{     // ���v���̏���
			if (VecABcrossOut < 0)     //�x�N�g��A�̉E���ɂ���
			{
				VecB *= -1;
			}
		}
		else
		{     // �����v���
			if (VecABcrossOut > 0)     //�x�N�g��A�̍����ɂ���
			{
				VecB *= -1;
			}
		}


		// �x�N�g��V�����߂�
		VecV = VecB * (CurveSize * cos(Rad));


		//================ �ړ����� ================

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


		// �x�N�g��A�̈ړ�����
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