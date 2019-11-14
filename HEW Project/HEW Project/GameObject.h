#pragma once
#include <d3d9.h>
#include "DxLib.h"
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

	TEXTURE_INDEX_MAX

}TEXTURE_KEY;

// �F�ʃf�[�^
typedef struct {

	int hue = 0;
	int saturation = 0;
	int bright = 0;

}Color_Data;

typedef struct {

	double Scale = 1.0;
	double Rotate = 0;

}Object_Data;

// �Q�[���I�u�W�F�N�g
class GameObject {

private:

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

	// �`��(x,y)(����)
	void Draw(int x, int y);
	
	// �`��(x,y,�A���t�@�g��)
	void Draw(int x, int y, bool use_alpha);

	// �����`��(x,y,�e�N�X�`��x,�e�N�X�`��y,�e�N�X�`��x�T�C�Y,�e�N�X�`��y�T�C�Y,�A���t�@�g��,���]�����g��)
	void Draw(int x, int y, int tsx, int tsy, int tex, int tey, bool use_alpha, bool turn);

	// �A�j���`��(x,y,�J�b�g)
	void Draw_Anime(int x,int y,int cut);

	// �J�E�X�t�B���^�[(�d��)
	void Gauss_Filter(int param);

	// HSB�t�B���^�[
	void HSB_Fillter();

	// HSB�ݒ�
	void SetHSB(int hue, int saturation, int bright);

	// Get�n���h��
	int GetHandle();

	// Get�F�ʃf�[�^
	Color_Data GetColorData();
};

// �摜�p�X�x�N�g��
extern vector <const char *>TexturePassDict;