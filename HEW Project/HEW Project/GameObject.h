#pragma once
#include <d3d9.h>
#include "DxLib.h"
#include "main.h"
#include <vector>

// �A�j���t���[�����~�b�g
#define ANIME_CUT_LIMIT 36

using namespace std;

// �e�N�X�`���L�[
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
	TEXTURE_INDEX_FIRE,
	TEXTURE_INDEX_ARM,
	TEXTURE_INDEX_PINK,
	TEXTURE_INDEX_PROGRESS_BAR,
	TEXTURE_INDEX_BAR_FRAME,
	TEXTURE_INDEX_BATON_TEST,
	TEXTURE_INDEX_STAMINA_GAUGE,


	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

// �F�ʃf�[�^
typedef struct {

	// �F��
	float hue = 0;
	// �ʓx
	float saturation = 0;
	// ���x
	float bright = 0;

}Color_Data;

// �I�u�W�F�N�g�f�[�^
typedef struct {

	// ���W
	D3DXVECTOR2 Pos;
	// �g�嗦
	D3DXVECTOR2 Scale;
	// ��]
	double Rotate = 0;

}Object_Data;

// �Q�[���I�u�W�F�N�g
class GameObject {

private:

	// �x�ꏈ���p�^�C�}�[
	float Delay_Timer[3] = {0,0,0};
	// �x�������p�t���O
	bool Delay_Flag[3] = { true,true,true };
	// �摜�T�C�Y
	D3DXVECTOR2 Size;

public:

	// �n���h���i�A�j���Ȃ��j
	int handle;

	// �n���h���z��i�A�j������j
	int Anime_handle[ANIME_CUT_LIMIT];

	// �F�ʃf�[�^
	Color_Data Color;

	// �I�u�W�F�N�g�f�[�^
	Object_Data Object;

	GameObject();

	~GameObject();

	// �e�N�X�`�����[�h (�t�@�C���p�X)
	// (�A�j���Ȃ�)(Init�Ŏg��)
	void LoadTexture(const char * name);

	// �e�N�X�`�����[�h (�t�@�C���p�X,�t���[����,���t���[����,�c�t���[����,���摜�T�C�Y,�c�摜�T�C�Y)
	// (�A�j������)(Init�Ŏg��)
	void LoadTexture(const char * name,int allcut,int xcut,int ycut,int xsize,int ysize);

	// �x��ړ�(����,����,x,y)
	// (�K��Flag��ݒ肵�Ȃ��Ƃ����Ȃ�)
	// (0:�E 1: �� 2:�� 3:��)
	void Delay_Move(int arrow,float sec,int x,int y,int speed);

	// �x��g��(����,�g�嗦,���x)
	// (�K��Flag��ݒ肵�Ȃ��Ƃ����Ȃ�)
	void Delay_Zoom(float sec,double scale,double speed);

	// �x���](����,��]�p�x,���x)
	// (�K��Flag��ݒ肵�Ȃ��Ƃ����Ȃ�)
	void Delay_Rotate(float sec,double rotate,double speed);

	// �`��(����)
	void Draw();
	
	// �����`��(�e�N�X�`��x,�e�N�X�`��y,�e�N�X�`��x�T�C�Y,�e�N�X�`��y�T�C�Y,�A���t�@�g��,���]�����g��)
	void Draw(int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	// �A�j���`��(�J�b�g)
	void Draw_Anime(int cut);

	// �J�E�X�t�B���^�[(�d��)
	void Gauss_Filter(int param);

	// HSB�t�B���^�[
	void HSB_Fillter();

	void SetDelayFlag(int index);

	// HSB�ݒ�
	void SetHSB(int hue, int saturation, int bright);

	// Get�n���h��
	int GetHandle();

	// Get�F�ʃf�[�^
	Color_Data GetColorData();
};

// �摜�p�X�x�N�g��
extern vector <const char *>TexturePassDict;