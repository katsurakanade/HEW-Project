#pragma once
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "main.h"

using namespace std;

// Live2D ���f���L�[
typedef enum {

	LIVE2D_INDEX_HIYORI,
	LIVE2D_INDEX_RICE,

	LIVE2D_INDEX_MAX

}LIVE2D_MODEL_KEY;

class Live2D
{

private:

	// ���[�V�����C���f�b�N�X
	int MotionIndex;

	// ���[�V�����O���[�v
	const char *MotionGroup;

public:

	// �n���h��
	int handle;

	// ���W
	D3DXVECTOR2 Pos;

	// �g�嗦
	D3DXVECTOR2 Zoom;

	// ���f�����[�h
	// (Init�Ŏg��)
	void LoadModel(const char * name);

	// �`��
	void Draw();

	Live2D();

	~Live2D();

	// Set���[�V����(���[�V�����C���f�b�N�X)
	void SetMontionIndex(int index);

	// Set���[�V�����C���O���[�v(���[�V�����C���O���[�v��)
	void SetMontionGroup(const char *name);

	// Get���[�V�����C���f�b�N�X
	int GetMotionIndex();

	// Get���[�V�����O���[�v
	const char *GetMontionGroup();
};

// Live2D���f���p�X
extern vector <const char *>Live2DModelPassDict;

