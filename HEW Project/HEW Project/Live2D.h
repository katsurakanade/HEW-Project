#pragma once
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "main.h"

using namespace std;

typedef enum {

	LIVE2D_INDEX_HIYORI,

	LIVE2D_INDEX_MAX

}LIVE2D_MODEL_KEY;

class Live2D
{

private:

	int MotionIndex;

	const char *MotionGroup;

public:

	int handle;

	D3DXVECTOR2 Pos;

	D3DXVECTOR2 Zoom;

	void LoadModel(const char * name);

	void Draw();

	Live2D();

	~Live2D();

	void SetMontionIndex(int index);

	void SetMontionGroup(const char *name);

	int GetMotionIndex();

	const char *GetMontionGroup();
};

extern vector <const char *>Live2DModelPassDict;

