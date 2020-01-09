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



//// r(���a)���w�肵�Č��ݒn����ړI���W�܂ŋȐ��ňړ�����֐�(r <= 0 : r=0.01) ////

	// �֐��Ă񂾎��������� //
// this->Object.Pos;     //�����̍��W
// ����̍��W�F�����̒l
/*
	�������W�Ƒ�����W(�ړ���)����x�N�g��A(Ax, Ay)�����
	�x�N�g��A�̋����𑪂��Ē��_M�����

	�������x�N�g�����擾����(���߂�x�N�g�������FVx, Vy)
	��1�FVx^2 + Vy^2 = 1
	��2�FVx = -(Ay*Vy) / Ax
	��(-(Ay*Vy) / Ax)^2 + Vy^2 = 1
	Vy = �} 2Ax / sqrt(Ax^2 + Ay^2)
	Vx = -(Ay*Vy) / Ax �� Vy����
	V(Vx, Vy)


	���O�όv�Z
	�x�N�g��V�𐳋K������
	�x�N�g��V��r(�����Ŏw�肵�����a) = Vmax
	Vmax + M = �������W���瑊����W�܂ł̊p�x���Z�o���錴�_O
	�x�N�g��A�ɑ΂��ăx�N�g��B(�������W�����_O)�̊O�ς����

	�����v���̌�(�Ȑ�)��`�������Ȃ�x�N�g��A�ɑ΂��ĉE��(�O�ό��ʃ}�C�i�X)�̌��_O���̗p����
	�������v���̌�(�Ȑ�)��`�������Ȃ�x�N�g��A�ɑ΂��č���(�O�ό��ʃv���X)�̌��_O���̗p����
	�����t�Ȃ�(*= -1)

	O���������W�F�x�N�g��C
	O��������W�F�x�N�g��D
	rad = acos( (C�ED) / (C.Length * D.Length) )


	// ���t���[������ //
//��ŋ��߂��urad(���W�A��)�v��sin(), cos()�ɂԂ�����ňړ��ʂ��v�Z

*/

//--------------------------------------------------

// �x�꒼���ړ��ړ�(���v���==true, �Ȑ��̌ʂ̑傫��, �I�u�W�F�N�g�̌��ݍ��W, ����, x, y)
void GameObject::Delay_CurveMove(bool cw, float r, const D3DXVECTOR2 &pos, float sec, float x, float y)
{

	/*

	// �ϐ��錾
	float Rad;     //�ړ��Ɏg�p���郉�W�A����( �x�N�g��C�ƃx�N�g��D�̊p�x )
	float rad_a;     //�ړ��Ɏg�p���郉�W�A����( �x�N�g��A��-�x�N�g��C�̊p�x )
	D3DXVECTOR3 ThisPos = { pos.x, pos.y, 0.0f };     //�������W(�����ʒu)
	D3DXVECTOR3 VecA;     //�������W(�����ʒu)���ړ�����W
	D3DXVECTOR3 VecB;     //�������W(�����ʒu)�����_O
	D3DXVECTOR3 VecC;     //���_O���������W
	D3DXVECTOR3 VecD;     //���_O��������W
	D3DXVECTOR3 MovePos = {x, y, 0.0f};     //�ړ�����W(�I�_�ʒu)
	D3DXVECTOR3 MiddlePoint;     //���_M
	D3DXVECTOR3 VecV;     //�x�N�g��A�ɑ΂��鐂���x�N�g��
	D3DXVECTOR3 VecVmax;     //VecV * r (���a)
	D3DXVECTOR3 CenterPoint;     //���_O
	D3DXVECTOR3 VecABCrossOut;     //�x�N�g��A�ƃx�N�g��B�̊O�ό���


	// �����w�b�h=============

	//�x�N�g��A�쐬
	VecA = MovePos - ThisPos;

	//���_M�쐬(���΋���)
	MiddlePoint.x = VecA.x / 2.0f;
	MiddlePoint.y = VecA.y / 2.0f;

	//�����x�N�g��:VecV�쐬(�����{��)
	VecV.y = 2 * VecA.x / sqrt((VecA.x * VecA.x) + (VecA.y * VecA.y));
	VecV.x = -(VecA.y * VecV.y) / VecA.x;

	//VecV���K��
	D3DXVec3Normalize(&VecV, &VecV);

	//VecV���w�蔼�a�{���ɒ���
	VecVmax = VecV * r;

	//���_O���Z�o(���W)
	CenterPoint = VecVmax + MiddlePoint;

	//�x�N�g��B�����
	VecB = MiddlePoint - ThisPos;

	//�x�N�g��A�ƃx�N�g��B�̊O��
	D3DXVec3Cross(&VecABCrossOut, &VecA, &VecB);

	//���v���A�����v���𔻕�(���_O�̊m��)
	if (cw)     // ���v���̏���
	{
		if (!(VecABCrossOut < 0))     //�t��������
		{
			CenterPoint *= -1;     // �t���̌��_O���g�p����
		}
	}
	else     // �����v���̏���
	{
		if (!(VecABCrossOut > 0))     //�t��������
		{
			CenterPoint *= -1;     // �t���̌��_O���g�p����
		}
	}


	//�x�N�g��C��	�x�N�g��D�����
	VecC = ThisPos - CenterPoint;
	VecC = MovePos - CenterPoint;


	//// ���W�A�������߂� ////
	Rad = acos(D3DXVec3Dot(&VecC, &VecD) / ( D3DXVec3Length(&VecC) * D3DXVec3Length(&VecD) ) );     //�x�N�g��C�ƃx�N�g��D�̊p�x
	VecC *= -1;     //�x�N�g��C���]
	rad_a = acos(D3DXVec3Dot(&VecA, &VecC) / ( D3DXVec3Length(&VecA) * D3DXVec3Length(&VecC) ) );     //�x�N�g��A��-�x�N�g��C�̊p�x
	VecC *= -1;     //�x�N�g��C���](���ɖ߂�)



	//================�ړ�����(��΋���)================

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
		//Finalize����
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